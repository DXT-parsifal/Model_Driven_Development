#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main(){
    int fd;
    char buf[128]="我是测试程序\n";
    fd=open("/dev/mycdev",O_RDWR);
    if(fd<0){
        perror("文件打开失败\n");
        return -1;
    }
    write(fd,buf,sizeof(buf));
    
    memset(buf,0,sizeof(buf));
    read(fd,buf,sizeof(buf));
    printf("read_buf=%s\n",buf);
    close(fd);
    return 0;
}