#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_gpio.h>
#include <linux/interrupt.h>
#include <linux/timer.h>
    // mykey_irq{//设备树
    //     compatible = "hqyj,mykey_irq";
    //     interrupt-parent = <&gpiof>; //输入子系统的父节点
    //     interrupts = <9 0>;
    //     key = <&gpiof 9 0>;
    // };
struct device_node *node;
unsigned int irqno;
unsigned int gpiono;
struct timer_list mytimer;

void timer_irq_handle(struct timer_list *timer){
    if(gpio_get_value(gpiono)==0){
        printk("key1按下\n");
    }
}
//触发时机按下触发中断，重启计时器
irqreturn_t key_irq_handler(int irq, void *dev){
    mod_timer(&mytimer,jiffies+HZ/100);
    return IRQ_HANDLED;
}

static int __init key_irq_init(void)
{
    //解析设备树
    node = of_find_compatible_node(NULL,NULL,"hqyj,mykey_irq");
    //解析中断树
    irqno=irq_of_parse_and_map(node,0);
    //注册中断
    request_irq(irqno,key_irq_handler,IRQF_TRIGGER_FALLING,"key_irq",NULL);

    //解析gpio引脚
    gpiono=of_get_named_gpio(node,"key",0);
    gpio_direction_input(gpiono);//输入模式

    //定时器
    mytimer.expires=jiffies+HZ/100;
    //初始化
    timer_setup(&mytimer,timer_irq_handle,0);
    //启动定时器
    add_timer(&mytimer);

    return 0;
}

static void __exit key_irq_exit(void)
{
    free_irq(irqno,NULL);
    del_timer(&mytimer);
    gpio_free(gpiono);
}

module_init(key_irq_init);
module_exit(key_irq_exit);
MODULE_LICENSE("GPL");
