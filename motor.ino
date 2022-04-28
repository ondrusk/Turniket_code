// Krokový motor a driver

// čísla pinů pro digitální výstupy
const int in1 =  8;
const int in2 =  9;
const int in3 = 10;
const int in4 = 11;

// proměnná pro nastavení rychlosti,
// se zvětšujícím se číslem se rychlost zmenšuje
int rychlost = 1;
//
int uhel = 120;

void setup() {
  // inicializace digitálních výstupů
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  // plná rotace o 360 stupňů = 512 volání
  // funkce rotacePoSmeru() či rotaceProtiSmeru()
  for(int i=0;i<(uhel*64/45);i++){
    rotaceProtiSmeru();
  }
  // pauza po dobu 1 vteřiny
  delay(1000);
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
