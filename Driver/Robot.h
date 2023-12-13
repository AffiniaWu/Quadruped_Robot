#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "Config.h"
#include "PCA9685_servo.h"
#include "NVIC.h"
#include "Switch.h"
#include "Config.h"
#include "GPIO.h"
#include "UART.h"
#include "EXTI.h"

// 初始化
void Robot_init();

//扭呀扭
void Robot_dance();

//趴下
void Robot_down();

//站立
void Robot_up();

//打招呼
void Robot_sayHi();

//向前
void Robot_forward();

//向后
void Robot_backward();

//向左
void Robot_left();

//向右
void Robot_right();

//旋转
void Robot_turn_around();

//停止
void Robot_stop();


#endif