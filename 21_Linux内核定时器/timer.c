#include <linux/init.h>
#include <linux/module.h>


//定义一个时间对象
struct timer_list mytimer;

void timer_handle(struct timer_list *timer){
    printk("超时了\n");
    mod_timer(&mytimer,jiffies + 1*HZ);
}
static int __init timer_init(void){
    //初始化定时器
    mytimer.expires = jiffies + 1*HZ; //１秒定时
    timer_setup(&mytimer,timer_handle,0);
    //启动定时器
    add_timer(&mytimer);
    return 0;
}

static void __exit timer_exit(void){
    del_timer(&mytimer);
}

module_init(timer_init);
module_exit(timer_exit);
MODULE_LICENSE("GPL");


// /*
//  * LOCKDEP and DEBUG timer interfaces.
//  */
// void init_timer_key(struct timer_list *timer,
// 		    void (*func)(struct timer_list *), unsigned int flags,
// 		    const char *name, struct lock_class_key *key);
