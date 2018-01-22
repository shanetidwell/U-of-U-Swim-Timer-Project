#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int button = 9;
unsigned int t1 = 0;
unsigned int t2 = 0;
bool buttonState;
int message = 2;
unsigned long t = 0;
int LED = 30;

RF24 radio(7, 8);

const byte rxAddr[6] = "00001";

void setup()
{
  pinMode(button, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  
  while (!Serial);
  Serial.begin(9600);
  
  radio.begin();
  //radio.openReadingPipe(0, rxAddr);
  
  //radio.startListening();
  radio.setRetries(15,15);
  radio.openWritingPipe(rxAddr);
  radio.stopListening();
  
  Serial.println("Ready");
  t = millis();
}

void loop()
{
  //Waiting to send some crap
  digitalWrite(LED, HIGH);
  
  while (true){
  //Wait to receive signal to send start time signal
    if (Serial.available()){
       int state = Serial.read() - '0';
       if (state == 1){ //If correct signal is received, begin doing stuff
        
          //const char text[2] = "GO"
      
          radio.write(&message, sizeof(message));
          
         // t1 = millis();
          //Serial.println("Sent Stuff");
          break;
      }
    }
  }


  //After Sending Stuff, setup radio for listening
  digitalWrite(LED, LOW);
  
  radio.openReadingPipe(0, rxAddr);
  radio.startListening();

  //Listening for crap to come in
  while (true){
    if (radio.available())
      {
      //char t[32] = {0};
      unsigned int a = 0;
      radio.read(&a, sizeof(a));
      digitalWrite(LED, HIGH);
      
      //t2 = millis() - t1;

      //Serial.print("Shane Time = ");
      Serial.println(a);
      //Serial.print("My Time = ");
      //Serial.println(t2);
      break;
  }
}

  radio.openWritingPipe(rxAddr);
  radio.stopListening();
  
}
