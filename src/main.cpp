/* HT13K33に仕込んだLEDを明滅させるための適当なプログラム */
#include <Arduino.h>
#include "ht16k33.h"

// HT16K33 制御用クラス定義
HT16K33 HT;

// LED番号管理用
uint8_t led;
// 現在の明るさ設定
uint8_t currBrightness;
// 明るさを増加させているか否か
bool isUpper;

void setup() {

  // HT16K33 開始
  HT.begin(0x00);
  // 明るさ初期値 0設定
  currBrightness = 0;
  HT.setBrightness(currBrightness);
  // 上昇から
  isUpper = true;

  // ログ出力用シリアル通信
  // Serial.begin(9600);

  // 初期化にてすべてのLEDを順次点灯
  for (led=0; led<128; led++) {
    HT.setLedNow(led);
    delay(10);
  }
}

void loop() {
  // デバッグ用シリアル通信
  // Serial.print(F("CurrentBrightness value "));
  // Serial.print(currBrightness);
  // Serial.print("\r\n");

  // かあるさを現在の値へ変更
  HT.setBrightness(currBrightness);
  // 雰囲気を出すために適当なディレイ
  delay(100);

  if(currBrightness <= 0)
  {
    // 現在の明るさが0を下回る場合、明るさ上昇設定
    currBrightness = 0;
    isUpper = true;
  }
  if(currBrightness >= 15)
  {
    // 現在の明るさが15を上回る場合、明るさ下降設定
    currBrightness = 15;
    isUpper = false;
  }
  if(isUpper == true)
  {
    // 上昇設定なら明るさ加算
    currBrightness += 1;
  }
  else
  {
    // 下降設定なら明るさ減産
    currBrightness -= 1;
  }
}