#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/mod_devicetable.h>
#include <linux/of_gpio.h>
#include <linux/pwm.h>
struct device_node *node;
struct pwm_device *pwm_dev;

int myfan_probe(struct platform_device *pdev){
    printk("%s:%s:%d\n",__FILE__,__func__,__LINE__);
    //获取地址类型 IORESOURCE_MEM
    node = pdev->dev.of_node;
    pwm_dev = of_pwm_get(NULL,node,NULL);
    printk("匹配成功\n");
    // pwm_config(pwm_dev,500000,1000000);
    // pwm_set_period(pwm_dev,900000);
    // pwm_enable(pwm_dev);

    return 0;
}

int myfan_remove(struct platform_device *pdev){
    printk("%s:%s:%d\n",__FILE__,__func__,__LINE__);
    pwm_free(pwm_dev);
    
    return 0;
}

/*------------- 用于匹配的设备树匹配 ---------------------*/
struct of_device_id oftable[] = {
    {.compatible = "hqyj,myplatform"},//特殊属性匹配
    {}, //用于防止访问越界
};

struct platform_driver myfan = {
    .probe = myfan_probe,            //匹配成功会调用 它
    .remove = myfan_remove,          //卸载时会调用 它
    .driver = {
        .name = "her",         //不管是不是name匹配都要填写,因为:内核会根据 .name 字段值会在设备树 /sys/bus/platform/drivers //目录下创建相应的文件,所以必须有，如果没有则会报错。
        .of_match_table = oftable,  //设备树匹配方式
    }
};

module_platform_driver(myfan);

/*------ 相关说明 ----------*/
MODULE_LICENSE("GPL");      //开源许可 GPL
MODULE_AUTHOR("mode");      //说明
MODULE_VERSION("V1.0");     //版本说明
