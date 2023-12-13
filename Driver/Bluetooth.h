#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#include "config.h"
#include "UART.h"

#define BT_EN			P03
#define BT_RXD		P10
#define BT_TXD		P11
#define BT_STATE	P02

#define BT_PIN_INIT() {P0M0 &= ~0x0c; P0M1 &= ~0x0c; P1M0 &= ~0x03; P1M1 &= ~0x03;}    

void BT_init();
void BT_send(u8 dat);
void BT_recv();

extern void BT_on_recv(u8 dat);

#endif