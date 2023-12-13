/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/* --- BBS: www.STCAIMCU.com  -----------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����            */
/*---------------------------------------------------------------------*/

#ifndef __UART_H
#define __UART_H	 

#include	"config.h"

//========================================================================
//                              ��������
//========================================================================

#define	UART1	1       //ʹ����Щ���ھͿ���Ӧ�Ķ��壬���õĴ��ڿ����ε����壬��ʡ��Դ
#define	UART2	2
#define	UART3	3
#define	UART4	4

#define	UART_QUEUE_MODE	0           //���ô��ڷ���ģʽ��0������ģʽ��1������ģʽ

#define	PRINTF_SELECT  UART1		//ѡ�� printf ������ʹ�õĴ��ڣ����� UART1~UART4

#ifdef UART1
#define	COM_TX1_Lenth	128
#define	COM_RX1_Lenth	128
#endif
#ifdef UART2
#define	COM_TX2_Lenth	128
#define	COM_RX2_Lenth	128
#endif
#ifdef UART3
#define	COM_TX3_Lenth	64
#define	COM_RX3_Lenth	64
#endif
#ifdef UART4
#define	COM_TX4_Lenth	32
#define	COM_RX4_Lenth	32
#endif

#define	UART_ShiftRight	0		//ͬ����λ���
#define	UART_8bit_BRTx	(1<<6)	//8λ����,�ɱ䲨����
#define	UART_9bit		(2<<6)	//9λ����,�̶�������
#define	UART_9bit_BRTx	(3<<6)	//9λ����,�ɱ䲨����

#define	TimeOutSet1		5
#define	TimeOutSet2		5
#define	TimeOutSet3		5
#define	TimeOutSet4		5

#define	BRT_Timer1	1
#define	BRT_Timer2	2
#define	BRT_Timer3	3
#define	BRT_Timer4	4

//========================================================================
//                              UART����
//========================================================================

#define		TI2					(S2CON & 2) 		/* �ж�TI2�Ƿ������ */
#define		RI2					(S2CON & 1) 		/* �ж�RI2�Ƿ������� */
#define		SET_TI2()			S2CON |=  (1<<1)	/* ����TI2(�����ж�) */
#define		CLR_TI2()			S2CON &= ~(1<<1)	/* ���TI2 */
#define		CLR_RI2()			S2CON &= ~1			/* ���RI2 */

#define		TI3					(S3CON & 2) != 0	/* �ж�TI3�Ƿ������ */
#define		RI3					(S3CON & 1) != 0	/* �ж�RI3�Ƿ������� */
#define		SET_TI3()			S3CON |=  (1<<1)	/* ����TI3(�����ж�) */
#define		CLR_TI3()			S3CON &= ~(1<<1)	/* ���TI3 */
#define		CLR_RI3()			S3CON &= ~1			/* ���RI3 */

#define		TI4					(S4CON & 2) != 0	/* �ж�TI3�Ƿ������ */
#define		RI4					(S4CON & 1) != 0	/* �ж�RI3�Ƿ������� */
#define		SET_TI4()			S4CON |=  2			/* ����TI3(�����ж�) */
#define		CLR_TI4()			S4CON &= ~2			/* ���TI3 */
#define		CLR_RI4()			S4CON &= ~1			/* ���RI3 */

#define		UART1_RxEnable(n)	(n==0?(REN = 0):(REN = 1))			/* UART1����ʹ�� */
#define		UART2_RxEnable(n)	S2CON = (S2CON & ~0x10) | (n << 4)	/* UART2����ʹ�� */
#define		UART3_RxEnable(n)	S3CON = (S3CON & ~0x10) | (n << 4)	/* UART3����ʹ�� */
#define		UART4_RxEnable(n)	S4CON = (S4CON & ~0x10) | (n << 4)	/* UART4����ʹ�� */

//========================================================================
//                              ��������
//========================================================================

#define	UART1_SW_P30_P31	0
#define	UART1_SW_P36_P37	1
#define	UART1_SW_P16_P17	2
#define	UART1_SW_P43_P44	3

#define	UART2_SW_P10_P11	0
#define	UART2_SW_P46_P47	1
#define	UART3_SW_P00_P01	0
#define	UART3_SW_P50_P51	1
#define	UART4_SW_P02_P03	0
#define	UART4_SW_P52_P53	1

//========================================================================
//                            ���ܽ��л�����
//========================================================================
#define  UART1_SW(Pin)				P_SW1 = (P_SW1 & 0x3F) | (Pin << 6)
#define  UART2_SW(Pin)				P_SW2 = (P_SW2 & 0xFE) | (Pin)
#define  UART3_SW(Pin)				P_SW2 = (P_SW2 & 0xFD) | (Pin << 1)
#define  UART4_SW(Pin)				P_SW2 = (P_SW2 & 0xFB) | (Pin << 2)


//========================================================================
//                              UART�ж�����
//========================================================================

#define		UART1_Interrupt(n)	(n==0?(ES = 0):(ES = 1))			/* UART1�ж�ʹ�� */
#define		UART2_Interrupt(n)	IE2 = (IE2 & ~0x01) | (n)			/* UART2�ж�ʹ�� */
#define		UART3_Interrupt(n)	IE2 = (IE2 & ~0x08) | (n << 3)		/* UART3�ж�ʹ�� */
#define		UART4_Interrupt(n)	IE2 = (IE2 & ~0x10) | (n << 4)		/* UART4�ж�ʹ�� */

