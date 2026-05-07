#include <SchooMyUtilities.h>
#include <TM1637Display.h>
SchooMyUtilities scmUtils = SchooMyUtilities();
// 基礎プログラミングII 第3回 Scrummyプロジェクト
TM1637Display num_display_14_15(14, 15);
float i = 0;
float count = 0;
void dispNumber(TM1637Display numDisplay, float f) {
  String val = String(f, 1);
  int num = val.toInt();
  uint8_t dot = 0x0;
  if(!val.substring(val.length() - 1).equals("0")) {
    num = val.toFloat() * 10;
    dot = 0b00100000;
  }
  numDisplay.showNumberDecEx(num, dot, false);
}
void dispBlank(TM1637Display numDisplay) {
  uint8_t SEG_BLANK[] = {0,0,0,0};
  numDisplay.setSegments(SEG_BLANK);
}

void setup() {
  Serial.begin(9600);
  num_display_14_15.setBrightness(0x0f);
  pinMode(19, INPUT);
}

void loop() {
  dispNumber(num_display_14_15, constrain(0, -999, 9999));
  if ((!digitalRead(19) == 1)) {
    if ((i == 0)) {
      count += 1;
      dispNumber(num_display_14_15, constrain(count, -999, 9999));
      i = 1;
    }
  } else if ((!digitalRead(19) != 1)) {
    i = 0;
  }
}
