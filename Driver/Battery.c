#include    "Battery.h"
#include    "GPIO.h"
#include	"ADC.h"
#include	"NVIC.h"

static void GPIO_config(void) {
	GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
	GPIO_InitStructure.Pin  = INIT_GPIO_PIN;		//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_HighZ;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(INIT_GPIO, &GPIO_InitStructure);//初始化
}

/******************* AD配置函数 *******************/
static void	ADC_config(void)
{
	ADC_InitTypeDef		ADC_InitStructure;		//结构定义

	ADC_InitStructure.ADC_SMPduty   = 31;		//ADC 模拟信号采样时间控制, 0~31（注意： SMPDUTY 一定不能设置小于 10）
	ADC_InitStructure.ADC_CsSetup   = 0;		//ADC 通道选择时间控制 0(默认),1
	ADC_InitStructure.ADC_CsHold    = 1;		//ADC 通道选择保持时间控制 0,1(默认),2,3
	ADC_InitStructure.ADC_Speed     = ADC_SPEED_2X1T;		//设置 ADC 工作时钟频率	ADC_SPEED_2X1T~ADC_SPEED_2X16T
	ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC结果调整,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
	ADC_Inilize(&ADC_InitStructure);		//初始化
	ADC_PowerControl(ENABLE);				//ADC电源开关, ENABLE或DISABLE
	NVIC_ADC_Init(DISABLE,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
}

// 初始化
void Battery_init() {
    GPIO_config();
    
    ADC_config();

}

// 获取电池电压
float Battery_get_voltage() {
    u16 adc_value;
    float vol;
    // 读采样值
    adc_value = Get_ADCResult(ADC_CHANNEL);
    // 转换为电压
    vol =  adc_value * 2.5 / 4096;
    
    // 电池8.19   vcc 7.5V
    
    // 返回  0.6 二极管的压差
    return vol * 3 + 0.6;
}