#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>


int pdrv_probe(struct platform_device *pdev){
    printk("%s:%s:%d\n",__FILE__,__func__,__LINE__);
    return 0;
}
int pdrv_remove(struct platform_device *pdev){
    printk("%s:%s:%d\n",__FILE__,__func__,__LINE__);
    return 0;
}

struct platform_driver pdrv = {
    .probe = pdrv_probe,
    .remove = pdrv_remove,
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
