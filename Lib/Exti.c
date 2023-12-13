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

#include	"Exti.h"

//========================================================================
// 函数: u8	Ext_Inilize(u8 EXT, EXTI_InitTypeDef *INTx)
// 描述: 外部中断初始化程序.
// 参数: EXT: 外部中断号, INTx: 结构参数,请参考Exti.h里的定义.
// 返回: 成功返回 SUCCESS, 错误返回 FAIL.
// 版本: V1.0, 2012-10-22
//========================================================================
u8	Ext_Inilize(u8 EXT, EXTI_InitTypeDef *INTx)
{
	if(EXT >  EXT_INT1)	return FAIL;	//空操作
	
	if(EXT == EXT_INT0)	//外中断0
	{
		IE0  = 0;					//外中断0标志位
		INT0_Mode(INTx->EXTI_Mode);
		return SUCCESS;		//成功
	}

	if(EXT == EXT_INT1)	//外中断1
	{
		IE1  = 0;					//外中断1标志位
		INT1_Mode(INTx->EXTI_Mode);
		return SUCCESS;		//成功
	}
	return FAIL;	//失败
}

//========================================================================
// 函数: NVIC_INT0_Init
// 描述: INT0嵌套向量中断控制器初始化.
// 参数: State:    中断使能状态, ENABLE/DISABLE.
// 参数: Priority: 中断优先级, Priority_0,Priority_1,Priority_2,Priority_3.
// 返回: 执行结果 SUCCESS/FAIL.
// 版本: V1.0, 2020-09-29
//========================================================================
u8 NVIC_INT0_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	if(Priority > Priority_3) return FAIL;
	INT0_Interrupt(State);
	INT0_Priority(Priority);
	return SUCCESS;
}

//========================================================================
// 函数: NVIC_INT1_Init
// 描述: INT1嵌套向量中断控制器初始化.
// 参数: State:    中断使能状态, ENABLE/DISABLE.
// 参数: Priority: 中断优先级, Priority_0,Priority_1,Priority_2,Priority_3.
// 返回: 执行结果 SUCCESS/FAIL.
// 版本: V1.0, 2020-09-29
//========================================================================
u8 NVIC_INT1_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	if(Priority > Priority_3) return FAIL;
	INT1_Interrupt(State);
	INT1_Priority(Priority);
	return SUCCESS;
}

//========================================================================
// 函数: NVIC_INT2_Init
// 描述: INT2嵌套向量中断控制器初始化.
// 参数: State:    中断使能状态, ENABLE/DISABLE.
// 参数: Priority: 中断优先级, NULL.
// 返回: 执行结果 SUCCESS/FAIL.
// 版本: V1.0, 2020-09-29
//========================================================================
u8 NVIC_INT2_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	INT2_Interrupt(State);
	Priority = NULL;
	return SUCCESS;
}

//========================================================================
// 函数: NVIC_INT3_Init
// 描述: INT3嵌套向量中断控制器初始化.
// 参数: State:    中断使能状态, ENABLE/DISABLE.
// 参数: Priority: 中断优先级, NULL.
// 返回: 执行结果 SUCCESS/FAIL.
// 版本: V1.0, 2020-09-29
//========================================================================
u8 NVIC_INT3_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	INT3_Interrupt(State);
	Priority = NULL;
	return SUCCESS;
}

//========================================================================
// 函数: NVIC_INT4_Init
// 描述: INT4嵌套向量中断控制器初始化.
// 参数: State:    中断使能状态, ENABLE/DISABLE.
// 参数: Priority: 中断优先级, NULL.
// 返回: 执行结果 SUCCESS/FAIL.
// 版本: V1.0, 2020-09-29
//========================================================================
u8 NVIC_INT4_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	INT4_Interrupt(State);
	Priority = NULL;
	return SUCCESS;
}
