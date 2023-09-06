#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/kfifo.h>
#define COUNT 1
#define NAME "mydev"
int major;
struct class *cls;
struct device *dev;
int mydev_open(struct inode *pnode, struct file *pfile){return 0;};
int mydev_close(struct inode *pnode, struct file *pfile){return 0;};

#include <linux/wait.h>
DECLARE_WAIT_QUEUE_HEAD(read_wq);//创建一个等待队列读操作
DECLARE_WAIT_QUEUE_HEAD(write_wq);//创建一个等待队列写操作
static int read_flag=0;
static int write_flag=0;

// char kbuf[32];
DEFINE_KFIFO(kbuf,char,32);//内核空间FIFO 队列
ssize_t mydev_read(struct file *pfile, char *ubuf, size_t size, loff_t *poff){
    int ret,copied;
    //判断是否阻塞
    if(kfifo_is_empty(&kbuf)){
        read_flag=0;//确保进入阻塞
        wait_event_interruptible(read_wq,read_flag);           //进入等待
    }
    ret=kfifo_to_user(&kbuf,ubuf,size,&copied);
    if(!kfifo_is_full(&kbuf)){
        wake_up_interruptible(&write_wq);
        write_flag=1;
    }
    return copied;
}
ssize_t mydev_write(struct file *pfile, const char *ubuf, size_t size, loff_t *poff){
    int ret,copied;
    if(kfifo_is_full(&kbuf)){
        read_flag=0;
        wait_event_interruptible(write_wq,read_flag);
    }
    ret= kfifo_from_user(&kbuf,ubuf,size,&copied);
    if(!kfifo_is_empty(&kbuf)){
        wake_up_interruptible(&read_wq);
        read_flag=1;//确保再设置一次
    }
    return copied;
}
struct file_operations fops = {
    .open = mydev_open,
    .release = mydev_close,
    .read=mydev_read,
    .write=mydev_write,
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