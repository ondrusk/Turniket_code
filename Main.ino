//#include <Ethernet.h>
//#include <SD.h>
//#include "secrets.h" (nelze najít knihovnu)
//#include "ThingSpeak.h"

//byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

#include <SPI.h>
#include <MFRC522.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

const int buzzer = 11; 
#define LEDR 13
#define LEDG 12
#define SS_PIN 9
#define RST_PIN 8
MFRC522 mfrc522(SS_PIN, RST_PIN);   // vytvoří MFRC522 instanci.

 // čísla pinů pro digitální výstupy korokového motoru
const int in1 = 4;
const int in2 = 5;
const int in3 = 6;
const int in4 = 7;
// proměnná pro nastavení rychlosti,
// se zvětšujícím se číslem se rychlost zmenšuje
int rychlost = 1;
//úhel otočení turniketu
int uhel = 120;

//const String name = Pavel Novak;
//unsigned long myChannelNumber = 1717774;
//const char * myWriteAPIKey = WKLHT0RNI4UTFQQQ;

void setup() 
{
  Serial.begin(9600);   // spustí sériovou komunikaci
  SPI.begin();      // spustí  SPI bus
  mfrc522.PCD_Init();   // spustí MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
    // inicializace digitálních výstupů
  pinMode(in1, OUTPUT); // prohlásí in 1-4 (výstup krokového motoru) jako výstup
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(LEDR, OUTPUT); // prohlásí LEDR jako výstup
  pinMode(LEDG, OUTPUT); // prohlásí LEDG jako výstup
  pinMode(buzzer, OUTPUT);

  // inicializace LCD
  lcd.begin();
  // zapnutí podsvícení
  lcd.backlight();
  // vytisknutí hlášky na první řádek
  lcd.print("Priloz kartu");
  lcd.setCursor ( 19, 3);
  lcd.print("!");



}
void loop() 
{
  // hledání nové karty
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // výběr karty
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  // ukáže UID na sériový monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "C7 11 7E B4") // Povolí kartu s UID: C7 11 7E B4
  {
    Serial.println("Authorized access");
    Serial.println();
    //zápis do databáze thingspeak
   // ThingSpeak.setField(1,"Pavel Novak");
   // ThingSpeak.writeField(myChannelNumber, myWriteAPIKey);

    lcd.setCursor ( 0, 0 );
    lcd.print("                    ");
    lcd.setCursor ( 0, 1 );
    lcd.print("                    ");
    lcd.setCursor ( 0, 2 );
    lcd.print("                    ");
    
    lcd.setCursor ( 0, 0 );
    lcd.print("Pavel Novak");
    lcd.setCursor ( 0, 1 );
    lcd.print("--------------------");
    lcd.setCursor ( 0, 2 );
    lcd.print("Pristup povolen");

  tone(buzzer, 1000); // sepne bzučák o * KHZ
  delay(1000);        // doba sepnutí bzučáku
  noTone(buzzer);     // zastaví bzučák
  
  digitalWrite(LEDG, HIGH); // rozsvítí zelenou diodu
  delay(1000);
  digitalWrite(LEDG, LOW); // zhasne zelenou diodu
    
   // plná rotace o 360 stupňů = 512 volání
  // funkce rotacePoSmeru() či rotaceProtiSmeru()
  for(int i=0;i<(uhel*64/45);i++){
    rotacePoSmeru();
  }
  // pauza po dobu 1 vteřiny
  delay(1000);
    
    delay(3000);

    lcd.setCursor ( 0, 0 );
    lcd.print("                    ");
    lcd.setCursor ( 0, 1 );
    lcd.print("                    ");
    lcd.setCursor ( 0, 2 );
    lcd.print("                    ");

    lcd.setCursor ( 0, 0 );
    lcd.print("Priloz kartu");
    lcd.setCursor ( 19, 3);
    lcd.print("!");
  }

   
  
 else   {
    Serial.println(" Access denied");

    lcd.setCursor ( 0, 0 );
    lcd.print("                    ");
    lcd.setCursor ( 0, 1 );
    lcd.print("                    ");
    lcd.setCursor ( 0, 2 );
    lcd.print("                    ");

    lcd.setCursor ( 0, 0 );
    lcd.print("Neznama karta");
    lcd.setCursor ( 0, 1 );
    lcd.print("--------------------");
    lcd.setCursor ( 0, 2 );
    lcd.print("Pristup zamitnut");
    
    digitalWrite(LEDR, HIGH); // rozsvítí červenou diodu
    
    tone(buzzer, 1000); // sepne bzučák o * KHZ
    delay(1000);        // doba sepnutí bzučáku
    noTone(buzzer);     // zastaví bzučák
    delay(100);
    tone(buzzer, 500); // sepne bzučák o * KHZ
    delay(500);        // doba sepnutí bzučáku
    noTone(buzzer);     // zastaví bzučák
  
    digitalWrite(LEDR, LOW); // zhasne červenou diodu
    delay(3000);

    lcd.setCursor ( 0, 0 );
    lcd.print("                    ");
    lcd.setCursor ( 0, 1 );
    lcd.print("                    ");
    lcd.setCursor ( 0, 2 );
    lcd.print("                    ");

    lcd.setCursor ( 0, 0 );
    lcd.print("Priloz kartu");
    lcd.setCursor ( 19, 3);
    lcd.print("!");
  }
} 
// zde následují funkce pro volání jednotlivých
// kroků pro otočení po či proti směru hodinových
// ručiček
void rotacePoSmeru() {
  krok1();
  krok2();
  krok3();
  krok4();
  krok5();
  krok6();
  krok7();
  krok8();
}
void rotaceProtiSmeru() {
  krok8();
  krok7();
  krok6();
  krok5();
  krok4();
  krok3();
  krok2();
  krok1();
}
// každý krok obsahuje výrobcem dané pořadí
// pro správné spínání motoru a následnou
// pauzu, kterou určujeme rychlost otáčení
void krok1(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(rychlost);
}
void krok2(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(rychlost);
}
void krok3(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(rychlost);
}
void krok4(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(rychlost);
}
void krok5(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(rychlost);
}
void krok6(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
  delay(rychlost);
}
void krok7(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(rychlost);
}
void krok8(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(rychlost);
}
