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

#include	"SPI.h"

u8 	SPI_RxTimerOut;
u8 	SPI_BUF_type SPI_RxBuffer[SPI_BUF_LENTH];
bit B_SPI_Busy; //����æ��־


//========================================================================
// ����: void	SPI_Init(SPI_InitTypeDef *SPIx)
// ����: SPI��ʼ������.
// ����: SPIx: �ṹ����,��ο�spi.h��Ķ���.
// ����: none.
// �汾: V1.0, 2012-11-22
//========================================================================
void	SPI_Init(SPI_InitTypeDef *SPIx)
{
	if(SPIx->SPI_SSIG == ENABLE)			SPCTL &= ~(1<<7);	//enable SS, conform Master or Slave by SS pin.
	else									SPCTL |=  (1<<7);	//disable SS, conform Master or Slave by SPI_Mode
	SPI_Start(SPIx->SPI_Enable);
	SPI_FirstBit_Set(SPIx->SPI_FirstBit);
	SPI_Mode_Set(SPIx->SPI_Mode);
	SPI_CPOL_Set(SPIx->SPI_CPOL);
	SPI_CPHA_Set(SPIx->SPI_CPHA);
	SPI_Clock_Select(SPIx->SPI_Speed);
	
	SPI_RxTimerOut = 0;
	B_SPI_Busy = 0;
}

//========================================================================
// ����: void	SPI_SetMode(u8 mode)
// ����: SPI��������ģʽ����.
// ����: mode: ָ��ģʽ, ȡֵ SPI_Mode_Master �� SPI_Mode_Slave.
// ����: none.
// �汾: V1.0, 2012-11-22
//========================================================================
void	SPI_SetMode(u8 mode)
{
	if(mode == SPI_Mode_Slave)
	{
		SPCTL &= ~(1<<4);	//��������Ϊ�ӻ�����
		SPCTL &= ~(1<<7);	//SS����ȷ������
	}
	else
	{
		SPCTL |= (1<<4);	//ʹ�� SPI ����ģʽ
		SPCTL |= (1<<7);	//����SS���Ź���
	}
}

//========================================================================
// ����: void SPI_WriteByte(u8 dat)
// ����: SPI����һ���ֽ�����.
// ����: dat: Ҫ���͵�����.
// ����: none.
// �汾: V1.0, 2020-09-14
//========================================================================
void	SPI_WriteByte(u8 dat)		//SPI����һ���ֽ�����
{
	SPDAT = dat;
	B_SPI_Busy = 1;
	while(B_SPI_Busy) ;
}


//========================================================================
// ����: NVIC_SPI_Init
// ����: SPIǶ�������жϿ�������ʼ��.
// ����: State:    �ж�ʹ��״̬, ENABLE/DISABLE.
// ����: Priority: �ж����ȼ�, Priority_0,Priority_1,Priority_2,Priority_3.
// ����: ִ�н�� SUCCESS/FAIL.
// �汾: V1.0, 2020-09-29
//========================================================================
u8 NVIC_SPI_Init(u8 State, u8 Priority)
{
	if(State > ENABLE) return FAIL;
	if(Priority > Priority_3) return FAIL;
	SPI_Interrupt(State);
	SPI_Priority(Priority);
	return SUCCESS;
}
