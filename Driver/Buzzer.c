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


// 初始化
void Buzzer_init() {
    // 扩展寄存器使能
    EAXSFR();

    GPIO_config();
}

// 按照指定频率播放
void Buzzer_play(u16 hz_value) {

    PWMx_InitDefine		PWMx_InitStructure;

    u16 Period = MAIN_Fosc / hz_value;

    // 配置PWM5
    PWMx_InitStructure.PWM_Mode    		= CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    PWMx_InitStructure.PWM_Duty   	 	= (u16)(Period * 0.5);	//PWM占空比时间, 0~Period
    PWMx_InitStructure.PWM_EnoSelect    = ENO5P;			//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWM_Configuration(PWM5, &PWMx_InitStructure);			//初始化PWM,  PWMA,PWMB

    // 配置PWMB
    PWMx_InitStructure.PWM_Period   = Period - 1;			//周期时间,   0~65535
    PWMx_InitStructure.PWM_DeadTime = 0;					//死区发生器设置, 0~255
    PWMx_InitStructure.PWM_MainOutEnable= ENABLE;			//主输出使能, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;			//使能计数器, ENABLE,DISABLE
    PWM_Configuration(PWMB, &PWMx_InitStructure);			//初始化PWM通用寄存器,  PWMA,PWMB

    // 切换PWM通道
    PWM5_SW(PWM5_SW_P00);					//PWM5_SW_P20,PWM5_SW_P17,PWM5_SW_P00,PWM5_SW_P74

    // 初始化PWMB的中断
    NVIC_PWM_Init(PWMB,DISABLE,Priority_0);
}

// 按照指定音节播放 1 2 3 4 5 6 7 8
void Buzzer_beep(u8 hz_value_index){
	u16 hz_value = hz[hz_value_index - 1];
	Buzzer_play(hz_value);	
}

// 停止播放
void Buzzer_stop() {
    PWMx_InitDefine		PWMx_InitStructure;
    PWMx_InitStructure.PWM_MainOutEnable= DISABLE;			//主输出使能, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable   = DISABLE;			//使能计数器, ENABLE,DISABLE
    PWM_Configuration(PWMB, &PWMx_InitStructure);			//初始化PWM通用寄存器,  PWMA,PWMB
}