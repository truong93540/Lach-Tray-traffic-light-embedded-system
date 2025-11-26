/*
 * ==============================================================
 * * * * CODE SLAVE (NẠP VÀO ARDUINO UNO/NANO) * * * *
 *
 * CẬP NHẬT:
 * - Đổi chân 0, 1 (RX, TX) sang chân A0, A1 (An toàn hơn).
 * - Vẫn giữ Serial Debug.
 * ==============================================================
 */

#include <Arduino.h>
#include <SoftwareSerial.h>

// --- 1. CẤU HÌNH PHẦN CỨNG (ĐÃ THAY ĐỔI PIN) ---
int clockPin1 = 2;
int dataPin1 = 13;   // <-- ĐÃ ĐỔI sang A1
int latchPin1 = 12;  // <-- ĐÃ ĐỔI sang A0

int clockPin2 = 5;
int dataPin2 = 4;
int latchPin2 = 3;

int clockPin3 = 8;
int dataPin3 = 7;
int latchPin3 = 6;

int clockPin4 = 11;
int dataPin4 = 10;
int latchPin4 = 9;
int delayTime = 4;

// --- 2. BIẾN LOGIC (GIỮ NGUYÊN) ---
const byte digitCode[10][7] = {
  {0,0,0,0,0,0,1}, {1,0,0,1,1,1,1}, {0,0,1,0,0,1,0}, {0,0,0,0,1,1,0}, {1,0,0,1,1,0,0},
  {0,1,0,0,1,0,0}, {0,1,0,0,0,0,0}, {0,0,0,1,1,1,1}, {0,0,0,0,0,0,0}, {0,0,0,0,1,0,0}
};
byte data1 = 0, data2 = 0, data3 = 0, data4 = 0;

unsigned long x1 = 70000;
unsigned long x2 = 80000;
unsigned long x3 = 90000;
const unsigned long v1 = 3000;
const unsigned long v2 = 3000;
const unsigned long v3 = 3000;

int Mode = 0;
const int MODE_AUTO = 0;
const int MODE_OFF = 1;
const int MODE_FLASH = 2;

unsigned long autoStartTime = 0;
unsigned long flashLastToggleTime = 0;
bool flashState = false;

// --- 4. GIAO TIẾP VỚI ESP32 ---
SoftwareSerial espSerial(A3, A4); // RX = A3, TX = A4
String inputString = "";
bool stringComplete = false;

