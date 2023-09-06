#include <linux/init.h>
#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/delay.h>
#include "m74hc595.h"
struct spi_device *gspi;

int	m74hc595_probe(struct spi_device *spi){
    char buf[2];
    printk("匹配成功\n");
    gspi= spi;
    while(1){
        //发送数据，数码管显示数据,在第二个管显示数字５
        buf[0]=G1;buf[1]=DIGIT_0;
        spi_write(gspi,buf,2);
        mdelay(1000);

        buf[0]=G2;buf[1]=DIGIT_1;
        spi_write(gspi,buf,2);
        mdelay(1000);

        buf[0]=G3;buf[1]=DIGIT_3;
        spi_write(gspi,buf,2);
        mdelay(1000);

        buf[0]=G4;buf[1]=DIGIT_4;
        spi_write(gspi,buf,2);
        mdelay(1000);
    }

    return 0;
}


int	m74hc595_remove(struct spi_device *spi){
    printk("m74hc595卸载\n");
    return 0;
}

struct of_device_id oftable[] = {
    {.compatible = "hqyj,m74hc595"},
    {},
};

struct spi_driver m74hc595 = {
    .probe = m74hc595_probe,
    .remove = m74hc595_remove,
    .driver = {
        .name = "myspi",
        .of_match_table = oftable,
    },
};

module_spi_driver(m74hc595);

MODULE_LICENSE("GPL");
