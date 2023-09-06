#ifndef __STM32MP1XX_RCC_H__
#define __STM32MP1XX_RCC_H__

typedef struct {
	volatile unsigned int TZCR;     	// 0x000
	volatile unsigned int res1[2]; 		// 0x004-0x008
	volatile unsigned int OCENSETR;     // 0x00C
	volatile unsigned int OCENCLRR;  	// 0x010
	volatile unsigned int res2[1]; 		// 0x014
	volatile unsigned int HSICFGR; 		// 0x018
	volatile unsigned int CSICFGR; 		// 0x01C
	volatile unsigned int MPCKSELR; 	// 0x020
	volatile unsigned int ASSCKSELR; 	// 0x024
	volatile unsigned int PCK12SELR; 	// 0x028
	volatile unsigned int MPCKDIVR; 	// 0x02C
	volatile unsigned int AXIDIVR; 		// 0x030
	volatile unsigned int res3[2];
	volatile unsigned int APB4DIVR; 	// 0x03C
	volatile unsigned int APB5DIVR; 	// 0x040
	volatile unsigned int RTCDIVR; 		// 0x044
	volatile unsigned int MSSCKSELR;    // 0x048
	volatile unsigned int res4[13];
	volatile unsigned int PLL1CR; 		// 0x080
	volatile unsigned int PLL1CFGR1; 	// 0x084
	volatile unsigned int PLL1CFGR2; 	// 0x088
	volatile unsigned int PLL1FRACR; 	// 0x08C
	volatile unsigned int PLL1CSGR;     // 0x090
	volatile unsigned int PLL2CR; 		// 0x094
	volatile unsigned int PLL2CFGR1; 	// 0x098
	volatile unsigned int PLL2CFGR2; 	// 0x09C
	volatile unsigned int PLL2FRACR;    // 0x0A0
	volatile unsigned int PLL2CSGR;     // 0x0A4
	volatile unsigned int res5[6];
	volatile unsigned int I2C46CKSELR;  // 0x0C0
	volatile unsigned int SPI6CKSELR;   // 0x0C4
	volatile unsigned int UART1CKSELR;  // 0x0C8
	volatile unsigned int RNG1CKSELR;   // 0x0CC
	volatile unsigned int CPERCKSELR;   // 0x0D0
	volatile unsigned int STGENCKSELR;  // 0x0D4
	volatile unsigned int DDRITFCR; 	// 0x0D8
	volatile unsigned int res6[9];
	volatile unsigned int MP_BOOTCR;  	// 0x100
	volatile unsigned int MP_SREQSETR;  // 0x104
	volatile unsigned int MP_SREQCLRR;  // 0x108
	volatile unsigned int MP_GCR;  		// 0x10C
	volatile unsigned int MP_APRSTCR; 	// 0x110
	volatile unsigned int MP_APRSTSR;   // 0x114
	volatile unsigned int res7[10];
	volatile unsigned int BDCR; 		// 0x140
	volatile unsigned int RDLSICR;  	// 0x144
	volatile unsigned int res8[14];
	volatile unsigned int APB4RSTSETR; 	// 0x180
	volatile unsigned int APB4RSTCLRR; 	// 0x184
	volatile unsigned int APB5RSTSETR;  // 0x188
	volatile unsigned int APB5RSTCLRR;  // 0x18C
	volatile unsigned int AHB5RSTSETR;  // 0x190
	volatile unsigned int AHB5RSTCLRR;  // 0x194
	volatile unsigned int AHB6RSTSETR;  // 0x198
	volatile unsigned int AHB6RSTCLRR;  // 0x19C
	volatile unsigned int TZAHB6RSTSELR;// 0x1A0
	volatile unsigned int TZAHB6RSTCLRR;// 0x1A4
	volatile unsigned int res9[22];
	volatile unsigned int MP_APB4ENSETR;// 0x200
	volatile unsigned int MP_APB4ENCLRR;// 0x204
	volatile unsigned int MP_APB5ENSETR;// 0x208
	volatile unsigned int MP_APB5ENCLRR;// 0x20C
	volatile unsigned int MP_AHB5ENSETR;// 0x210
	volatile unsigned int MP_AHB5ENCLRR;// 0x214
	volatile unsigned int MP_AHB6ENSETR;// 0x218
	volatile unsigned int MP_AHB6ENCLRR;// 0x21C
	volatile unsigned int MP_TZAHB6ENSELR;// 0x220
	volatile unsigned int MP_TZAHB6ENCLRR;// 0x224
	volatile unsigned int res10[22];
	volatile unsigned int MC_APB4ENSETR; // 0x280
	volatile unsigned int MC_APB4ENCLRR; // 0x284
	volatile unsigned int MC_APB5ENSETR; // 0x288
	volatile unsigned int MC_APB5ENCLRR; // 0x28C
	volatile unsigned int MC_AHB5ENSETR; // 0x290
	volatile unsigned int MC_AHB5ENCLRR; // 0x294
	volatile unsigned int MC_AHB6ENSETR; // 0x298
	volatile unsigned int MC_AHB6ENCLRR; // 0x29C
	volatile unsigned int res11[24];
	volatile unsigned int MP_APB4LPENSETR; // 0x300
	volatile unsigned int MP_APB4LPENCLRR; // 0x304
	volatile unsigned int MP_APB5LPENSETR; // 0x308
	volatile unsigned int MP_APB5LPENCLRR; // 0x30C
	volatile unsigned int MP_AHB5LPENSETR; // 0x310
	volatile unsigned int MP_AHB5LPENCLRR; // 0x314
	volatile unsigned int MP_AHB6LPENSETR; // 0x318
	volatile unsigned int MP_AHB6LPENCLRR; // 0x31C
	volatile unsigned int MP_TZAHB6LPENSETR; // 0x320
	volatile unsigned int MP_TZAHB6LPENCLRR; // 0x324
	volatile unsigned int res12[22];
	volatile unsigned int MC_APB4LPENSETR; // 0x380
	volatile unsigned int MC_APB4LPENCLRR; // 0x384
	volatile unsigned int MC_APB5LPENSETR; // 0x388
	volatile unsigned int MC_APB5LPENCLRR; // 0x38C
	volatile unsigned int MC_AHB5LPENSETR; // 0x390
	volatile unsigned int MC_AHB5LPENCLRR; // 0x394
	volatile unsigned int MC_AHB6LPENSETR; // 0x398
	volatile unsigned int MC_AHB6LPENCLRR; // 0x39C
	volatile unsigned int res13[24];
	volatile unsigned int BR_RSTSCLRR; 		// 0x400
	volatile unsigned int MP_GRSTCSETR; 	// 0x404
	volatile unsigned int MP_RSTSR; 		// 0x408
	volatile unsigned int MP_IWDGFZSETR; 	// 0x40C
	volatile unsigned int MP_IWDGFZCLRR;  	// 0x410
	volatile unsigned int MP_CIER; 			// 0x414
	volatile unsigned int MP_CIFR; 			// 0x418
	volatile unsigned int PWRLPDLYCR; 		// 0x41C
	volatile unsigned int MP_RSTSS; 		// 0x420
	volatile unsigned int res14[247];
	volatile unsigned int MCO1CFGR; 		// 0x800
	volatile unsigned int MCO2CFGR; 		// 0x804
	volatile unsigned int OCRDYR; 			// 0x808
	volatile unsigned int DBGCFGR; 			// 0x80C
	volatile unsigned int res15[4];
	volatile unsigned int RCK3SELR; 		// 0x820
	volatile unsigned int RCK4SELR; 		// 0x824
	volatile unsigned int TIMG1PRER;  		// 0x828
	volatile unsigned int TIMG2PRER; 		// 0x82C
	volatile unsigned int MCUDIVR; 			// 0x830
	volatile unsigned int APB1DIVR; 		// 0x834
	volatile unsigned int APB2DIVR; 		// 0x838
	volatile unsigned int APB3DIVR; 		// 0x83C
	volatile unsigned int res16[16];
	volatile unsigned int PLL3CR;   		// 0x880
	volatile unsigned int PLL3CFGR1; 		// 0x884
	volatile unsigned int PLL3CFGR2; 		// 0x888
	volatile unsigned int PLL3FRACR; 		// 0x88C
	volatile unsigned int PLL3CSGR; 		// 0x890
	volatile unsigned int PLL4CR; 			// 0x894
	volatile unsigned int PLL4CFGR1; 		// 0x898
	volatile unsigned int PLL4CFGR2; 		// 0x89C
	volatile unsigned int PLL4FRACR; 		// 0x8A0
	volatile unsigned int PLL4CSGR; 		// 0x8A4
	volatile unsigned int res17[6];
	volatile unsigned int I2C12CKSELR; 		// 0x8C0
	volatile unsigned int I2C35CKSELR;  	// 0x8C4
	volatile unsigned int SAI1CKSELR; 		// 0x8C8
	volatile unsigned int SAI2CKSELR; 		// 0x8CC
	volatile unsigned int SAI3CKSELR; 		// 0x8D0
	volatile unsigned int SAI4CKSELR; 		// 0x8D4
	volatile unsigned int SPI2S1CKSELR; 	// 0x8D8
	volatile unsigned int SPI2S23CKSELR; 	// 0x8DC
	volatile unsigned int SPI45CKSELR; 		// 0x8E0
	volatile unsigned int UART6CKSELR; 		// 0x8E4
	volatile unsigned int UART24CKSELR; 	// 0x8E8
	volatile unsigned int UART35CKSELR; 	// 0x8EC
	volatile unsigned int UART78CKSELR; 	// 0x8F0
	volatile unsigned int SDMMC12CKSELR; 	// 0x8F4
	volatile unsigned int SDMMC3CKSELR; 	// 0x8F8
	volatile unsigned int ETHCKSELR; 		// 0x8FC
	volatile unsigned int QSPICKSELR; 		// 0x900
	volatile unsigned int FMCCKSELR; 		// 0x904
	volatile unsigned int res18[1];
	volatile unsigned int FDCANCKSELR; 		// 0x90C
	volatile unsigned int res19[1];
	volatile unsigned int SPDIFCKSELR; 		// 0x914
	volatile unsigned int CECCKSELR; 		// 0x918
	volatile unsigned int USBCKSELR; 		// 0x91C
	volatile unsigned int RNG2CKSELR;  		// 0x920
	volatile unsigned int DSICKSELR; 		// 0x924
	volatile unsigned int ADCCKSELR; 		// 0x928
	volatile unsigned int LPTIM45CKSELR; 	// 0x92C
	volatile unsigned int LPTIM23CKSELR;    // 0x930
	volatile unsigned int LPTIM1CKSELR; 	// 0x934
	volatile unsigned int res20[18];
	volatile unsigned int APB1RSTSETR; 		// 0x980
	volatile unsigned int APB1RSTCLRR; 		// 0x984
	volatile unsigned int APB2RSTSETR; 		// 0x988
	volatile unsigned int APB2RSTCLRR; 		// 0x98C
	volatile unsigned int APB3RSTSETR; 		// 0x990
	volatile unsigned int APB3RSTCLRR; 		// 0x994
	volatile unsigned int AHB2RSTSETR; 		// 0x998
	volatile unsigned int AHB2RSTCLRR;  	// 0x99C
	volatile unsigned int AHB3RSTSETR; 		// 0x9A0
	volatile unsigned int AHB3RSTCLRR; 		// 0x9A4
	volatile unsigned int AHB4RSTSETR; 		// 0x9A8
	volatile unsigned int AHB4RSTCLRR; 		// 0x9AC
	volatile unsigned int res21[20];
	volatile unsigned int MP_APB1ENSETR; 	// 0xA00
	volatile unsigned int MP_APB1ENCLRR; 	// 0xA04
	volatile unsigned int MP_APB2ENSETR; 	// 0xA08
	volatile unsigned int MP_APB2ENCLRR;  	// 0xA0C
	volatile unsigned int MP_APB3ENSETR; 	// 0xA10
	volatile unsigned int MP_APB3ENCLRR; 	// 0xA14
	volatile unsigned int MP_AHB2ENSETR; 	// 0xA18
	volatile unsigned int MP_AHB2ENCLRR; 	// 0xA1C
	volatile unsigned int MP_AHB3ENSETR; 	// 0xA20
	volatile unsigned int MP_AHB3ENCLRR; 	// 0xA24
	volatile unsigned int MP_AHB4ENSETR; 	// 0xA28
	volatile unsigned int MP_AHB4ENCLRR; 	// 0xA2C
	volatile unsigned int res22[2];
	volatile unsigned int MP_MLAHBENSETR; 	// 0xA38
	volatile unsigned int MP_MLAHBENCLRR; 	// 0xA3C
	volatile unsigned int res23[16];
	volatile unsigned int MC_APB1ENSETR; 	// 0xA80
	volatile unsigned int MC_APB1ENCLRR; 	// 0xA84
	volatile unsigned int MC_APB2ENSETR; 	// 0xA88
	volatile unsigned int MC_APB2ENCLRR; 	// 0xA8C
	volatile unsigned int MC_APB3ENSETR; 	// 0xA90
	volatile unsigned int MC_APB3ENCLRR; 	// 0xA94
	volatile unsigned int MC_AHB2ENSETR; 	// 0xA98
	volatile unsigned int MC_AHB2ENCLRR; 	// 0xA9C
	volatile unsigned int MC_AHB3ENSETR; 	// 0xAA0
	volatile unsigned int MC_AHB3ENCLRR; 	// 0xAA4
	volatile unsigned int MC_AHB4ENSETR; 	// 0xAA8
	volatile unsigned int MC_AHB4ENCLRR; 	// 0xAAC
	volatile unsigned int MC_AXIMENSETR; 	// 0xAB0
	volatile unsigned int MC_AXIMENCLRR; 	// 0xAB4
	volatile unsigned int MC_MLAHBENSETR; 	// 0xAB8
	volatile unsigned int MC_MLAHBENCLRR; 	// 0xABC
	volatile unsigned int res24[16];
	volatile unsigned int MP_APB1LPENSETR; 	// 0xB00
	volatile unsigned int MP_APB1LPENCLRR; 	// 0xB04
	volatile unsigned int MP_APB2LPENSETR;  // 0xB08
	volatile unsigned int MP_APB2LPENCLRR; 	// 0xB0C
	volatile unsigned int MP_APB3LPENSETR; 	// 0xB10
	volatile unsigned int MP_APB3LPENCLRR;  // 0xB14
	volatile unsigned int MP_AHB2LPENSETR;  // 0xB18
	volatile unsigned int MP_AHB2LPENCLRR;  // 0xB1C
	volatile unsigned int MP_AHB3LPENSETR;  // 0xB20
	volatile unsigned int MP_AHB3LPENCLRR;  // 0xB24
	volatile unsigned int MP_AHB4LPENSETR;  // 0xB28
	volatile unsigned int MP_AHB4LPENCLRR;  // 0xB2C
	volatile unsigned int MP_AXIMLPENSETR;  // 0xB30
	volatile unsigned int MP_AXIMLPENCLRR;  // 0xB34
	volatile unsigned int MP_MLAHBLPENSETR; // 0xB38
	volatile unsigned int MP_MLAHBLPENCLRR; // 0xB3C
	volatile unsigned int res25[16];
	volatile unsigned int MC_APB1LPENSETR;  // 0xB80
	volatile unsigned int MC_APB1LPENCLRR; 	// 0xB84
	volatile unsigned int MC_APB2LPENSETR;  // 0xB88
	volatile unsigned int MC_APB2LPENCLRR;  // 0xB8C
	volatile unsigned int MC_APB3LPENSETR;  // 0xB90
	volatile unsigned int MC_APB3LPENCLRR;  // 0xB94
	volatile unsigned int MC_AHB2LPENSETR;  // 0xB98
	volatile unsigned int MC_AHB2LPENCLRR;  // 0xB9C
	volatile unsigned int MC_AHB3LPENSETR;  // 0xBA0
	volatile unsigned int MC_AHB3LPENCLRR;  // 0xBA4
	volatile unsigned int MC_AHB4LPENSETR;  // 0xBA8
	volatile unsigned int MC_AHB4LPENCLRR;  // 0xBAC
	volatile unsigned int MC_AXIMLPENSETR;  // 0xBB0
	volatile unsigned int MC_AXIMLPENCLRR;  // 0xBB4
	volatile unsigned int MC_MLAHBLPENSETR; // 0xBB8
	volatile unsigned int MC_MLAHBLPENCLRR; // 0xBBC
	volatile unsigned int res26[16];
	volatile unsigned int MC_RSTSCLRR;  	// 0xC00
	volatile unsigned int res27[4];
	volatile unsigned int MC_CIER;  		// 0xC14
	volatile unsigned int MC_CIFR; 			// 0xC18
	volatile unsigned int res28[246];
	volatile unsigned int VERR; 			// 0xFF4
	volatile unsigned int IDR; 				// 0xFF8
	volatile unsigned int SIDR; 			// 0xFFC
}rcc_t;

#define RCC_BASE 0x50000000

#endif  // __STM32MP1XX_RCC_H__
