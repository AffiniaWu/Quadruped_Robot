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

#include	"Compare.h"

//========================================================================
// 函数:void	CMP_Inilize(CMP_InitDefine *CMPx)
// 描述: 比较器初始化程序.
// 参数: CMPx: 结构参数,请参考compare.h里的定义.
// 返回: none.
// 版本: V1.0, 2012-10-22
//========================================================================
void	CMP_Inilize(CMP_InitDefine *CMPx)
{
	CMPCR1 &= 0x30;
	CMPCR2 = CMPx->CMP_OutDelayDuty & 0x3f;							//比较结果变化延时周期数, 0~63
	if(CMPx->CMP_Outpt_En == ENABLE)		CMPCR1 |= CMPOE;		//允许比较结果输出到P3.4/P4.1,   ENABLE,DISABLE
	if(CMPx->CMP_InvCMPO     == ENABLE)		CMPCR2 |= INVCMPO;		//比较器输出取反, 	ENABLE,DISABLE
	if(CMPx->CMP_100nsFilter == DISABLE)	CMPCR2 |= DISFLT;		//内部0.1us滤波,  	ENABLE,DISABLE

    CMP_P_Select(CMPx->CMP_P_Select);   //比较器输入负极选择, CMP_P_P37,CMP_P_P50,CMP_P_P51,CMP_P_ADC.
    CMP_N_Select(CMPx->CMP_N_Select);   //比较器输入负极选择, CMP_N_GAP: 选择内部BandGap经过OP后的电压做负输入, CMP_N_P36: 选择P3.6做负输入.
    CMP_CHYS_Set(CMPx->CMP_CHYS);       //比较器DC迟滞输入选择
	if(CMPx->CMP_EN == ENABLE)				CMPCR1 |= CMPEN;		//允许比较器		ENABLE,DISABLE
}


//========================================================================
// 函数: NVIC_CMP_Init
// 描述: 比较器嵌套向量中断控制器初始化.
// 参数: State:    中断使能状态, RISING_EDGE/FALLING_EDGE/DISABLE.
// 参数: Priority: 中断优先级, Priority_0,Priority_1,Priority_2,Priority_3.
// 返回: 执行结果 SUCCESS/FAIL.
// 版本: V1.0, 2020-09-29
//========================================================================
u8 NVIC_CMP_Init(u8 State, u8 Priority)
{
	if(Priority > Priority_3) return FAIL;
	if(State & RISING_EDGE)	CMPCR1 |= PIE;			//允许上升沿中断
	else	CMPCR1 &= ~PIE;			//禁止上升沿中断
	if(State & FALLING_EDGE)	CMPCR1 |= NIE;		//允许下降沿中断
	else	CMPCR1 &= ~NIE;			//禁止上升沿中断
	CMP_Priority(Priority);
	return SUCCESS;
}
