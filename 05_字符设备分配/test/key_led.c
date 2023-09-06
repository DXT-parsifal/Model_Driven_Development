#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/of.h>
#include <linux/device.h>
#include <linux/platform_device.h>

#define NAME "key_led"
#define COUNT 1
int major;
struct class *cls;
struct class *node;

int key_led_open (struct inode *pnode, struct file *pfile){    return 0;}

int key_led_close (struct inode *pnode, struct file *pfile){    return 0;}
ssize_t key_led_read (struct file *pfile, char __user *ubuf, size_t size, loff_t *poff){

    return 0;
}

struct file_operations fops = {
    .open = key_led_open,
    .release = key_led_close,
    .read = key_led_read,
    
};

int pdrv_probe(struct platform_device *pdev){
    int i;
    major = register_chrdev(0,NAME,&fops);
    /*----------------自动注册设备--------------*/
    cls = class_create(THIS_MODULE,NAME);
    for(i=0;i<COUNT;i++){
        device_create(cls,NULL,MKDEV(major,i),NULL,"%s%d",NAME,i);
    }

    return 0;
}
int pdrv_remove(struct platform_device *pdev){
    int i;
    for(i=0;i<COUNT;i++){
        device_destroy(cls,MKDEV(major,i));
    }
    class_destroy(cls);
    unregister_chrdev(major,NAME);

    return 0;
}

struct of_device_id oftable[] = {
    {.compatible = "hqyj,key_led"},
    {},
};

struct platform_driver pdrv = {
    .probe = pdrv_probe,
    .remove = pdrv_remove,
    .driver = {
        .name = "platform driver",
        .of_match_table = oftable,
    }
};

static int __init key_led_init(void)
{
    return platform_driver_register(&pdrv);
}

static void __exit key_led_exit(void)
{
    platform_driver_unregister(&pdrv);
}

module_init(key_led_init);
module_exit(key_led_exit);
MODULE_LICENSE("GPL");
