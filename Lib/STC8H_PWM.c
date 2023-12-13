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

#include "STC8H_PWM.h"

//========================================================================
// ����: PWM_Configuration
// ����: PWM��ʼ������.
// ����: PWMx: �ṹ����,��ο�PWM.h��Ķ���.
// ����: �ɹ����� SUCCESS, ���󷵻� FAIL.
// �汾: V1.0, 2012-10-22
//========================================================================
u8 PWM_Configuration(u8 PWM, PWMx_InitDefine *PWMx)
{
	if(PWM == PWM1)
	{
		PWMA_CC1E_Disable();		//�ر����벶��/�Ƚ����
		PWMA_CC1NE_Disable();		//�رձȽ����
		PWMA_CC1S_Direction(CCAS_OUTPUT);		//CCnS����ͨ���ر�ʱ���ǿ�д��
		PWMA_OC1ModeSet(PWMx->PWM_Mode);		//��������Ƚ�ģʽ

		if(PWMx->PWM_EnoSelect & ENO1P)
		{
			PWMA_CC1E_Enable();			//�������벶��/�Ƚ����
			PWMA_ENO |= ENO1P;
		}
		else
		{
			PWMA_CC1E_Disable();		//�ر����벶��/�Ƚ����
			PWMA_ENO &= ~ENO1P;
		}
		if(PWMx->PWM_EnoSelect & ENO1N)
		{
			PWMA_CC1NE_Enable();		//�������벶��/�Ƚ����
			PWMA_ENO |= ENO1N;
		}
		else
		{
			PWMA_CC1NE_Disable();		//�ر����벶��/�Ƚ����
			PWMA_ENO &= ~ENO1N;
		}
		
		PWMA_Duty1(PWMx->PWM_Duty);
		
		return	SUCCESS;
	}
	
	if(PWM == PWM2)
	{
		PWMA_CC2E_Disable();		//�ر����벶��/�Ƚ����
		PWMA_CC2NE_Disable();		//�رձȽ����
		PWMA_CC2S_Direction(CCAS_OUTPUT);		//CCnS����ͨ���ر�ʱ���ǿ�д��
		PWMA_OC2ModeSet(PWMx->PWM_Mode);		//��������Ƚ�ģʽ

		if(PWMx->PWM_EnoSelect & ENO2P)
		{
			PWMA_CC2E_Enable();			//�������벶��/�Ƚ����
			PWMA_ENO |= ENO2P;
		}
		else
		{
			PWMA_CC2E_Disable();		//�ر����벶��/�Ƚ����
			PWMA_ENO &= ~ENO2P;
		}
		if(PWMx->PWM_EnoSelect & ENO2N)
		{
			PWMA_CC2NE_Enable();		//�������벶��/�Ƚ����
			PWMA_ENO |= ENO2N;
		}
		else
		{
			PWMA_CC2NE_Disable();		//�ر����벶��/�Ƚ����
			PWMA_ENO &= ~ENO2N;
		}
		
		PWMA_Duty2(PWMx->PWM_Duty);
		
		return	SUCCESS;
	}
	
	if(PWM == PWM3)
	{
		PWMA_CC3E_Disable();		//�ر����벶��/�Ƚ����
		PWMA_CC3NE_Disable();		//�رձȽ����
		PWMA_CC3S_Direction(CCAS_OUTPUT);		//CCnS����ͨ���ر�ʱ���ǿ�д��
		PWMA_OC3ModeSet(PWMx->PWM_Mode);		//��������Ƚ�ģʽ

		if(PWMx->PWM_EnoSelect & ENO3P)
		{
			PWMA_CC3E_Enable();			//�������벶��/�Ƚ����
			PWMA_ENO |= ENO3P;
		}
		else
		{
			PWMA_CC3E_Disable();		//�ر����벶��/�Ƚ����
			PWMA_ENO &= ~ENO3P;
		}
		if(PWMx->PWM_EnoSelect & ENO3N)
		{
			PWMA_CC3NE_Enable();		//�������벶��/�Ƚ����
			PWMA_ENO |= ENO3N;
		}
		else
		{
			PWMA_CC3NE_Disable();		//�ر����벶��/�Ƚ����
			PWMA_ENO &= ~ENO3N;
		}
		
		PWMA_Duty3(PWMx->PWM_Duty);
		
		return	SUCCESS;
	}
	
	if(PWM == PWM4)
	{
		PWMA_CC4E_Disable();		//�ر����벶��/�Ƚ����
		PWMA_CC4NE_Disable();		//�رձȽ����
		PWMA_CC4S_Direction(CCAS_OUTPUT);		//CCnS����ͨ���ر�ʱ���ǿ�д��
		PWMA_OC4ModeSet(PWMx->PWM_Mode);		//��������Ƚ�ģʽ

		if(PWMx->PWM_EnoSelect & ENO4P)
		{
			PWMA_CC4E_Enable();			//�������벶��/�Ƚ����
			PWMA_ENO |= ENO4P;
		}
		else
		{
			PWMA_CC4E_Disable();		//�ر����벶��/�Ƚ����
			PWMA_ENO &= ~ENO4P;
		}
		if(PWMx->PWM_EnoSelect & ENO4N)
		{
			PWMA_CC4NE_Enable();		//�������벶��/�Ƚ����
			PWMA_ENO |= ENO4N;
		}
		else
		{
			PWMA_CC4NE_Disable();		//�ر����벶��/�Ƚ����
			PWMA_ENO &= ~ENO4N;
		}
		
		PWMA_Duty4(PWMx->PWM_Duty);
		
		return	SUCCESS;
	}
	
	if(PWM == PWMA)
	{
//		PWMA_OC1_ReloadEnable(PWMx->PWM_Reload);	//����Ƚϵ�Ԥװ��ʹ��
//		PWMA_OC1_FastEnable(PWMx->PWM_Fast);		//����ȽϿ��ٹ���ʹ��
//		PWMA_CCPCAPreloaded(PWMx->PWM_PreLoad);	//����/�Ƚ�Ԥװ�ؿ���λ(��λֻ�Ծ��л��������ͨ��������)
//		PWMA_BrakeEnable(PWMx->PWM_BrakeEnable);	//����/��ֹɲ������

		PWMA_DeadTime(PWMx->PWM_DeadTime);	//��������������
		PWMA_AutoReload(PWMx->PWM_Period);	//��������
		PWMA_BrakeOutputEnable(PWMx->PWM_MainOutEnable);	//�����ʹ��
		PWMA_CEN_Enable(PWMx->PWM_CEN_Enable);	//ʹ�ܼ�����
		
		return	0;
	}

	if(PWM == PWM5)
	{
		PWMB_CC5E_Disable();		//�ر����벶��/�Ƚ����
		PWMB_CC5S_Direction(CCAS_OUTPUT);		//CCnS����ͨ���ر�ʱ���ǿ�д��
		PWMB_OC5ModeSet(PWMx->PWM_Mode);		//��������Ƚ�ģʽ

		if(PWMx->PWM_EnoSelect & ENO5P)
		{
			PWMB_CC5E_Enable();			//�������벶��/�Ƚ����
			PWMB_ENO |= ENO5P;
		}
		else
		{
			PWMB_CC5E_Disable();		//�ر����벶��/�Ƚ����
			PWMB_ENO &= ~ENO5P;
		}
		
		PWMB_Duty5(PWMx->PWM_Duty);
		
		return	SUCCESS;
	}
	
	if(PWM == PWM6)
	{
		PWMB_CC6E_Disable();		//�ر����벶��/�Ƚ����
		PWMB_CC6S_Direction(CCAS_OUTPUT);		//CCnS����ͨ���ر�ʱ���ǿ�д��
		PWMB_OC6ModeSet(PWMx->PWM_Mode);		//��������Ƚ�ģʽ

		if(PWMx->PWM_EnoSelect & ENO6P)
		{
			PWMB_CC6E_Enable();			//�������벶��/�Ƚ����
			PWMB_ENO |= ENO6P;
		}
		else
		{
			PWMB_CC6E_Disable();		//�ر����벶��/�Ƚ����
			PWMB_ENO &= ~ENO6P;
		}
		
		PWMB_Duty6(PWMx->PWM_Duty);
		
		return	SUCCESS;
	}
	
	if(PWM == PWM7)
	{
		PWMB_CC7E_Disable();		//�ر����벶��/�Ƚ����
		PWMB_CC7S_Direction(CCAS_OUTPUT);		//CCnS����ͨ���ر�ʱ���ǿ�д��
		PWMB_OC7ModeSet(PWMx->PWM_Mode);		//��������Ƚ�ģʽ

		if(PWMx->PWM_EnoSelect & ENO7P)
		{
			PWMB_CC7E_Enable();			//�������벶��/�Ƚ����
			PWMB_ENO |= ENO7P;
		}
		else
		{
			PWMB_CC7E_Disable();		//�ر����벶��/�Ƚ����
			PWMB_ENO &= ~ENO7P;
		}
		
		PWMB_Duty7(PWMx->PWM_Duty);
		
		return	SUCCESS;
	}
	
	if(PWM == PWM8)
	{
		PWMB_CC8E_Disable();		//�ر����벶��/�Ƚ����
		PWMB_CC8S_Direction(CCAS_OUTPUT);		//CCnS����ͨ���ر�ʱ���ǿ�д��
		PWMB_OC8ModeSet(PWMx->PWM_Mode);		//��������Ƚ�ģʽ

		if(PWMx->PWM_EnoSelect & ENO8P)
		{
			PWMB_CC8E_Enable();			//�������벶��/�Ƚ����
			PWMB_ENO |= ENO8P;
		}
		else
		{
			PWMB_CC8E_Disable();		//�ر����벶��/�Ƚ����
			PWMB_ENO &= ~ENO8P;
		}
		
		PWMB_Duty8(PWMx->PWM_Duty);
		
		return	SUCCESS;
	}
	
	if(PWM == PWMB)
	{
//		PWMB_OC5_ReloadEnable(PWMx->PWM_Reload);	//����Ƚϵ�Ԥװ��ʹ��
//		PWMB_OC5_FastEnable(PWMx->PWM_Fast);		//����ȽϿ��ٹ���ʹ��
//		PWMB_CCPCBPreloaded(PWMx->PWM_PreLoad);	//����/�Ƚ�Ԥװ�ؿ���λ(��λֻ�Ծ��л��������ͨ��������)
//		PWMB_BrakeEnable(PWMx->PWM_BrakeEnable);	//����/��ֹɲ������

		PWMB_DeadTime(PWMx->PWM_DeadTime);	//��������������
		PWMB_AutoReload(PWMx->PWM_Period);	//��������
		PWMB_BrakeOutputEnable(PWMx->PWM_MainOutEnable);	//�����ʹ��
		PWMB_CEN_Enable(PWMx->PWM_CEN_Enable);	//ʹ�ܼ�����
		
		return	0;
	}

	return	FAIL;	//����
}

