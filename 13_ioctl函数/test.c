#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#define LED1 "/dev/myled"
const char *NAME[3]={"/dev/myled1","/dev/myled2","/dev/myled3"};
int fd_leds[3];

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

    close(fd);

    return 0;
}