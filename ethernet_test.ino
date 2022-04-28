#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
 
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
 
void setup() 
{
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
 
  Serial.print(F("Starting SD..."));
  if(!SD.begin(4)) 
  {
    Serial.println(F("failed"));
  }
  else 
  {
    Serial.println(F("ok"));
  }
 
  Serial.print(F("Starting ethernet..."));
  if(!Ethernet.begin(mac)) 
  {
    Serial.println(F("failed"));
  }
  else 
  {
    Serial.println(Ethernet.localIP());
  }
  digitalWrite(10, HIGH);
}
 
void loop() 
{
}
