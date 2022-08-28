#ifndef DataBlocks_h
#define DataBlocks_h

#include "Arduino.h"
class DataBlocks
{
   public:
    DataBlocks( );
    //开始命令 &
    byte start[2] = { 0xBB, 0x01};
    //延迟命令 D
    byte delay[2] = { 0xA1, 0x00  };
    //延迟命令 D01
    byte delay1[2] = { 0xA1, 0x01};
    //延迟命令 D02
    byte delay2[2] = { 0xA1, 0x02 };
     //延迟命令 D03
    byte delay3[2] = { 0xA1, 0x03 };
    //延迟命令 D04
    byte delay4[2] = { 0xA1, 0x04 };
    //延迟命令 D05
    byte delay5[2] = { 0xA1, 0x05};
    //延迟命令 D06
    byte delay6[2] = { 0xA1, 0x06 };
     //延迟命令 D07
    byte delay7[2] = { 0xA1, 0x07 };
     //延迟命令 D08
    byte delay8[2] = { 0xA1, 0x08 };
    //延迟命令 D09
    byte delay9[2] = { 0xA1, 0x09 };
    //LOOP （0 -实际默认循环2次，因为要等待用户后面加数字
    byte loop[2] = { 0xA2, 0x00 };
    //LOOP （2
    byte loop2[2] = { 0xA2, 0x02};
    //LOOP （3
    byte loop3[2] = { 0xA2, 0x03};
    //LOOP （4
    byte loop4[2] = { 0xA2, 0x04};
    //LOOP （5
    byte loop5[2] = { 0xA2, 0x05};
    //LOOP （6
    byte loop6[2] = { 0xA2, 0x06};
    //LOOP （7
    byte loop7[2] = { 0xA2, 0x07};
    //LOOP （8
    byte loop8[2] = { 0xA2, 0x08};
    //LOOP （9
    byte loop9[2] = { 0xA2, 0x08};
    //LOOP END )
    byte loop_end[2] = { 0xA3, 0x01};
     //number 1
    byte num_1[2] = { 0xA4, 0x01};
    //number 2
    byte num_2[2] = { 0xA4, 0x02};
    //number 3
    byte num_3[2] = { 0xA4, 0x03};
    //number 4
    byte num_4[2] = { 0xA4, 0x04};
    //number 5
    byte num_5[2] = { 0xA4, 0x05};
    //number 6
    byte num_6[2] = { 0xA4, 0x06};
    //number 7
    byte num_7[2] = { 0xA4, 0x07};
    //number 8
    byte num_8[2] = { 0xA4, 0x08};
    //number 9
    byte num_9[2] = { 0xA4, 0x09};
    //number 10
    byte num_10[2] = { 0xA4, 0x0A};
    //angle 0
    byte angle_0[2] = { 0xA5, 0x00};
    //angle 30
    byte angle_30[2] = { 0xA5, 0x01};
    //angle 45
    byte angle_45[2] = { 0xA5, 0x02};
    //angle 60
    byte angle_60[2] = { 0xA5, 0x03};
    //angle 90
    byte angle_90[2] = { 0xA5, 0x04};
    //angle 120
    byte angle_120[2] = { 0xA5, 0x05};
    //angle 180
    byte angle_180[2] = { 0xA5, 0x06};
    // grabberA 停止开合
    byte grabberA_stop[2] = { 0xB0, 0xA0};
    // grabberA 张开
    byte grabberA_open[2] = { 0xB0, 0xA1};
    // grabberA 合拢
    byte grabberA_close[2] = { 0xB0, 0xA2};
    // grabberB 停止开合
    byte grabberB_stop[2] = { 0xB0, 0xB0};
    // grabberB 张开
    byte grabberB_open[2] = { 0xB0, 0xB1};
    // grabberB 合拢
    byte grabberB_close[2] = { 0xB0, 0xB2};
    // 4轮 停止

    byte wheel_stop[2] = { 0xB1, 0xA0};
    // 4轮 前进
    byte wheel_forward[2] = { 0xB1, 0xA1};
    // 4轮 后退
    byte wheel_backward[2] = { 0xB1, 0xA2};
    // 4轮 左转
    byte wheel_left[2] = { 0xB1, 0xA3};
    // 4轮 右转
    byte wheel_right[2] = { 0xB1, 0xA4};
    // 4轮 麦克纳姆左平移
    byte wheel_mec_left[2] = { 0xB1, 0xB0};
    // 4轮 麦克纳姆右平移
    byte wheel_mec_right[2] = { 0xB1, 0xB1};


