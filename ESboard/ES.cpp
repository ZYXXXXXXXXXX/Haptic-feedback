#include "Arduino.h"
#include "config.h"
#include <cmath>

int currentTime = 0;
int frequency_table[32];
int ES_dir = 0;
// 计时器的时间长度ms
int timer_counting = 1500;
//电刺激频率Hz
int ES_fre = 250;
int ES_time = 200;


void setFrequency() {
  //设置32通道频率全为0
  for (int i = 0; i < 32; i++) {
    frequency_table[i] = 0;
  }
}



// 定时器中断服务函数
void IRAM_ATTR onTimer() {
  setFrequency();
  if (ES_dir == 0) {
    up();
  } else if (ES_dir == 1) {
    down();
  } else if (ES_dir == 2) {
    left();
  } else if (ES_dir == 3) {
    right();
  } else if (ES_dir == 4) {
    left_up();
  } else if (ES_dir == 5) {
    left_down();
  } else if (ES_dir == 6) {
    right_up();
  } else if (ES_dir == 7) {
    right_down();
  } else if (ES_dir == 8) {
    clockwise();
  } else if (ES_dir == 9) {
    counterclockwise();
  }

  digitalWrite(LE, LOW);
  for (int i = 0; i < 32; i++) {
    if (frequency_table[i] == 0) {
      //close switch
      digitalWrite(DIN, LOW);
      digitalWrite(CLK, LOW);
      digitalWrite(CLK, HIGH);
    } else if (currentTime % frequency_table[i] == 0) {
      // open switch
      digitalWrite(DIN, HIGH);
      digitalWrite(CLK, LOW);
      digitalWrite(CLK, HIGH);
    } else {
      //close switch
      digitalWrite(DIN, LOW);
      digitalWrite(CLK, LOW);
      digitalWrite(CLK, HIGH);
    }
  }
  digitalWrite(LE, HIGH);
  // 增加1ms
  if (currentTime < timer_counting) {
    currentTime = currentTime + 1;
  } else {
    currentTime = 0;
  }
}



void up() {
  if (currentTime > round(timer_counting * 0 / 6) && currentTime < round(timer_counting * 0 / 6) + ES_time) {
    frequency_table[18] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 1 / 6) && currentTime < round(timer_counting * 1 / 6) + ES_time) {
    frequency_table[17] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 2 / 6) && currentTime < round(timer_counting * 2 / 6) + ES_time) {
    frequency_table[16] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 3 / 6) && currentTime < round(timer_counting * 3 / 6) + ES_time) {
    frequency_table[15] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 4 / 6) && currentTime < round(timer_counting * 4 / 6) + ES_time) {
    frequency_table[14] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 5 / 6) && currentTime < round(timer_counting * 5 / 6) + ES_time) {
    frequency_table[21] = round(1000.0 / ES_fre);
  }
}
void down() {
  if (currentTime > round(timer_counting * 0 / 6) && currentTime < round(timer_counting * 0 / 6) + ES_time) {
    frequency_table[21] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 1 / 6) && currentTime < round(timer_counting * 1 / 6) + ES_time) {
    frequency_table[14] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 2 / 6) && currentTime < round(timer_counting * 2 / 6) + ES_time) {
    frequency_table[15] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 3 / 6) && currentTime < round(timer_counting * 3 / 6) + ES_time) {
    frequency_table[16] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 4 / 6) && currentTime < round(timer_counting * 4 / 6) + ES_time) {
    frequency_table[17] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 5 / 6) && currentTime < round(timer_counting * 5 / 6) + ES_time) {
    frequency_table[18] = round(1000.0 / ES_fre);
  }
}

void left() {
  if (currentTime > round(timer_counting * 0 / 5) && currentTime < round(timer_counting * 0 / 5) + ES_time) {
    frequency_table[24] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 1 / 5) && currentTime < round(timer_counting * 1 / 5) + ES_time) {
    frequency_table[25] = round(1000.0 / ES_fre);
  }
}

void right() {
  if (currentTime > round(timer_counting * 0 / 5) && currentTime < round(timer_counting * 0 / 5) + ES_time) {
    frequency_table[7] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 1 / 5) && currentTime < round(timer_counting * 1 / 5) + ES_time) {
    frequency_table[6] = round(1000.0 / ES_fre);
  }
}

void left_up() {
  if (currentTime > round(timer_counting * 0 / 3) && currentTime < round(timer_counting * 0 / 3) + ES_time) {
    frequency_table[12] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 1 / 3) && currentTime < round(timer_counting * 1 / 3) + ES_time) {
    frequency_table[16] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 2 / 3) && currentTime < round(timer_counting * 2 / 3) + ES_time) {
    frequency_table[29] = round(1000.0 / ES_fre);
  }
}
void left_down() {
  if (currentTime > round(timer_counting * 0 / 3) && currentTime < round(timer_counting * 0 / 3) + ES_time) {
    frequency_table[2] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 1 / 3) && currentTime < round(timer_counting * 1 / 3) + ES_time) {
    frequency_table[16] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 2 / 3) && currentTime < round(timer_counting * 2 / 3) + ES_time) {
    frequency_table[20] = round(1000.0 / ES_fre);
  }
}
void right_up() {
  if (currentTime > round(timer_counting * 0 / 3) && currentTime < round(timer_counting * 0 / 3) + ES_time) {
    frequency_table[20] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 1 / 3) && currentTime < round(timer_counting * 1 / 3) + ES_time) {
    frequency_table[16] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 2 / 3) && currentTime < round(timer_counting * 2 / 3) + ES_time) {
    frequency_table[2] = round(1000.0 / ES_fre);
  }
}
void right_down() {
  if (currentTime > round(timer_counting * 0 / 3) && currentTime < round(timer_counting * 0 / 3) + ES_time) {
    frequency_table[29] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 1 / 3) && currentTime < round(timer_counting * 1 / 3) + ES_time) {
    frequency_table[16] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 2 / 3) && currentTime < round(timer_counting * 2 / 3) + ES_time) {
    frequency_table[12] = round(1000.0 / ES_fre);
  }
}
void clockwise() {
  if (currentTime > round(timer_counting * 0 / 4) && currentTime < round(timer_counting * 0 / 4) + ES_time) {
    frequency_table[21] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 1 / 4) && currentTime < round(timer_counting * 1 / 4) + ES_time) {
    frequency_table[4] = round(1000.0 / ES_fre);
    frequency_table[6] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 2 / 4) && currentTime < round(timer_counting * 2 / 4) + ES_time) {
    frequency_table[18] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 3 / 4) && currentTime < round(timer_counting * 3 / 4) + ES_time) {
    frequency_table[27] = round(1000.0 / ES_fre);
    frequency_table[25] = round(1000.0 / ES_fre);
  }
}
void counterclockwise() {
  if (currentTime > round(timer_counting * 0 / 4) && currentTime < round(timer_counting * 0 / 4) + ES_time) {
    frequency_table[21] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 1 / 4) && currentTime < round(timer_counting * 1 / 4) + ES_time) {
    frequency_table[27] = round(1000.0 / ES_fre);
    frequency_table[25] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 2 / 4) && currentTime < round(timer_counting * 2 / 4) + ES_time) {
    frequency_table[18] = round(1000.0 / ES_fre);
  } else if (currentTime > round(timer_counting * 3 / 4) && currentTime < round(timer_counting * 3 / 4) + ES_time) {
    frequency_table[4] = round(1000.0 / ES_fre);
    frequency_table[6] = round(1000.0 / ES_fre);
  }
}