/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/* --- BBS: www.STCAIMCU.com  -----------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序            */
/*---------------------------------------------------------------------*/

#ifndef	__EXTI_H
#define	__EXTI_H

#include	"config.h"

//========================================================================
//                             外部中断设置
//========================================================================

#define 	INT0_Mode(n)		(n==0?(IT0 = 0):(IT0 = 1))	/* INT0中断模式  下降沿/上升,下降沿中断 */
#define 	INT1_Mode(n)		(n==0?(IT1 = 0):(IT1 = 1))	/* INT0中断模式  下降沿/上升,下降沿中断 */

#define 	INT0_Interrupt(n)		(n==0?(EX0 = 0):(EX0 = 1))			/* INT0中断使能 */
#define 	INT1_Interrupt(n)		(n==0?(EX1 = 0):(EX1 = 1))			/* INT1中断使能 */
#define 	INT2_Interrupt(n)		INTCLKO = (INTCLKO & ~0x10) | (n << 4)	/* INT2中断使能 */
#define 	INT3_Interrupt(n)		INTCLKO = (INTCLKO & ~0x20) | (n << 5)	/* INT3中断使能 */
#define 	INT4_Interrupt(n)		INTCLKO = (INTCLKO & ~0x40) | (n << 6)	/* INT4中断使能 */


#define		PX4		0x10
#define		PX4H		0x10

//外部中断4中断优先级控制
#define 	INT4_Priority(n)			do{if(n == 0) IP2H &= ~PX4H, IP2 &= ~PX4; \
																if(n == 1) IP2H &= ~PX4H, IP2 |= PX4; \
																if(n == 2) IP2H |= PX4H, IP2 &= ~PX4; \
																if(n == 3) IP2H |= PX4H, IP2 |= PX4; \
															}while(0)
//                                           7      6      5      4      3      2      1      0      Reset Value
//sfr IPH   = 0xB7; //中断优先级高位       PPCAH  PLVDH   PADCH   PSH   PT1H    PX1H   PT0H   PX0H    0000,0000
#define		PX1H	0x04
#define		PX0H	0x01

//外部中断0中断优先级控制
#define 	INT0_Priority(n)			do{if(n == 0) IPH &= ~PX0H, PX0 = 0; \
																if(n == 1) IPH &= ~PX0H, PX0 = 1; \
																if(n == 2) IPH |= PX0H, PX0 = 0; \
																if(n == 3) IPH |= PX0H, PX0 = 1; \
															}while(0)
//外部中断1中断优先级控制
#define 	INT1_Priority(n)			do{if(n == 0) IPH &= ~PX1H, PX1 = 0; \
																if(n == 1) IPH &= ~PX1H, PX1 = 1; \
																if(n == 2) IPH |= PX1H, PX1 = 0; \
																if(n == 3) IPH |= PX1H, PX1 = 1; \
															}while(0)
															

//========================================================================
//                              定义声明
//========================================================================

//sbit INT0 = P3^2;
//sbit INT1 = P3^3;
sbit INT2 = P3^6;
sbit INT3 = P3^7;
sbit INT4 = P3^0;

#define	EXT_INT0			0	//外中断0
#define	EXT_INT1			1	//外中断1
#define	EXT_INT2			2	//外中断2
#define	EXT_INT3			3	//外中断3
#define	EXT_INT4			4	//外中断4

#define	EXT_MODE_RiseFall	0	//上升沿/下降沿中断
#define	EXT_MODE_Fall			1	//下降沿中断

typedef struct
{
	u8	EXTI_Mode;			//中断模式,  	EXT_MODE_RiseFall, EXT_MODE_Fall
} EXTI_InitTypeDef;

extern u8 WakeUpSource;

u8	Ext_Inilize(u8 EXT, EXTI_InitTypeDef *INTx);

u8 NVIC_INT0_Init(u8 State, u8 Priority);
u8 NVIC_INT1_Init(u8 State, u8 Priority);
u8 NVIC_INT2_Init(u8 State, u8 Priority);
u8 NVIC_INT3_Init(u8 State, u8 Priority);
u8 NVIC_INT4_Init(u8 State, u8 Priority);

#endif
