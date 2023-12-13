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

#ifndef	__NVIC_H
#define	__NVIC_H

#include	"config.h"

//========================================================================
//                              定义声明
//========================================================================

#define	FALLING_EDGE		1		//产生下降沿中断
#define	RISING_EDGE			2		//产生上升沿中断

//========================================================================
//                             外部中断设置
//========================================================================

//========================================================================
//                              ADC中断设置
//========================================================================

//========================================================================
//                              SPI中断设置
//========================================================================

//========================================================================
//                              I2C中断设置
//========================================================================

//========================================================================
//                              UART中断设置
//========================================================================

//========================================================================
//                              RTC中断设置
//========================================================================

//========================================================================
//                            中断优先级定义
//========================================================================

//                                           7      6      5      4      3      2      1      0      Reset Value
//sfr IP2   = 0xB5; //                    PPWM2FD PI2C   PCMP    PX4  PPWM0FD  PPWM0  PSPI   PS2     0000,0000
#define		PUSB	0x80
#define		PPWM2FD	0x80
#define		PTKSU	0x80
#define		PI2C	0x40
#define		PCMP	0x20
#define		PX4		0x10
#define		PPWM0FD	0x08
#define		PPWMB	0x08
#define		PPWM0	0x04
#define		PPWMA	0x04
#define		PSPI	0x02
#define		PS2		0x01
//                                           7      6      5      4      3      2      1      0      Reset Value
//sfr IP2H  = 0xB6; //                    PPWM2FDH PI2CH PCMPH   PX4H PPWM0FDH PPWM0H PSPIH  PS2H    0000,0000
#define		PUSBH		0x80
#define		PPWM2FDH	0x80
#define		PTKSUH		0x80
#define		PI2CH		0x40
#define		PCMPH		0x20
#define		PX4H		0x10
#define		PPWM0FDH	0x08
#define		PPWMBH		0x08
#define		PPWM0H		0x04
#define		PPWMAH		0x04
#define		PSPIH		0x02
#define		PS2H		0x01

//串口1中断优先级控制
//串口2中断优先级控制
//串口3中断优先级控制
//串口4中断优先级控制

//SPI中断优先级控制

//外部中断4中断优先级控制
															
//比较器中断优先级控制
															
//I2C中断优先级控制
															
//增强型PWM0中断优先级控制
															
//增强型PWM0异常检测中断优先级控制
															
//增强型PWM2异常检测中断优先级控制
															
//触摸按键中断优先级控制
#define 	PTKSU_Priority(n)			do{if(n == 0) IP2H &= ~PTKSUH, IP2 &= ~PTKSU; \
																if(n == 1) IP2H &= ~PTKSUH, IP2 |= PTKSU; \
																if(n == 2) IP2H |= PTKSUH, IP2 &= ~PTKSU; \
																if(n == 3) IP2H |= PTKSUH, IP2 |= PTKSU; \
															}while(0)

//USB中断优先级控制
#define 	USB_Priority(n)				do{if(n == 0) IP2H &= ~PUSBH, IP2 &= ~PUSB; \
																if(n == 1) IP2H &= ~PUSBH, IP2 |= PUSB; \
																if(n == 2) IP2H |= PUSBH, IP2 &= ~PUSB; \
																if(n == 3) IP2H |= PUSBH, IP2 |= PUSB; \
															}while(0)

//高级PWMA中断优先级控制

//高级PWMB中断优先级控制


//                                           7      6      5     4      3      2      1     0      Reset Value
//sfr IP3   = 0xDF; //                    PPWM4FD PPWM5  PPWM4  PPWM3  PPWM2  PPWM1  PS4   PS3     0000,0000
#define		PPWM4FD		0x80
#define		PPWM5		0x40
#define		PPWM4		0x20
#define		PPWM3		0x10
#define		PPWM2		0x08
#define		PPWM1		0x04
#define		PRTC		0x04
#define		PS4			0x02
#define		PS3			0x01
//                                           7        6       5      4       3       2     1     0      Reset Value
//sfr IP3H  = 0xEE; //                    PPWM4FDH PPWM5H  PPWM4H  PPWM3H  PPWM2H  PPWM1H PS4H  PS3H    0000,0000
#define		PPWM4FDH	0x80
#define		PPWM5H		0x40
#define		PPWM4H		0x20
#define		PPWM3H		0x10
#define		PPWM2H		0x08
#define		PPWM1H		0x04
#define		PRTCH		0x04
#define		PS4H		0x02
#define		PS3H		0x01


//增强型PWM1中断优先级控制
//增强型PWM2中断优先级控制
//增强型PWM3中断优先级控制
//增强型PWM4中断优先级控制
//增强型PWM5中断优先级控制
//增强型PWM4异常检测中断优先级控制
															
//串口3中断优先级控制
//串口4中断优先级控制

//                                           7      6      5      4      3      2      1      0      Reset Value
//sfr IPH   = 0xB7; //中断优先级高位       PPCAH  PLVDH   PADCH   PSH   PT1H    PX1H   PT0H   PX0H    0000,0000
#define		PLVDH	0x40
#define		PADCH	0x20
#define		PSH		0x10
#define		PT1H	0x08
#define		PX1H	0x04
#define		PT0H	0x02
#define		PX0H	0x01

//外部中断0中断优先级控制

//外部中断1中断优先级控制

//串口1中断优先级控制
															
//ADC中断优先级控制
//低压检测中断优先级控制

#endif

