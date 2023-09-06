#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int main(int argc, const char *argv[])
{
    int fd;
    char buf[128] = "我是测试代码";
    if ((fd = open("/dev/vser", O_RDWR)) == -1){
        perror("打开错误");
        return -1;
    }

    write(fd, buf, sizeof(buf));
    read(fd, buf, sizeof(buf));
    printf("read buf=%s\n",buf);
    close(fd);
    return 0;
}