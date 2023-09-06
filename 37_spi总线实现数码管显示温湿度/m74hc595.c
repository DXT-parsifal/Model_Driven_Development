#include <linux/init.h>
#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/delay.h>
#include "m74hc595.h"
struct spi_device *gspi;

#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include "m74hc595.h"
#define NAME "m74hc595"
int major;
struct class *cls;
int m74hc595_open(struct inode *pnode, struct file *pfile){     return 0;}
int m74hc595_close(struct inode *pnoe, struct file *pfile){     return 0;}
ssize_t m74hc595_write(struct file *pfile,const char __user *ubuf, size_t size, loff_t *poff){
    int buf_r[4];
    copy_from_user(buf_r,ubuf,sizeof(buf_r));

    spi_write(gspi,buf,2);
    mdelay(5);

    printk("个位：%d\n",buf_r[1]);
    return 0;
}

struct file_operations fops = {
    .open = m74hc595_open,
    .release = m74hc595_close,
    .write = m74hc595_write,
};

int	m74hc595_probe(struct spi_device *spi){
    int i=1000;
    printk("匹配成功\n");
    gspi= spi;
    //创键设备
    major = register_chrdev(0,NAME,&fops);
    cls = class_create(THIS_MODULE,NAME);
    device_create(cls,NULL,MKDEV(major,0),NULL,NAME);

    return 0;
}


int	m74hc595_remove(struct spi_device *spi){
    printk("m74hc595卸载\n");
    device_destroy(cls,MKDEV(major,0));
    class_destroy(cls);
    unregister_chrdev(major,NAME);
    return 0;
}

struct of_device_id oftable[] = {
    {.compatible = "hqyj,m74hc595"},
    {},
};

struct spi_driver m74hc595 = {
    .probe = m74hc595_probe,
    .remove = m74hc595_remove,
    .driver = {
        .name = "myspi",
        .of_match_table = oftable,
    },
};

module_spi_driver(m74hc595);

MODULE_LICENSE("GPL");
