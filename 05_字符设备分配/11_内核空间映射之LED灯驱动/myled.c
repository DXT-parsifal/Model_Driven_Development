#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/io.h>
#include "myled.h"

#define COUNT 1
#define NAME "myled"
int major;
struct class *cls;
struct device *dev;

unsigned int *RCC_MP_AHB4ENSETR;
GPIO_t *GPIOE;
GPIO_t *GPIOF;

struct file_operations fops={

};

static int __init myled_init(void)
{
    int ret,i;
    //注册设备号
    ret=register_chrdev(0,NAME,&fops);
    major = ret;
    printk("设备号major=%d\n",major);

    //自动创建设备节点
    cls=class_create(THIS_MODULE,NAME);//创建目录
    for(i=0;i<COUNT;i++){
        dev=device_create(cls,NULL,MKDEV(major,i),NULL,"%s%d",NAME,i);//创建设备节点
    }

    //申请空间映射
    RCC_MP_AHB4ENSETR=ioremap(RCC_BASE+0xA28,4);
    GPIOF=ioremap(GPIOF_BASE,sizeof(GPIO_t));
    //时钟
    *RCC_MP_AHB4ENSETR |= 0x1<<4;
    //初始化
    GPIOE->MODER &= ~(0x3<<20);
    GPIOE->MODER |= (0x1<<20);
    //亮灯
    GPIOE->ODR |= (0x1<<10);//F10引脚


    return 0;
}

static void __exit myled_exit(void)
{
    int i;
    for(i = 0; i < COUNT;i++){
        device_destroy(cls,MKDEV(major,i));
    }
    
    class_destroy(cls);
    unregister_chrdev(major,NAME);
}


module_init(myled_init);
module_exit(myled_exit);
MODULE_LICENSE("GPL");
