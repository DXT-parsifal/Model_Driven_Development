#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "m74hc595.h"

#define GET_TEM _IOR('a',1,int)//温度获取ioctl
#define GET_HUM _IOR('a',2,int)//湿度获取ioctl

int fd_74;
int cal_num_show(float num,float num2);

int main()
{   
    int fd_th;
    int status;
    fd_th = open("/dev/si7006",O_RDWR);
    if(fd_th<0){
        perror("si7006打开失败\n");
    }
    printf("si7006打开成功\n");

    fd_74 = open("dev/m74hc595",O_RDWR);
    if(fd_74<0){
        perror("m74hc595打开失败\n");
    }
    printf("m74hc595打开成功\n");

    int tem,hum;
    float rtem,rhum;
    while(1){
        ioctl(fd_th,GET_TEM,&tem);
        ioctl(fd_th,GET_HUM,&hum);
        
        rtem = 175.72 * tem / 65536 - 46.85;
        rhum = 125 * hum / 65536 - 6;
        printf("tem = %.2f \t hum = %.2f \n",rtem,rhum);

        cal_num_show(rtem,rhum);

        sleep(1);
    }

    close(fd_th);
    return 0;
}

int cal_num_show(float num1,float num2){
    int shi,ge,thnths,percentile;
    int buf_w[4];
    
    
    shi = (int)num1/10;
    ge = (int)num1/1%10;
    buf_w[0]=shi;buf_w[1]=ge;

    thnths = num1*10;    thnths = thnths/1%10;
    percentile = num1*100;    percentile = percentile/1%10; 
    buf_w[2]=thnths; buf_w[3]=percentile;

    write(fd_74,buf_w,sizeof(buf_w));
}


