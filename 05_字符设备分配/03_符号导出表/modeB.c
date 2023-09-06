#include <linux/module.h>
#include <linux/init.h>

extern int add(int a,int b);

static int __init modeB_init(void){
    int c=0;
    c=add(10,20);
    printk("%s:%s:%d\tc=%d\n",__FILE__,__func__,__LINE__,c);
    return 0;
}

static void __exit modeB_exit(void){
    printk("modeB卸载\n");
}

module_init(modeB_init);
module_exit(modeB_exit);
MODULE_LICENSE("GPL");


