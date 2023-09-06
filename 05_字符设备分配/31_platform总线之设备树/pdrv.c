#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/of_gpio.h>

struct resource *res;
int irqno;
int led1_no;
int pdrv_probe(struct platform_device *pdev){
    printk("%s:%s:%d\n",__FILE__,__func__,__LINE__);
    //地址资源类型
    res = platform_get_resource(pdev,IORESOURCE_MEM,0);
    printk("起始地址：%d\n",res->start);
    //中断类型
    irqno = platform_get_irq(pdev,0);
    printk("中断号:%d\n",irqno);

    //获取设备树节点led1的gpio的信息
    led1_no = of_get_named_gpio(pdev->dev.of_node,"led1",0);
    gpio_request(led1_no,NULL);
    gpio_direction_output(led1_no,0);
    gpio_set_value(led1_no,1);

    return 0;
}

int pdrv_remove(struct platform_device *pdev){
    printk("%s:%s:%d\n",__FILE__,__func__,__LINE__);
    return 0;
}

struct platform_device_id idtable[] = {
    {"hello0",0},
    {"hello1",0},
    {"hello2",0},
    {"her0",0},
    {},//必须有结束，防止访问脏数据，越界访问
};

struct of_device_id oftable[] = {
    {.compatible = "hqyj,myplatform"},
    {},
};


struct platform_driver pdrv = {
    .probe = pdrv_probe,  //匹配是调用
    .remove = pdrv_remove,  //卸载时调用
    .driver = {
        .name = "her", //不管什么匹配都要填写,内核会在设备树创建文件
        .of_match_table = oftable, //设备树匹配
    },
    // .id_table = idtable,　//id_table匹配
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
