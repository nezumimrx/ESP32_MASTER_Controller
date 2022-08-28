#include "Card_process.h"
#include <Arduino.h>
#include <ESPNOW_MASTER.h>
#include "global_vars.h"

void cards_music(byte block_buffer[18])
{
    if (block_buffer[1] == 0xFF)
        code_str_raw += ";VF"; //开始录音
    else if (block_buffer[1] == 0xFE)
        code_str_raw += ";VE"; //播放录音
    else
    {
        int music_number = block_buffer[1];
        code_str_raw += ";V";
        code_str_raw += music_number;
    }
    Serial.println(code_str_raw);
    delay(1000);
}
void cards_sphere(byte block_buffer[18])
{
    if (block_buffer[1] == 0xA0)
        code_str_raw += ";SA0"; //球A停止
    else if (block_buffer[1] == 0xA1)
        code_str_raw += ";SA1"; //球A左转半秒
    else if (block_buffer[1] == 0xA2)
        code_str_raw += ";SA2"; //球A右转半秒
    else if (block_buffer[1] == 0xA3)
        code_str_raw += ";SA3"; //球A持续左转
    else if (block_buffer[1] == 0xA4)
        code_str_raw += ";SA4"; //球A持续右转
    else if (block_buffer[1] == 0xA5)
        code_str_raw += ";SA5"; //球A30°
    else if (block_buffer[1] == 0xA6)
        code_str_raw += ";SA6"; //球A45°
    else if (block_buffer[1] == 0xA7)
        code_str_raw += ";SA7"; //球A60°
    else if (block_buffer[1] == 0xA8)
        code_str_raw += ";SA8"; //球A90°
    else if (block_buffer[1] == 0xA9)
        code_str_raw += ";SA9"; //球A120°
    else if (block_buffer[1] == 0xAA)
        code_str_raw += ";SAA"; //球A180°
    else if (block_buffer[1] == 0xAB)
        code_str_raw += ";SAB"; //球A左转指定角度（配合数字卡片，默认0度）
    else if (block_buffer[1] == 0xAC)
        code_str_raw += ";SAC"; //球A右转指定角度（配合数字卡片，默认0度）
    else if (block_buffer[1] == 0xB0)
        code_str_raw += ";SB0"; //球B停止
    else if (block_buffer[1] == 0xB1)
        code_str_raw += ";SB1"; //球B左转半秒
    else if (block_buffer[1] == 0xB2)
        code_str_raw += ";SB2"; //球B右转半秒
    else if (block_buffer[1] == 0xB3)
        code_str_raw += ";SB3"; //球B持续左转
    else if (block_buffer[1] == 0xB4)
        code_str_raw += ";SB4"; //球B持续右转
    else if (block_buffer[1] == 0xB5)
        code_str_raw += ";SB5"; //球B30°
    else if (block_buffer[1] == 0xB6)
        code_str_raw += ";SB6"; //球B45°
    else if (block_buffer[1] == 0xB7)
        code_str_raw += ";SB7"; //球B60°
    else if (block_buffer[1] == 0xB8)
        code_str_raw += ";SB8"; //球B90°
    else if (block_buffer[1] == 0xB9)
        code_str_raw += ";SB9"; //球B120°
    else if (block_buffer[1] == 0xBA)
        code_str_raw += ";SBA"; //球B180°
    else if (block_buffer[1] == 0xBB)
        code_str_raw += ";SBB"; //球B左转指定角度（配合数字卡片，默认0度）
    else if (block_buffer[1] == 0xBC)
        code_str_raw += ";SBC"; //球B右转指定角度（配合数字卡片，默认0度）
    Serial.println(code_str_raw);
    delay(1000);
}
void cards_roto(byte block_buffer[18])
{
    if (block_buffer[1] == 0xA0)
        code_str_raw += ";RA0"; // RotoA 停止
    else if (block_buffer[1] == 0xA1)
        code_str_raw += ";RA1"; // A4号机左摆半秒
    else if (block_buffer[1] == 0xA2)
        code_str_raw += ";RA2"; // A4号机右摆半秒
    else if (block_buffer[1] == 0xA3)
        code_str_raw += ";RA3"; // A4号机左摆到底
    else if (block_buffer[1] == 0xA4)
        code_str_raw += ";RA4"; // A4号机右摆到底
    else if (block_buffer[1] == 0xB0)
        code_str_raw += ";RB0"; // RotoB 停止
    else if (block_buffer[1] == 0xB1)
        code_str_raw += ";RB1"; // B4号机左摆半秒
    else if (block_buffer[1] == 0xB2)
        code_str_raw += ";RB2"; // B4号机右摆半秒
    else if (block_buffer[1] == 0xB1)
        code_str_raw += ";RB3"; // B4号机左摆到底
    else if (block_buffer[1] == 0xB2)
        code_str_raw += ";RB4"; // B4号机右摆到底
    Serial.println(code_str_raw);
    delay(1000);
}
void cards_wheel(byte block_buffer[18])
{
    if (block_buffer[1] == 0xA0)
        code_str_raw += ";W0"; // 停
    else if (block_buffer[1] == 0xA1)
        code_str_raw += ";W1"; // 前进
    else if (block_buffer[1] == 0xA2)
        code_str_raw += ";W2"; // 后退
    else if (block_buffer[1] == 0xA3)
        code_str_raw += ";W3"; // 左转
    else if (block_buffer[1] == 0xA4)
        code_str_raw += ";W4"; // 右转
    else if (block_buffer[1] == 0xB0)
        code_str_raw += ";W5"; // 麦克纳姆左平移
    else if (block_buffer[1] == 0xB1)
        code_str_raw += ";W6"; // 麦克纳姆右平移
    Serial.println(code_str_raw);
    voice_trigger = true;
    voice_type = 1; //动作指令卡片
    code_str_raw_item_counter++;
    delay(1000);
}

