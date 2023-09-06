#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include "control.h"

#define COUNT 3
#define NAME "myled"
int major;
struct class *cls;
struct device *dev;
struct device_node *node;
const char *LEDS[] ={"led1","led2","led3"};//设备树查找属性name
int leds[COUNT];//找到的gpio节点

int myled_open(struct inode *pnode, struct file *pfile){return 0;};
int myled_close(struct inode *pnode, struct file *pfile){return 0;};

long myled_ioctl(struct file *pfile, unsigned int cmd, unsigned long arg){
    printk("cmd = %d\n",cmd);
    printk("LED1_ON:%d\n",LED1_ON);
    printk("LED2_ON:%d\n",LED2_ON);
    printk("LED3_ON:%d\n",LED3_ON);
    switch(cmd)
    {
        case LED1_ON:
            printk("LED1开\n");
            gpio_set_value(leds[0],1);
            break;
        case LED1_OFF:
            printk("LED1关\n");
            gpio_set_value(leds[0],0);
            break;
        case LED2_ON:
            printk("LED2开\n");
            gpio_set_value(leds[1],1);
            break;
        case LED2_OFF:
            printk("LED2关\n");
            gpio_set_value(leds[1],0);
            break;
        case LED3_ON:
            printk("LED3开\n");
            gpio_set_value(leds[2],1);
            break;
        case LED3_OFF:
            printk("LED3关\n");
            gpio_set_value(leds[2],0);
            break;
    }
    return 0;
}

struct file_operations fops = {
    .open = myled_open,
    .release = myled_close,
    .unlocked_ioctl = myled_ioctl,
};

static int __init myled_init(void)
{
    int i;
    //注册设备得到设备号
    major = register_chrdev(0,NAME,&fops);
    //创建设备节点
    cls = class_create(THIS_MODULE,NAME);   //创建目录
    for( i = 0; i < COUNT;i++){
        dev = device_create(cls,NULL,MKDEV(major,i),NULL,"%s%d",NAME,i);  //创建设备节点
    }
    node = of_find_compatible_node(NULL,NULL,"dxt_mycontl");
    if(node!=NULL) printk("myled设备树匹配成功\n");
    for(i=0;i<COUNT;i++){
        leds[i]=of_get_named_gpio(node,LEDS[i],0);
        gpio_request(leds[i],NULL);
        gpio_direction_output(leds[i],0);
    }

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

/*------ 加载和卸载接口 -----*/
module_init(myled_init);
module_exit(myled_exit);

/*------ 相关说明 ----------*/
MODULE_LICENSE("GPL");      //开源许可 GPL 
MODULE_AUTHOR("mode");      //说明
MODULE_VERSION("V1.0");     //版本说明
