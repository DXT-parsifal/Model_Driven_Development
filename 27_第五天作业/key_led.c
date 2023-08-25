#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_gpio.h>
#include <linux/interrupt.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/wait.h>

#define NAME "key_led"
#define COUNT 1
int major;

struct class *cls;
struct device_node *node;
int gpiono_led1;
int gpiono_key1;
unsigned int irqno_key1;

int status=0;//LED1的状态
wait_queue_head_t wq_head;
int condiction=0;

//建立stacklet任务
struct tasklet_struct tasklet;

int key_led_open (struct inode *pnode, struct file *pfile){
    return 0;
}

int key_led_release (struct inode *pnode, struct file *pfile){
    return 0;
}

ssize_t key_led_read (struct file *pfile, char __user *ubuf, size_t size, loff_t *poff){
    if(pfile->f_flags & O_NONBLOCK){//O_NONBLOCK非阻塞
        return -EINVAL;
    }
    //读取数据  确保数据准备好,没有进入休眠
    wait_event_interruptible(wq_head,condiction);
    
    //向用户空间拷贝数据
    size = size > sizeof(status) ? sizeof(status) : size;//防止数据越界??????
    //拷贝数据
    copy_to_user(ubuf,&status,size);
    //下次再读取因为阻塞
    condiction=0;
    return size;
}

struct file_operations fops = {
    .open = key_led_open,
    .release = key_led_release,
    .read = key_led_read,
    
};

irqreturn_t irqno_key1_handler(int irq, void *dev){
    //进行消抖
    tasklet_schedule(&tasklet);
    return IRQ_HANDLED;
}

void tasklet_handler(unsigned long data){
    mdelay(10);//１０毫秒
    if(gpio_get_value(gpiono_key1)==0){
        status=!status;
        gpio_set_value(gpiono_led1,status);
        //唤醒等待队列
        condiction=1;
        wake_up_interruptible(&wq_head);
    }
} 

static int __init key_led_init(void)
{
    int i;
    //创建字符设备
    major = register_chrdev(0,NAME,&fops);
    //自动创建设备
    cls = class_create(THIS_MODULE,NAME);
    for(i=0;i<COUNT;i++){
        device_create(cls,NULL,MKDEV(major,i),"%s%d",NAME,i);
    }

    //获取设备树节点
    node = of_find_compatible_node(NULL,NULL,"hqyj,key_led");

    //获取gpio
    gpiono_key1 = of_get_named_gpio(node,"key1",0);
    gpio_request(gpiono_key1,NULL);
    gpio_direction_input(gpiono_key1);
    
    gpiono_led1 = of_get_named_gpio(node,"led1",0);
    gpio_request(gpiono_led1,NULL);
    gpio_direction_output(gpiono_led1,0);
    
    //获取中断
    irqno_key1=irq_of_parse_and_map(node,0); 
    request_irq(irqno_key1,irqno_key1_handler,IRQF_TRIGGER_FALLING,NAME,NULL);
    
    //初始化等待队列
    init_waitqueue_head(&wq_head);

    //初始化tasklet
    tasklet_init(&tasklet,tasklet_handler,0);

    return 0;
}

static void __exit key_led_exit(void)
{
    int i;
    free_irq(irqno_key1,NULL);
    gpio_free(gpiono_led1);
    gpio_free(gpiono_key1);
    for(i=0;i<COUNT;i++){
        device_destroy(cls,MKDEV(major,i));
    }
    unregister_chrdev(major,NAME);
    class_destroy(cls);
}


module_init(key_led_init);
module_exit(key_led_exit);
MODULE_LICENSE("GPL");