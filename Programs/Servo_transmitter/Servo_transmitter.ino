//Transmitter

#include <nRF24L01.h>
#include <RF24.h>
#include<SPI.h>

/*for my void loop part
 * set value to input received from pin
 * check value > check +threshold or value<check-threshold
 * radio.write(device adrress and size)
 * map my angle
 * radio.write(angle, size)
 * check = value 
 * Serial monitor printing
 */


RF24 radio(9,10);
const byte address[6] = "00001";
#define pin A0

const int threshold = 20;

int value = 0;


int angle = 0;

int check = 0;

const char device[32] = "Servo";



void setup() {
  Serial.begin(9600);

  radio.begin();
  
  radio.openWritingPipe(address);
  radio.setChannel(100);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
  }

}

void loop() {
  //setting value from pin
  value= analogRead(pin);
  if (value > check + threshold || value < check-threshold){
    radio.write(&device, sizeof(device));
    angle= map(value,0,1023,0,180);
    radio.write(&angle,sizeof(angle));
    check=value;
  //Serial monitor prints :
  // angle 
  Serial.println("Angle : ");
  Serial.println(angle);
  
  //value
  Serial.println("Value : ");
  Serial.println(value);
  Serial.println();
    
  }
  delay(1000);
}
