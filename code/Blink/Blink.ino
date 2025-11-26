int clockPin1 = 2;
int dataPin1 = 1;
int latchPin1 = 0;

int clockPin2 = 5;
int dataPin2 = 4;
int latchPin2 = 3;

int clockPin3 = 8;
int dataPin3 = 7;
int latchPin3 = 6;

int clockPin4 = 11;
int dataPin4 = 10;
int latchPin4 = 9;

int Mode;
int btnAuto = A0;// nút điều khiển chế độ auto
int btnOff = A1;// nút tắt đèn
int btnFlashYellow = A2;// nút nháy đèn vàng
int delayTime = 5;


const byte digitCode[10][7] = {
  {0,0,0,0,0,0,1},  // 0
  {1,0,0,1,1,1,1},  // 1
  {0,0,1,0,0,1,0},  // 2
  {0,0,0,0,1,1,0},  // 3
  {1,0,0,1,1,0,0},  // 4
  {0,1,0,0,1,0,0},  // 5
  {0,1,0,0,0,0,0},  // 6
  {0,0,0,1,1,1,1},  // 7
  {0,0,0,0,0,0,0},  // 8
  {0,0,0,0,1,0,0}   // 9
};

byte data1 = 0;
byte data2 = 0;
byte data3 = 0;
byte data4 = 0;

unsigned long x1 = 18000;
unsigned long v1 = 3000;
unsigned long x2 = 34000;
unsigned long v2 = 3000;
unsigned long x3 = 22000;
unsigned long v3 = 3000;

void setup(){
  pinMode(clockPin1, OUTPUT);
  pinMode(dataPin1, OUTPUT);
  pinMode(latchPin1, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);
  pinMode(latchPin2, OUTPUT);
  pinMode(clockPin3, OUTPUT);
  pinMode(dataPin3, OUTPUT);
  pinMode(latchPin3, OUTPUT);
  pinMode(clockPin4, OUTPUT);
  pinMode(dataPin4, OUTPUT);
  pinMode(latchPin4, OUTPUT);
  pinMode(btnAuto, INPUT_PULLUP);
  pinMode(btnOff, INPUT_PULLUP);
  pinMode(btnFlashYellow, INPUT_PULLUP);
}

