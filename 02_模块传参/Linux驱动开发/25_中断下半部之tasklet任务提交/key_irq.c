#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/of_irq.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/delay.h>
#include <linux/interrupt.h>

struct device_node *node;//设备树节点　
unsigned int irqno;//中断号
int gpiono;//gpio 引脚


struct tasklet_struct tasklet;

irqreturn_t key_irq_handler(int irqno, void *dev){
    tasklet_schedule(&tasklet);//开启任务
    return IRQ_HANDLED;
}

void tasklet_handler(unsigned long data){//任务处理
    mdelay(100);
    if(gpio_get_value(gpiono)==0){
        printk("key1按下\n");
    }
}   

static int __init key_irq_init(void)
{
    //解析设备树
    node = of_find_compatible_node(NULL,NULL,"hqyj,mykey_irq");
    //解析中断号
    irqno=irq_of_parse_and_map(node,0);//node的第０个中断
    request_irq(irqno,key_irq_handler,IRQF_TRIGGER_FALLING,"key_irq",NULL);//申请中断
    //解析gpio引脚
    gpiono=of_get_named_gpio(node,"key",0);//设备树节点　属性名　序号０
    //申请gpio引脚
    gpio_request(gpiono,"key");
    //配置引脚
    gpio_direction_input(gpiono);//输入模式

    //初始化中断下半部tasklet
    tasklet_init(&tasklet,tasklet_handler,0);

    return 0;
}

static void __exit key_irq_exit(void)
{
    free_irq(irqno,0);
    gpio_free(gpiono);
}


module_init(key_irq_init);
module_exit(key_irq_exit);
MODULE_LICENSE("GPL");