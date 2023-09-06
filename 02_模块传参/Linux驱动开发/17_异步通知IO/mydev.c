#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/kfifo.h>
#define COUNT 2
#define NAME "mydev"
int major;
struct class *cls;
struct device *dev;

//建立一个异步通知队列
struct fasync_struct *fapp;

int mydev_open(struct inode *pnode, struct file *pfile){return 0;};
int mydev_close(struct inode *pnode, struct file *pfile){return 0;};

DEFINE_KFIFO(kbuf,char,32); ///内核空间ＦＩＦＯ环形缓冲队列
ssize_t mydev_read (struct file *pfile, char __user *ubuf, size_t size, loff_t *poff){
    int copied;
    kfifo_to_user(&kbuf,ubuf,size,&copied);
    return copied;
}
ssize_t mydev_write (struct file *pfile, const char __user *ubuf, size_t size, loff_t *poff){
    int copied; 
    kfifo_from_user(&kbuf,ubuf,size,&copied); //有数据写入到内核，内核有资源通知进程读取
    kill_fasync(&fapp,SIGIO,POLL_IN);          //有输入数据要处理，发出信号，通知进程处理
    kill_fasync(&fapp->fa_next,SIGIO);
    return copied;
}


int mydev_fasync(int fd, struct file *pfile, int on){//on 进程
    //构造异步通知队列
    fasync_helper(fd,pfile,on,&fapp);
    return 0;
}


struct file_operations fops = {
    .open = mydev_open,
    .release = mydev_close,
    .fasync=mydev_fasync,
    .write=mydev_write,
    .read=mydev_read,
};

static int __init mydev_init(void)
{
    int i;
    //注册设备得到设备号
    major = register_chrdev(0,NAME,&fops);
    //创建设备节点
    cls = class_create(THIS_MODULE,NAME);   //创建目录
    for( i = 0; i < COUNT;i++){
        dev = device_create(cls,NULL,MKDEV(major,i),NULL,"%s%d",NAME,i);  //创建设备节点
    }
    return 0;
}

static void __exit mydev_exit(void)
{
    int i;
    for(i = 0; i < COUNT;i++){
        device_destroy(cls,MKDEV(major,i));
    }
    class_destroy(cls);
    unregister_chrdev(major,NAME);
}

/*------ 加载和卸载接口 -----*/
module_init(mydev_init);
module_exit(mydev_exit);

/*------ 相关说明 ----------*/
MODULE_LICENSE("GPL");      //开源许可 GPL 
MODULE_AUTHOR("mode");      //说明
MODULE_VERSION("V1.0");     //版本说明