    // A4号机 左摆0.5秒
    byte rotoA_left1[2] = { 0xB2, 0xA1};
    // A4号机 右摆0.5秒
    byte rotoA_right1[2] = { 0xB2, 0xA2};
    // A4号机 左摆到底
    byte rotoA_left[2] = { 0xB2, 0xA3};
    // A4号机 右摆到底
    byte rotoA_right[2] = { 0xB2, 0xA4};
    // A4号机 停止
    byte rotoA_stop[2] = { 0xB2, 0xA0};
    // B4号机 左摆0.5秒
    byte rotoB_left1[2] = { 0xB2, 0xB1};
    // B4号机 右摆0.5秒
    byte rotoB_right1[2] = { 0xB2, 0xB2};
    // B4号机 左摆到底
    byte rotoB_left[2] = { 0xB2, 0xB3};
    // B4号机 右摆到底
    byte rotoB_right[2] = { 0xB2, 0xB4};
    // B4号机 停止
    byte rotoB_stop[2] = { 0xB2, 0xB0};
    // A球 左转0.5秒
    byte sphereA_left1[2] = { 0xB3, 0xA1};
    // A球 右转0.5秒
    byte sphereA_right1[2] = { 0xB3, 0xA2};
    // A球 持续左转
    byte sphereA_left[2] = { 0xB3, 0xA3};
    // A球 持续右转
    byte sphereA_right[2] = { 0xB3, 0xA4};
    // A球 停止
    byte sphereA_stop[2] = { 0xB3, 0xA0};
    // A球 左转角度(需配合角度卡片，默认0度）
    byte sphereA_left3[2] = { 0xB3, 0xAB};
    // A球 右转角度(需配合角度卡片，默认0度）
    byte sphereA_left4[2] = { 0xB3, 0xAC};
   // A球 左转角度30度
    byte sphereA_left30[2] = { 0xB3, 0xA5};
    // A球 左转角度45度
    byte sphereA_left45[2] = { 0xB3, 0xA6};
    // A球 左转角度60度
    byte sphereA_left60[2] = { 0xB3, 0xA7};
    // A球 左转角度90度
    byte sphereA_left90[2] = { 0xB3, 0xA8};
    // A球 左转角度120度
    byte sphereA_left120[2] = { 0xB3, 0xA9};
    // A球 左转角度180度
    byte sphereA_left180[2] = { 0xB3, 0xAA};
    // B球 左转0.5秒
    byte sphereB_left1[2] = { 0xB3, 0xB1};
    // B球 右转0.5秒
    byte sphereB_right1[2] = { 0xB3, 0xB2};
    // B球 持续左转
    byte sphereB_left[2] = { 0xB3, 0xB3};
    // B球 持续右转
    byte sphereB_right[2] = { 0xB3, 0xB4};
    // B球 停止
    byte sphereB_stop[2] = { 0xB3, 0xB0};
    // B球 左转角度(需配合角度卡片，默认0度）
    byte sphereB_left3[2] = { 0xB3, 0xBB};
    // B球 右转角度(需配合角度卡片，默认0度）
    byte sphereB_left4[2] = { 0xB3, 0xBC};
   // B球 左转角度30度
    byte sphereB_left30[2] = { 0xB3, 0xB5};
    // B球 左转角度45度
    byte sphereB_left45[2] = { 0xB3, 0xB6};
    // B球 左转角度60度
    byte sphereB_left60[2] = { 0xB3, 0xB7};
    // B球 左转角度90度
    byte sphereB_left90[2] = { 0xB3, 0xB8};
    // B球 左转角度120度
    byte sphereB_left120[2] = { 0xB3, 0xB9};
    // B球 左转角度180度
    byte sphereB_left180[2] = { 0xB3, 0xBA};
    //MUSIC 录音
    byte music_record[2] = { 0xB4, 0xFF};    
    //MUSIC 播放录音
    byte music_play_record[2] = { 0xB4, 0xFE};    
   //MUSIC 播放声音由于音乐很多，只校验第一位0xB4，然后读取第二位 0x00-0x63 0-99首
    byte conditionA_leftbracket[2] ={0xB5,0xA0};
    //第一种条件提示符{ 
    byte conditionA_rightbracket[2] ={0xB5,0xA1};
    //第一种条件提示符{ 
    byte conditionB_leftbracket[2] ={0xB5,0xA2};
    //第二种条件提示符[
    byte conditionB_rightbracket[2] ={0xB5,0xA3};
    //第二种条件提示符]
    byte conditionC_leftbracket[2] ={0xB5,0xA4};
    //第二种条件提示符[
    byte conditionC_rightbracket[2] ={0xB5,0xA5};
    //第二种条件提示符]

};

#endif





















