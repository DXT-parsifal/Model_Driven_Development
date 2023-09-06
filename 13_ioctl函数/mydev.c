#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include "mydev.h"
#define COUNT 1  //最多设备节点数
#define NAME "mydev"
int major;

struct class *cls;
struct device *dev;
int mydev_open(struct inode *pnode, struct file *pfile){
    printk("设备打开\n");
    return 0;
}

int mydev_close(struct inode *pnode, struct file *pfile){
    printk("设备关闭\n");
    return 0;
}

long mydev_ioctl(struct file *pfile, unsigned int cmd, unsigned long arg){
    struct Image kimage;
    printk("cmd=%d\n",cmd);
    switch(cmd){
    case WRITE_IMAGE:
        copy_from_user(&kimage,(void *)arg,sizeof(kimage));//接收来自应用层数据arg，
        printk("kimage.height=%d\n",kimage.height);
        printk("kimage.width=%d\n",kimage.width);
        printk("大小：%d\n",GET_CMD_SIZE(cmd));
        break;
    case LED1_ON:
        printk("LED1_ON\n");
        break;
    case LED1_OFF:
        printk("LED1_OFF\n");
        break;
    case READ_IMAGE:
        printk("image read\n");
        break;
    }
        
    return 0;
}

struct file_operations fops={
    .open=mydev_open,
    .release=mydev_close,
    .unlocked_ioctl=mydev_ioctl,
};

static int __init mydev_init(void)
{
    int ret,i;
    //注册设备得到设备号
    ret=register_chrdev(0,NAME,&fops);
    major=ret;

    printk("设备号major=%d\n",major);

    //创建设备目录和设备节点
    cls=class_create(THIS_MODULE,NAME);

    for(i=0;i<COUNT;i++){
        dev=device_create(cls,NULL,MKDEV(major,i),NULL,"%s%d",NAME,i);//主设备号和次设备号组成的设备号
    }

    return 0;
}

static void __exit mydev_exit(void)
{
    int i;
    for(i=0;i<COUNT;i++){
        device_destroy(cls,MKDEV(major,i));
    }
    class_destroy(cls);
    unregister_chrdev(major,NAME);
    printk("设备驱动卸载\n");
}

module_init(mydev_init);
module_exit(mydev_exit);
MODULE_LICENSE("GPL");
