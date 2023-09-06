#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>

#define COUNT 5  //最多设备节点数
#define NAME "vser"
int major;

struct class *cls;
struct device *dev;
int vser_open(struct inode *pnode, struct file *pfile){
    printk("设备打开\n");
    return 0;
}
struct file_operations fops={
    .open=vser_open,
};

static int __init vser_init(void)
{
    int ret,i;
    //注册设备得到设备号
    ret=register_chrdev(major,NAME,&fops);
    if(ret<0){
        printk("注册设备失败\n");
        goto ret_err;
    }
    major=ret;
    printk("设备号major=%d\n",major);

    //创建设备目录和设备节点
    cls=class_create(THIS_MODULE,NAME);
    if(IS_ERR(cls)){
        printk("创建设备目录失败\n");
        ret=PTR_ERR(cls);
        goto class_err;
    }

    for(i=0;i<COUNT;i++){
        dev=device_create(cls,NULL,MKDEV(major,i),NULL,NAME);//主设备号和次设备号组成的设备号
        if(IS_ERR(dev)){
            printk("创建设备节点失败\n");
            ret=PTR_ERR(dev);
            goto dev_err;
        }
    }

    return 0;
dev_err:
    class_destroy(cls);
class_err:
    unregister_chrdev(major,NAME);
ret_err:
    return ret;
}

static void __exit vser_exit(void)
{
    int i;
    for(i=0;i<COUNT;i++){
        device_destroy(cls,MKDEV(major,i));
    }
    class_destroy(cls);
    unregister_chrdev(major,NAME);
    printk("设备驱动卸载\n");
}

module_init(vser_init);
module_exit(vser_exit);
MODULE_LICENSE("GPL");
