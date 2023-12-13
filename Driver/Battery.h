#ifndef __BATTERY_H__
#define __BATTERY_H__

#include "Config.h"

#define INIT_GPIO		GPIO_P0
#define INIT_GPIO_PIN	GPIO_Pin_1
#define ADC_CHANNEL		ADC_CH9

// 初始化
void Battery_init();
// 获取电池电压
float Battery_get_voltage();

#endif