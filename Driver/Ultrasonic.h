#ifndef __ULTRISONIC_H__
#define __ULTRISONIC_H__

#include "Config.h"

// trig：单片机发送信号，高速超声波的模组去测距
// echo：高速超声波的模组响应信号
#define 	PIN_TRIG		P13
#define 	PIN_ECHO		P40

//初始化
void Ultrasonic_init();

// 返回值为char，因为有负数，代表不同的状态
char Ultrasonic_get_distance(float *distance);

#endif