void cards_condition(byte block_buffer[18])
{
    if (block_buffer[1] == 0xA0){
        code_str_raw += ";{"; //第一种条件提示符 {}
        voice_type = 9; //录入了条件指令卡前半部分
    }
    else if (block_buffer[1] == 0xA1){
        code_str_raw += ";}"; // 第一种条件提示符 {}
        voice_type = 10;
    }
    else if (block_buffer[1] == 0xA2){
        code_str_raw += ";["; // 第二种条件提示符 []
        voice_type=9;
    }
    else if (block_buffer[1] == 0xA3){
        voice_type=10;
        code_str_raw += ";]"; // 第二种条件提示符 []
    }
    else if (block_buffer[1] == 0xA4){
        voice_type=9;
        code_str_raw += ";<"; // 第三种条件提示符 <>
    }
    else if (block_buffer[1] == 0xA5){
        voice_type=10;
        code_str_raw += ";>"; // 第三种条件提示符 <>
    }
    Serial.println(code_str_raw);
    voice_trigger = true;
    code_str_raw_item_counter++;
    delay(1000);
}
void cards_grabber(byte block_buffer[18])
{
    if (block_buffer[1] == 0xA0)
        code_str_raw += ";GA0"; //爪子A停止
    else if (block_buffer[1] == 0xA1)
        code_str_raw += ";GA1"; //爪子A张开
    else if (block_buffer[1] == 0xA2)
        code_str_raw += ";GA2"; //爪子B合拢
    else if (block_buffer[1] == 0xB0)
        code_str_raw += ";GB0"; //爪子A张开
    else if (block_buffer[1] == 0xB1)
        code_str_raw += ";GB1"; //爪子B合拢
    else if (block_buffer[1] == 0xB2)
        code_str_raw += ";GB2"; //爪子B合拢
    Serial.println(code_str_raw);
    delay(1000);
}

void cards_angles(byte block_buffer[18])
{
    if (block_buffer[1] == 0x00)
        code_str_raw += ";^";
    else if (block_buffer[1] == 0x01)
        code_str_raw += ";30";
    else if (block_buffer[1] == 0x02)
        code_str_raw += ";45";
    else if (block_buffer[1] == 0x03)
        code_str_raw += ";60";
    else if (block_buffer[1] == 0x04)
        code_str_raw += ";90";
    else if (block_buffer[1] == 0x05)
        code_str_raw += ";120";
    else if (block_buffer[1] == 0x06)
        code_str_raw += ";180";
    Serial.println(code_str_raw);
    delay(1000);
}

