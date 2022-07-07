#include <DHT.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);//atau 0x3F
DHT dht(8, DHT11);

float kelembaban;
float suhu;
int msensor = A0;
int msvalue= 21;
int pinLDR = A1;
int LDR;
int relayPin = 6;

void setup() {
    lcd.init();
    dht.begin();
    lcd.backlight();
    pinMode(msensor, INPUT);
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, HIGH);
    lcd.setCursor(2, 0);
    lcd.print("KELOMPOK 4");
    lcd.setCursor(2, 1);
    lcd.print("EMBEDDED SYSTEM ");
    for (int i = 0 ; i < 16; i ++) {
        lcd.scrollDisplayLeft();
        delay(500);
    }
}

void loop() {
  
    lcd.clear();
    
    //dht 11
    kelembaban = dht.readHumidity();
    suhu = dht.readTemperature();
    lcd.setCursor(0, 0);
    lcd.print("Moist : "); 
    lcd.print(kelembaban);
    
    lcd.setCursor(0, 1);
    lcd.print("Temp  : ");
    lcd.print(suhu);

    delay(2000);
    lcd.clear();

    //ldr sensor
  
    lcd.setCursor(0, 0);
    LDR = analogRead(pinLDR);
    lcd.print("Kecerahan : ");
    lcd.print(LDR);
    
    if (LDR < 300){
      lcd.setCursor(0, 1);
      lcd.print("Cahaya Cukup");
      }
    else{
      lcd.setCursor(0, 1);
      lcd.print("Cahaya Kurang");
      }
    
    delay(2000);
    lcd.clear();
    
    //moisture sensor
    msvalue = analogRead(msensor);
    msvalue = map(msvalue,550,0,0,100);
    
    if(msvalue<20){
      digitalWrite(relayPin, LOW);
      lcd.backlight();
      while(true){
        lcd.setCursor(0, 0);
        lcd.print("Mositure  : ");
        lcd.print(msvalue);
        lcd.print("%");
        lcd.setCursor(0, 1);
        lcd.print("Water Pump: ON");
        delay(500);
        msvalue = analogRead(msensor);
        msvalue = map(msvalue,550,0,0,100);
        
        if(msvalue > 20){
          digitalWrite(relayPin, HIGH);
          lcd.setCursor(0, 0);
          lcd.print("Mositure  : ");
          lcd.print(msvalue);
          lcd.print("%");
          lcd.setCursor(0, 1);
          lcd.print("Water Pump : OFF");
          delay(1000);
          break;
        }
      }
    }
    
    else
     {
      digitalWrite(relayPin, HIGH);
      lcd.setCursor(0, 0);
      lcd.print("Mositure  : ");
      lcd.print(msvalue);
      lcd.print("%");
      lcd.setCursor(0, 1);
      lcd.print("Water Pump: OFF");
      delay(2000);       
     }
}
