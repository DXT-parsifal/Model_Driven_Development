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
                system("clear");
                printf("输入LED编号(1~3):");scanf("%d",&select);
                printf("输入LED电平(1高0低):");scanf("%d",&start);
                write(fd_leds[select-1],&start,sizeof(start));
                break;
            case 2:
                system("clear");
                printf("输入读取的LED编号(1~3):");scanf("%d",&select);
                read(fd_leds[select-1],&start,sizeof(start));
                printf("状态:%d\n",start-'0');
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