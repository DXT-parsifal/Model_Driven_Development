#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kfifo.h>
#include <linux/fs.h>
#define COUNT 3
DEFINE_KFIFO(myfifo0,char,32);//创建一个FIFO0内核队列
DEFINE_KFIFO(myfifo1,char,32);//创建一个FIFO1内核队列
DEFINE_KFIFO(myfifo2,char,32);//创建一个FIFO2内核队列
int major;
#define NAME "mydev"

int mydev_close(struct inode *pnode, struct file *pfile){   return 0;   }
ssize_t mydev_read(struct file *pfile, char __user *ubuf, size_t size, loff_t *poff){
    unsigned int copied = 0;//成功拷贝的长度
    struct kfifo *myfifo = pfile->private_data;//获取私有数据
    kfifo_to_user(myfifo,ubuf,size,&copied);
    return copied;
}

ssize_t mydev_write(struct file *pfile, const char *ubuf, size_t size, loff_t *poff){
    unsigned int copied = 0;//成功拷贝的长度
    struct kfifo *myfifo = pfile->private_data;//获取私有数据
    kfifo_from_user(myfifo,ubuf,size,&copied);
    return copied;
}

int mydev_open(struct inode *pnode, struct file *pfile){
    int minor = MINOR(pnode->i_rdev);
    switch (minor){
        case 0:
            pfile->private_data=&myfifo0;
            break;
        case 1:
            pfile->private_data=&myfifo1;
            break;
        case 2:
            pfile->private_data=&myfifo2;
            break;
    }
    return 0;
}

struct file_operations fops={
    .open=mydev_open,
    .read=mydev_read,
    .write=mydev_write,
    .release=mydev_close,
};
static int __init mydev_init(void)
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

static void __exit mydev_exit(void)
{
    unregister_chrdev(major,NAME);
    printk("卸载驱动:%d\n",major);
}


module_init(mydev_init);
module_exit(mydev_exit);
MODULE_LICENSE("GPL");
