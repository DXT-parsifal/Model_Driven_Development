#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>


struct resource *res;
int irqno;
int pdrv_probe(struct platform_device *pdev){
    printk("%s:%s:%d\n",__FILE__,__func__,__LINE__);
    //地址资源类型
    res = platform_get_resource(pdev,IORESOURCE_MEM,0);
    printk("起始地址：%lld\n",res->start);
    //中断类型
    irqno = platform_get_irq(pdev,0);
    printk("中断号:%d\n",irqno);
    return 0;
}

int pdrv_remove(struct platform_device *pdev){
    printk("%s:%s:%d\n",__FILE__,__func__,__LINE__);
    return 0;
}

struct platform_driver pdrv = {
    .probe = pdrv_probe,  //匹配是调用
    .remove = pdrv_remove,  //卸载时调用
    .driver = {
        .name = "her",
    },
};

static int __init pdrv_init(void)
{
    
    return platform_driver_register(&pdrv); //
}

static void __exit pdrv_exit(void)
{
    platform_driver_unregister(&pdrv);
}


module_init(pdrv_init);
module_exit(pdrv_exit);
MODULE_LICENSE("GPL");