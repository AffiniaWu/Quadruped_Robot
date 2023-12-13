#include 			"Config.h"
#include 			"GPIO.h"
#include 			"UART.h"
#include 			"EXTI.h"
#include 			"NVIC.h"
#include 			"Switch.h"
#include 			"STC8H_PWM.h"
#include		  "PCA9685_servo.h"	//16位舵机
#include 			"Light.h"					//灯光
#include			"Ultrasonic.h" 		//超声波
//#include      "Battery.h"     	//电源检测



#define TASK_UART1	1
#define TASK_UART2	2

u8 order;//全局变量，用于给同一任务不同动作

// 简谱
u8 notes[] = {
    1, 1, 2, 3, 4,5,6,5,4, 3, 2,1,8,8
};

// 音长
u8 durations[] = {
    4, 1,1,1,1,1,1,1,1,1,1,2,2,2
};

u16 hz[] = {
    523 * 1, 587 * 1, 659 * 1, 698 * 1, 784 * 1, 880 * 1, 988 * 1,
    523 * 2, 587 * 2, 659 * 2, 698 * 2, 784 * 2, 880 * 2, 988 * 2,
    523 * 4, 587 * 4, 659 * 4, 698 * 4, 784 * 4, 880 * 4, 988 * 4,
    523 * 8, 587 * 8, 659 * 8, 698 * 8, 784 * 8, 880 * 8, 988 * 8,
};

void GPIO_config() {
    //准双向口	uart1: P30 P31
    P3_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);

    //准双向口	uart2: P10 P11
    P1_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);
	
	//语音模块 uaer3: P50 P51
		P5_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);

    // 蓝牙 en引脚 P03
    P0_MODE_IO_PU( GPIO_Pin_3);

    //ADC采集
    P0_MODE_IN_HIZ(GPIO_Pin_1);

    //蜂鸣器
    P0_MODE_OUT_PP(GPIO_Pin_0);
}

//void	ADC_config(void)
//{
//    ADC_InitTypeDef		ADC_InitStructure;		//结构定义

//    ADC_InitStructure.ADC_SMPduty   = 31;		//ADC 模拟信号采样时间控制, 0~31（注意： SMPDUTY 一定不能设置小于 10）
//    ADC_InitStructure.ADC_CsSetup   = 0;		//ADC 通道选择时间控制 0(默认),1
//    ADC_InitStructure.ADC_CsHold    = 1;		//ADC 通道选择保持时间控制 0,1(默认),2,3
//    ADC_InitStructure.ADC_Speed     = ADC_SPEED_2X1T;		//设置 ADC 工作时钟频率	ADC_SPEED_2X1T~ADC_SPEED_2X16T
//    ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC结果调整,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
//    ADC_Inilize(&ADC_InitStructure);		//初始化
//    ADC_PowerControl(ENABLE);				//ADC电源开关, ENABLE或DISABLE
//    NVIC_ADC_Init(DISABLE,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
//}

void UART_config(void) {
    COMx_InitDefine		COMx_InitStructure;								//结构定义
    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//选择波特率发生器, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;				//波特率, 一般 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;					//接收允许,   ENABLE或DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;				//波特率加倍, ENABLE或DISABLE
    UART_Configuration(UART1, &COMx_InitStructure);			//初始化串口1 UART1,UART2,UART3,UART4

    NVIC_UART1_Init(ENABLE,Priority_1);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
    UART1_SW(UART1_SW_P30_P31);						// 引脚选择, UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44

    // uart2 蓝牙
    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;			//选择波特率发生器, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 9600ul;			//波特率, 一般 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//波特率加倍, ENABLE或DISABLE
    UART_Configuration(UART2, &COMx_InitStructure);		//初始化串口1 UART1,UART2,UART3,UART4

    NVIC_UART2_Init(ENABLE,Priority_1);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
    UART2_SW(UART2_SW_P10_P11);		// 引脚选择, UART2_SW_P10_P11,UART2_SW_P46_P47

    //uart3 语音
		COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer3;			//选择波特率发生器, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 9600ul;			//波特率, 一般 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//波特率加倍, ENABLE或DISABLE
    UART_Configuration(UART3, &COMx_InitStructure);		//初始化串口1 UART1,UART2,UART3,UART4

  	NVIC_UART3_Init(ENABLE,Priority_1);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
    UART3_SW(UART3_SW_P50_P51);		// 引脚选择, UART3_SW_P00_P01,UART3_SW_P50_P51
}

