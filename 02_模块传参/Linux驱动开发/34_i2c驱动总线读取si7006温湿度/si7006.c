#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/mod_devicetable.h>
/*------------------------------------------
&i2c1{
    //引脚需要复用
 pinctrl-names = "default", "sleep";
 pinctrl-0 = <&i2c1_pins_b>;
 pinctrl-1 = <&i2c1_pins_sleep_b>;
    status = "okay";    //使能I2C1 总线
    ----- 自己加 ------
    si7006@40{
        compatible = "hqyj,si7006";
        reg = <0x40>;
    };
};
-------------------------------------------*/
struct i2c_client *gclient;
/***********************************************************
函数名:unsigned short i2c_read_tep_hum(unsigned char reg)
功能:读取温湿度
参数:
 @reg : 命令字
返回值:
 结果值
************************************************************/
unsigned short i2c_read_tep_hum(unsigned char reg)
{
    unsigned short data;
    char r_buf[1] = {reg};  
    struct i2c_msg r_msg[2] = {
        [0]={
            .addr = gclient->addr,
            .flags = 0,
            .buf = r_buf,
            .len = 1,
        },
        [1]={
            .addr = gclient->addr,
            .flags = 1,
            .buf = (u8*)&data,
            .len = 2,
        }
    };
    i2c_transfer(gclient->adapter,r_msg,2);
    return data >> 8 | data << 8;           //注意在使用左右移动时注意越界,为了解决这个问题，就可以直接本类型就好
}

#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include "si7006.h"
#define NAME "si7006"
int major;
struct class *cls;
int si7006_open(struct inode *pnode, struct file *pfile){return 0;}
int si7006_close(struct inode *pnoe, struct file *pfile){return 0;}
long si7006_ioctl(struct file *pfile, unsigned int cmd, unsigned long arg){
    int data;
    switch(cmd){
        case GET_TEM:
            data = i2c_read_tep_hum(0xE3);     //温度
            copy_to_user((void *)arg,&data,sizeof(data));
            break;
        case GET_HUM:
            data = i2c_read_tep_hum(0xE5);     //湿度
            copy_to_user((void *)arg,&data,sizeof(data));
            break;
    }
    return 0;
}

struct file_operations fops = {
    .open = si7006_open,
    .release = si7006_close,
    .unlocked_ioctl = si7006_ioctl
};
int si7006_probe(struct i2c_client *client, const struct i2c_device_id *id){
    printk("I2C匹配成功\n");
    gclient = client;
    /*--- 注册设备 ----*/
    major = register_chrdev(0,NAME,&fops);
    cls = class_create(THIS_MODULE,NAME);
    device_create(cls,NULL,MKDEV(major,0),NULL,NAME);
    return 0;
}
int si7006_remove(struct i2c_client *client){
    device_destroy(cls,MKDEV(major,0));
    class_destroy(cls);
    unregister_chrdev(major,NAME);
    return 0;
}
struct of_device_id oftable[] = {
    {.compatible = "hqyj,si7006"},
    {}
};
struct i2c_driver si7006 = {
    .probe = si7006_probe,
    .remove = si7006_remove,
    .driver = {
        .name = "si7006",
        .of_match_table = oftable, //设备树匹配
    }
};
module_i2c_driver(si7006);   //一键注册注销
MODULE_LICENSE("GPL");
