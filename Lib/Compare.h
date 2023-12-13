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

#ifndef	__COMPARE_H
#define	__COMPARE_H

#include	"config.h"

//========================================================================
//                              定义声明
//========================================================================

//                       7      6     5    4    3    2     1      0        Reset Value
//sfr CMPCR1 = 0xE6;   CMPEN  CMPIF  PIE  NIE  PIS  NIS  CMPOE  CMPRES      00000000B
#define	CMPEN		0x80	//1: 允许比较器, 0: 禁止,关闭比较器电源
#define	CMPIF		0x40	//比较器中断标志, 包括上升沿或下降沿中断, 软件清0
//#define	PIE			0x20	//1: 比较结果由0变1, 产生上升沿中断
//#define	NIE			0x10	//1: 比较结果由1变0, 产生下降沿中断
//#define	PIS         0x08	//(旧版比较器)输入正极性选择, 0: 选择内部P5.5做正输入,          1: 由ADCIS[2:0]所选择的ADC输入端做正输入.
//#define	NIS         0x04	//(旧版比较器)输入负极性选择, 0: 选择内部BandGap电压BGv做负输入, 1: 选择外部P5.4做输入.
#define	CMPOE       0x02	//1: 允许比较结果输出到P1.2, 0: 禁止.
#define	CMPRES      0x01	//比较结果, 1: CMP+电平高于CMP-,  0: CMP+电平低于CMP-,  只读

#define	CMP_P_P37	0x00	//输入正极性选择, 0: 选择内部P3.7做正输入
#define	CMP_P_P50	0x01	//输入正极性选择, 1: 选择内部P5.0做正输入
#define	CMP_P_P51	0x02	//输入正极性选择, 2: 选择内部P5.1做正输入
#define	CMP_P_ADC	0x03	//输入正极性选择, 3: 由ADC_CHS[3:0]所选择的ADC输入端做正输入.

#define	CMP_N_P36	0x00	//输入负极性选择, 0: 选择外部P3.6做负输入.
#define	CMP_N_GAP	0x04	//输入负极性选择, 1: 选择内部BandGap电压BGv做负输入.

#define	CMP_CHYS_0mV	0x00	//DC迟滞输入：0mV
#define	CMP_CHYS_10mV	0x40	//DC迟滞输入：10mV
#define	CMP_CHYS_20mV	0x80	//DC迟滞输入：20mV
#define	CMP_CHYS_30mV	0xC0	//DC迟滞输入：30mV

#define CMP_CHYS_Set(n)		CMPEXCFG = (CMPEXCFG & ~0xC0) | (n)		/* DC迟滞输入设置 */
#define CMP_N_Select(n)		(n==0?(CMPEXCFG &= ~0x04):(CMPEXCFG |= 0x04))	/* 比较器负极性选择 */
#define CMP_P_Select(n)		CMPEXCFG = (CMPEXCFG & ~0x03) | (n)	/* 比较器正极性选择 */

#define	CMPO_P34()	P_SW2 &= ~0x08	//结果输出到P3.4.
#define	CMPO_P41()	P_SW2 |=  0x08	//结果输出到P4.1.

//                       7        6       5  4  3  2  1  0    Reset Value
//sfr CMPCR2 = 0xE7;   INVCMPO  DISFLT       LCDTY[5:0]       00001001B
#define	INVCMPO	0x80	//1: 比较器输出取反,  0: 不取反
#define	DISFLT	0x40	//1: 关闭0.1us滤波,   0: 允许
#define	LCDTY	0x00	//0~63, 比较结果变化延时周期数

#define		PCMP	0x20
#define		PCMPH		0x20

//比较器中断优先级控制
#define 	CMP_Priority(n)				do{if(n == 0) IP2H &= ~PCMPH, IP2 &= ~PCMP; \
																if(n == 1) IP2H &= ~PCMPH, IP2 |= PCMP; \
																if(n == 2) IP2H |= PCMPH, IP2 &= ~PCMP; \
																if(n == 3) IP2H |= PCMPH, IP2 |= PCMP; \
															}while(0)

//========================================================================
//                            功能脚切换设置
//========================================================================
#define	CMP_OUT_P34				0
#define	CMP_OUT_P41				1

#define  COMP_SW(Pin)				P_SW2 = (P_SW2 & 0xF7) | (Pin << 3)
															
															
typedef struct
{ 
	u8	CMP_EN;				//比较器允许或禁止,   ENABLE,DISABLE
	u8	CMP_P_Select;		//比较器输入正极选择, CMP_P_P37,CMP_P_P50,CMP_P_P51,CMP_P_ADC
	u8	CMP_N_Select;		//比较器输入负极选择, CMP_N_GAP: 选择内部BandGap经过OP后的电压做负输入, CMP_N_P36: 选择P3.6做负输入.
	u8	CMP_Outpt_En;		//允许比较结果输出,   ENABLE,DISABLE
	u8	CMP_InvCMPO;		//比较器输出取反, ENABLE,DISABLE
	u8	CMP_100nsFilter;	//内部0.1us滤波,  ENABLE,DISABLE
	u8	CMP_OutDelayDuty;	//0~63, 比较结果变化延时周期数
	u8	CMP_CHYS;			//DC迟滞输入选择,  CMP_CHYS_0mV,CMP_CHYS_10mV,CMP_CHYS_20mV,CMP_CHYS_30mV
} CMP_InitDefine; 

void	CMP_Inilize(CMP_InitDefine *CMPx);


u8 NVIC_CMP_Init(u8 State, u8 Priority);

#endif
