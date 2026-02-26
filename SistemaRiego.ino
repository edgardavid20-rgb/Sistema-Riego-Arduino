#include <LiquidCrystal.h>
LiquidCrystal lcd(11,10,9,8,7,6);

// ----- Pines -----
const int potHumedad = A0;
const int pinLM35 = A1;
const int pinLDR = A2;

const int motor1 = 5;   
const int motor2 = 3;   
const int ledLuz = 4;

// ----- Variables -----
int humedad = 0;
float tempC = 0;
int luzLDR = 0;

void setup() {

  lcd.begin(16,2);

  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(ledLuz, OUTPUT);

  lcd.setCursor(0,0);
  lcd.print("Sistema Riego");
  delay(2000);
  lcd.clear();
}

void loop() {

  // ----- Lecturas -----
  humedad = analogRead(potHumedad);
  humedad = map(humedad, 0, 1023, 0, 100);

  int lecturaTemp = analogRead(pinLM35);
  tempC = (lecturaTemp * 5.0 * 100.0) / 1024.0;

  luzLDR = analogRead(pinLDR);

  // ----- Control motores -----

  if(humedad < 55 && tempC > 25){
      analogWrite(motor1, 200);
      analogWrite(motor2, 200);
  }
  else if(humedad < 55){
      analogWrite(motor1, 150);
      analogWrite(motor2, 0);
  }
  else{
      analogWrite(motor1, 0);
      analogWrite(motor2, 0);
  }

  // ----- Control luz -----
  if(luzLDR < 300){
      digitalWrite(ledLuz, HIGH);
  } else {
      digitalWrite(ledLuz, LOW);
  }

  // ----- LCD (sin clear) -----
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(tempC);
  lcd.print("C  ");

  lcd.setCursor(9,0);
  lcd.print("H:");
  lcd.print(humedad);
  lcd.print("% ");

  lcd.setCursor(0,1);

  if(humedad < 55){
      lcd.print("REGANDO        ");
  } else {
      lcd.print("SUELO HUMEDO   ");
  }

  delay(800);
}
