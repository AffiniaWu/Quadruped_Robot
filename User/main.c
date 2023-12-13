#include 			"Config.h"
#include 			"GPIO.h"
#include 			"UART.h"
#include 			"EXTI.h"
#include 			"NVIC.h"
#include 			"Switch.h"
#include 			"STC8H_PWM.h"
#include		  "PCA9685_servo.h"	//16λ���
#include 			"Light.h"					//�ƹ�
#include			"Ultrasonic.h" 		//������
//#include      "Battery.h"     	//��Դ���



#define TASK_UART1	1
#define TASK_UART2	2

u8 order;//ȫ�ֱ��������ڸ�ͬһ����ͬ����

// ����
u8 notes[] = {
    1, 1, 2, 3, 4,5,6,5,4, 3, 2,1,8,8
};

// ����
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
    //׼˫���	uart1: P30 P31
    P3_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);

    //׼˫���	uart2: P10 P11
    P1_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);
	
	//����ģ�� uaer3: P50 P51
		P5_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);

    // ���� en���� P03
    P0_MODE_IO_PU( GPIO_Pin_3);

    //ADC�ɼ�
    P0_MODE_IN_HIZ(GPIO_Pin_1);

    //������
    P0_MODE_OUT_PP(GPIO_Pin_0);
}

//void	ADC_config(void)
//{
//    ADC_InitTypeDef		ADC_InitStructure;		//�ṹ����

//    ADC_InitStructure.ADC_SMPduty   = 31;		//ADC ģ���źŲ���ʱ�����, 0~31��ע�⣺ SMPDUTY һ����������С�� 10��
//    ADC_InitStructure.ADC_CsSetup   = 0;		//ADC ͨ��ѡ��ʱ����� 0(Ĭ��),1
//    ADC_InitStructure.ADC_CsHold    = 1;		//ADC ͨ��ѡ�񱣳�ʱ����� 0,1(Ĭ��),2,3
//    ADC_InitStructure.ADC_Speed     = ADC_SPEED_2X1T;		//���� ADC ����ʱ��Ƶ��	ADC_SPEED_2X1T~ADC_SPEED_2X16T
//    ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC�������,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
//    ADC_Inilize(&ADC_InitStructure);		//��ʼ��
//    ADC_PowerControl(ENABLE);				//ADC��Դ����, ENABLE��DISABLE
//    NVIC_ADC_Init(DISABLE,Priority_0);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
//}

void UART_config(void) {
    COMx_InitDefine		COMx_InitStructure;								//�ṹ����
    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//ѡ�����ʷ�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;				//������, һ�� 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;					//��������,   ENABLE��DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;				//�����ʼӱ�, ENABLE��DISABLE
    UART_Configuration(UART1, &COMx_InitStructure);			//��ʼ������1 UART1,UART2,UART3,UART4

    NVIC_UART1_Init(ENABLE,Priority_1);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
    UART1_SW(UART1_SW_P30_P31);						// ����ѡ��, UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44

    // uart2 ����
    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;			//ѡ�����ʷ�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 9600ul;			//������, һ�� 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//�����ʼӱ�, ENABLE��DISABLE
    UART_Configuration(UART2, &COMx_InitStructure);		//��ʼ������1 UART1,UART2,UART3,UART4

    NVIC_UART2_Init(ENABLE,Priority_1);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
    UART2_SW(UART2_SW_P10_P11);		// ����ѡ��, UART2_SW_P10_P11,UART2_SW_P46_P47

    //uart3 ����
		COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer3;			//ѡ�����ʷ�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 9600ul;			//������, һ�� 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//�����ʼӱ�, ENABLE��DISABLE
    UART_Configuration(UART3, &COMx_InitStructure);		//��ʼ������1 UART1,UART2,UART3,UART4

  	NVIC_UART3_Init(ENABLE,Priority_1);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
    UART3_SW(UART3_SW_P50_P51);		// ����ѡ��, UART3_SW_P00_P01,UART3_SW_P50_P51
}