void DisplayNumber(int num1, int num2, int num3){
  int hangchuc1 = num1 / 10;
  int hangdonvi1 = num1 % 10;
  int hangchuc2 = num2 / 10;
  int hangdonvi2 = num2 % 10;
  int hangchuc3 = num3 / 10;
  int hangdonvi3 = num3 % 10;

  // tắt tất cả các led 7 sec, bật led 7 sec đầu tiên
  data2 = 0;
  bitSet(data2 , 0);
  digitalWrite(latchPin2, LOW);
  shiftOut(dataPin2, clockPin2, MSBFIRST, data2);
  digitalWrite(latchPin2, HIGH);

  // hiển thị hàng chục đường lạch tray rẽ trái
  data1 = 0;
  for(int i=0; i<7; i++){
    if(digitCode[hangchuc1][i] == 1){
      bitSet(data1 , i);
    }
  }
  digitalWrite(latchPin1, LOW);
  shiftOut(dataPin1, clockPin1, MSBFIRST, data1);
  digitalWrite(latchPin1, HIGH);
  delay(delayTime);

  // tắt tất cả các led 7 sec, bật led 7 sec thứ 2
  data2 = 0;
  bitSet(data2 , 1);
  digitalWrite(latchPin2, LOW);
  shiftOut(dataPin2, clockPin2, MSBFIRST, data2);
  digitalWrite(latchPin2, HIGH);

  // hiển thị hàng đơn vị đường lạch tray rẽ trái
  data1 = 0;
  for(int i=0; i<7; i++){
    if(digitCode[hangdonvi1][i] == 1){
      bitSet(data1 , i);
    }
  }
  digitalWrite(latchPin1, LOW);
  shiftOut(dataPin1, clockPin1, MSBFIRST, data1);
  digitalWrite(latchPin1, HIGH);
  delay(delayTime);

  // tắt tất cả các led 7 sec, bật led 7 sec thứ 3
  data2 = 0;
  bitSet(data2 , 2);
  digitalWrite(latchPin2, LOW);
  shiftOut(dataPin2, clockPin2, MSBFIRST, data2);
  digitalWrite(latchPin2, HIGH);

  // hiển thị hàng chục đường lạch tray rẽ đi thẳng
  data1 = 0;
  for(int i=0; i<7; i++){
    if(digitCode[hangchuc2][i] == 1){
      bitSet(data1 , i);
    }
  }
  digitalWrite(latchPin1, LOW);
  shiftOut(dataPin1, clockPin1, MSBFIRST, data1);
  digitalWrite(latchPin1, HIGH);
  delay(delayTime);


  // tắt tất cả các led 7 sec, bật led 7 sec thứ 4
  data2 = 0;
  bitSet(data2 , 3);
  digitalWrite(latchPin2, LOW);
  shiftOut(dataPin2, clockPin2, MSBFIRST, data2);
  digitalWrite(latchPin2, HIGH);
  // hiển thị hàng đơn vị đường lạch tray rẽ đi thẳng
  data1 = 0;
  for(int i=0; i<7; i++){
    if(digitCode[hangdonvi2][i] == 1){
      bitSet(data1 , i);
    }
  }
  digitalWrite(latchPin1, LOW);
  shiftOut(dataPin1, clockPin1, MSBFIRST, data1);
  digitalWrite(latchPin1, HIGH);
  delay(delayTime);

  // tắt tất cả các led 7 sec, bật led 7 sec thứ 5
  data2 = 0;
  bitSet(data2 , 4);
  digitalWrite(latchPin2, LOW);
  shiftOut(dataPin2, clockPin2, MSBFIRST, data2);
  digitalWrite(latchPin2, HIGH);
  // hiển thị hàng chục đường nguyễn văn linh
  data1 = 0;
  for(int i=0; i<7; i++){
    if(digitCode[hangchuc3][i] == 1){
      bitSet(data1 , i);
    }
  }
  digitalWrite(latchPin1, LOW);
  shiftOut(dataPin1, clockPin1, MSBFIRST, data1);
  digitalWrite(latchPin1, HIGH);
  delay(delayTime);

  // tắt tất cả các led 7 sec, bật led 7 sec thứ 6
  data2 = 0;
  bitSet(data2 , 5);
  digitalWrite(latchPin2, LOW);
  shiftOut(dataPin2, clockPin2, MSBFIRST, data2);
  digitalWrite(latchPin2, HIGH);
  // hiển thị hàng đơn vị đường nguyễn văn linh
  data1 = 0;
  for(int i=0; i<7; i++){
    if(digitCode[hangdonvi3][i] == 1){
      bitSet(data1 , i);
    }
  }
  digitalWrite(latchPin1, LOW);
  shiftOut(dataPin1, clockPin1, MSBFIRST, data1);
  digitalWrite(latchPin1, HIGH);
  delay(delayTime);
}

