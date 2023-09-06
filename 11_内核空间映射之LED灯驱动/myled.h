#ifndef __MYLED_H__
#define __MYLED_H__

#define RCC_BASE    0x5000000
#define GPIOE_BASE  0x50006000
#define GPIOF_BASE  0x50007000

/*------ GPIO寄存器 --------*/
typedef struct {
    unsigned int MODER;		//偏移:0x00
    unsigned int TYPER;		//偏移:0x04
	unsigned int SPEEDR;	//偏移:0x08
    unsigned int PUPDR;     //偏移:0x0c
    unsigned int IDR;		//偏移:0x10
    unsigned int ODR;		//偏移:0x14
}GPIO_t;

#endif