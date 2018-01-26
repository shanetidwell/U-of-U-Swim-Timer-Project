#include <SPI.h>
#include <nRF24L01.h>
//#include <printf.h>
#include <RF24.h>
//#include <RF24_config.h>

RF24 radio(7,8);

const byte rxAddr[6] = "00001";

void setup()
{
  while(!Serial);
  Serial.begin(9600);

  radio.begin();
  radio.openReadingPipe(0, rxAddr);

  radio.startListening();
}

void loop()
{
  if(radio.available())
  {
    int text = 0;
    radio.read(&text, sizeof(text));

    Serial.println(text);
  }
}

  


