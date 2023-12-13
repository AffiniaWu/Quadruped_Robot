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

#ifndef	__SPI_H
#define	__SPI_H

#include	"config.h"

//========================================================================
//                            ���ܽ��л�����
//========================================================================

#define  SPI_SW(Pin)				P_SW1 = (P_SW1 & 0xF3) | (Pin << 2)
//========================================================================
//                              �Ĵ���λ����
//========================================================================

//sfr SPSTAT  = 0xCD;	//SPI״̬�Ĵ���
//   7       6      5   4   3   2   1   0    	Reset Value
//	SPIF	WCOL	-	-	-	-	-	-
#define	SPIF	0x80		/* SPI������ɱ�־��д��1��0��*/
#define	WCOL	0x40		/* SPIд��ͻ��־��д��1��0��  */

//========================================================================
//                               SPI����
//========================================================================

#define		SPI_SSIG_Set(n)					SPCTL = (SPCTL & ~0x80) | (n << 7)		/* SS���Ź��ܿ��� */
#define		SPI_Start(n)						SPCTL = (SPCTL & ~0x40) | (n << 6)		/* SPIʹ�ܿ���λ */
#define		SPI_FirstBit_Set(n)			SPCTL = (SPCTL & ~0x20) | (n << 5)		/* ���ݷ���/����˳�� MSB/LSB */
#define		SPI_Mode_Set(n)					SPCTL = (SPCTL & ~0x10) | (n << 4)		/* SPI����ģʽ���� */
#define		SPI_CPOL_Set(n)					SPCTL = (SPCTL & ~0x08) | (n << 3)		/* SPIʱ�Ӽ��Կ��� */
#define		SPI_CPHA_Set(n)					SPCTL = (SPCTL & ~0x04) | (n << 2)		/* SPIʱ����λ���� */
#define		SPI_Clock_Select(n)			SPCTL = (SPCTL & ~0x03) | (n)					/* SPIʱ��Ƶ��ѡ�� */


#define		PSPI	0x02
#define		PSPIH		0x02
//SPI�ж����ȼ�����
#define 	SPI_Priority(n)				do{if(n == 0) IP2H &= ~PSPIH, IP2 &= ~PSPI; \
																if(n == 1) IP2H &= ~PSPIH, IP2 |= PSPI; \
																if(n == 2) IP2H |= PSPIH, IP2 &= ~PSPI; \
																if(n == 3) IP2H |= PSPIH, IP2 |= PSPI; \
															}while(0)

															
//========================================================================
//                              SPI�ж�����
//========================================================================

#define 	SPI_Interrupt(n)		IE2 = (IE2 & ~0x02) | (n << 1)	/* SPI�ж�ʹ�� */

//========================================================================
//                              ��������
//========================================================================

#define	SPI_P12_P13_P14_P15		0
#define	SPI_P22_P23_P24_P25		1
#define	SPI_P54_P40_P41_P43		2
#define	SPI_P35_P34_P33_P32		3

#define	SPI_BUF_LENTH	128
#define	SPI_BUF_type	xdata

sbit  SPI_SS    = P1^2;
sbit  SPI_MOSI  = P1^3;
sbit  SPI_MISO  = P1^4;
sbit  SPI_SCLK  = P1^5;

sbit  SPI_SS_2    = P2^2;
sbit  SPI_MOSI_2  = P2^3;
sbit  SPI_MISO_2  = P2^4;
sbit  SPI_SCLK_2  = P2^5;

sbit  SPI_SS_3    = P5^4;
sbit  SPI_MOSI_3  = P4^0;
sbit  SPI_MISO_3  = P4^1;
sbit  SPI_SCLK_3  = P4^3;

sbit  SPI_SS_4    = P3^5;
sbit  SPI_MOSI_4  = P3^4;
sbit  SPI_MISO_4  = P3^3;
sbit  SPI_SCLK_4  = P3^2;

#define	SPI_Mode_Master		1
#define	SPI_Mode_Slave		0
#define	SPI_CPOL_High		1
#define	SPI_CPOL_Low		0
#define	SPI_CPHA_1Edge		0
#define	SPI_CPHA_2Edge		1
#define	SPI_Speed_4			0
#define	SPI_Speed_16		1
#define	SPI_Speed_64		2
#define	SPI_Speed_128		3
#define	SPI_MSB				0
#define	SPI_LSB				1

typedef struct
{
	u8	SPI_Enable;		//ENABLE,DISABLE
	u8	SPI_SSIG;			//ENABLE, DISABLE
	u8	SPI_FirstBit;	//SPI_MSB, SPI_LSB
	u8	SPI_Mode;			//SPI_Mode_Master, SPI_Mode_Slave
	u8	SPI_CPOL;			//SPI_CPOL_High,   SPI_CPOL_Low
	u8	SPI_CPHA;			//SPI_CPHA_1Edge,  SPI_CPHA_2Edge
	u8	SPI_Speed;		//SPI_Speed_4,SPI_Speed_16,SPI_Speed_64,SPI_Speed_128
} SPI_InitTypeDef;


extern	bit B_SPI_Busy; //����æ��־
extern	u8 	SPI_RxCnt;
extern	u8 	SPI_RxTimerOut;
extern	u8 	SPI_BUF_type SPI_RxBuffer[SPI_BUF_LENTH];


void	SPI_Init(SPI_InitTypeDef *SPIx);
void	SPI_SetMode(u8 mode);
void	SPI_WriteByte(u8 dat);

//========================================================================
//                           �ⲿ�����ͱ�������
//========================================================================

u8 NVIC_SPI_Init(u8 State, u8 Priority);

#endif

