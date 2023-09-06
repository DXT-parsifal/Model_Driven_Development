#include <linux/module.h>
#include <linux/init.h>

int a = 50;
module_param(a,int,0664);
MODULE_PARM_DESC(a,"这是我的a变量，用来来存放");

int addr[4];
module_param_array(addr,int,NULL,0644);
MODULE_PARM_DESC(addr,"这是我的addr变量数组，用来存放串口号");

static int __init mode_init(void){
    printk("构造\n");
    printk("a=%d\n",a);

    int i=0;
    printk("addr:");
    for(i=0;i<4;i++){
        printk("%d ",addr[i]);
        
    }
    // printk("\n");
    return 0;
}

static void __exit mode_exit(void){

}   

module_init(mode_init);
module_exit(mode_exit);
MODULE_LICENSE("GPL");
