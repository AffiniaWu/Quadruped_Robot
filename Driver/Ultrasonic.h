#ifndef __ULTRISONIC_H__
#define __ULTRISONIC_H__

#include "Config.h"

// trig����Ƭ�������źţ����ٳ�������ģ��ȥ���
// echo�����ٳ�������ģ����Ӧ�ź�
#define 	PIN_TRIG		P13
#define 	PIN_ECHO		P40

//��ʼ��
void Ultrasonic_init();

// ����ֵΪchar����Ϊ�и���������ͬ��״̬
char Ultrasonic_get_distance(float *distance);

#endif