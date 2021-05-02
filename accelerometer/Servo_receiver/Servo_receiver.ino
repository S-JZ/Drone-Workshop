
// Receiver
#include <nRF24L01.h>
#include <RF24.h>
#include<SPI.h>
#include<Servo.h>

/*
 * if radio unavailable we read angle
 * check if input and device is equal then :
 * if not radio available 
 * read angle
 * servo print
 * Serial monitor printing 
 * 
 */

RF24 radio(9,10);
const byte address[6] = "00001";
Servo servo;

char input[32]="";
const char device[32] = "Servo";
int angle=0;

void setup() {
  Serial.begin(9600);
  servo.attach(2);
  
  radio.begin();
  
  radio.openReadingPipe(0, address);
  radio.setChannel(100);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
 }

void loop() {
  while (!radio.available()) radio.read(&input,sizeof(input));
  if (strcmp(input,device)==0){
    while(!radio.available()){
      radio.read(&angle,sizeof(angle));
      servo.write(angle);
      Serial.println("input values :");
      Serial.println(input);
      Serial.println("Angle :");
      Serial.println(angle);
    }
    
  }
  delay(500);

}
