#include "PCA9685_servo.h"
#include "GPIO.h"
//#include "I2C.h"
#include "Soft_I2C.h"
#include "Delay.h"

double floor(double x) {
    int integerPart = (int)x;
    return (double)integerPart;
}
static void GPIO_config(void) {
    GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
    GPIO_InitStructure.Pin  = GPIO_Pin_2 | GPIO_Pin_3;		//指定要初始化的IO,
    GPIO_InitStructure.Mode = GPIO_OUT_OD;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);//初始化
}
/****************  I2C初始化函数 *****************/
//void	I2C_config(void)
//{
//    I2C_InitTypeDef		I2C_InitStructure;

//    I2C_InitStructure.I2C_Mode      = I2C_Mode_Master;	//主从选择   I2C_Mode_Master, I2C_Mode_Slave
//    I2C_InitStructure.I2C_Enable    = ENABLE;			//I2C功能使能,   ENABLE, DISABLE
//    I2C_InitStructure.I2C_MS_WDTA   = DISABLE;			//主机使能自动发送,  ENABLE, DISABLE
//    I2C_InitStructure.I2C_Speed     = 13;				//总线速度=Fosc/2/(Speed*2+4),      0~63
//    // 400k, 24M => 13
//    I2C_Init(&I2C_InitStructure);
//    NVIC_I2C_Init(I2C_Mode_Master,DISABLE,Priority_0);	//主从模式, I2C_Mode_Master, I2C_Mode_Slave; 中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3

//    I2C_SW(I2C_P33_P32);					//I2C_P14_P15,I2C_P24_P25,I2C_P33_P32
//}

/**************************************************************************/
/*!
    @brief  Initial the I2C interface and hardware
*/
/**************************************************************************/
void PCA9685_init() {
//    sccb_bus_init();
    GPIO_config();
//    I2C_config();

    PCA9685_reset();
    // set a default frequency
    PCA9685_setPWMFreq(60);
}


/**************************************************************************/
/*!
    @brief  Sends a reset command to the PCA9685 chip over I2C
*/
/**************************************************************************/
void PCA9685_reset(void) {
    delay_ms(10);
//    wrSensorReg8_8(PCA9685_MODE1, 0x80);
    wrSensorReg8_8(PCA9685_MODE1, 0x00);
    delay_ms(10);
}

/**************************************************************************/
/*!
    @brief  Sets the PWM frequency for the entire chip, up to ~1.6 KHz
    @param  freq Floating point frequency that we will attempt to match
*/
/**************************************************************************/
void PCA9685_setPWMFreq(float freq) {
    uint8_t oldmode;
    uint8_t newmode;
    uint8_t prescale ;
    //PCA9685的内部时钟频率是25Mhz
    double prescaleval = 25000000;
    // 公式: presale_Volue = round(25000000/(4096 * freq) ) - 1
    // freq *= 0.9;  // Correct for overshoot in the frequency setting.
    prescaleval /= 4096;
    prescaleval /= freq;
    prescaleval -= 1;
    prescale = (u8)(floor(prescaleval + 0.5));

    rdSensorReg8_8(PCA9685_MODE1, &oldmode);
    newmode = (oldmode&0x7F) | 0x10; // sleep
    wrSensorReg8_8(PCA9685_MODE1, newmode); // go to sleep
    wrSensorReg8_8(PCA9685_PRESCALE, prescale); // set the prescaler
    // 重新复位
    wrSensorReg8_8(PCA9685_MODE1, oldmode);
    // 等待复位完成
    delay_ms(5);
    //设置MODE1寄存器开启自动递增
    wrSensorReg8_8(PCA9685_MODE1, oldmode | 0xa1);  //  This sets the MODE1 register to turn on auto increment. 0xa0关闭，0xa1开启
}

/**************************************************************************/
/*!
    @brief  Sets the PWM output of one of the PCA9685 pins
    @param  num One of the PWM output pins, from 0 to 15
    @param  on At what point in the 4096-part cycle to turn the PWM output ON
    @param  off At what point in the 4096-part cycle to turn the PWM output OFF
*/
/**************************************************************************/
void PCA9685_setPWM(uint8_t num, uint16_t on, uint16_t off) {
    wrSensorReg8_8(LED0_ON_L + 4*num, on);
    wrSensorReg8_8(LED0_ON_L + 4*num + 1, on>>8);
    wrSensorReg8_8(LED0_ON_L + 4*num + 2, off);
    wrSensorReg8_8(LED0_ON_L + 4*num + 3, off>>8);
}

/**************************************************************************/
/*!
    @brief  Helper to set pin PWM output. Sets pin without having to deal with on/off tick placement and properly handles a zero value as completely off and 4095 as completely on.  Optional invert parameter supports inverting the pulse for sinking to ground.
    @param  num One of the PWM output pins, from 0 to 15
    @param  val The number of ticks out of 4096 to be active, should be a value from 0 to 4095 inclusive.
    @param  invert If true, inverts the output, defaults to 'false'
*/
/**************************************************************************/
void PCA9685_setPin(uint8_t num, uint16_t val, Bool invert)
{
    // Clamp value between 0 and 4095 inclusive.
    //val = min(val, (uint16_t)4095);
    (val < (uint16_t)4095) ? (val = val): (val = (uint16_t)4095);
    if (invert) {
        if (val == 0) {
            // Special value for signal fully on.
            PCA9685_setPWM(num, 4096, 0);
        }
        else if (val == 4095) {
            // Special value for signal fully off.
            PCA9685_setPWM(num, 0, 4096);
        }
        else {
            PCA9685_setPWM(num, 0, 4095-val);
        }
    }
    else {
        if (val == 4095) {
            // Special value for signal fully on.
            PCA9685_setPWM(num, 4096, 0);
        }
        else if (val == 0) {
            // Special value for signal fully off.
            PCA9685_setPWM(num, 0, 4096);
        }
        else {
            PCA9685_setPWM(num, 0, val);
        }
    }
}
/**************************************************************************/
/*!
    @brief  Set the pulse width of servo.
    @param  PWM output channal.
    @param  Pulse width(seconds)
*/
/**************************************************************************/
void setServoPulse(uint8_t n, double pulse) {
    double pulselength;

    pulselength = 1000;   // 1,000 ms per second
    pulselength /= 60;   // 60 Hz
    pulselength /= 4096;
    pulse *= 1000; //ms
    pulse /= pulselength;
    PCA9685_setPWM(n, 0, pulse);
}
/**************************************************************************/
/*!
    @brief  Set the rotation degree of the servo.
    @param  PWM output channel.
    @param  Degree.
*/
/**************************************************************************/
void setServoDegree(uint8_t n, uint8_t Degree) {
    double pulse;
    if(Degree >= 180) {
        Degree = 180;
    }
    else if(Degree <= 0) {
        Degree = 0;
    }
    pulse = (Degree + 45) / (90.0 * 1000);
    setServoPulse(n, pulse);
}


/**************************************************************************/
/*!
    @brief  Write 8bits data to sensor address.
    @param  Register address.
    @param  Write data.
*/
/**************************************************************************/
unsigned char wrSensorReg8_8(u8 regID, u8 regDat)
{
    SI2C_WriteNbyte(I2C_ADDR, regID, &regDat, 1);
    return 0;
}

/**************************************************************************/
/*!
    @brief  Read 8bits data from sensor address.
    @param  Register address.
    @param  Read data.
*/
/**************************************************************************/
unsigned char rdSensorReg8_8(u8 regID, u8* regDat)
{
    SI2C_ReadNbyte(I2C_ADDR, regID, regDat, 1);
    return 0;
}