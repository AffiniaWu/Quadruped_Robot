#include "Ultrasonic.h"
#include "GPIO.h"

static void GPIO_config(void) {
    // trig 准双向
    GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
    GPIO_InitStructure.Pin  = GPIO_Pin_3;		//指定要初始化的IO,
    GPIO_InitStructure.Mode = GPIO_PullUp;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_Inilize(GPIO_P1, &GPIO_InitStructure);//初始化
    // echo 高阻输入
    GPIO_InitStructure.Pin  = GPIO_Pin_0;		//指定要初始化的IO,
    GPIO_InitStructure.Mode = GPIO_HighZ;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_Inilize(GPIO_P4, &GPIO_InitStructure);//初始化
}


//软件实现延时，用来计算高低电平时间
static void Delay10us(void)	//@24.000MHz
{
    unsigned char data i;
    i = 78;
    while (--i);
}



//对外函数1：初始化
void Ultrasonic_init() {
    GPIO_config();
    PIN_TRIG = 0; // 初始状态先给一个低电平
}

//对外函数2： 返回值为char，因为有负数，代表不同的状态
char Ultrasonic_get_distance(float *distance) {
    float dis; //距离
    u16 cnt = 0;  //用来进行累计计算
    
	// 1. 至少给trig 10us高电平时间，再拉低，这里给20us
    PIN_TRIG = 1;
    Delay10us();
    Delay10us();
    PIN_TRIG = 0;

    // 2. 计算echo低电平的时间，大概197us左右
    // 当echo变高电平时，退出循环
    // 假如 超过 30 * 10 = 300us都没有变为高电平，也要退出循环
    do {
        cnt ++;
        Delay10us();
    } while(PIN_ECHO == 0 && cnt < 30);

    if (cnt >= 30) {
        printf("超时：%d us\n", (int)cnt * 10);
        return -1;
    }

    // 3. 计算echo高电平时间
    cnt = 0;
    do {
        cnt ++;
        Delay10us();
    } while(PIN_ECHO == 1);

/* 
		4. 计算距离		
		
		测距范围： 2cm ~ 400 cm 
		转换过程：
		340m/s ===>34 cm / ms
		dis = (34 cm / ms * ms单位的时间) / 2
		dis = 34 *  (cnt * 10) * 0.001  * 0.5
*/		
    dis = 34 * cnt * 0.01  * 0.5;

 
// 不在2cm~400cm范围测距，数据混乱，没有这种判断也一样    
//    if (dis < 2) {
//        return -2;
//    } else if (dis > 400) {
//        return -3;
//    }
    
    *distance = dis; //将计算转换好的距离 赋值到距离参数中

    return 0;
}