// --- 5. HÀM LOGIC GỐC (GIỮ NGUYÊN TỪ CODE 11:07 PM) ---
void DisplayNumber(int num1, int num2, int num3) {
  // (Nội dung hàm DisplayNumber của bạn giữ nguyên)
  int hangchuc1 = num1 / 10;
  int hangdonvi1 = num1 % 10;
  int hangchuc2 = num2 / 10;
  int hangdonvi2 = num2 % 10;
  int hangchuc3 = num3 / 10;
  int hangdonvi3 = num3 % 10;

  data2 = 0; bitSet(data2 , 0);
  digitalWrite(latchPin2, LOW); shiftOut(dataPin2, clockPin2, MSBFIRST, data2); digitalWrite(latchPin2, HIGH);
  data1 = 0;
  for(int i=0; i<7; i++) if(digitCode[hangchuc1][i] == 1) bitSet(data1 , i);
  digitalWrite(latchPin1, LOW); shiftOut(dataPin1, clockPin1, MSBFIRST, data1); digitalWrite(latchPin1, HIGH);
  delay(delayTime);

  data2 = 0; bitSet(data2 , 1);
  digitalWrite(latchPin2, LOW); shiftOut(dataPin2, clockPin2, MSBFIRST, data2); digitalWrite(latchPin2, HIGH);
  data1 = 0;
  for(int i=0; i<7; i++) if(digitCode[hangdonvi1][i] == 1) bitSet(data1 , i);
  digitalWrite(latchPin1, LOW); shiftOut(dataPin1, clockPin1, MSBFIRST, data1); digitalWrite(latchPin1, HIGH);
  delay(delayTime);

  data2 = 0; bitSet(data2 , 2);
  digitalWrite(latchPin2, LOW); shiftOut(dataPin2, clockPin2, MSBFIRST, data2); digitalWrite(latchPin2, HIGH);
  data1 = 0;
  for(int i=0; i<7; i++) if(digitCode[hangchuc2][i] == 1) bitSet(data1 , i);
  digitalWrite(latchPin1, LOW); shiftOut(dataPin1, clockPin1, MSBFIRST, data1); digitalWrite(latchPin1, HIGH);
  delay(delayTime);

  data2 = 0; bitSet(data2 , 3);
  digitalWrite(latchPin2, LOW); shiftOut(dataPin2, clockPin2, MSBFIRST, data2); digitalWrite(latchPin2, HIGH);
  data1 = 0;
  for(int i=0; i<7; i++) if(digitCode[hangdonvi2][i] == 1) bitSet(data1 , i);
  digitalWrite(latchPin1, LOW); shiftOut(dataPin1, clockPin1, MSBFIRST, data1); digitalWrite(latchPin1, HIGH);
  delay(delayTime);

  data2 = 0; bitSet(data2 , 4);
  digitalWrite(latchPin2, LOW); shiftOut(dataPin2, clockPin2, MSBFIRST, data2); digitalWrite(latchPin2, HIGH);
  data1 = 0;
  for(int i=0; i<7; i++) if(digitCode[hangchuc3][i] == 1) bitSet(data1 , i);
  digitalWrite(latchPin1, LOW); shiftOut(dataPin1, clockPin1, MSBFIRST, data1); digitalWrite(latchPin1, HIGH);
  delay(delayTime);

  data2 = 0; bitSet(data2 , 5);
  digitalWrite(latchPin2, LOW); shiftOut(dataPin2, clockPin2, MSBFIRST, data2); digitalWrite(latchPin2, HIGH);
  data1 = 0;
  for(int i=0; i<7; i++) if(digitCode[hangdonvi3][i] == 1) bitSet(data1 , i);
  digitalWrite(latchPin1, LOW); shiftOut(dataPin1, clockPin1, MSBFIRST, data1); digitalWrite(latchPin1, HIGH);
  delay(delayTime);
}

void ModeOff() {
  // (Nội dung hàm ModeOff của bạn giữ nguyên)
  data1 = 0;
  digitalWrite(latchPin1, LOW); shiftOut(dataPin1, clockPin1, MSBFIRST, data1); digitalWrite(latchPin1, HIGH);
  data2 = 0;
  digitalWrite(latchPin2, LOW); shiftOut(dataPin2, clockPin2, MSBFIRST, data2); digitalWrite(latchPin2, HIGH);
  data3 = 0;
  digitalWrite(latchPin3, LOW); shiftOut(dataPin3, clockPin3, MSBFIRST, data3); digitalWrite(latchPin3, HIGH);
  data4 = 0;
  digitalWrite(latchPin4, LOW); shiftOut(dataPin4, clockPin4, MSBFIRST, data4); digitalWrite(latchPin4, HIGH);
}

