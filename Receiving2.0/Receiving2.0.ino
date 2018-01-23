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

const uint64_t rxAddr = 0xF0F0F0F0E1LL;

void setup()
{
  pinMode(button, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  
  while (!Serial);
  Serial.begin(9600);
  
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.setRetries(8,15);
  radio.openReadingPipe(1, rxAddr);
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
  
  
  radio.startListening();

  //Listening for crap to come in
  while (true){
    if (radio.available())
      {
      //char t[32] = {0};
      unsigned long receivedMessage[3];
      radio.read(&receivedMessage, sizeof(receivedMessage));
      digitalWrite(LED, HIGH);
      
      //t2 = millis() - t1;
      String messageToSend = "";
      messageToSend = (String)receivedMessage[0] + " " + (String)receivedMessage[1] + " " + (String)receivedMessage[2];
      //Serial.print("Shane Time = ");
      Serial.println(messageToSend);
      //Serial.print("My Time = ");
      //Serial.println(t2);
      break;
  }
}

  radio.openWritingPipe(rxAddr);
  radio.stopListening();
  
}
