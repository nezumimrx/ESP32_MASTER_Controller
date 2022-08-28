#include <Arduino.h>
#include "global_vars.h"
#include "ESPNOW_MASTER.h"

void send_voice_messages(){
    if(voice_trigger==true){
        /*voice type 定义
        voice_type=1;//录入动作模块
        voice_type=2;//扫描了新模块但程序数量超出code_str_raw_item_max
        voice_type=3;//紧急停止
        voice_type=4;//清除所有指令
        voice_type=5;//撤销指令
        voice_type=6;//运行、启动、开始执行编程指令
        voice_type = 7; //程序有错误
        voice_type = 8; //没有录入程序指令
        voice_type=9;//条件开始命令
        voice_type=10;//条件结束命令
        voice_type=11;//循环起始命令
        voice_type=12;//循环结束命令
        voice_type=13;//程序运行完毕
        voice_type=14;//yoho
        */
        send_data_now('v',voice_type);
        voice_type=0;
        voice_trigger=false;
    }
}