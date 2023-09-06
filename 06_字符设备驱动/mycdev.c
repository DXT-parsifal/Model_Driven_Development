#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

#define NAME "mycdev"   //设备名
int major;              //主设备

int mycdev_open(struct inode *pnode, struct file *pfile){
    printk("func:%s\n",__func__); 
    return 0;
}

ssize_t mycdev_read(struct file *pfile, char *ubuf, size_t size, loff_t *poff){
    printk("func:%s\n",__func__);
    return 0;
}

int mycdev_release(struct inode *pnode, struct file *pfile){
    printk("func:%s\n",__func__);
    return 0;
}

ssize_t mycdev_write(struct file *pfile, const char *ubuf, size_t size, loff_t *poff){
    printk("func:%s\n",__func__);
    return 0;
}

struct file_operations fops={
    .open=mycdev_open,
    .read=mycdev_read,
    .release=mycdev_release,
    .write=mycdev_write,
};

static int __init mycdev_init(void)
{
    int ret=0;
    ret=register_chrdev(0,NAME,&fops);
    if(ret<0){
        goto ret_err;
    }
    major=ret;
    printk("字符设备申请成功\n");
    return 0;
ret_err:
    printk("字符设备申请失败\n");
    return ret;
}

static void __exit mycdev_exit(void)
{
    unregister_chrdev(major,NAME);
}

module_init(mycdev_init);
module_exit(mycdev_exit);
MODULE_LICENSE("GPL");
