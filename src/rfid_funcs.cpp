#include <Arduino.h>
#include "global_vars.h"
#include <MFRC522.h>
#include <SPI.h>
#include <DataBlocks.h>
#include <Button_funcs.h>
#define rfid_rst_pin 0
#define rfid_sda_pin 5
DataBlocks data_blocks;
MFRC522 rfid(rfid_sda_pin, rfid_rst_pin);
boolean write_or_read = 0; // if 0 read, if 1 write
int what_rfid_block_to_write=0;
void rfid_init()
{
    SPI.begin();
    rfid.PCD_Init();
    bool rfid_initResult = rfid.PCD_PerformSelfTest(); //
    if (rfid_initResult)
        Serial.println("RFID READY!");
    else
        Serial.println("RFID NOT READY!");
}

void read_block_ntag213(uint8_t blockAddr, byte (&block_buffer)[18])
{
    byte block_size = sizeof(block_buffer);
    MFRC522::StatusCode read_status = (MFRC522::StatusCode)rfid.MIFARE_Read(0x06, block_buffer, &block_size);
    if (read_status != MFRC522::STATUS_OK)
    {
        Serial.print(F("MIFARE_Read() failed: "));
        Serial.println(rfid.GetStatusCodeName(read_status));
    }
    for (byte i = 0; i < 16; i++)
    {
        Serial.print(block_buffer[i], HEX);
    }
    Serial.println();
}
void write_block_ntag213(byte *dataBlock, uint8_t blockAddr)
{
    byte data_to_write[] = {dataBlock[0], dataBlock[1], 0x00, 0x00};
    int write_status = (MFRC522::StatusCode)rfid.MIFARE_Ultralight_Write(blockAddr, &data_to_write[0], 4);
    if (write_status != MFRC522::STATUS_OK)
    {
        Serial.print(F("NTAG213_Read() failed "));
        return;
    }
    else
        Serial.println(F("NTAG213_Write() OK "));
}

void rfid_scan_card()//write_or_read切换为1的时候是写入
{
    boolean is_new_card_present = rfid.PICC_IsNewCardPresent();
    boolean read_card_serial = rfid.PICC_ReadCardSerial();
    if (is_new_card_present && read_card_serial)
    {
        if (write_or_read == 0)
        {
            rfid_block_buffer[18]={0};
            read_block_ntag213(0x06, rfid_block_buffer);
            rfid.PICC_HaltA();
            rfid.PCD_StopCrypto1();
            read_new_card=true;
        }
        else
        {
            Serial.println("");
            Serial.println(what_rfid_block_to_write);
            if(what_rfid_block_to_write==1)write_block_ntag213(data_blocks.wheel_forward, 0x06);//写入卡片改这里
            else if(what_rfid_block_to_write==2)write_block_ntag213(data_blocks.wheel_backward, 0x06);//写入卡片改这里
            else if(what_rfid_block_to_write==3)write_block_ntag213(data_blocks.wheel_left, 0x06);//写入卡片改这里
            else if(what_rfid_block_to_write==4)write_block_ntag213(data_blocks.wheel_right, 0x06);//写入卡片改这里
            else if(what_rfid_block_to_write==5)write_block_ntag213(data_blocks.wheel_mec_left, 0x06);//写入卡片改这里
            else if(what_rfid_block_to_write==6)write_block_ntag213(data_blocks.wheel_mec_right, 0x06);//写入卡片改这里

            else if(what_rfid_block_to_write==11)write_block_ntag213(data_blocks.num_1, 0x06);//写入卡片改这里
            else if(what_rfid_block_to_write==12)write_block_ntag213(data_blocks.num_2, 0x06);//写入卡片改这里
            else if(what_rfid_block_to_write==13)write_block_ntag213(data_blocks.num_3, 0x06);//写入卡片改这里
            else if(what_rfid_block_to_write==14)write_block_ntag213(data_blocks.num_4, 0x06);//写入卡片改这里
            
            else if(what_rfid_block_to_write==15)write_block_ntag213(data_blocks.num_5, 0x06);//写入卡片改这里
            else if(what_rfid_block_to_write==16)write_block_ntag213(data_blocks.num_6, 0x06);//写入卡片改这里
            else if(what_rfid_block_to_write==17)write_block_ntag213(data_blocks.num_7, 0x06);//写入卡片改这里
            else if(what_rfid_block_to_write==18)write_block_ntag213(data_blocks.num_8, 0x06);//写入卡片改这里
            else if(what_rfid_block_to_write==19)write_block_ntag213(data_blocks.num_9, 0x06);//写入卡片改这里

            else if(what_rfid_block_to_write==20)write_block_ntag213(data_blocks.loop, 0x06);//写入卡片改这里
            else if(what_rfid_block_to_write==21)write_block_ntag213(data_blocks.loop_end, 0x06);//写入卡片改这里
            else if(what_rfid_block_to_write==22)write_block_ntag213(data_blocks.loop2, 0x06);//写入卡片改这里
            else if(what_rfid_block_to_write==23)write_block_ntag213(data_blocks.loop3, 0x06);//写入卡片改这里


            else if(what_rfid_block_to_write==30)write_block_ntag213(data_blocks.conditionA_leftbracket, 0x06);//写入卡片改这里
            else if(what_rfid_block_to_write==31)write_block_ntag213(data_blocks.conditionA_rightbracket, 0x06);//写入卡片改这里
            else if(what_rfid_block_to_write==32)write_block_ntag213(data_blocks.conditionB_leftbracket, 0x06);//写入卡片改这里
            else if(what_rfid_block_to_write==33)write_block_ntag213(data_blocks.conditionB_rightbracket, 0x06);//写入卡片改这里
            else if(what_rfid_block_to_write==34)write_block_ntag213(data_blocks.conditionC_leftbracket, 0x06);//写入卡片改这里
            else if(what_rfid_block_to_write==35)write_block_ntag213(data_blocks.conditionC_rightbracket, 0x06);//写入卡片改这里

        }
    }
}


void Serial_commands()
{
    while (Serial.available())
    {
        String c = Serial.readString();
        if (c.startsWith("w"))
        {
            
            Serial.print("即将录入的卡片为：");
            what_rfid_block_to_write=c.substring(1).toInt();
            Serial.print(what_rfid_block_to_write);
            Serial.println("....");
            write_or_read = 1;
        }
        else if (c.startsWith("r"))
        {
            
            Serial.println("放入读取卡片...");
            write_or_read = 0;
        }else if(c.startsWith("&")){
            Serial.println(c);
            button_result=9;
            code_str_raw=c;//
            Button_functions();
        }
    }
}
