#include "Light.h"
#include "GPIO.h"

#define LED_SW  P45
#define LED_F   P35
#define LED1    P27
#define LED2    P26
#define LED3    P15
#define LED4    P14
#define LED5    P23
#define LED6    P22
#define LED7    P21
#define LED8    P20

static void GPIO_config() {
    // P45  推挽  开关
    P4_MODE_OUT_PP(GPIO_Pin_5);
    // P45  两个前灯
    P3_MODE_OUT_PP(GPIO_Pin_5);
    // P20 P21 P22 P23 P26 P27 氛围灯
    P2_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7);
    // P14 P15 氛围灯
    P1_MODE_IO_PU(GPIO_Pin_4 | GPIO_Pin_5);
}

//#define PERIOD (MAIN_Fosc / 1000)
//PWMx_Duty dutyA;
//void	PWM_config(void)
//{
//    PWMx_InitDefine		PWMx_InitStructure;

//    // 配置PWM1
//    //  CCMRn_PWM_MODE1 和  CCMRn_PWM_MODE2 模式相反
//    PWMx_InitStructure.PWM_Mode    		= CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
//    PWMx_InitStructure.PWM_Duty    		= 0;	//PWM占空比时间, 0~Period
//    PWMx_InitStructure.PWM_EnoSelect    = ENO1P | ENO1N;	//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
//    PWM_Configuration(PWM1, &PWMx_InitStructure);

//    // 配置PWM2
//    //  CCMRn_PWM_MODE1 和  CCMRn_PWM_MODE2 模式相反
//    PWMx_InitStructure.PWM_Mode    		= CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
//    PWMx_InitStructure.PWM_Duty    		= 0;	//PWM占空比时间, 0~Period
//    PWMx_InitStructure.PWM_EnoSelect    = ENO2P | ENO2N;	//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
//    PWM_Configuration(PWM2, &PWMx_InitStructure);

//    // 配置PWM3
//    //  CCMRn_PWM_MODE1 和  CCMRn_PWM_MODE2 模式相反
//    PWMx_InitStructure.PWM_Mode    		= CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
//    PWMx_InitStructure.PWM_Duty    		= 0;	//PWM占空比时间, 0~Period
//    PWMx_InitStructure.PWM_EnoSelect    = ENO3P | ENO3N;	//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
//    PWM_Configuration(PWM3, &PWMx_InitStructure);

//    // 配置PWM4
//    //  CCMRn_PWM_MODE1 和  CCMRn_PWM_MODE2 模式相反
//    PWMx_InitStructure.PWM_Mode    		= CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
//    // 100%   高电平
//    PWMx_InitStructure.PWM_Duty    		= 0;	//PWM占空比时间, 0~Period
//    PWMx_InitStructure.PWM_EnoSelect    = ENO4P | ENO4N;	//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
//    PWM_Configuration(PWM4, &PWMx_InitStructure);

//    // 配置PWMA
//    PWMx_InitStructure.PWM_Period   = PERIOD - 1;			//周期时间,   0~65535
//    PWMx_InitStructure.PWM_DeadTime = 0;					//死区发生器设置, 0~255
//    PWMx_InitStructure.PWM_MainOutEnable= ENABLE;			//主输出使能, ENABLE,DISABLE
//    PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;			//使能计数器, ENABLE,DISABLE
//    PWM_Configuration(PWMA, &PWMx_InitStructure);			//初始化PWM通用寄存器,  PWMA,PWMB

//    // 切换PWM通道
//    PWM1_SW(PWM1_SW_P20_P21);
//    PWM2_SW(PWM2_SW_P22_P23);
//    PWM3_SW(PWM3_SW_P14_P15);
//    PWM4_SW(PWM4_SW_P26_P27);			//PWM4_SW_P16_P17,PWM4_SW_P26_P27,PWM4_SW_P66_P67,PWM4_SW_P34_P33

//    // 初始化PWMA的中断
//    NVIC_PWM_Init(PWMA,DISABLE,Priority_0);
//}

//延时  300ms  200ms  100ms
void Delay300ms()		//@24.000MHz
{
    unsigned char data i, j, k;

    _nop_();
    _nop_();
    i = 37;
    j = 135;
    k = 138;
    do
    {
        do
        {
            while (--k);
        } while (--j);
    } while (--i);
}

void Delay200ms()		//@24.000MHz
{
    unsigned char data i, j, k;

    _nop_();
    _nop_();
    i = 25;
    j = 90;
    k = 176;
    do
    {
        do
        {
            while (--k);
        } while (--j);
    } while (--i);
}


void Delay100ms()		//@24.000MHz
{
    unsigned char data i, j, k;

    _nop_();
    _nop_();
    i = 13;
    j = 45;
    k = 214;
    do
    {
        do
        {
            while (--k);
        } while (--j);
    } while (--i);
}



// 初始化
void Light_init() {
    //PWM配置
//    PWM_config();
    // IO配置
    GPIO_config();
    // 开关   0通，1断
    LED_SW = 0;
    LED1=1;
    LED2=1;
    LED3=1;
    LED4=1;
    LED5=1;
    LED6=1;
    LED7=1;
    LED8=1;
}
// 开前灯
void Light_on() {
    LED_F = 0;
}
// 关前灯
void Light_off() {
    LED_F = 1;
}

//跳舞灯  //考虑是否使用
void Dance_Light() {
//    int d = 0;
//    u8 i;


//    if (d >= 100) {
//        d = 100;
//    } else {
//        d += 5;
//    }
//    //外层逐渐变亮
//    dutyA.PWM1_Duty = d * PERIOD / 100.0;
//    dutyA.PWM2_Duty = d * PERIOD / 100.0;
//    dutyA.PWM3_Duty = d * PERIOD / 100.0;
//    dutyA.PWM4_Duty = d * PERIOD / 100.0;
//    UpdatePwm(PWMA, &dutyA);

}


//快速跑马灯
void Horse_Race_Light() {
    u8 i;
    for(i=0; i<=3; i++) {
        LED1=LED2=LED3=LED4=LED5=LED6=LED7=LED8=0;
        Delay100ms();
        LED1=LED2=LED3=LED4=LED5=LED6=LED7=LED8=1;
        Delay100ms();
    }

    for(i=0; i<2; i++) {
        LED1=0;
        Delay100ms();
        LED1=1;
        LED3=0;
        Delay100ms();
        LED3=1;
        LED5=0;
        Delay100ms();
        LED5=1;
        LED7=0;
        Delay100ms();
        LED7=1;
        LED2=0;
        Delay100ms();
        LED2=1;
        LED4=0;
        Delay100ms();
        LED4=1;
        LED6=0;
        Delay100ms();
        LED6=1;
        LED8=0;
        Delay100ms();
				LED8=1;
    }
    for(i=0; i<=3; i++) {
        LED1=LED2=LED3=LED4=LED5=LED6=LED7=LED8=0;
        Delay100ms();
        LED1=LED2=LED3=LED4=LED5=LED6=LED7=LED8=1;
        Delay100ms();
    }
		
    LED1=LED2= LED3= LED4= LED5= LED6= LED7= LED8=1;
}