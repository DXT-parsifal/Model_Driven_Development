#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/kfifo.h>
/*****内核变量*******/
#define NAME "vser"
int major;
// char kbuf[128];//内核空间数组
DEFINE_KFIFO(myfifo,char,32);//创建一个内核队列FIFO
int vser_open(struct inode *pnode, struct file *pfile){   return 0;   }
int vser_close(struct inode *pnode, struct file *pfile){  return 0;   }

ssize_t vser_read(struct file *pfile, char *ubuf, size_t size, loff_t *poff){
    unsigned int copied=0;//成功拷贝的长度
    kfifo_to_user(&myfifo,ubuf,size,&copied);
    return copied;
}

ssize_t vser_write(struct file *pfile, const char *ubuf, size_t size, loff_t *poff){
    unsigned int copied=0;//成功拷贝的长度
    kfifo_from_user(&myfifo,ubuf,size,&copied);
    return copied;
}

struct file_operations fops={
    .open=vser_open,
    .release=vser_close,
    .read=vser_read,
    .write=vser_write,
};

/*加载卸载函数*/
static int __init vser_init(void)
{
    int ret;
    //注册设备
    ret = register_chrdev(0,NAME,&fops);
    if(ret<0){
        printk("注册设备失败\n");
        goto ret_err;
    }
    major=ret;
    printk("申请设备号成功\n");
    return 0;
ret_err:
    return ret;
}

static void __exit vser_exit(void)
{
    unregister_chrdev(major,NAME);
    printk("驱动卸载:%d",major);
}

module_init(vser_init);
module_exit(vser_exit);
MODULE_LICENSE("GPL");