void Buzzer_play(u16 hz_value) {

    PWMx_InitDefine		PWMx_InitStructure;
    u16 Period = MAIN_Fosc / hz_value;

    // ����PWM5
    PWMx_InitStructure.PWM_Mode    		= CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    PWMx_InitStructure.PWM_Duty   	 	= (u16)(Period * 0.5);	//PWMռ�ձ�ʱ��, 0~Period
    PWMx_InitStructure.PWM_EnoSelect    = ENO5P;			//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWM_Configuration(PWM5, &PWMx_InitStructure);			//��ʼ��PWM,  PWMA,PWMB

    // ����PWMB
    PWMx_InitStructure.PWM_Period   = Period - 1;			//����ʱ��,   0~65535
    PWMx_InitStructure.PWM_DeadTime = 0;					//��������������, 0~255
    PWMx_InitStructure.PWM_MainOutEnable= ENABLE;			//�����ʹ��, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;			//ʹ�ܼ�����, ENABLE,DISABLE
    PWM_Configuration(PWMB, &PWMx_InitStructure);			//��ʼ��PWMͨ�üĴ���,  PWMA,PWMB

    // �л�PWMͨ��
    PWM5_SW(PWM5_SW_P00);					//PWM5_SW_P20,PWM5_SW_P17,PWM5_SW_P00,PWM5_SW_P74

    // ��ʼ��PWMB���ж�
    NVIC_PWM_Init(PWMB,DISABLE,Priority_0);
}

// ����ָ�����ڲ��� 1 2 3 4 5 6 7 8
void Buzzer_beep(u8 hz_value_index) {
    u16 hz_value = hz[hz_value_index - 1];
    Buzzer_play(hz_value);
}

// ֹͣ����
void Buzzer_stop() {
    PWMx_InitDefine		PWMx_InitStructure;
    PWMx_InitStructure.PWM_MainOutEnable= DISABLE;			//�����ʹ��, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable   = DISABLE;			//ʹ�ܼ�����, ENABLE,DISABLE
    PWM_Configuration(PWMB, &PWMx_InitStructure);			//��ʼ��PWMͨ�üĴ���,  PWMA,PWMB
}

//���ݽ��յ������ݣ������ض�����
void do_work (u8 dat) {
    if(dat == 0x20) {  //ŤѽŤ
        os_create_task(3);
        os_create_task(15);
        os_create_task(5);
    } else if(dat ==0x02) { //ſ��
        order = dat;
        os_create_task(4);
    } else if(dat ==0x01) { //վ��
        order = dat;
        os_create_task(4);
    } else if(dat ==0x21) { //���к�
        os_create_task(6);
    } else if(dat ==0x12) { //����
        order = dat;
        os_create_task(7);
    } else if(dat ==0x13) { //�ص�
        order = dat;
        os_create_task(7);
    } else if(dat ==0x10) { //��ǰ
        os_create_task(9);
        os_create_task(8);
    } else if(dat ==0x11) { //���
        os_create_task(10);
    } else if(dat ==0x03) { //����
        order = dat;
        os_create_task(11);
    } else if(dat ==0x04) { //����
        order = dat;
        os_create_task(11);
    } else if(dat ==0x05) { //��ת
        os_create_task(13);
    } else if(dat == 0x00) { //ֹͣ
        os_create_task(14);
    }
}

//��ʼ����̬
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
    //��չ�Ĵ�������ʹ��
    EAXSFR();
    //GPIO��ʼ��
    GPIO_config();
    // ADC_config();
    //UART��ʼ��
    UART_config();
    //PCA9685ģ���ʼ��
    PCA9685_init();
    //led�Ƴ�ʼ��
    Light_init();
    //�ж�����
    EA = 1;
    //�������˶���ʼ��
    posture_init();
    //������ģ���ʼ��
    Ultrasonic_init();
    //��Դ����ʼ��
    //Battery_init();

    printf("init complete\n");
}

void task_main() _task_ 0 {
    u8 i=0;
    //ϵͳ��ʼ��
    sys_init();
    //�������� 1��2 ������������  ����12������ģ��
    os_create_task(TASK_UART1);
    os_create_task(TASK_UART2);
		os_create_task(12);
    //�����ʼֵ������������
    order=0x00;
    //ɾ������0
    os_delete_task(0);
}

