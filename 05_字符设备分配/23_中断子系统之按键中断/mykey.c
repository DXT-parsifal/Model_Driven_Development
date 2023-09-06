#include <linux/init.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/interrupt.h>

#define COUNT 3

unsigned int irqno[COUNT];  //软中段号
const char *NAMES[COUNT] = {"key1","key2","key3"};
struct device_node *node;
irqreturn_t key_irq_handler(int irq, void *dev){
    int i;
    for(i=0;i<COUNT;i++){
        if(irqno[i]==irq){
            printk("key%d按下,irq=%d\n",i+1,irq);
        }
    }
    return IRQ_HANDLED;
}

static int __init mykey_init(void)
{
    int i;
    node=of_find_compatible_node(NULL,NULL,"dxt,mykeys");
    if(node==NULL){
        printk("获取按键设备树节点失败\n");
    }
    for(i=0;i<COUNT;i++){
        irqno[i] = irq_of_parse_and_map(node,i);
        request_irq(irqno[i],key_irq_handler,IRQF_TRIGGER_FALLING,NAMES[i],NULL);//
        printk("irqno[%d] = %d\n",i,irqno[i]);
    }
    
    return 0;
}

static void __exit mykey_exit(void)
{
    int i;
    for(i=0;i<COUNT;i++){
        free_irq(irqno[i],NULL);
    }
}

module_init(mykey_init);
module_exit(mykey_exit);
MODULE_LICENSE("GPL");
