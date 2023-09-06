#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
//设备注册相关
#define COUNT 8
#define NAME "mycontl"

int major;
struct class *cls;
struct device *dev;

//设备控制相关
const char *NAMES[] = {"led1","led2","led3","beep","fan","led4","led5","led6"};
struct device_node *node;
int gpiono[COUNT];

int mydev_open(struct inode *pnode, struct file *pfile){return 0;};
int mydev_close(struct inode *pnode, struct file *pfile){return 0;};
struct file_operations fops = {
    .open = mydev_open,
    .release = mydev_close
};

static int __init mydev_init(void)
{
    int i;
    //注册设备得到设备号
    major = register_chrdev(0,NAME,&fops);
    //创建设备节点
    cls = class_create(THIS_MODULE,NAME);   //创建目录
    for( i = 0; i < COUNT;i++){
        dev = device_create(cls,NULL,MKDEV(major,i),NULL,"%s%d",NAME,i);  //创建设备节点
    }

    //设备树子系统gpio操作
    node = of_find_compatible_node(NULL,NULL,"dxt_mycontl");
    if(node==NULL) return -1;  
    //灯
    gpiono[0] = of_get_named_gpio(node,"led1",0);
    gpio_request(gpiono[0],NULL);
    gpio_direction_output(gpiono[0],1);

    gpiono[5] = of_get_named_gpio(node,"led4",0);
    gpio_request(gpiono[5],NULL);
    gpio_direction_output(gpiono[5],1);
    //蜂鸣器
    // gpiono[3] = of_get_named_gpio(node,"beep",0);
    // gpio_request(gpiono[3],NULL);
    // gpio_direction_output(gpiono[3],1);
    //风扇
    gpiono[4] = of_get_named_gpio(node,"fan",0);
    gpio_request(gpiono[4],NULL);
    gpio_direction_output(gpiono[4],1);

    return 0;
}

static void __exit mydev_exit(void)
{
    int i;
    for(i = 0; i < COUNT;i++){
        //设备关闭
        device_destroy(cls,MKDEV(major,i));
        gpio_set_value(gpiono[i],0);
        gpio_free(gpiono[i]);
    }
    //注销目录和设备号
    class_destroy(cls);
    unregister_chrdev(major,NAME);
}

/*------ 加载和卸载接口 -----*/
module_init(mydev_init);
module_exit(mydev_exit);

/*------ 相关说明 ----------*/
MODULE_LICENSE("GPL");      //开源许可 GPL 
MODULE_AUTHOR("mode");      //说明
MODULE_VERSION("V1.0");     //版本说明