void ModeAuto() {
  unsigned long start = millis();
  // Mốc thời gian 1 từ 0 giây đến 18 giây
  while(millis() - start > 0 && millis() - start < x1 && digitalRead(btnOff) == HIGH && digitalRead(btnFlashYellow) == HIGH){

    // đèn xanh lạch tray rẽ trái bật và đèn đỏ lạch tray đi thẳng bật
    data3 = 0;// bit của data = 00000000
    bitSet(data3, 0); //bit của data = 10000000
    bitSet(data3, 5); //bit của data = 10000100
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, MSBFIRST, data3);
    digitalWrite(latchPin3, HIGH);

    // đèn đỏ nguyễn văn linh đi thẳng bật
    data4 = 0;
    bitSet(data4, 2);
    digitalWrite(latchPin4, LOW);
    shiftOut(dataPin4, clockPin4, MSBFIRST, data4);
    digitalWrite(latchPin4, HIGH);
    DisplayNumber((x1-(millis()-start))/1000, (x1+v1-(millis()-start))/1000, (x1+v1+x2+v2-(millis()-start))/1000);
    if (digitalRead(btnOff) == LOW  || digitalRead(btnFlashYellow) == LOW ) return;
  }
  // Mốc thời gian 1 từ 19 giây đến 21 giây
  while((millis()-start) > x1 && (millis()-start) < x1+v1 && digitalRead(btnOff) == HIGH && digitalRead(btnFlashYellow) == HIGH ){

    // đèn vàng lạch tray rẽ trái bật và đèn đỏ lạch tray đi thẳng bật
    data3 = 0;
    bitSet(data3, 1);
    bitSet(data3, 5);
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, MSBFIRST, data3);
    digitalWrite(latchPin3, HIGH);

    // đèn đỏ nguyễn văn linh đi thẳng bật
    data4 = 0;
    bitSet(data4, 2);
    digitalWrite(latchPin4, LOW);
    shiftOut(dataPin4, clockPin4, MSBFIRST, data4);
    digitalWrite(latchPin4, HIGH);
    DisplayNumber((x1+v1-(millis()-start))/1000, (x1+v1-(millis()-start))/1000, (x1+v1+x2+v2-(millis()-start))/1000);
    if (digitalRead(btnOff) == LOW  || digitalRead(btnFlashYellow) == LOW) return;
  }
  // Mốc thời gian 1 từ 22 giây đến 55 giây
  while((millis()-start) > x1+v1 && (millis()-start) < x1+v1+x2 && digitalRead(btnOff) == HIGH && digitalRead(btnFlashYellow) == HIGH ){

    // đèn đỏ lạch tray rẽ trái bật và đèn xanh lạch tray đi thẳng bật
    data3 = 0;
    bitSet(data3, 2);
    bitSet(data3, 3);
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, MSBFIRST, data3);
    digitalWrite(latchPin3, HIGH);

    // đèn đỏ nguyễn văn linh đi thẳng bật
    data4 = 0;
    bitSet(data4, 2);
    digitalWrite(latchPin4, LOW);
    shiftOut(dataPin4, clockPin4, MSBFIRST, data4);
    digitalWrite(latchPin4, HIGH);
    DisplayNumber((x1+v1+x2+v2+x3+v3-(millis()-start))/1000, (x1+v1+x2-(millis()-start))/1000, (x1+v1+x2+v2-(millis()-start))/1000);
    if (digitalRead(btnOff) == LOW  || digitalRead(btnFlashYellow) == LOW) {
      return;
    }
  }

  // Mốc thời gian 1 từ 56 giây đến 58 giây
  while((millis()-start) > x1+v1+x2 && (millis()-start) < x1+v1+x2+v2 && digitalRead(btnOff) == HIGH && digitalRead(btnFlashYellow) == HIGH ){

    // đèn đỏ lạch tray rẽ trái bật và đèn vàng lạch tray đi thẳng bật
    data3 = 0;
    bitSet(data3, 2);
    bitSet(data3, 4);
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, MSBFIRST, data3);
    digitalWrite(latchPin3, HIGH);

    // đèn đỏ nguyễn văn linh đi thẳng bật
    data4 = 0;
    bitSet(data4, 2);
    digitalWrite(latchPin4, LOW);
    shiftOut(dataPin4, clockPin4, MSBFIRST, data4);
    digitalWrite(latchPin4, HIGH);
    DisplayNumber((x1+v1+x2+v2+x3+v3-(millis()-start))/1000, (x1+v1+x2+v2-(millis()-start))/1000, (x1+v1+x2+v2-(millis()-start))/1000);
    if (digitalRead(btnOff) == LOW  || digitalRead(btnFlashYellow) == LOW) {
      return;
    };
  }

  // Mốc thời gian 1 từ 59 giây đến 80 giây
  while((millis()-start) > x1+v1+x2+v2 && (millis()-start) < x1+v1+x2+v2+x3 && digitalRead(btnOff) == HIGH && digitalRead(btnFlashYellow) == HIGH ){

    // đèn đỏ lạch tray rẽ trái bật và đèn đỏ lạch tray đi thẳng bật
    data3 = 0;
    bitSet(data3, 2);
    bitSet(data3, 5);
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, MSBFIRST, data3);
    digitalWrite(latchPin3, HIGH);

    // đèn xanh nguyễn văn linh đi thẳng bật
    data4 = 0;
    bitSet(data4, 0);
    digitalWrite(latchPin4, LOW);
    shiftOut(dataPin4, clockPin4, MSBFIRST, data4);
    digitalWrite(latchPin4, HIGH);
    
    DisplayNumber((x1+v1+x2+v2+x3+v3-(millis()-start))/1000, ((x1+v1)*2+x2+v2+x3+v3-(millis()-start))/1000, (x1+v1+x2+v2+x3-(millis()-start))/1000);
    if (digitalRead(btnOff) == LOW  || digitalRead(btnFlashYellow) == LOW){
      return;
    }
  }

  // Mốc thời gian 1 từ 81 giây đến 83 giây
  while((millis()-start) > x1+v1+x2+v2+x3 && (millis()-start) < x1+v1+x2+v2+x3+v3 && digitalRead(btnOff) == HIGH && digitalRead(btnFlashYellow) == HIGH ){

    // đèn đỏ lạch tray rẽ trái bật và đèn đỏ lạch tray đi thẳng bật
    data3 = 0;
    bitSet(data3, 2);
    bitSet(data3, 5);
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, MSBFIRST, data3);
    digitalWrite(latchPin3, HIGH);

    // đèn vàng nguyễn văn linh đi thẳng bật
    data4 = 0;
    bitSet(data4, 1);
    digitalWrite(latchPin4, LOW);
    shiftOut(dataPin4, clockPin4, MSBFIRST, data4);
    digitalWrite(latchPin4, HIGH);
    DisplayNumber((x1+v1+x2+v2+x3+v3-(millis()-start))/1000, ((x1+v1)*2+x2+v2+x3+v3-(millis()-start))/1000, (x1+v1+x2+v2+x3+v3-(millis()-start))/1000);
    if (digitalRead(btnOff) == LOW  || digitalRead(btnFlashYellow) == LOW) {
      return;
    }
  }
}

