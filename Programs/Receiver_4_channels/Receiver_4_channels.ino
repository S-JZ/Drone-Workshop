
// receiver for 4 channels
#include <EnableInterrupt.h>

/*
 * reader function
 * calculator
 * setup 
 * loop 
 */

#define CH1 0
#define CH2 1
#define CH3 2
#define CH4 3


#define CH1_INPUT A0
#define CH2_INPUT A1
#define CH3_INPUT A2
#define CH4_INPUT A3

uint16_t rc_values[4];
uint32_t rc_channels[4];
volatile uint16_t rc_share[4];

void reader(){
  noInterrupts();
  
  memcpy(rc_values, (const void *)rc_share, sizeof(rc_share));
  interrupts();
}

void calculator(uint8_t channels, uint8_t pin){
  if (digitalRead(pin)==HIGH){
    rc_channels[channels]=micros();
  }
  else{
    uint16_t compare=(uint16_t)micros()- rc_channels[channels];
  }
}

void calch1(){calculator(CH1_INPUT,CH1);}
void calch2(){calculator(CH2_INPUT,CH2);}
void calch3(){calculator(CH3_INPUT,CH3);}
void calch4(){calculator(CH4_INPUT,CH4);}

void setup() {
  Serial.begin(57600);

  pinMode(CH1_INPUT, INPUT);
  pinMode(CH2_INPUT, INPUT);
  pinMode(CH3_INPUT, INPUT);
  pinMode(CH4_INPUT, INPUT);

  enableInterrupt(CH1_INPUT,calch1,CHANGE);
  enableInterrupt(CH2_INPUT,calch2,CHANGE);
  enableInterrupt(CH3_INPUT,calch3,CHANGE);
  enableInterrupt(CH4_INPUT,calch4,CHANGE);
  
  
}

void loop() {
  reader();
  Serial.println("Channel 1 :");
  Serial.println(rc_values[CH1]);
  Serial.println("\nChannel 2 :");
  Serial.println(rc_values[CH2]);
  Serial.println("\nChannel 3 :");
  Serial.println(rc_values[CH3]);
  Serial.println("\nChannel 4 :");
  Serial.println(rc_values[CH4]);
  delay(250);
}