// --- 6. HÀM LOGIC (VIẾT LẠI NON-BLOCKING) ---
void ModeAuto_nonBlocking() {
  unsigned long totalCycleTime = x1 + v1 + x2 + v2 + x3 + v3;
  if (totalCycleTime == 0) return; 
  
  unsigned long currentTime = (millis() - autoStartTime) % totalCycleTime;

  // (Nội dung 6 pha logic đèn của bạn giữ nguyên)
  if (currentTime < x1) {
    data3 = 0; bitSet(data3, 0); bitSet(data3, 5);
    digitalWrite(latchPin3, LOW); shiftOut(dataPin3, clockPin3, MSBFIRST, data3); digitalWrite(latchPin3, HIGH);
    data4 = 0; bitSet(data4, 2);
    digitalWrite(latchPin4, LOW); shiftOut(dataPin4, clockPin4, MSBFIRST, data4); digitalWrite(latchPin4, HIGH);
    DisplayNumber((x1 - currentTime + 999) / 1000, (x1 + v1 - currentTime + 999) / 1000, (x1 + v1 + x2 + v2 - currentTime + 999) / 1000);
  }
  else if (currentTime < x1 + v1) {
    data3 = 0; bitSet(data3, 1); bitSet(data3, 5);
    digitalWrite(latchPin3, LOW); shiftOut(dataPin3, clockPin3, MSBFIRST, data3); digitalWrite(latchPin3, HIGH);
    data4 = 0; bitSet(data4, 2);
    digitalWrite(latchPin4, LOW); shiftOut(dataPin4, clockPin4, MSBFIRST, data4); digitalWrite(latchPin4, HIGH);
    DisplayNumber((x1 + v1 - currentTime + 999) / 1000, (x1 + v1 - currentTime + 999) / 1000, (x1 + v1 + x2 + v2 - currentTime + 999) / 1000);
  }
  else if (currentTime < x1 + v1 + x2) {
    data3 = 0; bitSet(data3, 2); bitSet(data3, 3);
    digitalWrite(latchPin3, LOW); shiftOut(dataPin3, clockPin3, MSBFIRST, data3); digitalWrite(latchPin3, HIGH);
    data4 = 0; bitSet(data4, 2);
    digitalWrite(latchPin4, LOW); shiftOut(dataPin4, clockPin4, MSBFIRST, data4); digitalWrite(latchPin4, HIGH);
    DisplayNumber((x1 + v1 + x2 + v2 + x3 + v3 - currentTime + 999) / 1000, (x1 + v1 + x2 - currentTime + 999) / 1000, (x1 + v1 + x2 + v2 - currentTime + 999) / 1000);
  }
  else if (currentTime < x1 + v1 + x2 + v2) {
    data3 = 0; bitSet(data3, 2); bitSet(data3, 4);
    digitalWrite(latchPin3, LOW); shiftOut(dataPin3, clockPin3, MSBFIRST, data3); digitalWrite(latchPin3, HIGH);
    data4 = 0; bitSet(data4, 2);
    digitalWrite(latchPin4, LOW); shiftOut(dataPin4, clockPin4, MSBFIRST, data4); digitalWrite(latchPin4, HIGH);
    DisplayNumber((x1 + v1 + x2 + v2 + x3 + v3 - currentTime + 999) / 1000, (x1 + v1 + x2 + v2 - currentTime + 999) / 1000, (x1 + v1 + x2 + v2 - currentTime + 999) / 1000);
  }
  else if (currentTime < x1 + v1 + x2 + v2 + x3) {
    data3 = 0; bitSet(data3, 2); bitSet(data3, 5);
    digitalWrite(latchPin3, LOW); shiftOut(dataPin3, clockPin3, MSBFIRST, data3); digitalWrite(latchPin3, HIGH);
    data4 = 0; bitSet(data4, 0);
    digitalWrite(latchPin4, LOW); shiftOut(dataPin4, clockPin4, MSBFIRST, data4); digitalWrite(latchPin4, HIGH);
    DisplayNumber((x1 + v1 + x2 + v2 + x3 + v3 - currentTime + 999) / 1000, ((x1 + v1) * 2 + x2 + v2 + x3 + v3 - currentTime + 999) / 1000, (x1 + v1 + x2 + v2 + x3 - currentTime + 999) / 1000);
  }
  else { // Pha 6
    data3 = 0; bitSet(data3, 2); bitSet(data3, 5);
    digitalWrite(latchPin3, LOW); shiftOut(dataPin3, clockPin3, MSBFIRST, data3); digitalWrite(latchPin3, HIGH);
    data4 = 0; bitSet(data4, 1);
    digitalWrite(latchPin4, LOW); shiftOut(dataPin4, clockPin4, MSBFIRST, data4); digitalWrite(latchPin4, HIGH);
    DisplayNumber((x1 + v1 + x2 + v2 + x3 + v3 - currentTime + 999) / 1000, ((x1 + v1) * 2 + x2 + v2 + x3 + v3 - currentTime + 999) / 1000, (x1 + v1 + x2 + v2 + x3 + v3 - currentTime + 999) / 1000);
  }
}

