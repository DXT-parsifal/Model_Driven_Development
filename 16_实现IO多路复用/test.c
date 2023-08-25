#include <sys/epoll.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

//创建epoll对象 文件描述符对应内核中的红黑树
//int epoll_create(int __size)

//操作epoll对象  添加和删除
//int epoll_ctl(int __epfd,int _op,)