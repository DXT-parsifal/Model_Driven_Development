#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/module.h>

int myi2c_probe(struct i2c_client *client, const struct i2c_device_id *id){
    printk("I2C匹配成功\n");
    printk("%s:%s:%d",__FILE__,__func__,__LINE__);
    return 0;
}
int myi2c_remove(struct i2c_client *client){
    printk("%s:%s:%d",__FILE__,__func__,__LINE__);
    return 0;
}

struct of_device_id oftable[] = {
    {.compatible = "hqyj,si7006"},
    {},
};

struct i2c_driver myi2c = {
    .probe = myi2c_probe,
    .remove = myi2c_remove,
    .driver = {
        .name = "myi2c",
        .of_match_table = oftable,
    },
};

module_i2c_driver(myi2c);

MODULE_LICENSE("GPL");
