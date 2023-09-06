#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "control.h"

/****************************
 * 要实现的功能：ioctl实现
 *  用户指定打开哪个led灯
 *  
 * 
 * 
 * 
 * 
 * ***************************/

int fd_led;
int main(void)
{
    printf("运行中\n");
    int select=0;
    fd_led = open("/dev/myled0",O_RDWR);
    if(fd_led<0){
        perror("设备myled0打开失败\n");
        return -1;
    }
    printf("设备myled0打开成功\n");
    printf("1.led1\n2.led2\n3.led3\n");
    printf("输入要打开的led为:");
    scanf("%d",&select);
    switch (select)
    {
    case 1:
        ioctl(fd_led,LED1_ON);
        break;
    case 2:
        ioctl(fd_led,LED2_ON);
        break;
    case 3:
        ioctl(fd_led,LED3_ON);
        break;
    case 4:
        ioctl(fd_led,LED3_OFF);
        break;
    default:
        break;
    }
    


    return 0;
}