void Buzzer_play(u16 hz_value) {

    PWMx_InitDefine		PWMx_InitStructure;
    u16 Period = MAIN_Fosc / hz_value;

    // 配置PWM5
    PWMx_InitStructure.PWM_Mode    		= CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    PWMx_InitStructure.PWM_Duty   	 	= (u16)(Period * 0.5);	//PWM占空比时间, 0~Period
    PWMx_InitStructure.PWM_EnoSelect    = ENO5P;			//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWM_Configuration(PWM5, &PWMx_InitStructure);			//初始化PWM,  PWMA,PWMB

    // 配置PWMB
    PWMx_InitStructure.PWM_Period   = Period - 1;			//周期时间,   0~65535
    PWMx_InitStructure.PWM_DeadTime = 0;					//死区发生器设置, 0~255
    PWMx_InitStructure.PWM_MainOutEnable= ENABLE;			//主输出使能, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;			//使能计数器, ENABLE,DISABLE
    PWM_Configuration(PWMB, &PWMx_InitStructure);			//初始化PWM通用寄存器,  PWMA,PWMB

    // 切换PWM通道
    PWM5_SW(PWM5_SW_P00);					//PWM5_SW_P20,PWM5_SW_P17,PWM5_SW_P00,PWM5_SW_P74

    // 初始化PWMB的中断
    NVIC_PWM_Init(PWMB,DISABLE,Priority_0);
}

// 按照指定音节播放 1 2 3 4 5 6 7 8
void Buzzer_beep(u8 hz_value_index) {
    u16 hz_value = hz[hz_value_index - 1];
    Buzzer_play(hz_value);
}

// 停止播放
void Buzzer_stop() {
    PWMx_InitDefine		PWMx_InitStructure;
    PWMx_InitStructure.PWM_MainOutEnable= DISABLE;			//主输出使能, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable   = DISABLE;			//使能计数器, ENABLE,DISABLE
    PWM_Configuration(PWMB, &PWMx_InitStructure);			//初始化PWM通用寄存器,  PWMA,PWMB
}

//根据接收到的内容，进行特定动作
void do_work (u8 dat) {
    if(dat == 0x20) {  //扭呀扭
        os_create_task(3);
        os_create_task(15);
        os_create_task(5);
    } else if(dat ==0x02) { //趴下
        order = dat;
        os_create_task(4);
    } else if(dat ==0x01) { //站立
        order = dat;
        os_create_task(4);
    } else if(dat ==0x21) { //打招呼
        os_create_task(6);
    } else if(dat ==0x12) { //开灯
        order = dat;
        os_create_task(7);
    } else if(dat ==0x13) { //关灯
        order = dat;
        os_create_task(7);
    } else if(dat ==0x10) { //向前
        os_create_task(9);
        os_create_task(8);
    } else if(dat ==0x11) { //向后
        os_create_task(10);
    } else if(dat ==0x03) { //向左
        order = dat;
        os_create_task(11);
    } else if(dat ==0x04) { //向右
        order = dat;
        os_create_task(11);
    } else if(dat ==0x05) { //旋转
        os_create_task(13);
    } else if(dat == 0x00) { //停止
        os_create_task(14);
    }
}

//初始化形态
void posture_init() {
    setServoDegree(1, 135);
    setServoDegree(3, 45);
    setServoDegree(5, 135);
    setServoDegree(7, 45);
    setServoDegree(0, 45);
    setServoDegree(2, 135);
    setServoDegree(4, 45);
    setServoDegree(6, 135);
    os_wait2(K_TMO, 50);
}

void sys_init() {
    //扩展寄存器访问使能
    EAXSFR();
    //GPIO初始化
    GPIO_config();
    // ADC_config();
    //UART初始化
    UART_config();
    //PCA9685模块初始化
    PCA9685_init();
    //led灯初始化
    Light_init();
    //中断启动
    EA = 1;
    //机器人运动初始化
    posture_init();
    //超声波模块初始化
    Ultrasonic_init();
    //电源检测初始化
    //Battery_init();

    printf("init complete\n");
}

