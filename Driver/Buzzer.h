#ifndef __BUZZER_H__
#define __BUZZER_H__

#include "Config.h"

// ��ʼ��
void Buzzer_init();

// ����ָ��Ƶ�ʲ���
void Buzzer_play(u16 hz_value);

// ����ָ�����ڲ���
void Buzzer_beep(u8 hz_value_index);

// ֹͣ����
void Buzzer_stop();


#endif