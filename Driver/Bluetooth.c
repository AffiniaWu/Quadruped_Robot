#include "Bluetooth.h"


static void UART_config(void) {
    COMx_InitDefine		COMx_InitStructure;					//�ṹ����
    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//ģʽ, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;			//ѡ�����ʷ�����, BRT_Timer1, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 9600ul;			//������, һ�� 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//�����ʼӱ�, ENABLE��DISABLE
    UART_Configuration(UART2, &COMx_InitStructure);		//��ʼ������1 UART1,UART2,UART3,UART4

  	NVIC_UART2_Init(ENABLE,Priority_1);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
    UART2_SW(UART2_SW_P10_P11);		// ����ѡ��, UART2_SW_P10_P11,UART2_SW_P46_P47
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
        //��ʱ����
        if(--COM2.RX_TimeOut == 0) {
            if(COM2.RX_Cnt > 0) {
                for(i=0; i<COM2.RX_Cnt; i++)	{
                    // TODO: RX2_Buffer[i]����ǽ��յ�����
                    // TODO: ��������߼�
									TX1_write2buff(RX2_Buffer[i]);
                    BT_on_recv(RX2_Buffer[i]);
									
                }
            }
            COM2.RX_Cnt = 0;
        }
    }
}