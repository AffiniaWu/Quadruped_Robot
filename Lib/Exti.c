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

#include	"Exti.h"

//========================================================================
// ����: u8	Ext_Inilize(u8 EXT, EXTI_InitTypeDef *INTx)
// ����: �ⲿ�жϳ�ʼ������.
// ����: EXT: �ⲿ�жϺ�, INTx: �ṹ����,��ο�Exti.h��Ķ���.
// ����: �ɹ����� SUCCESS, ���󷵻� FAIL.
// �汾: V1.0, 2012-10-22
//========================================================================
u8	Ext_Inilize(u8 EXT, EXTI_InitTypeDef *INTx)
{
	if(EXT >  EXT_INT1)	return FAIL;	//�ղ���
	
	if(EXT == EXT_INT0)	//���ж�0
	{
		IE0  = 0;					//���ж�0��־λ
		INT0_Mode(INTx->EXTI_Mode);
		return SUCCESS;		//�ɹ�
	}

	if(EXT == EXT_INT1)	//���ж�1
	{
		IE1  = 0;					//���ж�1��־λ
		INT1_Mode(INTx->EXTI_Mode);
		return SUCCESS;		//�ɹ�
	}
	return FAIL;	//ʧ��
}

//========================================================================
// ����: NVIC_INT0_Init
// ����: INT0Ƕ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, ENABLE/DISABLE.
// ����: Priority: �ж����ȼ�, Priority_0,Priority_1,Priority_2,Priority_3.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
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
// ����: NVIC_INT1_Init
// ����: INT1Ƕ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, ENABLE/DISABLE.
// ����: Priority: �ж����ȼ�, Priority_0,Priority_1,Priority_2,Priority_3.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
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
// ����: NVIC_INT2_Init
// ����: INT2Ƕ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, ENABLE/DISABLE.
// ����: Priority: �ж����ȼ�, NULL.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_INT2_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	INT2_Interrupt(State);
	Priority = NULL;
	return SUCCESS;
}

//========================================================================
// ����: NVIC_INT3_Init
// ����: INT3Ƕ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, ENABLE/DISABLE.
// ����: Priority: �ж����ȼ�, NULL.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_INT3_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	INT3_Interrupt(State);
	Priority = NULL;
	return SUCCESS;
}

//========================================================================
// ����: NVIC_INT4_Init
// ����: INT4Ƕ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, ENABLE/DISABLE.
// ����: Priority: �ж����ȼ�, NULL.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_INT4_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	INT4_Interrupt(State);
	Priority = NULL;
	return SUCCESS;
}
