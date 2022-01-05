#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
RF24 radio(9, 10); // CE, CSN
const byte add[6] ="00001";
Servo power;
Servo control;
void setup() {
  power.attach(4);
  control.attach(5);
  radio.begin();
  radio.openReadingPipe(0,add); // 00002
  radio.setPALevel(RF24_PA_MIN);
    radio.startListening();
    Serial.begin(9600);
}
void loop() {

  if ( radio.available()) {
    while (radio.available()) {
     int data[2];
      int onOff=0;
      int angleV=0;
     radio.read(&data, sizeof(data));
     angleV = data[0];
      onOff= data[1];
      Serial.print("angle V is ");
      Serial.print(data[0]);
      Serial.println(" ");
      Serial.print("contV is ");
      Serial.print(data[1]);
      Serial.println(" ");
      control.write(angleV);
      if(onOff==1){
        power.write(45);
      }else if (onOff==-1){
        power.write(55);
      }else{
        power.write(50);
      }
      
    }
    
//    radio.stopListening();
//    buttonState = digitalRead(button);
//    radio.write(&buttonState, sizeof(buttonState));
//  }
}
}
