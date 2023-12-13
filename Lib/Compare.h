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

#ifndef	__COMPARE_H
#define	__COMPARE_H

#include	"config.h"

//========================================================================
//                              ��������
//========================================================================

//                       7      6     5    4    3    2     1      0        Reset Value
//sfr CMPCR1 = 0xE6;   CMPEN  CMPIF  PIE  NIE  PIS  NIS  CMPOE  CMPRES      00000000B
#define	CMPEN		0x80	//1: ����Ƚ���, 0: ��ֹ,�رձȽ�����Դ
#define	CMPIF		0x40	//�Ƚ����жϱ�־, ���������ػ��½����ж�, �����0
//#define	PIE			0x20	//1: �ȽϽ����0��1, �����������ж�
//#define	NIE			0x10	//1: �ȽϽ����1��0, �����½����ж�
//#define	PIS         0x08	//(�ɰ�Ƚ���)����������ѡ��, 0: ѡ���ڲ�P5.5��������,          1: ��ADCIS[2:0]��ѡ���ADC�������������.
//#define	NIS         0x04	//(�ɰ�Ƚ���)���븺����ѡ��, 0: ѡ���ڲ�BandGap��ѹBGv��������, 1: ѡ���ⲿP5.4������.
#define	CMPOE       0x02	//1: ����ȽϽ�������P1.2, 0: ��ֹ.
#define	CMPRES      0x01	//�ȽϽ��, 1: CMP+��ƽ����CMP-,  0: CMP+��ƽ����CMP-,  ֻ��

#define	CMP_P_P37	0x00	//����������ѡ��, 0: ѡ���ڲ�P3.7��������
#define	CMP_P_P50	0x01	//����������ѡ��, 1: ѡ���ڲ�P5.0��������
#define	CMP_P_P51	0x02	//����������ѡ��, 2: ѡ���ڲ�P5.1��������
#define	CMP_P_ADC	0x03	//����������ѡ��, 3: ��ADC_CHS[3:0]��ѡ���ADC�������������.

#define	CMP_N_P36	0x00	//���븺����ѡ��, 0: ѡ���ⲿP3.6��������.
#define	CMP_N_GAP	0x04	//���븺����ѡ��, 1: ѡ���ڲ�BandGap��ѹBGv��������.

#define	CMP_CHYS_0mV	0x00	//DC�������룺0mV
#define	CMP_CHYS_10mV	0x40	//DC�������룺10mV
#define	CMP_CHYS_20mV	0x80	//DC�������룺20mV
#define	CMP_CHYS_30mV	0xC0	//DC�������룺30mV

#define CMP_CHYS_Set(n)		CMPEXCFG = (CMPEXCFG & ~0xC0) | (n)		/* DC������������ */
#define CMP_N_Select(n)		(n==0?(CMPEXCFG &= ~0x04):(CMPEXCFG |= 0x04))	/* �Ƚ���������ѡ�� */
#define CMP_P_Select(n)		CMPEXCFG = (CMPEXCFG & ~0x03) | (n)	/* �Ƚ���������ѡ�� */

#define	CMPO_P34()	P_SW2 &= ~0x08	//��������P3.4.
#define	CMPO_P41()	P_SW2 |=  0x08	//��������P4.1.

//                       7        6       5  4  3  2  1  0    Reset Value
//sfr CMPCR2 = 0xE7;   INVCMPO  DISFLT       LCDTY[5:0]       00001001B
#define	INVCMPO	0x80	//1: �Ƚ������ȡ��,  0: ��ȡ��
#define	DISFLT	0x40	//1: �ر�0.1us�˲�,   0: ����
#define	LCDTY	0x00	//0~63, �ȽϽ���仯��ʱ������

#define		PCMP	0x20
#define		PCMPH		0x20

//�Ƚ����ж����ȼ�����
#define 	CMP_Priority(n)				do{if(n == 0) IP2H &= ~PCMPH, IP2 &= ~PCMP; \
																if(n == 1) IP2H &= ~PCMPH, IP2 |= PCMP; \
																if(n == 2) IP2H |= PCMPH, IP2 &= ~PCMP; \
																if(n == 3) IP2H |= PCMPH, IP2 |= PCMP; \
															}while(0)

//========================================================================
//                            ���ܽ��л�����
//========================================================================
#define	CMP_OUT_P34				0
#define	CMP_OUT_P41				1

#define  COMP_SW(Pin)				P_SW2 = (P_SW2 & 0xF7) | (Pin << 3)
															
															
typedef struct
{ 
	u8	CMP_EN;				//�Ƚ���������ֹ,   ENABLE,DISABLE
	u8	CMP_P_Select;		//�Ƚ�����������ѡ��, CMP_P_P37,CMP_P_P50,CMP_P_P51,CMP_P_ADC
	u8	CMP_N_Select;		//�Ƚ������븺��ѡ��, CMP_N_GAP: ѡ���ڲ�BandGap����OP��ĵ�ѹ��������, CMP_N_P36: ѡ��P3.6��������.
	u8	CMP_Outpt_En;		//����ȽϽ�����,   ENABLE,DISABLE
	u8	CMP_InvCMPO;		//�Ƚ������ȡ��, ENABLE,DISABLE
	u8	CMP_100nsFilter;	//�ڲ�0.1us�˲�,  ENABLE,DISABLE
	u8	CMP_OutDelayDuty;	//0~63, �ȽϽ���仯��ʱ������
	u8	CMP_CHYS;			//DC��������ѡ��,  CMP_CHYS_0mV,CMP_CHYS_10mV,CMP_CHYS_20mV,CMP_CHYS_30mV
} CMP_InitDefine; 

void	CMP_Inilize(CMP_InitDefine *CMPx);


u8 NVIC_CMP_Init(u8 State, u8 Priority);

#endif
