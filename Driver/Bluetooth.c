#include "Bluetooth.h"


static void UART_config(void) {
    COMx_InitDefine		COMx_InitStructure;					//结构定义
    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;			//选择波特率发生器, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 9600ul;			//波特率, 一般 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//波特率加倍, ENABLE或DISABLE
    UART_Configuration(UART2, &COMx_InitStructure);		//初始化串口1 UART1,UART2,UART3,UART4

  	NVIC_UART2_Init(ENABLE,Priority_1);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
    UART2_SW(UART2_SW_P10_P11);		// 引脚选择, UART2_SW_P10_P11,UART2_SW_P46_P47
}

void BT_init() {
    BT_PIN_INIT();

    UART_config();
}

void BT_send(u8 dat) {
}
void BT_recv() {
		u8 i;
    if(COM2.RX_TimeOut > 0) {
        //超时计数
        if(--COM2.RX_TimeOut == 0) {
            if(COM2.RX_Cnt > 0) {
                for(i=0; i<COM2.RX_Cnt; i++)	{
                    // TODO: RX2_Buffer[i]存的是接收的数据
                    // TODO: 做具体的逻辑
									TX1_write2buff(RX2_Buffer[i]);
                    BT_on_recv(RX2_Buffer[i]);
									
                }
            }
            COM2.RX_Cnt = 0;
        }
    }
}