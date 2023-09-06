#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include "stm32mp1xx_gpio.h"
#include "stm32mp1xx_rcc.h"
#include <linux/uaccess.h>
#include <linux/io.h>
#define NAME "myled"
int major;
#define COUNT 3
struct class *cls;

rcc_t *RCC;
gpio_t *GPIOE;
gpio_t *GPIOF;

typedef struct {
    gpio_t *GPIOx;
    int pin;
} led_t;
led_t leds[COUNT];

int myled_open(struct inode *pnode, struct file *pfile){
    int minor= MINOR(pnode->i_rdev);
    pfile->private_data = &leds[minor];
    return 0;
}
int myled_close(struct inode *pnode, struct file *pfile){
    return 0;
}
char kbuf[32];
ssize_t myled_write(struct file *pfile, const char *ubuf, size_t size, loff_t *poff){
    int ret=0;
    led_t *led = pfile->private_data;
    ret = copy_from_user(kbuf,ubuf,size);
    if(kbuf[0]=='1'||kbuf[0]==1){
        led->GPIOx->ODR |= 0x1 << led->pin;
    }else if(kbuf[0]=='0'||kbuf[0]==0){
        led->GPIOx->ODR &= ~0x1 << led->pin;
    }
    return ret;
}
ssize_t myled_read(struct file *pfile, char *ubuf, size_t size, loff_t *poff){
    int ret=0;
    led_t *led=pfile->private_data;
    unsigned int ODR =led->GPIOx->ODR;
    // memset(kbuf,0,32);
    kbuf[0]=((ODR >>led->pin) & 0x1) + '0';
    kbuf[1]='\0';
    ret = copy_to_user(ubuf,kbuf,size);
    return ret;

}
struct file_operations fops={
    .open=myled_open,
    .release=myled_close,
    .write=myled_write,
    .read=myled_read,
};//操作集


static int __init myled_init(void)
{
    int ret,i;
    ret=register_chrdev(0,NAME,&fops);
    major=ret;

    //注册设备目录
    cls = class_create(THIS_MODULE,NAME);
    //创建设备节点
    for(i=0;i<COUNT;i++){
        device_create(cls,NULL,MKDEV(major,i),NULL,"%s%d",NAME,i+1);
    }

    //地址空间映射
    RCC = ioremap(RCC_BASE,sizeof(rcc_t));
    GPIOE=ioremap(GPIOE_BASE,sizeof(gpio_t));
    GPIOF=ioremap(GPIOF_BASE,sizeof(gpio_t));
    printk("RCC = 0x%p\n",RCC);

    //功能实现:时钟使能
    RCC->MP_AHB4ENSETR |= (0x01<<4) | (0x01<<5);
    //功能实现：GPIO初始化
    leds[0].GPIOx = GPIOE; leds[0].pin=10;
    leds[1].GPIOx = GPIOF; leds[1].pin=10;
    leds[2].GPIOx = GPIOE; leds[2].pin=8;

    //初始化
    for(i=0;i<COUNT;i++){
        leds[i].GPIOx->MODER &= ~(0x3 << leds[i].pin*2);
        leds[i].GPIOx->MODER |= 0x1 << leds[i].pin*2;
        //默认不亮
        leds[i].GPIOx->ODR &= (0x1<<leds[i].pin);
    }
    return 0;
}

static void __exit myled_exit(void)
{
    int i;
    for(i=0;i<COUNT;i++){
        leds[i].GPIOx->ODR &= (0x1<<leds[i].pin);
    }
    //取消地址映射
    iounmap(RCC);
    iounmap(GPIOE);
    iounmap(GPIOF);

    for(i=0;i<COUNT;i++){
        device_destroy(cls,i);
    }

}


module_init(myled_init);
module_exit(myled_exit);
MODULE_LICENSE("GPL");