void ModeOff(){
  data1 = 0;
  digitalWrite(latchPin1, LOW);
  shiftOut(dataPin1, clockPin1, MSBFIRST, data1);
  digitalWrite(latchPin1, HIGH);
  data2 = 0;
  digitalWrite(latchPin2, LOW);
  shiftOut(dataPin2, clockPin2, MSBFIRST, data2);
  digitalWrite(latchPin2, HIGH);
  data3 = 0;
  digitalWrite(latchPin3, LOW);
  shiftOut(dataPin3, clockPin3, MSBFIRST, data3);
  digitalWrite(latchPin3, HIGH);
  data4 = 0;
  digitalWrite(latchPin4, LOW);
  shiftOut(dataPin4, clockPin4, MSBFIRST, data4);
  digitalWrite(latchPin4, HIGH);
}

void FlashYellow() {
  unsigned long previousMillis = millis();
  const int interval = 300;  // Thời gian nhấp nháy 300ms
  bool state = false; // Biến trạng thái đèn (ban đầu tắt)
  ModeOff(); // Tắt tất cả trước khi vào chế độ nhấp nháy

  while (digitalRead(btnOff) == HIGH && digitalRead(btnAuto) == HIGH) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis; // Cập nhật thời gian
      state = !state; // Đảo trạng thái

      if (state) {
        // Bật đèn vàng
        data3 = 0;
        bitSet(data3, 1); // Bật LED trên shift register 3
        bitSet(data3, 4);
        digitalWrite(latchPin3, LOW);
        shiftOut(dataPin3, clockPin3, MSBFIRST, data3);
        digitalWrite(latchPin3, HIGH);

        data4 = 0;
        bitSet(data4, 1); // Bật LED trên shift register 4
        digitalWrite(latchPin4, LOW);
        shiftOut(dataPin4, clockPin4, MSBFIRST, data4);
        digitalWrite(latchPin4, HIGH);
      } else {
        // Tắt đèn vàng
        data3 = 0;
        digitalWrite(latchPin3, LOW);
        shiftOut(dataPin3, clockPin3, MSBFIRST, data3);
        digitalWrite(latchPin3, HIGH);

        data4 = 0;
        digitalWrite(latchPin4, LOW);
        shiftOut(dataPin4, clockPin4, MSBFIRST, data4);
        digitalWrite(latchPin4, HIGH);
      }
    }

    // Kiểm tra nếu nút bấm thay đổi trạng thái -> thoát khỏi vòng lặp
    if (digitalRead(btnAuto) == LOW || digitalRead(btnOff) == LOW) {
      return;
    }
  }
}


void loop() {
  if (digitalRead(btnAuto) == LOW){
    Mode = 0;
  }
  if(digitalRead(btnOff) == LOW){
    Mode = 1;
  }
  if(digitalRead(btnFlashYellow) == LOW) {
    Mode = 2;
  }
  switch(Mode) {
    case 0: 
      ModeAuto();
      break;
    case 1:
      ModeOff();
      break;
    case 2:
      FlashYellow();
      break;
    default: Mode = 0;
  }

}