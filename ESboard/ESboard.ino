#include "config.h"
BluetoothSerial SerialBT;
String BTData;  // receive string from BT

int current_DAC = 180;  // default DAC value


void setup() {
  /* serial initiate */
  Serial.begin(115200);

  /* BT */
  SerialBT.begin("ESBoard-v1");
  Serial.println("BlueTooth is ready to use");

  /* DAC */
  dacWrite(DAC1, current_DAC);

  // 设置定时器 80M/分频系数
  hw_timer_t* timer = NULL;                    // 声明一个定时器
  timer = timerBegin(0, 80, true);             //基础时间是1MHz 1us
  timerAttachInterrupt(timer, onTimer, true);  // 绑定定时器
  timerAlarmWrite(timer, 1000, true);          // 就是设置时间(us)
  // initiate GPIO output
  pinMode(DIN, OUTPUT);
  pinMode(LE, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(CLR, OUTPUT);

  //initiate switches
  digitalWrite(CLR, HIGH);  // 关闭所有开关
  delayMicroseconds(1000);
  digitalWrite(CLR, LOW);
  digitalWrite(LE, HIGH);
  digitalWrite(CLK, HIGH);

  //初始化频率全0
  setFrequency();

  timerAlarmEnable(timer);  // 启用定时器
  Serial.println("end setup");
}


void loop() {
  // Serial.println(String((analogRead(NEG) * 3.3) / 4095.0));
  if (SerialBT.available()) {
    BTData = SerialBT.readStringUntil('\xff');
    // SerialBT.println(BTData);  //蓝牙发送镜像的接受数据
    Serial.println(BTData);  // 串口发送收到的数据

    if (BTData.compareTo("vup") == 0) {
      current_DAC = current_DAC + 5;
      String txt_msg = "now DAC = " + String(current_DAC);
      SerialBT.println(txt_msg);
      dacWrite(DAC1, current_DAC);
    } else if (BTData.compareTo("vdown") == 0) {
      current_DAC = current_DAC - 5;
      String txt_msg = "now DAC = " + String(current_DAC);
      SerialBT.println(txt_msg);
      dacWrite(DAC1, current_DAC);
    } else if (BTData.compareTo("random") == 0) { // 随机方向
      ES_dir = currentTime % 4;
      String txt_msg;
      if (ES_dir == 0) {
        txt_msg = "Random : up";
      } else if (ES_dir == 1) {
        txt_msg = "Random : down";
      } else if (ES_dir == 2) {
        txt_msg = "Random : left";
      } else if (ES_dir == 3) {
        txt_msg = "Random : right";
      }else if (ES_dir == 4) {
        txt_msg = "Random : left up";
      }else if (ES_dir == 5) {
        txt_msg = "Random : left down";
      }else if (ES_dir == 6) {
        txt_msg = "Random : right up";
      }else if (ES_dir == 7) {
        txt_msg = "Random : right down";
      }else if (ES_dir == 8) {
        txt_msg = "Random : clockwise";
      }else if (ES_dir == 9) {
        txt_msg = "Random : counterclockwise";
      }else{
        txt_msg = "Random : ERROR";
      }
      dacWrite(DAC1, current_DAC);
      SerialBT.println(txt_msg);
      // Serial.println(txt_msg);
    } else if (BTData.compareTo("reset") == 0) { /*Reset DAC value*/
      current_DAC = 170;
    } else if (BTData.compareTo("sample") == 0) { /* ADC sampling */
      SerialBT.println("ADC(V):" + String((analogRead(NEG) * 3.3) / 4095.0));
    }
  }
}