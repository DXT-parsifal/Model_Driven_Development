#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "si7006.h"

int main()
{   
    int fd;
    int status;
    fd = open("/dev/si7006",O_RDWR); 
    if(fd<0){
        perror("打开失败\n");
    }
    printf("打开成功\n");

    int tem,hum;
    float rtem,rhum;
    while(1){
        ioctl(fd,GET_TEM,&tem);
        ioctl(fd,GET_HUM,&hum);
        
        rtem = 175.72 * tem / 65536 - 46.85;
        rhum = 125 * hum / 65536 - 6;
        printf("tem = %.2f \t hum = %.2f \n",rtem,rhum);
        sleep(1);
    }

    close(fd);
    return 0;
}