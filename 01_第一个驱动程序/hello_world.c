#include <linux/module.h>
#include <linux/init.h>

static int __init helloworld_init(void){
    printk(KERN_SOH "4""hello world init\n");
    printk(KERN_SOH "2""hello world init\n");
    return 0;
}

static void __exit helloworld_exit(void){
    printk("hello world exit\n");
}

//加载和卸载接口
module_init(helloworld_init);
module_exit(helloworld_exit);

//相关说明
MODULE_LICENSE("GPL");
MODULE_AUTHOR("mode");
MODULE_VERSION("V1.0");