void FlashYellow_nonBlocking() {
  const int interval = 300;
  if (millis() - flashLastToggleTime >= interval) {
    flashLastToggleTime = millis();
    flashState = !flashState; 

    if (flashState) {
      data3 = 0; bitSet(data3, 1); bitSet(data3, 4);
      digitalWrite(latchPin3, LOW); shiftOut(dataPin3, clockPin3, MSBFIRST, data3); digitalWrite(latchPin3, HIGH);
      data4 = 0; bitSet(data4, 1);
      digitalWrite(latchPin4, LOW); shiftOut(dataPin4, clockPin4, MSBFIRST, data4); digitalWrite(latchPin4, HIGH);
    } else {
      ModeOff(); 
    }
  }
}

// --- 7. HÀM XỬ LÝ LỆNH TỪ ESP32 ---
void processCommand() {
  if (stringComplete) {
    inputString.trim();
    Serial.println("Arduino Received: " + inputString); // <-- DEBUG
    
    char cmdType = inputString.charAt(0);
    
    if (cmdType == 'O') {
      Mode = MODE_OFF;
      ModeOff(); 
      Serial.println("Mode set to: OFF"); // <-- DEBUG
    } 
    else if (cmdType == 'F') {
      if (Mode != MODE_FLASH) {
        ModeOff();
        flashLastToggleTime = millis();
        flashState = false;
      }
      Mode = MODE_FLASH;
      Serial.println("Mode set to: FLASH"); // <-- DEBUG
    } 
    else if (cmdType == 'A') {
      int c[4];
      c[0] = inputString.indexOf(',');
      c[1] = inputString.indexOf(',', c[0] + 1);
      c[2] = inputString.indexOf(',', c[1] + 1);
      
      x1 = atol(inputString.substring(c[0] + 1, c[1]).c_str());
      x2 = atol(inputString.substring(c[1] + 1, c[2]).c_str());
      x3 = atol(inputString.substring(c[2] + 1).c_str());
      
      Serial.println("Mode set to: AUTO"); // <-- DEBUG
      Serial.println("x1=" + String(x1) + ", x2=" + String(x2) + ", x3=" + String(x3)); // <-- DEBUG

      if (Mode != MODE_AUTO) {
        autoStartTime = millis(); 
      }
      Mode = MODE_AUTO;
    }
    
    inputString = "";
    stringComplete = false;
  }
}

// --- 8. HÀM SETUP ---
void setup(){
  Serial.begin(115200); // <-- DEBUG ĐÃ ĐƯỢC THÊM
  
  espSerial.begin(9600);    // Dùng để nói chuyện với ESP32 (Chân A3)
  inputString.reserve(100); 
  
  // Cài đặt pin (ĐÃ THAY ĐỔI)
  pinMode(clockPin1, OUTPUT);
  pinMode(dataPin1, OUTPUT);      // (Chân A1)
  pinMode(latchPin1, OUTPUT);     // (Chân A0)
  pinMode(clockPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);
  pinMode(latchPin2, OUTPUT);
  pinMode(clockPin3, OUTPUT);
  pinMode(dataPin3, OUTPUT);
  pinMode(latchPin3, OUTPUT);
  pinMode(clockPin4, OUTPUT);
  pinMode(dataPin4, OUTPUT);
  pinMode(latchPin4, OUTPUT);
  
  Mode = MODE_OFF; 
  ModeOff();
  Serial.println("Arduino Slave Ready. Waiting for commands..."); // <-- DEBUG
}

// --- 9. HÀM LOOP (NON-BLOCKING) ---
void loop() {
  while (espSerial.available()) {
    char inChar = (char)espSerial.read();
    if (inChar == '\n') {
      stringComplete = true;
    } else if (inChar != '\r') {
      inputString += inChar;
    }
  }
  
  processCommand();

  switch(Mode) {
    case MODE_AUTO: 
      ModeAuto_nonBlocking(); 
      break;
    case MODE_OFF: 
      break;
    case MODE_FLASH:
      FlashYellow_nonBlocking();
      break;
  }
}