//========================================================================
// ����: NVIC_PWM_Init
// ����: PWMǶ�������жϿ�������ʼ��.
// ����: Channel:  ͨ��, PWMA/PWMB.
// ����: State:    �ж�ʹ��״̬, PWM_BIE/PWM_TIE/PWM_COMIE/PWM_CC8IE~PWM_CC1IE/PWM_UIE/DISABLE.
// ����: Priority: �ж����ȼ�, Priority_0,Priority_1,Priority_2,Priority_3.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_PWM_Init(u8 Channel, u8 State, u8 Priority)
{
	if(Channel > PWMB) return FAIL;
	if(Priority > Priority_3) return FAIL;
	switch(Channel)
	{
		case PWMA:
			PWMA_IER = State;
			PWMA_Priority(Priority);
		break;

		case PWMB:
			PWMB_IER = State;
			PWMB_Priority(Priority);
		break;

		default:
			PWMB_IER = State;
			Priority = NULL;
		break;
	}
	return SUCCESS;
}

//========================================================================
// ����: UpdatePwm
// ����: PWMռ�ձȸ��³���.
// ����: PWM: PWMͨ��/���, PWMx�ṹ����,��ο�PWM.h��Ķ���.
// ����: none.
// �汾: V1.0, 2012-10-22
//========================================================================
void UpdatePwm(u8 PWM, PWMx_Duty *PWMx)
{
	switch(PWM)
	{
		case PWM1:
			PWMA_Duty1(PWMx->PWM1_Duty);
		break;

		case PWM2:
			PWMA_Duty2(PWMx->PWM2_Duty);
		break;

		case PWM3:
			PWMA_Duty3(PWMx->PWM3_Duty);
		break;

		case PWM4:
			PWMA_Duty4(PWMx->PWM4_Duty);
		break;

		case PWM5:
			PWMB_Duty5(PWMx->PWM5_Duty);
		break;

		case PWM6:
			PWMB_Duty6(PWMx->PWM6_Duty);
		break;

		case PWM7:
			PWMB_Duty7(PWMx->PWM7_Duty);
		break;

		case PWM8:
			PWMB_Duty8(PWMx->PWM8_Duty);
		break;

		case PWMA:
			PWMA_Duty1(PWMx->PWM1_Duty);
			PWMA_Duty2(PWMx->PWM2_Duty);
			PWMA_Duty3(PWMx->PWM3_Duty);
			PWMA_Duty4(PWMx->PWM4_Duty);
		break;

		case PWMB:
			PWMB_Duty5(PWMx->PWM5_Duty);
			PWMB_Duty6(PWMx->PWM6_Duty);
			PWMB_Duty7(PWMx->PWM7_Duty);
			PWMB_Duty8(PWMx->PWM8_Duty);
		break;
	}
}

/*********************************************************/
