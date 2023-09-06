#include <linux/module.h>
#include <linux/init.h>

int add(int a,int b){
    return a+b;
}
EXPORT_SYMBOL_GPL(add);//到处符号表

static int __init modeA_init(void){
    printk("%s:%s:%d\n",__FILE__,__func__,__LINE__);
    return 0;
}

static void __exit modeA_exit(void){
    printk("modeA卸载\n");
}

module_init(modeA_init);
module_exit(modeA_exit);
MODULE_LICENSE("GPL");