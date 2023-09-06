# ARCH是架构
ARCH?=arm

# KERNELDIR是内核源码路径
ifeq ($(ARCH),arm)
	 KERNELDIR:= /home/student/linux-5.4.31
else
	 KERNELDIR:= /lib/modules/$(shell uname -r)/build
endif

# PWD 当前模块路径
PWD:=$(shell pwd)

all:
	 make -C $(KERNELDIR) M=$(PWD) modules
	 #@ make -C $(KERNELDIR) 进入内核目录下读取内核目录下的Makefile文件
	 #@ 然后执行 make M=$(PWD) modules
	 #@ make modules 进行模块化编译
	 #@ M= 编译模块的路径，默认是内核顶层目录
 
clean:
	 make -C $(KERNELDIR) M=$(PWD) clean
 
# 要编译的模块
obj-m:= myspi.o  #详解,例如:我们的源文件是 myspi.c 则-c编译后就是 myspi.o

cp:
	 cp myspi.ko /source/rootfs/root/
