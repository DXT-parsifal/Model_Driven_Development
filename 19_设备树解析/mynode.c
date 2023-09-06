#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/of.h>

struct device_node *node;
static int __init mynode_init(void)
{
    // int len;
    // struct property *pt;
    const char *astring;
    u32 uint_arr[2];
    //通过特殊属性compatible查找
    node = of_find_compatible_node(NULL,NULL,"dxt_mynode");//根节点开始找
    if(node==NULL){
        printk("获取mynode节点失败\n");
        return -1;
    }
#if 1
    //第一个属性
    of_property_read_string(node,"astring",&astring);
    printk("第一个属性astring:%s\n",astring);
    //第二属性
    of_property_read_u32_array(node,"unit",uint_arr,ARRAY_SIZE(uint_arr));
    printk("第二个数据值[0]:%#x\n",uint_arr[0]);
    printk("第二个数据值[1]:%#x\n",uint_arr[1]);

#else
    pt=of_find_property(node,"astring",&len);
    if(pt==NULL){
        printk("获取mynode节点astring属性失败\n");
        return -1;
    }else {
        //打印相关节点信息
        printk("第一个节点名%s 数据值%s",pt->name,(char *)pt->value);
    }

    pt=of_find_property(node,"uint",&len);
    if(pt==NULL){
        printk("获取mynode节点uint属性失败\n");
        return -1;
    }else{
        printk("第二个节点名%s 数据值[0]%#x 数据值[1]%#x\n",pt->next->name,\
                    __be32_to_cpup(pt->value),\
                    __be32_to_cpup(pt->value+4));
    }
#endif
    return 0;
}

static void __exit mynode_exit(void)
{
    printk("mynode卸载\n");
}


module_init(mynode_init);
module_exit(mynode_exit);
MODULE_LICENSE("GPL");
