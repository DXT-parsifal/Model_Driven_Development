#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/of.h>

struct device_node *node;
static int __init mynode_init(void)
{
    //通过节点名获取设备节点
    node = of_find_node_by_name(NULL,"mynode");//根节点开始找
    if(node==NULL){
        printk("获取mynode节点失败\n");
        return -1;
    }

    //打印相关节点信息
    printk("第一个节点名%s 数据值%s",node->properties->name,(char *)node->properties->value);
    printk("第二个节点名%s 数据值[0]%#x 数据值[1]%#x\n",node->properties->next->name,\
                __be32_to_cpup(node->properties->next->value),\
                __be32_to_cpup(node->properties->next->value+4));

    return 0;
}

static void __exit mynode_exit(void)
{
    printk("mynode卸载\n");
}


module_init(mynode_init);
module_exit(mynode_exit);
MODULE_LICENSE("GPL");