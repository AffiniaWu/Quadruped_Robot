/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/* --- BBS: www.STCAIMCU.com  -----------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����            */
/*---------------------------------------------------------------------*/

#ifndef	__EXTI_H
#define	__EXTI_H

#include	"config.h"

//========================================================================
//                             �ⲿ�ж�����
//========================================================================

#define 	INT0_Mode(n)		(n==0?(IT0 = 0):(IT0 = 1))	/* INT0�ж�ģʽ  �½���/����,�½����ж� */
#define 	INT1_Mode(n)		(n==0?(IT1 = 0):(IT1 = 1))	/* INT0�ж�ģʽ  �½���/����,�½����ж� */

#define 	INT0_Interrupt(n)		(n==0?(EX0 = 0):(EX0 = 1))			/* INT0�ж�ʹ�� */
#define 	INT1_Interrupt(n)		(n==0?(EX1 = 0):(EX1 = 1))			/* INT1�ж�ʹ�� */
#define 	INT2_Interrupt(n)		INTCLKO = (INTCLKO & ~0x10) | (n << 4)	/* INT2�ж�ʹ�� */
#define 	INT3_Interrupt(n)		INTCLKO = (INTCLKO & ~0x20) | (n << 5)	/* INT3�ж�ʹ�� */
#define 	INT4_Interrupt(n)		INTCLKO = (INTCLKO & ~0x40) | (n << 6)	/* INT4�ж�ʹ�� */


#define		PX4		0x10
#define		PX4H		0x10

//�ⲿ�ж�4�ж����ȼ�����
#define 	INT4_Priority(n)			do{if(n == 0) IP2H &= ~PX4H, IP2 &= ~PX4; \
																if(n == 1) IP2H &= ~PX4H, IP2 |= PX4; \
																if(n == 2) IP2H |= PX4H, IP2 &= ~PX4; \
																if(n == 3) IP2H |= PX4H, IP2 |= PX4; \
															}while(0)
//                                           7      6      5      4      3      2      1      0      Reset Value
//sfr IPH   = 0xB7; //�ж����ȼ���λ       PPCAH  PLVDH   PADCH   PSH   PT1H    PX1H   PT0H   PX0H    0000,0000
#define		PX1H	0x04
#define		PX0H	0x01

//�ⲿ�ж�0�ж����ȼ�����
#define 	INT0_Priority(n)			do{if(n == 0) IPH &= ~PX0H, PX0 = 0; \
																if(n == 1) IPH &= ~PX0H, PX0 = 1; \
																if(n == 2) IPH |= PX0H, PX0 = 0; \
																if(n == 3) IPH |= PX0H, PX0 = 1; \
															}while(0)
//�ⲿ�ж�1�ж����ȼ�����
#define 	INT1_Priority(n)			do{if(n == 0) IPH &= ~PX1H, PX1 = 0; \
																if(n == 1) IPH &= ~PX1H, PX1 = 1; \
																if(n == 2) IPH |= PX1H, PX1 = 0; \
																if(n == 3) IPH |= PX1H, PX1 = 1; \
															}while(0)
															

//========================================================================
//                              ��������
//========================================================================

//sbit INT0 = P3^2;
//sbit INT1 = P3^3;
sbit INT2 = P3^6;
sbit INT3 = P3^7;
sbit INT4 = P3^0;

#define	EXT_INT0			0	//���ж�0
#define	EXT_INT1			1	//���ж�1
#define	EXT_INT2			2	//���ж�2
#define	EXT_INT3			3	//���ж�3
#define	EXT_INT4			4	//���ж�4

#define	EXT_MODE_RiseFall	0	//������/�½����ж�
#define	EXT_MODE_Fall			1	//�½����ж�

typedef struct
{
	u8	EXTI_Mode;			//�ж�ģʽ,  	EXT_MODE_RiseFall, EXT_MODE_Fall
} EXTI_InitTypeDef;

extern u8 WakeUpSource;

u8	Ext_Inilize(u8 EXT, EXTI_InitTypeDef *INTx);

u8 NVIC_INT0_Init(u8 State, u8 Priority);
u8 NVIC_INT1_Init(u8 State, u8 Priority);
u8 NVIC_INT2_Init(u8 State, u8 Priority);
u8 NVIC_INT3_Init(u8 State, u8 Priority);
u8 NVIC_INT4_Init(u8 State, u8 Priority);

#endif
