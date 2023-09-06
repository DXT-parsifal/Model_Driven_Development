#ifndef __CONTROL_H__
#define __CONTROL_H__
#include <linux/ioctl.h>

enum{
    LED1,
    LED2,
    LED3,
};
enum{
    ON,
    OFF,
};

#define LED1_ON _IO(LED1,ON)
#define LED1_OFF _IO(LED1,OFF)

#define LED2_ON _IO(LED2,ON)
#define LED2_OFF _IO(LED2,OFF)

#define LED3_ON _IO(LED3,ON)
#define LED3_OFF _IO(LED3,OFF)


#endif // !__CONTROL_H__

