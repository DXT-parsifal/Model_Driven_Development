#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
/*****内核变量*******/
#define NAME "mycdev"
int major;
char kbuf[128];//内核空间数组

int mycdev_open(struct inode *pnode, struct file *pfile){   return 0;   }
int mycdev_close(struct inode *pnode, struct file *pfile){  return 0;   }

ssize_t mycdev_read(struct file *pfile, char *ubuf, size_t size, loff_t *poff){
    int ret;
    if(size>sizeof(kbuf)) size = sizeof(kbuf);
    ret = copy_to_user(ubuf,kbuf,sizeof(kbuf));
    return size - ret;//ret 成功返回0 失败返回未拷贝的字节数
}

ssize_t mycdev_write(struct file *pfile, const char *ubuf, size_t size, loff_t *poff){
    int ret;    
    if(size>sizeof(kbuf)) size = sizeof(kbuf);
    ret = copy_from_user(kbuf,ubuf,sizeof(kbuf));
    return size - ret;
}

struct file_operations fops={
    .open=mycdev_open,
    .release=mycdev_close,
    .read=mycdev_read,
    .write=mycdev_write,
};

/*加载卸载函数*/
static int __init mycdev_init(void)
{
    int ret;
    //注册设备
    ret = register_chrdev(0,NAME,&fops);
    if(ret<0){
        printk("注册设备失败\n");
        goto ret_err;
    }
    major=ret;
    printk("申请设备号成功:%d\n",major);
    return 0;
ret_err:
    return ret;
}

static void __exit mycdev_exit(void)
{
    unregister_chrdev(major,NAME);
    printk("驱动卸载成功:%d",major);
}

module_init(mycdev_init);
module_exit(mycdev_exit);
MODULE_LICENSE("GPL");
