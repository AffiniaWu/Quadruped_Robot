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

#ifndef	__I2C_H
#define	__I2C_H

#include	"config.h"

//========================================================================
//                            ���ܽ��л�����
//========================================================================
#define  I2C_SW(Pin)				P_SW2 = (P_SW2 & 0xCF) | (Pin << 4)

#define	I2C_P14_P15				0
#define	I2C_P24_P25				1
#define	I2C_P33_P32				3

//========================================================================
//                              I2C�ж�����
//========================================================================

#define		I2C_Master_Inturrupt(n)	(n==0?(I2CMSCR &= ~0x80):(I2CMSCR |= 0x80))	//0����ֹ I2C ���ܣ�1��ʹ�� I2C ����

#define		PI2C	0x40

#define		PI2CH		0x40


//I2C�ж����ȼ�����
#define 	I2C_Priority(n)				do{if(n == 0) IP2H &= ~PI2CH, IP2 &= ~PI2C; \
																if(n == 1) IP2H &= ~PI2CH, IP2 |= PI2C; \
																if(n == 2) IP2H |= PI2CH, IP2 &= ~PI2C; \
																if(n == 3) IP2H |= PI2CH, IP2 |= PI2C; \
															}while(0)

//========================================================================
//                               I2C����
//========================================================================

#define		I2C_Function(n)	(n==0?(I2CCFG &= ~0x80):(I2CCFG |= 0x80))	//0����ֹ I2C ���ܣ�1��ʹ�� I2C ����
#define		I2C_ENABLE()	I2CCFG |= 0x80		/* ʹ�� I2C ���� */
#define		I2C_DISABLE()	I2CCFG &= ~0x80		/* ��ֹ I2C ���� */
#define		I2C_Master()	I2CCFG |=  0x40		/* 1: ��Ϊ����	*/
#define		I2C_Slave()		I2CCFG &= ~0x40		/* 0: ��Ϊ�ӻ�	*/
#define		I2C_SetSpeed(n)	I2CCFG = (I2CCFG & ~0x3f) | (n & 0x3f)	/* �����ٶ�=Fosc/2/(Speed*2+4) */

#define		I2C_WDTA_EN()		I2CMSAUX |= 0x01		/* ʹ���Զ����� */
#define		I2C_WDTA_DIS()	I2CMSAUX &= ~0x01		/* ��ֹ�Զ����� */

#define		I2C_ESTAI_EN(n)		I2CSLCR = (I2CSLCR & ~0x40) | (n << 6)		/* ʹ�ܴӻ�����START�ź��ж� */
#define		I2C_ERXI_EN(n)		I2CSLCR = (I2CSLCR & ~0x20) | (n << 5)		/* ʹ�ܴӻ�����1�ֽ������ж� */
#define		I2C_ETXI_EN(n)		I2CSLCR = (I2CSLCR & ~0x10) | (n << 4)		/* ʹ�ܴӻ�����1�ֽ������ж� */
#define		I2C_ESTOI_EN(n)		I2CSLCR = (I2CSLCR & ~0x08) | (n << 3)		/* ʹ�ܴӻ�����STOP�ź��ж� */
#define		I2C_SLRET()				I2CSLCR |= 0x01			/* ��λ�ӻ�ģʽ */

#define		I2C_Address(n)	I2CSLADR = (I2CSLADR & 0x01) | (n << 1)	/* �ӻ���ַ */
#define		I2C_MATCH_EN()	I2CSLADR &= ~0x01	/* ʹ�ܴӻ���ַ�ȽϹ��ܣ�ֻ������ƥ���ַ */
#define		I2C_MATCH_DIS()	I2CSLADR |= 0x01	/* ��ֹ�ӻ���ַ�ȽϹ��ܣ����������豸��ַ */

//========================================================================
//                              ��������
//========================================================================

#define DEV_ADDR    0xA0    //�ӻ��豸д��ַ

#define	I2C_BUF_LENTH	8

#define		I2C_ESTAI					0x40		/* �ӻ�����START�ź��ж� */
#define		I2C_ERXI					0x20		/* �ӻ�����1�ֽ������ж� */
#define		I2C_ETXI					0x10		/* �ӻ�����1�ֽ������ж� */
#define		I2C_ESTOI					0x08		/* �ӻ�����STOP�ź��ж� */

typedef struct
{
	u8	I2C_Speed;				//�����ٶ�=Fosc/2/(Speed*2+4),      0~63
	u8	I2C_Enable;				//I2C����ʹ��,   ENABLE, DISABLE
	u8	I2C_Mode;					//����ģʽѡ��,  I2C_Mode_Master,I2C_Mode_Slave
	u8	I2C_MS_WDTA;				//����ʹ���Զ�����,  ENABLE, DISABLE

	u8	I2C_SL_ADR;				//�ӻ��豸��ַ,  0~127
	u8	I2C_SL_MA;				//�ӻ��豸��ַ�Ƚ�ʹ��,  ENABLE, DISABLE
} I2C_InitTypeDef;

typedef struct
{
	u8	isma;				//MEMORY ADDRESS �����жϱ�־
	u8	isda;				//DEVICE ADDRESS �����жϱ�־
	u8	addr;				//ADDRESS ����
} I2C_IsrTypeDef;


extern u8 xdata I2C_Buffer[I2C_BUF_LENTH];
extern bit DisplayFlag;

void I2C_Init(I2C_InitTypeDef *I2Cx);
void I2C_WriteNbyte(u8 dev_addr, u8 mem_addr, u8 *p, u8 number);
void I2C_ReadNbyte(u8 dev_addr, u8 mem_addr, u8 *p, u8 number);
u8 Get_MSBusy_Status(void);
void SendCmdData(u8 cmd, u8 dat);

u8 NVIC_I2C_Init(u8 Mode, u8 State, u8 Priority);

#endif

