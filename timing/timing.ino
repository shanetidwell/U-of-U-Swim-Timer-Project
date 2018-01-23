#include <SPI.h>
#include <nRF24L01.h>
//#include <printf.h>
#include <RF24.h>
//#include <RF24_config.h>
RF24 radio(7,8);

const uint64_t rxAddr = 0xF0F0F0F0E1LL;
int button = 5;
bool pressed = false; 
bool sending = false;
//unsigned int t = 0;
unsigned long timer = 0;
bool buttonState = 0;
int goLED = 2;
int stopLED = 4;

//*****************************************************
//--------------
//SET LANE HERE
//--------------
unsigned int identifier = 1;
//******************************************************

void setup()
{
  pinMode(goLED,OUTPUT);
  pinMode(stopLED,OUTPUT);
  pinMode(button,INPUT_PULLUP);
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.setRetries(8,15);
  radio.openWritingPipe(rxAddr);
  radio.openReadingPipe(1, rxAddr);
  //radio.stopListening();
  while(!Serial);
  Serial.begin(9600);
}

void loop()
{
  
  radio.startListening();
  
 //listening to the other radio
  Serial.println("Waiting...");
  digitalWrite(stopLED,HIGH);
  bool message = false;
  bool a = true;
  
  while(!message){
    //if (a == true){Serial.println("entered loop");a=false;}
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
      unsigned int seconds   = capture/1000;
      unsigned int hundreths = (capture % 1000)/10;
      unsigned int messageToSend[3] = {identifier, seconds, hundreths};
      radio.write(&messageToSend, sizeof(messageToSend));
      break;
    }
  }

  //delay(1000);
}

