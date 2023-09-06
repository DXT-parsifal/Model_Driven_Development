#ifndef __M74hc595_H__
#define __M74hc595_H__

//创建一个枚举，0-9所对应的十六进制数
enum{ 
    DIGIT_0 = 0x3f,
    DIGIT_1 = 0x06,
    DIGIT_2 = 0x5b,
    DIGIT_3 = 0x4f,
    DIGIT_4 = 0x66,
    DIGIT_5 = 0x6d,
    DIGIT_7 = 0x07,
    DIGIT_8 = 0x7f,
    DIGIT_9 = 0x6f,
    DIGIT_DOT = 0x80
};
//数码管选择显示
enum{
    G1 = 0x8,
    G2 = 0x4,
    G3 = 0x2,
    G4 = 0x1, 
};

#endif // !__M74hc595_H__