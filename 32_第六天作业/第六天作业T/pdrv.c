#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/mod_devicetable.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_gpio.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/wait.h>
#include <linux/uaccess.h>

#define NAME "key_led"
#define COUNT 1
int major;
struct class *cls;
int gpiono_led1;
int gpiono_key1;
int irqno;
struct tasklet_struct tasklet;
wait_queue_head_t wq_head;//等待队列做阻塞
int condition=0;
int status=0;
int pdrv_open(struct inode *pnode, struct file *pfile){
    return 0;
}
int pdrv_close (struct inode *pnode, struct file *pfile){
    return 0;
}
ssize_t pdrv_read (struct file *pfile, char __user *ubuf, size_t size, loff_t *poff){
    if(pfile->f_flags &O_NONBLOCK){
        return -EINVAL;
    }
    wait_event_interruptible(wq_head,condition);
    size = size > sizeof(status) ? sizeof(status) : size;
    copy_to_user(ubuf,&status,size);
    condition = 0;//清零，下次连续阻塞
    return size;
}

struct file_operations fops = {
    .open = pdrv_open,
    .release = pdrv_close,
    .read = pdrv_read,
};

void tasklet_handler(unsigned long data){
    mdelay(10);
    if(gpio_get_value(gpiono_key1)==0){
        status = !status;//led灯状态翻转
        gpio_set_value(gpiono_led1,status);
        condition=1;
        wake_up_interruptible(&wq_head);
    }
}

irqreturn_t irq_handler(int irq, void *dev){
    tasklet_schedule(&tasklet);
    return IRQ_HANDLED;
}

int pdrv_probe(struct platform_device *pdev){//初始化
    printk("匹配成功\n");
    //创建设备
    major = register_chrdev(0,NAME,&fops);
    //自动创建设备节点
    cls = class_create(THIS_MODULE,NAME);
    device_create(cls,NULL,MKDEV(major,0),NULL,"%s%d",NAME,0);
    //获取gpio口
    gpiono_led1=of_get_named_gpio(pdev->dev.of_node,"led1",0);
    gpiono_key1=of_get_named_gpio(pdev->dev.of_node,"key1",0);
    gpio_request(gpiono_key1,NULL);
    gpio_request(gpiono_led1,NULL);
    gpio_direction_output(gpiono_led1,0);
    gpio_direction_input(gpiono_key1);
    //获取中断号
    irqno = platform_get_irq(pdev,0);
    request_irq(irqno,irq_handler,IRQF_TRIGGER_FALLING,NAME,NULL);
    //初始化tasklet任务
    tasklet_init(&tasklet,tasklet_handler,0);
    //初始化等待队列
    init_waitqueue_head(&wq_head);
    return 0;
}
int pdrv_remove(struct platform_device *pdev){//卸载
    gpio_free(gpiono_key1);
    gpio_free(gpiono_led1);
    free_irq(irqno,NULL);
    device_destroy(cls,MKDEV(major,0));
    class_destroy(cls);
    printk("%s:%s:%d\n",__FILE__,__func__,__LINE__);
    return 0;
}

struct of_device_id oftable[] = {
    {.compatible = "hqyj,key_led"},
    {},
};

struct platform_driver pdrv = {
    .probe = pdrv_probe,
    .remove = pdrv_remove,
    .driver = {
        .name = "platform",
        .of_match_table = oftable,
    }
};

module_platform_driver(pdrv);//一键注册和注销，替换掉以下内容
// static int __init pdrv_init(void)
// {
    
//     return 0;
// }

// static void __exit pdrv_exit(void)
// {
    
// }

// module_init(pdrv_init);
// module_exit(pdrv_exit);
MODULE_LICENSE("GPL");