void task_main() _task_ 0 {
    u8 i=0;
    //系统初始化
    sys_init();
    //创建任务 1和2 用于蓝牙传输  任务12是语音模块
    os_create_task(TASK_UART1);
    os_create_task(TASK_UART2);
		os_create_task(12);
    //输入初始值，以免代码出错
    order=0x00;
    //删除任务0
    os_delete_task(0);
}

//使用蓝牙
// uart1收到数据，通过uart2发出去
void task1() _task_ TASK_UART1 {

    u8 i;
    while (1) {
        if(COM1.RX_TimeOut > 0) {
            //超时计数
            if(--COM1.RX_TimeOut == 0) {
                if(COM1.RX_Cnt > 0) {
                    for(i=0; i<COM1.RX_Cnt; i++)	{
                        TX2_write2buff(RX1_Buffer[i]);
                    }
                }
                COM1.RX_Cnt = 0;
            }
        }
        os_wait2(K_TMO, 4);  // 5ms * 4
    }
}

// uart2收到数据，通过uart1发出去
void task2() _task_ TASK_UART2 {
    u8 i;
    while (1) {
        if(COM2.RX_TimeOut > 0) {
            //超时计数
            if(--COM2.RX_TimeOut == 0) {
                if(COM2.RX_Cnt > 0) {
                    for(i=0; i<COM2.RX_Cnt; i++)	{
                        do_work(RX2_Buffer[i]);
                        TX1_write2buff(RX2_Buffer[i]);
                    }
                }
                COM2.RX_Cnt = 0;
            }
        }
        os_wait2(K_TMO, 4);  // 5ms * 4
    }
}

//任务3是扭呀扭
void task3() _task_ 3 {
    u8 c=0,d=0,e=0;
    //关闭其他动作
		os_delete_task(4);
    os_delete_task(6);
    os_delete_task(7);
    os_delete_task(8);
    os_delete_task(9);
    os_delete_task(10);
    os_delete_task(11);
    os_delete_task(13);
		//初始化原始形态
    posture_init();
    //上方脚
    while(c<2) {
        setServoDegree(1, 180);
        setServoDegree(3, 90);
        setServoDegree(5, 180);
        setServoDegree(7, 90);

        os_wait2(K_TMO, 50);

        setServoDegree(1, 135);
        setServoDegree(3, 45);
        setServoDegree(5, 135);
        setServoDegree(7, 45);
        os_wait2(K_TMO, 50);
        c=c+1;
    }
    while(d<2) {
        setServoDegree(1, 90);
        setServoDegree(3, 0);
        setServoDegree(5, 90);
        setServoDegree(7, 0);
        os_wait2(K_TMO, 50);

        setServoDegree(1, 135);
        setServoDegree(3, 45);
        setServoDegree(5, 135);
        setServoDegree(7, 45);
        os_wait2(K_TMO, 50);
        d=d+1;
    }
    //下方脚
    while(e<2) {
        setServoDegree(0, 90);
        setServoDegree(2, 90);
        setServoDegree(4, 90);
        setServoDegree(6, 90);

        os_wait2(K_TMO, 50);

        setServoDegree(0, 45);
        setServoDegree(2, 135);
        setServoDegree(4, 45);
        setServoDegree(6, 135);
        os_wait2(K_TMO, 50);
        e=e+1;
    }

    os_delete_task(3);
}

//任务4是站立/趴下
void task4() _task_ 4 {
	    //关闭其他动作
		os_delete_task(3);
    os_delete_task(5);
    os_delete_task(6);
    os_delete_task(8);
    os_delete_task(9);
    os_delete_task(10);
    os_delete_task(11);
    os_delete_task(13);
    os_delete_task(15);
    if(order == 0x01) { //站立
        setServoDegree(0, 45);
        setServoDegree(2, 135);
        setServoDegree(4, 45);
        setServoDegree(6, 135);
        os_wait2(K_TMO, 50);
    } else if(order == 0x02) { //趴下
        //初始化原始形态
        posture_init();
        setServoDegree(0, 90);
        setServoDegree(2, 90);
        setServoDegree(4, 90);
        setServoDegree(6, 90);
        os_wait2(K_TMO, 50);
    }

    os_delete_task(4);
}

