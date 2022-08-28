#include <Arduino.h>
#include <ESPNOW_MASTER.h>
#include <esp_now.h>
#include "global_vars.h"
#include "Timer_funcs.h"
#include "Button_funcs.h"
#include "Code_parse.h"
#include "Voice_actuator.h"
#include <MFRC522.h>
#include <SPI.h>
#include <rfid_funcs.h>
#include "Card_process.h"

#define connection_indicator 15
boolean receive_data_flag = false;
boolean connected_with_slave = false; //global variable 上位机判断有没有连接到下位机，没有则闪烁灯光提示
boolean ledstatus=false;//global variable 为什么设置成全局变量？因为要在main中用来闪灯的同时在timer中要0.5秒改变一次状态
boolean coder_mode=false;//是否为编程模式，如果不是则是遥控模式
String code_str_raw="&";
int code_str_raw_item_counter=0;
int code_str_raw_item_max=18;//可以录入的最大编程模块数量，默认为18
String code_str_clean="";

String code_str_condition_type1="";
boolean has_condition_type1=false;
boolean receive_condition_type1=false;

String code_str_condition_type2="";
boolean has_condition_type2=false;
boolean receive_condition_type2=false;

String code_str_condition_type3="";
boolean has_condition_type3=false;
boolean receive_condition_type3=false;

boolean instant_stop=0;
boolean start_cypher=0;

byte rfid_block_buffer[18];
boolean read_new_card=false;

boolean voice_trigger=false;
int voice_type=0;

int button_result = 0;
void RFID_TASK(void *parameters)
{
  for (;;)
  {
    rfid_scan_card();
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

void BUTTON_TASK(void *parameters){
  for(;;){
    Button_read();
    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}

void BUTTON_PROCESS_TASK(void *parameters){
  for(;;){
    Button_functions();
    vTaskDelay(80/portTICK_PERIOD_MS);
  }
}

void VOICE_SEND_TASK(void *parameters){
  for(;;){
    send_voice_messages();
    count_code_str_raw();
    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.setTimeout(25);
  rfid_init();
  espnow_master_init();
  xTaskCreate(RFID_TASK, "RFID_TASK", 5000, NULL, 1, NULL);
  Button_init();
  xTaskCreate(BUTTON_TASK, "BUTTON_TASK", 5000, NULL, 1, NULL);
  xTaskCreate(BUTTON_PROCESS_TASK, "BUTTON_PROCESS_TASK", 5000, NULL, 1, NULL);
  xTaskCreate(VOICE_SEND_TASK,"VOICE_SEND",5000,NULL,2,NULL);
  timer_init(3,500000);//3号timer，500,000us，500ms，0.5s
  timer_switch(true);
}

void loop()
{

  if (connected_with_slave == true)
  {
    timer_switch(false);
    digitalWrite(connection_indicator,HIGH);
    card_process(rfid_block_buffer);
    //Button_functions();//不能放在loop里，不然没法instant stop
    if(start_cypher==1){
      code_parse(code_str_clean);
      start_cypher=0;
      //play voice mission complete! and emo_mission_complete
      voice_type=13;
      voice_trigger=true;
      //
    }
    if(instant_stop==1){
      instant_stop_funcs();
      instant_stop=0;
    }
  }
  else
  {
    timer_switch(true);
    digitalWrite(connection_indicator,ledstatus);
  }

  Serial_commands();
}