#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

#define NAME "mydev"//设备名
#define COUNT 1 //次设备数
dev_t major=246; //设备号

static int __init mydev_init(void)
{
    int ret;
    ret = register_chrdev_region(major,COUNT,NAME);//静态申请
    if(ret < 0){
        goto ret_err;
    }
    printk("设备号申请成功\n");
    return 0;
ret_err:
    printk("设备号申请失败\n");
    return ret;
}

static void __exit mydev_exit(void)
{
    unregister_chrdev_region(major,COUNT);//注销申请
}

module_init(mydev_init);
module_exit(mydev_exit);
MODULE_LICENSE("GPL");
