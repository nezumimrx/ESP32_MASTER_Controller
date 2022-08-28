#include <Arduino.h>
#include "global_vars.h"
#include "ESPNOW_MASTER.h"
hw_timer_t *test_connecting_timer = NULL;
void IRAM_ATTR TimerEvent()
{
  send_data_now('0',0);
  ledstatus=!ledstatus;
}

void timer_init(int timernumber,int timerspeed){
     // 1. 定时器编号（0到3，对应全部4个硬件定时器），这里要注意和pwm所使用的通道分开
  // 2. 预分频器数值（ESP32计数器基频为80M，80分频单位是微秒）也就是1us
  // 3. 计数器向上（true）或向下（false）计数的标志
  test_connecting_timer = timerBegin(timernumber, 80, true);
  //绑定TimerEvent,timer1
  //表示中断触发类型是边沿（true）还是电平（false）的标志
  timerAttachInterrupt(test_connecting_timer, &TimerEvent, true);
  timerAlarmWrite(test_connecting_timer, timerspeed, true); // 1s=1000ms=1*10^6 us,true = autoreload
}

void timer_switch(boolean timerstatus){
    if(timerstatus==true)timerAlarmEnable(test_connecting_timer);
    else if(timerstatus==false)timerAlarmDisable(test_connecting_timer);
}