//========================================================================
//                            �ж����ȼ�����
//========================================================================
#define		PS2			0x01
#define		PS3			0x01
#define		PS4			0x02

#define		PSH			0x10
#define		PS2H		0x01
#define		PS3H		0x01
#define		PS4H		0x02


//����1�ж����ȼ�����
#define 	UART1_Priority(n)			do{if(n == 0) IPH &= ~PSH, PS = 0; \
																if(n == 1) IPH &= ~PSH, PS = 1; \
																if(n == 2) IPH |= PSH, PS = 0; \
																if(n == 3) IPH |= PSH, PS = 1; \
															}while(0)

//����2�ж����ȼ�����
#define 	UART2_Priority(n)			do{if(n == 0) IP2H &= ~PS2H, IP2 &= ~PS2; \
																if(n == 1) IP2H &= ~PS2H, IP2 |= PS2; \
																if(n == 2) IP2H |= PS2H, IP2 &= ~PS2; \
																if(n == 3) IP2H |= PS2H, IP2 |= PS2; \
															}while(0)

//����3�ж����ȼ�����
#define 	UART3_Priority(n)			do{if(n == 0) IP3H &= ~PS3H, IP3 &= ~PS3; \
																if(n == 1) IP3H &= ~PS3H, IP3 |= PS3; \
																if(n == 2) IP3H |= PS3H, IP3 &= ~PS3; \
																if(n == 3) IP3H |= PS3H, IP3 |= PS3; \
															}while(0)
//����4�ж����ȼ�����
#define 	UART4_Priority(n)			do{if(n == 0) IP3H &= ~PS4H, IP3 &= ~PS4; \
																if(n == 1) IP3H &= ~PS4H, IP3 |= PS4; \
																if(n == 2) IP3H |= PS4H, IP3 &= ~PS4; \
																if(n == 3) IP3H |= PS4H, IP3 |= PS4; \
															}while(0)

															
typedef struct
{ 
	u8	TX_send;		//�ѷ���ָ��
	u8	TX_write;		//����дָ��
	u8	B_TX_busy;		//æ��־

	u8 	RX_Cnt;			//�����ֽڼ���
	u8	RX_TimeOut;		//���ճ�ʱ
} COMx_Define; 

typedef struct
{ 
	u8	UART_Mode;			//ģʽ,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	u8	UART_BRT_Use;		//ʹ�ò�����,   BRT_Timer1,BRT_Timer2,BRT_Timer3,BRT_Timer4
	u32	UART_BaudRate;		//������, 	   һ�� 110 ~ 115200
	u8	Morecommunicate;	//���ͨѶ����, ENABLE,DISABLE
	u8	UART_RxEnable;		//�������,   ENABLE,DISABLE
	u8	BaudRateDouble;		//�����ʼӱ�, ENABLE,DISABLE
} COMx_InitDefine; 

#ifdef UART1
extern	COMx_Define	COM1;
extern	u8	xdata TX1_Buffer[COM_TX1_Lenth];	//���ͻ���
extern	u8 	xdata RX1_Buffer[COM_RX1_Lenth];	//���ջ���
#endif
#ifdef UART2
extern	COMx_Define	COM2;
extern	u8	xdata TX2_Buffer[COM_TX2_Lenth];	//���ͻ���
extern	u8 	xdata RX2_Buffer[COM_RX2_Lenth];	//���ջ���
#endif
#ifdef UART3
extern	COMx_Define	COM3;
extern	u8	xdata TX3_Buffer[COM_TX3_Lenth];	//���ͻ���
extern	u8 	xdata RX3_Buffer[COM_RX3_Lenth];	//���ջ���
#endif
#ifdef UART4
extern	COMx_Define	COM4;
extern	u8	xdata TX4_Buffer[COM_TX4_Lenth];	//���ͻ���
extern	u8 	xdata RX4_Buffer[COM_RX4_Lenth];	//���ջ���
#endif

u8	UART_Configuration(u8 UARTx, COMx_InitDefine *COMx);

u8 NVIC_UART1_Init(u8 State, u8 Priority);
u8 NVIC_UART2_Init(u8 State, u8 Priority);
u8 NVIC_UART3_Init(u8 State, u8 Priority);
u8 NVIC_UART4_Init(u8 State, u8 Priority);

#ifdef UART1
void TX1_write2buff(u8 dat);	//����1���ͺ���
void PrintString1(u8 *puts);
#endif
#ifdef UART2
void TX2_write2buff(u8 dat);	//����2���ͺ���
void PrintString2(u8 *puts);
#endif
#ifdef UART3
void TX3_write2buff(u8 dat);	//����3���ͺ���
void PrintString3(u8 *puts);
#endif
#ifdef UART4
void TX4_write2buff(u8 dat);	//����4���ͺ���
void PrintString4(u8 *puts);
#endif

//void COMx_write2buff(u8 UARTx, u8 dat);	//���ڷ��ͺ���
//void PrintString(u8 UARTx, u8 *puts);

#endif

