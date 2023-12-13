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

#include	"STC8H_RTC.h"

//========================================================================
// ����: u8	ADC_Inilize(ADC_InitTypeDef *ADCx)
// ����: ADC��ʼ������.
// ����: ADCx: �ṹ����,��ο�adc.h��Ķ���.
// ����: none.
// �汾: V1.0, 2012-10-22
//========================================================================
u8	RTC_Inilize(RTC_InitTypeDef *RTCx)
{
	if(RTCx->RTC_Year > 99)	return FAIL;	//����
	if(RTCx->RTC_Month > 12)	return FAIL;	//����
	if(RTCx->RTC_Day > 31)	return FAIL;	//����
	if(RTCx->RTC_Hour > 23)	return FAIL;	//����
	if(RTCx->RTC_Min > 59)	return FAIL;	//����
	if(RTCx->RTC_Sec > 59)	return FAIL;	//����
	if(RTCx->RTC_Ssec > 127)	return FAIL;	//����
	if(RTCx->RTC_ALAHour > 23)	return FAIL;	//����
	if(RTCx->RTC_ALAMin > 59)	return FAIL;	//����
	if(RTCx->RTC_ALASec > 59)	return FAIL;	//����
	if(RTCx->RTC_ALASsec > 127)	return FAIL;	//����

	INIYEAR = RTCx->RTC_Year;
	INIMONTH = RTCx->RTC_Month;
	INIDAY = RTCx->RTC_Day;
	INIHOUR = RTCx->RTC_Hour;
	INIMIN = RTCx->RTC_Min;
	INISEC = RTCx->RTC_Sec;
	INISSEC = RTCx->RTC_Ssec;

	ALAHOUR = RTCx->RTC_ALAHour;	//����Сʱ
	ALAMIN  = RTCx->RTC_ALAMin;		//���ӷ���
	ALASEC  = RTCx->RTC_ALASec;		//������
	ALASSEC = RTCx->RTC_ALASsec;	//����1/128��

	if(RTCx->RTC_Clock == RTC_IRC32KCR)
	{
		//STC8H8K64U B�汾оƬʹ���ڲ�32Kʱ�ӣ������޷�����
		IRC32KCR = 0x80;   //�����ڲ�32K����.
		while (!(IRC32KCR & 1));  //�ȴ�ʱ���ȶ�
		RTCCFG = 0x03;    //ѡ���ڲ�32Kʱ��Դ������RTC�Ĵ�����ʼ��
	}
	else
	{
		X32KCR = 0x80 + 0x40;   //�����ⲿ32K����, ������+0x00, ������+0x40.
		while (!(X32KCR & 1));  //�ȴ�ʱ���ȶ�
		RTCCFG = 0x01;    //ѡ���ⲿ32Kʱ��Դ������RTC�Ĵ�����ʼ��
	}

	if(RTCx->RTC_Enable == ENABLE)
	{
		RTCCR = 0x01;     //RTCʹ��
		while(RTCCFG & 0x01);	//�ȴ���ʼ�����,��Ҫ�� "RTCʹ��" ֮���ж�. 
		//����RTCʱ����Ҫ32768Hz��1������ʱ��,��Լ30.5us. ����ͬ��, ����ʵ�ʵȴ�ʱ����0~30.5us.
		//������ȴ�������ɾ�˯��, ��RTC����������û���, ֹͣ����, ���Ѻ�ż���������ò���������.
	}
	else
	{
		RTCCR = 0x00;     //RTC�ر�
	}
	
	return SUCCESS;
}



//========================================================================
// ����: NVIC_RTC_Init
// ����: SPIǶ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, �ж�ʹ��, 0x80:�����ж�, 0x40:���ж�, 0x20:Сʱ�ж�, 0x10:�����ж�, 0x08:���ж�, 0x04:1/2���ж�, 0x02:1/8���ж�, 0x01:1/32���ж� /DISABLE.
// ����: Priority: �ж����ȼ�, Priority_0,Priority_1,Priority_2,Priority_3.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_RTC_Init(u8 State, u8 Priority)
{
	if(Priority <= Priority_3) RTC_Priority(Priority); else  return FAIL;
	RTC_Interrupt(State); 
	return SUCCESS;
}
