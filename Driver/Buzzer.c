#include "Buzzer.h"
#include "GPIO.h"
#include "STC8H_PWM.h"
#include "Switch.h"
#include "NVIC.h"

static u16 hz[] = {
	523 * 1, 587 * 1, 659 * 1, 698 * 1, 784 * 1, 880 * 1, 988 * 1, 
	523 * 2, 587 * 2, 659 * 2, 698 * 2, 784 * 2, 880 * 2, 988 * 2, 
	523 * 4, 587 * 4, 659 * 4, 698 * 4, 784 * 4, 880 * 4, 988 * 4, 
	523 * 8, 587 * 8, 659 * 8, 698 * 8, 784 * 8, 880 * 8, 988 * 8, 
};

//			        C	 D    E 	F	 G	 A	  B	   C`
//static u16 hz[] = {523, 587, 659, 698, 784, 880, 988, 1047};

//			        C`	   D`     E`   F`	  G`	A`	  B`    C``
//static u16 hz[] = {1047, 1175, 1319, 1397, 1568, 1760, 1976, 2093};


static void GPIO_config(void) {
    P0_MODE_OUT_PP(GPIO_Pin_0);
}


// ��ʼ��
void Buzzer_init() {
    // ��չ�Ĵ���ʹ��
    EAXSFR();

    GPIO_config();
}

// ����ָ��Ƶ�ʲ���
void Buzzer_play(u16 hz_value) {

    PWMx_InitDefine		PWMx_InitStructure;

    u16 Period = MAIN_Fosc / hz_value;

    // ����PWM5
    PWMx_InitStructure.PWM_Mode    		= CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    PWMx_InitStructure.PWM_Duty   	 	= (u16)(Period * 0.5);	//PWMռ�ձ�ʱ��, 0~Period
    PWMx_InitStructure.PWM_EnoSelect    = ENO5P;			//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWM_Configuration(PWM5, &PWMx_InitStructure);			//��ʼ��PWM,  PWMA,PWMB

    // ����PWMB
    PWMx_InitStructure.PWM_Period   = Period - 1;			//����ʱ��,   0~65535
    PWMx_InitStructure.PWM_DeadTime = 0;					//��������������, 0~255
    PWMx_InitStructure.PWM_MainOutEnable= ENABLE;			//�����ʹ��, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;			//ʹ�ܼ�����, ENABLE,DISABLE
    PWM_Configuration(PWMB, &PWMx_InitStructure);			//��ʼ��PWMͨ�üĴ���,  PWMA,PWMB

    // �л�PWMͨ��
    PWM5_SW(PWM5_SW_P00);					//PWM5_SW_P20,PWM5_SW_P17,PWM5_SW_P00,PWM5_SW_P74

    // ��ʼ��PWMB���ж�
    NVIC_PWM_Init(PWMB,DISABLE,Priority_0);
}

// ����ָ�����ڲ��� 1 2 3 4 5 6 7 8
void Buzzer_beep(u8 hz_value_index){
	u16 hz_value = hz[hz_value_index - 1];
	Buzzer_play(hz_value);	
}

// ֹͣ����
void Buzzer_stop() {
    PWMx_InitDefine		PWMx_InitStructure;
    PWMx_InitStructure.PWM_MainOutEnable= DISABLE;			//�����ʹ��, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable   = DISABLE;			//ʹ�ܼ�����, ENABLE,DISABLE
    PWM_Configuration(PWMB, &PWMx_InitStructure);			//��ʼ��PWMͨ�üĴ���,  PWMA,PWMB
}