#include <Servo.h>
#include <Wire.h>
#include <iarduino_I2C_Matrix_8x8.h>

// изображения замка для матрицы 8х8
iarduino_I2C_Matrix_8x8 disp(0x09);
byte image_1[8] = { 0b00000000,
                    0b00011000,
                    0b00100100,
                    0b00100100,
                    0b00111100,
                    0b01111110,
                    0b01100110,
                    0b01111110 
                  };

byte image_2[8] = { 0b00000000,
                    0b00011100,
                    0b00100000,
                    0b00100000,
                    0b00111100,
                    0b01111110,
                    0b01100110,
                    0b01111110 
                  };

Servo servo1;
int btn = 2;
int btn_val;

void setup() {
  servo1.attach(5);
  disp.begin(&Wire);
  pinMode(btn, INPUT);

  servo1.write(0);
  Serial.begin(9600);  // для отладки
  Serial2.begin(115200);  // для считывания данных с esp32
}

void loop() {
  bool btn_val = digitalRead(btn);

  if (Serial2.available() > 0) {
    char data = Serial2.read();
    Serial.println(data);
    
    if (data == '1') {
       servo1.write(90);
      disp.drawImage(image_2);
    } else if (data == '0') {
       servo1.write(0);
       disp.drawImage(image_1);
    }
  }

  // прблема дребизга кнопки
  // if (btn_val == HIGH) {
  //     servo1.write(90);
  //     disp.drawImage(image_2);
  // }
  // else {
  //   servo1.write(0);
  //   disp.drawImage(image_1);
  // }
}
