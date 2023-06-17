
#include <TridentTD_LineNotify.h>
#include "./env.h";


const String Wifi_SSID = SSID;
const String Wifi_Password = PASSWORD;
const String LINE_TOKEN_CODE = LINE_TOKEN;
const String message = "เกิดการขโมย!";
const int outputPin = D4;
const int inputPin = D5;


void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println(LINE.getVersion());
  pinMode(outputPin, OUTPUT);
  pinMode(inputPin, INPUT);
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n", SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());
  String ipAddress = WiFi.localIP().toString();
  // กำหนด Line Token
  LINE.setToken(LINE_TOKEN);
  // ตัวอย่างส่งข้อความ
  LINE.notify("ทำการเชื่อมต่อใหม่ IP : " + ipAddress);
  // // ตัวอย่างส่งข้อมูล ตัวเลข
  // LINE.notify(2342);          // จำนวนเต็ม
  // LINE.notify(212.43434,5);   // จำนวนจริง แสดง 5 หลัก

  // // เลือก Line Sticker ได้จาก https://devdocs.line.me/files/sticker_list.pdf
  // LINE.notifySticker(3,240);        // ส่ง Line Sticker ด้วย PackageID 3 , StickerID 240
  // LINE.notifySticker("Hello",1,2);  // ส่ง Line Sticker ด้วย PackageID 1 , StickerID 2  พร้อมข้อความ

  // // ตัวอย่างส่ง รูปภาพ ด้วย url
  // LINE.notifyPicture("https://preview.ibb.co/j6G51n/capture25610417181915334.png");
  // LINE.notifyPicture("จตุธาตุ","https://www.fotoaparat.cz/storage/pm/09/10/23/670915_a5351.jpg");
}

void loop() {
  if (checkConnection()) {
    Serial.println(message);
    LINE.notify(message);
    LINE.notifySticker(6370, 11088017);
  } else {
    Serial.println("สถานะปกติ");
  }
}

bool checkConnection() {
  int pin1 = digitalRead(outputPin);
  int pin2 = digitalRead(inputPin);
  if (pin1 == pin2) {
    digitalWrite(outputPin, !pin1);
    delay(5000);
    return false;
  } else {
    delay(2000);
    return true;
  }
}
