#ifndef __BUZZER_H__
#define __BUZZER_H__

#include "Config.h"

// 初始化
void Buzzer_init();

// 按照指定频率播放
void Buzzer_play(u16 hz_value);

// 按照指定音节播放
void Buzzer_beep(u8 hz_value_index);

// 停止播放
void Buzzer_stop();


#endif