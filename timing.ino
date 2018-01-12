#include <SPI.h>
#include <nRF24L01.h>
//#include <printf.h>
#include <RF24.h>
//#include <RF24_config.h>
RF24 radio(7,8);

const byte rxAddr[6] = "00001";
int button = 5;
bool pressed = false; 
bool sending = false;
//unsigned int t = 0;
unsigned long timer = 0;
bool buttonState = 0;
int goLED = 2;
int stopLED = 4;
void setup()
{
  pinMode(goLED,OUTPUT);
  pinMode(stopLED,OUTPUT);
  pinMode(button,INPUT_PULLUP);
  radio.begin();
  radio.setRetries(15,15);
  //radio.openWritingPipe(rxAddr);

  //radio.stopListening();
  while(!Serial);
  Serial.begin(9600);
}

void loop()
{
  radio.openReadingPipe(0, rxAddr);
  radio.startListening();
  
 //listening to the other radio
  Serial.println("Waiting...");
  digitalWrite(stopLED,HIGH);
  bool message = false;
  bool a = true;
  
  while(!message){
    if (a == true){Serial.println("entered loop");a=false;}
    if(radio.available()){
      int text = 0;
      Serial.println("receiving stuff");
      radio.read(&text, sizeof(text));
      Serial.println(text);
      
 //checking for special message
 
        if (text == 2){
          Serial.println("Yay");
            message = true;
            timer = millis();
            digitalWrite(goLED,HIGH);
            digitalWrite(stopLED,LOW);
            //Serial.println(goLED);
            //Serial.println(stopLED);
            radio.stopListening();        
        }
  
      }
  }
  
//getting ready to send information
  radio.stopListening();
  radio.openWritingPipe(rxAddr);
  
  while(true){
    
//waiting for button to be pressed
    
    buttonState = digitalRead(button);
    
 //once the button is pressed send the time
 
    if (buttonState==LOW){
      //calculate the time
      unsigned long capture = millis()-timer;
      Serial.println(capture);
      digitalWrite(goLED,LOW);
      digitalWrite(stopLED,HIGH);
      //Serial.println(goLED);
      //Serial.println(stopLED);
 //send the time
 
      radio.write(&capture, sizeof(capture));
      break;
    }
  }

  //delay(1000);
}