//任务5是ADC监测电压----修改成 蜂鸣器
void task5() _task_ 5 {
//    float vol;
//    u8 i;
//    u16 adc_value;
//	    printf("1111111111111");
//    // 读采样值
//    adc_value = Get_ADCResult(ADC_CH9);
//    // 转换为电压
//    vol =  adc_value * 2.5 / 4096;
//    // 电池8.19   vcc 7.5V
//    // 返回  0.6 二极管的压差
//    vol = vol * 4 + 0.6;
//    printf("vol = %.2f\n", vol);
//	if(vol < 3){
//			//电压过低 执行操作
//
//		for(i=0;i<3;i++){
//			 Horse_Race_Light();
//		}
//		os_create_task(15);
//	}

    //os_wait2(K_TMO, 200);  // 5ms * 2000 =10s


    //蜂鸣器
    u16 len = sizeof(notes) / sizeof(notes[0]);
    u8 i;
    for(i = 0; i < len; i++) {
        Buzzer_beep(notes[i]);
        os_wait2(K_TMO, durations[i] * 20); // durations[i]*100

        Buzzer_stop();
        os_wait2(K_TMO, 4);
    }
    // stop
    Buzzer_stop();
    os_wait2(K_TMO, 200);
    os_delete_task(5);
}

//任务6是打招呼
void task6() _task_ 6 {
	   //关闭其他动作
	  os_delete_task(3);
		os_delete_task(4);
    os_delete_task(5);
    os_delete_task(8);
    os_delete_task(9);
    os_delete_task(10);
    os_delete_task(11);
    os_delete_task(13);
    os_delete_task(15);
    //初始化原始形态
    posture_init();
    setServoDegree(1, 180);
    setServoDegree(3, 0);

    setServoDegree(0, 180);
    os_wait2(K_TMO, 50);
    setServoDegree(0, 135);
    os_wait2(K_TMO, 50);
    setServoDegree(0, 180);
    os_wait2(K_TMO, 50);
    setServoDegree(0, 135);

    os_wait2(K_TMO, 100);
    setServoDegree(1, 135);
    os_wait2(K_TMO, 50);
    setServoDegree(0, 180);
    os_wait2(K_TMO, 50);
    setServoDegree(0, 135);
    os_wait2(K_TMO, 50);
    setServoDegree(0, 180);
    os_wait2(K_TMO, 50);
    setServoDegree(0, 135);
    os_wait2(K_TMO, 50);
    //恢复原样
    setServoDegree(0, 45);
    setServoDegree(3, 45);

    os_delete_task(6);
}

//任务7是开灯/关灯
void task7() _task_ 7 {
    if(order == 0x12) {
        //开灯
        Light_on();
        os_wait2(K_TMO, 100);
        os_delete_task(7);
    } else if (order == 0x13) {
        //关灯
        Light_off();
        os_wait2(K_TMO, 100);
        os_delete_task(7);
    }

    os_delete_task(7);
}

//任务8是超声波测距
void task8() _task_ 8 {
    float distance;
    char res;
    while(1) {
        res = Ultrasonic_get_distance(&distance);
        if (res == 0 && distance > 10 ) {
            printf("距离为：%.2f cm\n", distance);
        } else if(res == -1) {
            printf("res = %d\n", (int)res);
        } else if(res == 0 && distance <= 10 ) {
            //如果小于目标距离，就销毁前进任务9 os_delete_task(9);
            os_delete_task(12);
            os_delete_task(10);
            os_delete_task(11);
            os_delete_task(9);
            //将机器人恢复成初始状态
            os_wait2(K_TMO, 50);
            posture_init();
            os_wait2(K_TMO, 50);
            //销毁测距任务8
            os_delete_task(8);
        }
        os_wait2(K_TMO, 50);
    }
}

