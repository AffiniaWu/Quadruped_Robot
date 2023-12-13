#ifndef _PCA9685_SERVO_DRIVER_H
#define _PCA9685_SERVO_DRIVER_H


#include "Config.h"


typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;

#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4

#define I2C_ADDR  				0x80       //i2c address
#define PCA9685_MODE1 		0x00
#define PCA9685_PRESCALE 	0xFE

#define LED0_ON_L 	0x06
#define LED0_ON_H 	0x07
#define LED0_OFF_L 	0x08
#define LED0_OFF_H 	0x09

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD


#define SERVO_UP_MAX  145    //The upper servo's max degree
#define SERVO_UP_MIN  15     //The upper servo's min degree
#define SERVO_DOWN_MAX  180  //The under servo's max degree
#define SERVO_DOWN_MIN  0        //The under servo's min degree
#define STEP  1              //The step value
#define STEP_DELAY   2        //Delay time(ms) every step
#define SERVO_UP_CH  0       //The upper servo Channel
#define SERVO_DOWN_CH  1     //The under servo Channel

extern uint8_t ServoUpDegree;
extern uint8_t ServoDownDegree;

void PCA9685_reset(void);
void PCA9685_init();
void PCA9685_setPWMFreq(float freq);
void PCA9685_setPWM(uint8_t num, uint16_t on, uint16_t off);
void PCA9685_Pin(uint8_t num, uint16_t val, Bool invert);
void setServoPulse(uint8_t n, double pulse);
void setServoDegree(uint8_t n, uint8_t Degree);
int ServoDegreeDecrease(uint8_t Channel, uint8_t Step);
int ServoDegreeIncrease(uint8_t Channel, uint8_t Step);

unsigned char wrSensorReg8_8(u8 regID, u8 regDat);
unsigned char rdSensorReg8_8(u8 regID, u8* regDat);

#endif