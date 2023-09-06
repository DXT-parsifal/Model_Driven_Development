#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/mod_devicetable.h>

void pdev_release(struct device *dev){
    printk("%s:%s:%d\n",__FILE__,__func__,__LINE__);
}
struct resource res[] = {
    [0] = {//描述设备信息的结构体
        .start = 0x12345678,
        .end = 0x12345678+49,
        .flags = IORESOURCE_MEM, //资源类型
    },
    [1] = {
        .start = 71,
        .end = 71,
        .flags = IORESOURCE_IRQ,
    },
};
struct platform_device pdev={
    .name = "her0",//名字
    .id=PLATFORM_DEVID_AUTO,
    .dev = {
        .release = pdev_release,//父类的析构
    },
    .resource = res,
    .num_resources = ARRAY_SIZE(res),
};

static int __init pdev_init(void)
{
    return platform_device_register(&pdev);
}

static void __exit pdev_exit(void)
{
    platform_device_unregister(&pdev);
}


module_init(pdev_init);
module_exit(pdev_exit);
MODULE_LICENSE("GPL");
