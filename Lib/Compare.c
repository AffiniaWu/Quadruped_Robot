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

#include	"Compare.h"

//========================================================================
// ����:void	CMP_Inilize(CMP_InitDefine *CMPx)
// ����: �Ƚ�����ʼ������.
// ����: CMPx: �ṹ����,��ο�compare.h��Ķ���.
// ����: none.
// �汾: V1.0, 2012-10-22
//========================================================================
void	CMP_Inilize(CMP_InitDefine *CMPx)
{
	CMPCR1 &= 0x30;
	CMPCR2 = CMPx->CMP_OutDelayDuty & 0x3f;							//�ȽϽ���仯��ʱ������, 0~63
	if(CMPx->CMP_Outpt_En == ENABLE)		CMPCR1 |= CMPOE;		//����ȽϽ�������P3.4/P4.1,   ENABLE,DISABLE
	if(CMPx->CMP_InvCMPO     == ENABLE)		CMPCR2 |= INVCMPO;		//�Ƚ������ȡ��, 	ENABLE,DISABLE
	if(CMPx->CMP_100nsFilter == DISABLE)	CMPCR2 |= DISFLT;		//�ڲ�0.1us�˲�,  	ENABLE,DISABLE

    CMP_P_Select(CMPx->CMP_P_Select);   //�Ƚ������븺��ѡ��, CMP_P_P37,CMP_P_P50,CMP_P_P51,CMP_P_ADC.
    CMP_N_Select(CMPx->CMP_N_Select);   //�Ƚ������븺��ѡ��, CMP_N_GAP: ѡ���ڲ�BandGap����OP��ĵ�ѹ��������, CMP_N_P36: ѡ��P3.6��������.
    CMP_CHYS_Set(CMPx->CMP_CHYS);       //�Ƚ���DC��������ѡ��
	if(CMPx->CMP_EN == ENABLE)				CMPCR1 |= CMPEN;		//����Ƚ���		ENABLE,DISABLE
}


//========================================================================
// ����: NVIC_CMP_Init
// ����: �Ƚ���Ƕ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, RISING_EDGE/FALLING_EDGE/DISABLE.
// ����: Priority: �ж����ȼ�, Priority_0,Priority_1,Priority_2,Priority_3.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_CMP_Init(u8 State, u8 Priority)
{
	if(Priority > Priority_3) return FAIL;
	if(State & RISING_EDGE)	CMPCR1 |= PIE;			//�����������ж�
	else	CMPCR1 &= ~PIE;			//��ֹ�������ж�
	if(State & FALLING_EDGE)	CMPCR1 |= NIE;		//�����½����ж�
	else	CMPCR1 &= ~NIE;			//��ֹ�������ж�
	CMP_Priority(Priority);
	return SUCCESS;
}
