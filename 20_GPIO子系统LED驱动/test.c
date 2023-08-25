#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
const char *NAME[3]={"/dev/myled1","/dev/myled2","/dev/myled3"};
int fd_leds[3];

int main(int argc, const char *argv[])
{   
    int i;
    for(i=0;i<3;i++){
        fd_leds[i] = open(NAME[i], O_RDWR);
    }
    
    int select=0;
    int start=0;
    while(1){
        system("clear");
        printf("菜单\n");
        printf("1.控制LED灯状态\n");
        printf("2.读取LED灯状态\n");
        scanf("%d",&select);
        switch(select){
            case 1:

                break;
            case 2:

                getchar();getchar();
                break;
            default:
                printf("输入错误\n");
            break;
        }
    }

    for(i=0;i<3;i++){
        close(fd_leds[i]);
    }
    return 0;
}