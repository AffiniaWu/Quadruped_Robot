#ifndef __BATTERY_H__
#define __BATTERY_H__

#include "Config.h"

#define INIT_GPIO		GPIO_P0
#define INIT_GPIO_PIN	GPIO_Pin_1
#define ADC_CHANNEL		ADC_CH9

// ��ʼ��
void Battery_init();
// ��ȡ��ص�ѹ
float Battery_get_voltage();

#endif