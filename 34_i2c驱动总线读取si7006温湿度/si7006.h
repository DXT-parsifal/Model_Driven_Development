#ifndef __SI7006__
#define __SI7006__

#define GET_TEM _IOR('a',1,int)//温度获取ioctl
#define GET_HUM _IOR('a',2,int)//湿度获取ioctl

#endif // !__SI7006__