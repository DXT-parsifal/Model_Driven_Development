#include <linux/init.h>
#include <linux/module.h>
#include <linux/spi/spi.h>

int	myspi_probe(struct spi_device *spi){
    printk("匹配成功\n");
    return 0;
}


int	myspi_remove(struct spi_device *spi){
    return 0;
}

struct of_device_id oftable[] = {
    {.compatible = "hqyj,m74hc595"},
    {},
};

struct spi_driver myspi = {
    .probe = myspi_probe,
    .remove = myspi_remove,
    .driver = {
        .name = "myspi",
        .of_match_table = oftable,
    },
};

module_spi_driver(myspi);

MODULE_LICENSE("GPL");
