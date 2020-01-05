#define silnikPIN 10
#define plusPIN 3
#define minusPIN 4

int wypelnienie = 10; // wypelnienie na start
int wypelnienie_min = 5;
int wypelnienie_max = 255;
int spd = 50; //ms szybkosc zmiany
int zmiana = 1; // skok
unsigned long timer_max = 60000; // ms czas pracy silnika
int plus = LOW;
int minus = LOW;
int wyp_start = 6; // wypelnienie startu
unsigned long timer_now = millis();
unsigned long timer_diff = 0;
unsigned long timer_zero = millis();


void setup() {
  pinMode(silnikPIN, OUTPUT);//Konfiguracja pinu jako wyjścia 
  pinMode(plusPIN, INPUT_PULLUP);
  pinMode(minusPIN, INPUT_PULLUP);
  Serial.begin(9600);
  
  TCCR1B = TCCR1B & 11111000 | B00000100; // PWM 100Hz

}

void loop() {
  plus = digitalRead(plusPIN);
  minus = digitalRead(minusPIN);
  
  
  analogWrite(silnikPIN, wypelnienie); //Generujemy sygnał o zadanym wypełnieniu
  //Serial.print("Wypelnienie:");Serial.println(wypelnienie);
  //Serial.print("Plus:");Serial.println(plus);
  //Serial.print("Minus:");Serial.println(minus);
  //Serial.print("Timer:");Serial.println(timer_zero);
  
  if (wypelnienie == 0 && ((minus == HIGH && plus == LOW) || (minus == LOW && plus == HIGH))) { //start
    wypelnienie = wypelnienie + wyp_start;
    timer_zero = millis();
  }
  
  if (wypelnienie >= 0 && wypelnienie < wypelnienie_max && minus == HIGH && plus == LOW) { // dodaj 
    wypelnienie = wypelnienie + zmiana;
    Serial.println('PLUS');
    timer_zero = millis();
    delay(spd);
  }
  if (wypelnienie > wypelnienie_min && wypelnienie <= wypelnienie_max && minus == LOW && plus == HIGH) { // zmniejsz
      Serial.println('MINUS');
      wypelnienie = wypelnienie - zmiana;
      timer_zero = millis();
      delay(spd);
  } 

  if ((minus == LOW && plus == HIGH) || (minus == HIGH && plus == LOW)) {
    timer_zero = millis();
  }

  timer_now = millis();
  timer_diff = timer_now - timer_zero;

  if (timer_diff > timer_max) {
    timer_zero = timer_now;
    wypelnienie = 0;
  }
  
      

  
  
}
