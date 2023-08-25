#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>

static int __init delay_init(void)
{
    //小延时
    ndelay(10);
    udelay(10);
    mdelay(10);
    //大延时
    msleep(10);
    ssleep(10);
    printk("延时10纳秒10微妙10毫秒10毫秒10秒\n");
    return 0;
}

static void __exit delay_exit(void)
{
    
}

module_init(delay_init);
module_exit(delay_exit);
MODULE_LICENSE("GPL");