//任务9是向前
void task9() _task_ 9 {
    u8 i,j;
	    //关闭其他动作
	  os_delete_task(3);
		os_delete_task(4);
    os_delete_task(5);
    os_delete_task(6);
    os_delete_task(10);
    os_delete_task(11);
    os_delete_task(13);
    os_delete_task(15);
    //初始化前进姿态
    setServoDegree(1, 180);
    setServoDegree(3, 0);
    setServoDegree(5, 180);
    setServoDegree(7, 0);

    setServoDegree(0, 45);
    setServoDegree(2, 135);
    setServoDegree(4, 45);
    setServoDegree(6, 135);

    //运动模式
    for(j=0; j<3; j++) {
        //右脚先行
        for(i=1; i<=45; i++) {
            setServoDegree(0, 45+i);
            setServoDegree(4, 45-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);
        for(i=1; i<=45; i++) {
            setServoDegree(2, 135+i);
            setServoDegree(6, 135-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);
        for(i=1; i<=45; i++) {
            setServoDegree(0, 90-i);
            setServoDegree(4, 0+i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);
        for(i=1; i<=45; i++) {
            setServoDegree(2, 180-i);
            setServoDegree(6, 90+i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 20);

        //交替到左脚先行
        for(i=1; i<=45; i++) {
            setServoDegree(2, 135-i);
            setServoDegree(6, 135+i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);
        for(i=1; i<=45; i++) {
            setServoDegree(0, 45-i);
            setServoDegree(4, 45+i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);
        for(i=1; i<=45; i++) {
            setServoDegree(2, 90+i);
            setServoDegree(6, 180-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);
        for(i=1; i<=45; i++) {
            setServoDegree(0, 0+i);
            setServoDegree(4, 90-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 20);
    }
    os_delete_task(8);//向前行动结束的时候，关闭任务8的测距任务
    os_delete_task(9);
}

//任务10是向后
void task10() _task_ 10 {
    u8 i,j;
	    //关闭其他动作
	  os_delete_task(3);
		os_delete_task(4);
    os_delete_task(5);
    os_delete_task(6);
    os_delete_task(8);
    os_delete_task(9);
    os_delete_task(11);
    os_delete_task(13);
    os_delete_task(15);
    //初始化原始形态
    setServoDegree(1, 180);
    setServoDegree(3, 0);
    setServoDegree(5, 180);
    setServoDegree(7, 0);

    setServoDegree(0, 45);
    setServoDegree(2, 135);
    setServoDegree(4, 45);
    setServoDegree(6, 135);
    //运动模式
    for(j=0; j<3; j++) {
        //向后 右脚先行
        for(i=1; i<=45; i++) {
            setServoDegree(4, 45+i);
            setServoDegree(0, 45-i);
            os_wait2(K_TMO, 1);
        }
        for(i=1; i<=45; i++) {
            setServoDegree(6, 135+i);
            setServoDegree(2, 135-i);
            os_wait2(K_TMO, 1);
        }
        for(i=1; i<=45; i++) {
            setServoDegree(4, 90-i);
            setServoDegree(0, 0+i);
            os_wait2(K_TMO, 1);
        }
        for(i=1; i<=45; i++) {
            setServoDegree(6, 180-i);
            setServoDegree(2, 90+i);
            os_wait2(K_TMO, 1);
        }
        //左脚先行
        for(i=1; i<=45; i++) {
            setServoDegree(6, 135-i);
            setServoDegree(2, 135+i);
            os_wait2(K_TMO, 1);
        }
        for(i=1; i<=45; i++) {
            setServoDegree(4, 45-i);
            setServoDegree(0, 45+i);
            os_wait2(K_TMO, 1);
        }
        for(i=1; i<=45; i++) {
            setServoDegree(6, 90+i);
            setServoDegree(2, 180-i);
            os_wait2(K_TMO, 1);
        }
        for(i=1; i<=45; i++) {
            setServoDegree(4, 0+i);
            setServoDegree(0, 90-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 20);
    }

    os_delete_task(10);
}

//任务11是向左/向右
void task11() _task_ 11 {
    u8 i;
	    //关闭其他动作
	  os_delete_task(3);
		os_delete_task(4);
    os_delete_task(5);
    os_delete_task(6);
    os_delete_task(8);
    os_delete_task(9);
    os_delete_task(10);
    os_delete_task(13);
    os_delete_task(15);
    //初始化原始形态
    setServoDegree(1, 180);
    setServoDegree(3, 0);
    setServoDegree(5, 180);
    setServoDegree(7, 0);

    setServoDegree(0, 45);
    setServoDegree(2, 135);
    setServoDegree(4, 45);
    setServoDegree(6, 135);
    if(order == 0x03) {
        //向左
        for(i=1; i<=45; i++) {
            setServoDegree(2, 135+i);
            setServoDegree(6, 135+i);
            os_wait2(K_TMO, 1);
        }
        for(i=1; i<=45; i++) {
            setServoDegree(0, 45-i);
            setServoDegree(4, 45-i);
            os_wait2(K_TMO, 1);
        }
        for(i=1; i<=45; i++) {
            setServoDegree(2, 180-i);
            setServoDegree(6, 180-i);
            os_wait2(K_TMO, 1);
        }
        for(i=1; i<=45; i++) {
            setServoDegree(0, 0+i);
            setServoDegree(4, 0+i);
            os_wait2(K_TMO, 1);
        }
    } else if(order == 0x04) {
        //向右
        for(i=1; i<=45; i++) {
            setServoDegree(0, 45-i);
            setServoDegree(4, 45-i);
            os_wait2(K_TMO, 1);
        }
        for(i=1; i<=45; i++) {
            setServoDegree(2, 135+i);
            setServoDegree(6, 135+i);
            os_wait2(K_TMO, 1);
        }
        for(i=1; i<=45; i++) {
            setServoDegree(0, 0+i);
            setServoDegree(4, 0+i);
            os_wait2(K_TMO, 1);
        }
        for(i=1; i<=45; i++) {
            setServoDegree(2, 180-i);
            setServoDegree(6, 180-i);
            os_wait2(K_TMO, 1);
        }
    }

    os_delete_task(11);
}


//任务12是语音模块
void task12() _task_ 12 {
       u8 i;
    while (1) {
        if(COM3.RX_TimeOut > 0) {
            //超时计数
            if(--COM3.RX_TimeOut == 0) {
                if(COM3.RX_Cnt > 0) {
                    for(i=0; i<COM3.RX_Cnt; i++)	{
                        //根据接收到的内容，进行特定动作
                        do_work(RX3_Buffer[i]);
                        TX1_write2buff(RX3_Buffer[i]);
                    }
                }
                COM3.RX_Cnt = 0;
            }
        }
        os_wait2(K_TMO, 4);  // 5ms * 4
    }
}

//任务13是旋转
void task13() _task_ 13 {
    u8 i,j;
	    //关闭其他动作
	  os_delete_task(3);
		os_delete_task(4);
    os_delete_task(5);
    os_delete_task(6);
    os_delete_task(8);
    os_delete_task(9);
    os_delete_task(10);
    os_delete_task(11);
    os_delete_task(15);
    //初始化右转旋转姿态
    setServoDegree(1, 180);
    setServoDegree(3, 0);
    setServoDegree(5, 180);
    setServoDegree(7, 0);

    setServoDegree(0, 45);
    setServoDegree(2, 135);
    setServoDegree(4, 45);
    setServoDegree(6, 135);

    //运动模式
    for(j=0; j<5; j++) {
        //左前脚先行  2 左前 6右后
        for(i=1; i<=45; i++) {
            setServoDegree(2, 135+i);
            setServoDegree(6, 135+i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);

        //右脚  0右前 4 左后
        for(i=1; i<=45; i++) {
            setServoDegree(0, 45-i);
            setServoDegree(4, 45-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);

        //左脚  2 左前 6右后
        for(i=1; i<=45; i++) {
            setServoDegree(2, 180-i);
            setServoDegree(6, 180-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);

        //右脚  0右前 4 左后
        for(i=1; i<=45; i++) {
            setServoDegree(0, 0+i);
            setServoDegree(4, 0+i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 20);
    }

    os_delete_task(13);
}

//任务14是停止
void task14() _task_ 14 {
    u8 i;
    //关闭现在所有任务
    os_delete_task(3);
    os_delete_task(4);
    os_delete_task(5);
    os_delete_task(6);
    os_delete_task(7);
    os_delete_task(8);
    os_delete_task(9);
    os_delete_task(10);
    os_delete_task(11);
    os_delete_task(13);
    os_delete_task(15);
    P35=P27=P26=P15=P14=P23=P22=P21=P20=1;
    os_wait2(K_TMO, 50);
    //初始化原始形态
    posture_init();

    //逐步递减，不要太急速
    for(i=1; i<=45; i++) {
        setServoDegree(1,135-i);
        setServoDegree(5,135-i);
        setServoDegree(3, 45+i);
        setServoDegree(7, 45+i);
        os_wait2(K_TMO, 4);
    }
    os_wait2(K_TMO, 50);
    for(i=1; i<=45; i++) {
        setServoDegree(0, 45-i);
        setServoDegree(2, 135+i);
        setServoDegree(4, 45-i);
        setServoDegree(6, 135+i);
        os_wait2(K_TMO, 4);
    }

    os_delete_task(14);
}

//任务15是跑马灯
void task15() _task_ 15 {
    //初始化原始形态
    Horse_Race_Light();

    os_delete_task(15);
}