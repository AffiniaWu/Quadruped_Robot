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

// ��ʼ��
void Robot_init();

//ŤѽŤ
void Robot_dance();

//ſ��
void Robot_down();

//վ��
void Robot_up();

//���к�
void Robot_sayHi();

//��ǰ
void Robot_forward();

//���
void Robot_backward();

//����
void Robot_left();

//����
void Robot_right();

//��ת
void Robot_turn_around();

//ֹͣ
void Robot_stop();


#endif