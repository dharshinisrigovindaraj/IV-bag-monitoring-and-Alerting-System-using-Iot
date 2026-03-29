#define BLYNK_TEMPLATE_ID "TMPL3I5Xlt4WF"
#define BLYNK_TEMPLATE_NAME "IOT based IV bag monitor"
#define BLYNK_AUTH_TOKEN "1u77jnng471AYZ3l2paK2T8oii3bhzQk"
#include <HX711_ADC.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> 
#define ledPin 7
#define buzz 8
HX711_ADC LoadCell(4, 5); 
LiquidCrystal_I2C lcd(0x27, 16, 2); 
#define BLYNK_PRINT Serial

char auth[] = "1u77jnng471AYZ3l2paK2T8oii3bhzQk";
char ssid[] = "Galaxy M14 5G 516E";
char pass[] = "Dharshinisri@99";
int taree = 6;
int a = 0;
float b = 0;

void setup() {
  Serial.begin(57600);
  pinMode (taree, INPUT_PULLUP);
  LoadCell.begin(); 
  LoadCell.start(1000); 

  LoadCell.setCalFactor(475); 
 
  lcd.begin(2,16); 
  lcd.backlight(); 
  
  lcd.setCursor(1, 0); 
  lcd.print(" IOT BASED IV"); 
  lcd.setCursor(0, 1); 
  lcd.print(" BAG MONITORING ");
  delay(2000);
  lcd.clear();
  
  pinMode(ledPin, OUTPUT);
  pinMode(buzz, OUTPUT);
}
void loop() { 
  lcd.setCursor(1, 0); 
  lcd.print("Digital Scale ");
  LoadCell.update(); 
  float i = LoadCell.getData(); 
  Serial.println(i);
  if(LoadCell.getData() <= 150){
    digitalWrite(ledPin, HIGH);
  }else{
    digitalWrite(ledPin, LOW);
  }
  if(LoadCell.getData() <= 50){
    digitalWrite(buzz, HIGH);
  }else{
    digitalWrite(buzz, LOW);
  }
  
 if (i<0)
 {
  i = i * (-1);
  lcd.setCursor(0, 1);
  lcd.print("-");
   lcd.setCursor(8, 1);
  lcd.print("-");
 }
 else
 {
   lcd.setCursor(0, 1);
  lcd.print(" ");
   lcd.setCursor(8, 1);
  lcd.print(" ");
 }
  
  lcd.setCursor(1, 1); 
  lcd.print(i, 1); 
  lcd.print("g ");
  float z = i/28.3495;
  lcd.setCursor(9, 1);
  lcd.print(z, 2);
  lcd.print("oz ");

  if (i>=5000)
  {
    i=0;
  lcd.setCursor(0, 0); 
  lcd.print("  Over Loaded   "); 
  delay(200);
  }
  if (digitalRead (taree) == LOW)
  {
    lcd.setCursor(0, 1);
    lcd.print("   Taring...    ");
    LoadCell.start(1000);
    lcd.setCursor(0, 1);
    lcd.print("                ");
  }
}
