#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

void bar(void){
    printk("bar function\n");
}

MODULE_LICENSE("GPL");