//ʹ������
// uart1�յ����ݣ�ͨ��uart2����ȥ
void task1() _task_ TASK_UART1 {

    u8 i;
    while (1) {
        if(COM1.RX_TimeOut > 0) {
            //��ʱ����
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

// uart2�յ����ݣ�ͨ��uart1����ȥ
void task2() _task_ TASK_UART2 {
    u8 i;
    while (1) {
        if(COM2.RX_TimeOut > 0) {
            //��ʱ����
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

//����3��ŤѽŤ
void task3() _task_ 3 {
    u8 c=0,d=0,e=0;
    //�ر���������
		os_delete_task(4);
    os_delete_task(6);
    os_delete_task(7);
    os_delete_task(8);
    os_delete_task(9);
    os_delete_task(10);
    os_delete_task(11);
    os_delete_task(13);
		//��ʼ��ԭʼ��̬
    posture_init();
    //�Ϸ���
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
    //�·���
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

//����4��վ��/ſ��
void task4() _task_ 4 {
	    //�ر���������
		os_delete_task(3);
    os_delete_task(5);
    os_delete_task(6);
    os_delete_task(8);
    os_delete_task(9);
    os_delete_task(10);
    os_delete_task(11);
    os_delete_task(13);
    os_delete_task(15);
    if(order == 0x01) { //վ��
        setServoDegree(0, 45);
        setServoDegree(2, 135);
        setServoDegree(4, 45);
        setServoDegree(6, 135);
        os_wait2(K_TMO, 50);
    } else if(order == 0x02) { //ſ��
        //��ʼ��ԭʼ��̬
        posture_init();
        setServoDegree(0, 90);
        setServoDegree(2, 90);
        setServoDegree(4, 90);
        setServoDegree(6, 90);
        os_wait2(K_TMO, 50);
    }

    os_delete_task(4);
}

//����5��ADC����ѹ----�޸ĳ� ������
void task5() _task_ 5 {
//    float vol;
//    u8 i;
//    u16 adc_value;
//	    printf("1111111111111");
//    // ������ֵ
//    adc_value = Get_ADCResult(ADC_CH9);
//    // ת��Ϊ��ѹ
//    vol =  adc_value * 2.5 / 4096;
//    // ���8.19   vcc 7.5V
//    // ����  0.6 �����ܵ�ѹ��
//    vol = vol * 4 + 0.6;
//    printf("vol = %.2f\n", vol);
//	if(vol < 3){
//			//��ѹ���� ִ�в���
//
//		for(i=0;i<3;i++){
//			 Horse_Race_Light();
//		}
//		os_create_task(15);
//	}

    //os_wait2(K_TMO, 200);  // 5ms * 2000 =10s


    //������
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

//����6�Ǵ��к�
void task6() _task_ 6 {
	   //�ر���������
	  os_delete_task(3);
		os_delete_task(4);
    os_delete_task(5);
    os_delete_task(8);
    os_delete_task(9);
    os_delete_task(10);
    os_delete_task(11);
    os_delete_task(13);
    os_delete_task(15);
    //��ʼ��ԭʼ��̬
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
    //�ָ�ԭ��
    setServoDegree(0, 45);
    setServoDegree(3, 45);

    os_delete_task(6);
}

//����7�ǿ���/�ص�
void task7() _task_ 7 {
    if(order == 0x12) {
        //����
        Light_on();
        os_wait2(K_TMO, 100);
        os_delete_task(7);
    } else if (order == 0x13) {
        //�ص�
        Light_off();
        os_wait2(K_TMO, 100);
        os_delete_task(7);
    }

    os_delete_task(7);
}

//����8�ǳ��������
void task8() _task_ 8 {
    float distance;
    char res;
    while(1) {
        res = Ultrasonic_get_distance(&distance);
        if (res == 0 && distance > 10 ) {
            printf("����Ϊ��%.2f cm\n", distance);
        } else if(res == -1) {
            printf("res = %d\n", (int)res);
        } else if(res == 0 && distance <= 10 ) {
            //���С��Ŀ����룬������ǰ������9 os_delete_task(9);
            os_delete_task(12);
            os_delete_task(10);
            os_delete_task(11);
            os_delete_task(9);
            //�������˻ָ��ɳ�ʼ״̬
            os_wait2(K_TMO, 50);
            posture_init();
            os_wait2(K_TMO, 50);
            //���ٲ������8
            os_delete_task(8);
        }
        os_wait2(K_TMO, 50);
    }
}

//����9����ǰ
void task9() _task_ 9 {
    u8 i,j;
	    //�ر���������
	  os_delete_task(3);
		os_delete_task(4);
    os_delete_task(5);
    os_delete_task(6);
    os_delete_task(10);
    os_delete_task(11);
    os_delete_task(13);
    os_delete_task(15);
    //��ʼ��ǰ����̬
    setServoDegree(1, 180);
    setServoDegree(3, 0);
    setServoDegree(5, 180);
    setServoDegree(7, 0);

    setServoDegree(0, 45);
    setServoDegree(2, 135);
    setServoDegree(4, 45);
    setServoDegree(6, 135);

    //�˶�ģʽ
    for(j=0; j<3; j++) {
        //�ҽ�����
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

        //���浽�������
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
    os_delete_task(8);//��ǰ�ж�������ʱ�򣬹ر�����8�Ĳ������
    os_delete_task(9);
}

//����10�����
void task10() _task_ 10 {
    u8 i,j;
	    //�ر���������
	  os_delete_task(3);
		os_delete_task(4);
    os_delete_task(5);
    os_delete_task(6);
    os_delete_task(8);
    os_delete_task(9);
    os_delete_task(11);
    os_delete_task(13);
    os_delete_task(15);
    //��ʼ��ԭʼ��̬
    setServoDegree(1, 180);
    setServoDegree(3, 0);
    setServoDegree(5, 180);
    setServoDegree(7, 0);

    setServoDegree(0, 45);
    setServoDegree(2, 135);
    setServoDegree(4, 45);
    setServoDegree(6, 135);
    //�˶�ģʽ
    for(j=0; j<3; j++) {
        //��� �ҽ�����
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
        //�������
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

//����11������/����
void task11() _task_ 11 {
    u8 i;
	    //�ر���������
	  os_delete_task(3);
		os_delete_task(4);
    os_delete_task(5);
    os_delete_task(6);
    os_delete_task(8);
    os_delete_task(9);
    os_delete_task(10);
    os_delete_task(13);
    os_delete_task(15);
    //��ʼ��ԭʼ��̬
    setServoDegree(1, 180);
    setServoDegree(3, 0);
    setServoDegree(5, 180);
    setServoDegree(7, 0);

    setServoDegree(0, 45);
    setServoDegree(2, 135);
    setServoDegree(4, 45);
    setServoDegree(6, 135);
    if(order == 0x03) {
        //����
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
        //����
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


//����12������ģ��
void task12() _task_ 12 {
       u8 i;
    while (1) {
        if(COM3.RX_TimeOut > 0) {
            //��ʱ����
            if(--COM3.RX_TimeOut == 0) {
                if(COM3.RX_Cnt > 0) {
                    for(i=0; i<COM3.RX_Cnt; i++)	{
                        //���ݽ��յ������ݣ������ض�����
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

//����13����ת
void task13() _task_ 13 {
    u8 i,j;
	    //�ر���������
	  os_delete_task(3);
		os_delete_task(4);
    os_delete_task(5);
    os_delete_task(6);
    os_delete_task(8);
    os_delete_task(9);
    os_delete_task(10);
    os_delete_task(11);
    os_delete_task(15);
    //��ʼ����ת��ת��̬
    setServoDegree(1, 180);
    setServoDegree(3, 0);
    setServoDegree(5, 180);
    setServoDegree(7, 0);

    setServoDegree(0, 45);
    setServoDegree(2, 135);
    setServoDegree(4, 45);
    setServoDegree(6, 135);

    //�˶�ģʽ
    for(j=0; j<5; j++) {
        //��ǰ������  2 ��ǰ 6�Һ�
        for(i=1; i<=45; i++) {
            setServoDegree(2, 135+i);
            setServoDegree(6, 135+i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);

        //�ҽ�  0��ǰ 4 ���
        for(i=1; i<=45; i++) {
            setServoDegree(0, 45-i);
            setServoDegree(4, 45-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);

        //���  2 ��ǰ 6�Һ�
        for(i=1; i<=45; i++) {
            setServoDegree(2, 180-i);
            setServoDegree(6, 180-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);

        //�ҽ�  0��ǰ 4 ���
        for(i=1; i<=45; i++) {
            setServoDegree(0, 0+i);
            setServoDegree(4, 0+i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 20);
    }

    os_delete_task(13);
}

//����14��ֹͣ
void task14() _task_ 14 {
    u8 i;
    //�ر�������������
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
    //��ʼ��ԭʼ��̬
    posture_init();

    //�𲽵ݼ�����Ҫ̫����
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

//����15�������
void task15() _task_ 15 {
    //��ʼ��ԭʼ��̬
    Horse_Race_Light();

    os_delete_task(15);
}