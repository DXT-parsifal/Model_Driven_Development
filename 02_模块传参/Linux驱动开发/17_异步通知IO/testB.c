#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int fd;
char buf[32];

int main(){
    fd=open("/dev/mydev0",O_RDWR);
    if(fd < 0)
    {
        perror("设备打开失败\n");
        return -1;
    }

    while(1){\
        memset(buf,0,sizeof(buf));
        printf("输入传送的信息：\n");
        scanf("%s",buf);
        write(fd,buf,sizeof(buf));
    }
}