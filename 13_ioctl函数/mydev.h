#ifndef __MYDEV_H__
#define __MYDEV_H__
#include <linux/ioctl.h>

struct Image {
    int height;
    int width;
};

#define LED1_ON _IO("led",1) 
#define LED1_OFF _IO("led",0)

#define WRITE_IMAGE _IOW("image",1,struct Image)
#define READ_IMAGE _IOR("image",1,struct Image)

#define GET_CMD_SIZE(cmd) ((cmd>>16)&0x3FFF)

#endif