
#ifndef _ESPNOW_MASTER_H_
#define _ESPNOW_MASTER_H_
#include <Arduino.h>
const uint8_t masteraddress[]={0xA0, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};
const uint8_t otherguy[]={0xA0, 0x01, 0xAA, 0xAA, 0xAA, 0xAA};
void espnow_master_init();
void slave_send(uint8_t data,size_t len);
void send_data_now(char c,int num);
#endif