void cards_numbers(byte block_buffer[18])
{
    if (block_buffer[1] == 0x01)
        code_str_raw += ";01";
    else if (block_buffer[1] == 0x02)
        code_str_raw += ";02";
    else if (block_buffer[1] == 0x03)
        code_str_raw += ";03";
    else if (block_buffer[1] == 0x04)
        code_str_raw += ";04";
    else if (block_buffer[1] == 0x05)
        code_str_raw += ";05";
    else if (block_buffer[1] == 0x06)
        code_str_raw += ";06";
    else if (block_buffer[1] == 0x07)
        code_str_raw += ";07";
    else if (block_buffer[1] == 0x08)
        code_str_raw += ";08";
    else if (block_buffer[1] == 0x09)
        code_str_raw += ";09";
    Serial.println(code_str_raw);
    delay(1000);
}

void cards_loop_end(byte block_buffer[18])
{
    if (block_buffer[1] == 0x01){
        voice_type=12;
        voice_trigger = true;
        code_str_raw += ";)";
        Serial.println(code_str_raw);
    }
    delay(1000);
}

void cards_loop(byte block_buffer[18])
{
    if (block_buffer[1] == 0x00)
        code_str_raw += ";(0";
    else if (block_buffer[1] == 0x02)
        code_str_raw += ";(2";
    else if (block_buffer[1] == 0x03)
        code_str_raw += ";(3";
    else if (block_buffer[1] == 0x04)
        code_str_raw += ";(4";
    else if (block_buffer[1] == 0x05)
        code_str_raw += ";(5";
    else if (block_buffer[1] == 0x06)
        code_str_raw += ";(6";
    else if (block_buffer[1] == 0x07)
        code_str_raw += ";(7";
    else if (block_buffer[1] == 0x08)
        code_str_raw += ";(8";
    else if (block_buffer[1] == 0x09)
        code_str_raw += ";(9";
    Serial.println(code_str_raw);
    voice_trigger=true;
    voice_type=11;
    delay(1000);
}
void cards_delay(byte block_buffer[18])
{
        if (block_buffer[1] == 0x00)
            code_str_raw += ";D";
        else if (block_buffer[1] == 0x01)
            code_str_raw += ";D01";
        else if (block_buffer[1] == 0x02)
            code_str_raw += ";D02";
        else if (block_buffer[1] == 0x03)
            code_str_raw += ";D03";
        else if (block_buffer[1] == 0x04)
            code_str_raw += ";D04";
        else if (block_buffer[1] == 0x05)
            code_str_raw += ";D05";
        else if (block_buffer[1] == 0x06)
            code_str_raw += ";D06";
        else if (block_buffer[1] == 0x07)
            code_str_raw += ";D07";
        else if (block_buffer[1] == 0x08)
            code_str_raw += ";D08";
        else if (block_buffer[1] == 0x09)
            code_str_raw += ";D09";
        Serial.println(code_str_raw);
        
        delay(1000);
}

void card_process(byte block_buffer[18])
{
    if (read_new_card&&code_str_raw_item_counter<=code_str_raw_item_max)
    {
        if (block_buffer[0] == 0xA1)
        { // Delay cards
            cards_delay(block_buffer);
        }
        else if (block_buffer[0] == 0xA2)
        { // Loop cards
            cards_loop(block_buffer);
        }
        else if (block_buffer[0] == 0xA3)
        { // Loop End card
            cards_loop_end(block_buffer);
        }
        else if (block_buffer[0] == 0xA4)
        { // Numbers cards
            cards_numbers(block_buffer);
        }
        else if (block_buffer[0] == 0xA5)
        { // Angles cards
            cards_angles(block_buffer);
        }
        else if (block_buffer[0] == 0xB0)
        { // Grabber cards
            cards_grabber(block_buffer);
        }
        else if (block_buffer[0] == 0xB1)
        { // Wheel cards
            cards_wheel(block_buffer);
        }
        else if (block_buffer[0] == 0xB2)
        { // Roto cards
            cards_roto(block_buffer);
        }
        else if (block_buffer[0] == 0xB3)
        { // Sphere cards
            cards_sphere(block_buffer);
        }
        else if (block_buffer[0] == 0xB4)
        { // Music cards
            cards_music(block_buffer);
        }
        else if (block_buffer[0] == 0xB5)
        { // condition cards
            cards_condition(block_buffer);
        }
        // Serial.println(code_str_raw);
        //发送指令已添加声音
        read_new_card = false;
    }else if(read_new_card&&code_str_raw_item_counter>code_str_raw_item_max){
        voice_trigger=true;
        voice_type=2;//超过上限code_str_raw_item_max
        read_new_card=false;
    }
}
