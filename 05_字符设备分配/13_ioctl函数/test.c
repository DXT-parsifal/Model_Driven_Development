#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <mydev.h>
struct Image{
    int height;
    int width;
};

int main(int argc, const char *argv[])
{   
    int fd;
    fd = open("/dev/mydev0",O_RDWR); 
    if(fd<0){
        perror("打开失败\n");
    }
    printf("打开成功\n");

    struct Image image={.height=10,.width=50};
    ioctl(fd,1,&image);
    printf("传入图片\n");
    
    ioctl(fd,LED1_ON);
    printf("控制LED1\n");

    ioctl(fd,WRITE_IMAGE,&image);
    printf("指令接口宏传入图片\n");

    close(fd);

    return 0;
}