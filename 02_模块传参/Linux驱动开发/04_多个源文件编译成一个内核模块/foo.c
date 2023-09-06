#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

extern void bar(void);

static int __init foo_init(void){
    bar();
    return 0;
}

static void __exit foo_exit(void){
    printk("卸载\n");
}

module_init(foo_init);
module_exit(foo_exit);
MODULE_LICENSE("GPL");
