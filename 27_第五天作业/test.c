#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, const char *argv[])
{   
    int fd;
    int status;
    fd = open("/dev/key_led0",O_RDWR); 
    if(fd<0){
        perror("打开失败\n");
    }
    printf("打开成功\n");

    while(1){
        read(fd,&status,sizeof(status));
        printf("status = %d",status);
    }
    close(fd);
    return 0;
}