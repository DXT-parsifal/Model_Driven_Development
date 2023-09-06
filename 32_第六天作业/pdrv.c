#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/mod_devicetable.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/interrupt.h>
#include <linux/of.h>
#include <linux/device.h>
#include <linux/uaccess.h>//用户空间传输信息
#include <linux/delay.h>

#define NAME "key_led"
#define COUNT 1
int major;
struct class *cls;
struct device_node *node;

struct resource *res;
int irqno_key1;
int led1_no;
int key1_no;
struct tasklet_struct tasklet;//建立staklet 任务
int status = 0;
int condition = 0;
wait_queue_head_t wq_head;

int key_led_open(struct inode *pnode, struct file *pfile){return 0;}
int key_led_release(struct inode *pnode, struct file *pfile){return 0;}
ssize_t key_led_read(struct file *pfile, char __user *ubuf, size_t size, loff_t *poff){
    int ret;
    if(pfile->f_flags & O_NONBLOCK){    //O_NONBLOCK非阻塞
        return -EINVAL;
    }
    //读取数据 ----- 确保数据准备好没有?  如果没有则休眠
    wait_event_interruptible(wq_head,condition);        //如果 condition 为0则阻塞,为1则不阻塞
    //向用户空间拷贝数据
    size = size > sizeof(status) ? sizeof(status) : size;   //防止数据越界
    //拷贝数据
    ret = copy_to_user(ubuf,&status,size);
    printk("数据copy to user\n");
    //下次读取应该是阻塞的,所以 condition = 0为假，则阻塞
    condition = 0;
    return size - ret;
}

void tasklet_handler(unsigned long data){
    mdelay(10); //10毫秒
    if(gpio_get_value(key1_no) == 0)
    {
        status = !status;
        gpio_set_value(led1_no,status);
        //唤醒等待队列
        condition = 1;
        printk("status状态改变\n");
        wake_up_interruptible(&wq_head);
    }
}

irqreturn_t irq_handler(int irq, void *dev){
    tasklet_schedule(&tasklet); 
    return IRQ_HANDLED; //处理了
}

int pdrv_probe(struct platform_device *pdev){
    printk("%s:%s:%d\n",__FILE__,__func__,__LINE__);
    //中断类型
    irqno_key1 = platform_get_irq(pdev,0);
    printk("中断号:%d\n",irqno_key1);
    request_irq(irqno_key1,irq_handler,IRQF_TRIGGER_FALLING,NAME,NULL);
    
    //初始化等待队列
    init_waitqueue_head(&wq_head);
    //初始化tasklet任务
    tasklet_init(&tasklet,tasklet_handler,0);

    //获取key1按键状态
    key1_no = of_get_named_gpio(pdev->dev.of_node,"key1",0);
    gpio_request(key1_no,NULL);//gpio初始化
    gpio_direction_input(key1_no);//输入模式

    //获取设备树节点led1的gpio的信息
    led1_no = of_get_named_gpio(pdev->dev.of_node,"led1",0);
    gpio_request(led1_no,NULL);
    gpio_direction_output(led1_no,0);//输出模式

    return 0;
}

int pdrv_remove(struct platform_device *pdev){
    printk("%s:%s:%d\n",__FILE__,__func__,__LINE__);
    return 0;
}

struct of_device_id oftable[] = {
    {.compatible = "hqyj,key_led"},
    {},
};


struct platform_driver pdrv = {
    .probe = pdrv_probe,  //匹配是调用
    .remove = pdrv_remove,  //卸载时调用
    .driver = {
        .name = "her", //不管什么匹配都要填写,内核会在设备树创建文件
        .of_match_table = oftable, //设备树匹配
    },
};

struct file_operations fops = {
    .open = key_led_open,
    .release = key_led_release,
    .read = key_led_read,
};

static int __init pdrv_init(void)
{
    int i;
    //创建字符设备
    major = register_chrdev(0,NAME,&fops);
    //自动创建设备
    cls = class_create(THIS_MODULE,NAME);
    for(i = 0; i < COUNT;i++){
        device_create(cls,NULL,MKDEV(major,i),NULL,"%s%d",NAME,i);
    }
    return platform_driver_register(&pdrv); 
}

static void __exit pdrv_exit(void)
{
    int i;
    free_irq(irqno_key1,NULL);
    gpio_free(led1_no);
    gpio_free(key1_no);
    for(i = 0; i < COUNT;i++){
        device_destroy(cls,MKDEV(major,i));
    }
    class_destroy(cls);
    unregister_chrdev(major,NAME);

    platform_driver_unregister(&pdrv);
}

module_init(pdrv_init);
module_exit(pdrv_exit);
MODULE_LICENSE("GPL");
