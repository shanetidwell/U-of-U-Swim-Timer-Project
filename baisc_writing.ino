#include <SPI.h>
#include <nRF24L01.h>
//#include <printf.h>
#include <RF24.h>
//#include <RF24_config.h>

RF24 radio(7,8);

const byte rxAddr[6] = "00001";
void setup() {
  radio.begin();
  radio.setRetries(15,15);
  radio.openWritingPipe(rxAddr);

  radio.stopListening();
   while(!Serial);
  Serial.begin(9600);
  
}

void loop() {
  int text = millis();
  Serial.println(text);
  radio.write(&text, sizeof(text));

  delay(1000);
    

}
