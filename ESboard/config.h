#include "Arduino.h"
#include <BluetoothSerial.h>
#include <iostream>
#include <string>

using namespace std;


#define DAC1 25 //DAC输出
#define DIN 26  //IO26
#define LE 27   //IO27
#define CLK 14  // IO14
#define CLR 12  // IO12
#define NEG 34 // ADC采样


extern int frequency_table[32];  // 32通道的频率
extern int currentTime; //时间0-999
extern int ES_dir; // 这代表了输出的方向0-9


void setFrequency(); //设置32通道频率
void IRAM_ATTR onTimer(); //中断服务函数

//设置每个方向时的电刺激输出
void up();
void down();
void left();
void right();
void left_up();
void left_down();
void right_up();
void right_down();
void clockwise();
void counterclockwise();