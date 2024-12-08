#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define coinSLotPin 19

LiquidCrystal_I2C lcd(0x27, 20, 2);

void setup() {

    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);

    Serial.begin(9600);
    pinMode(coinSLotPin, INPUT_PULLUP);
}

int prevVal = HIGH, count = 0;

unsigned long startTime = millis();

void loop() {
    const int value = digitalRead(coinSLotPin);
    if (prevVal != value) {
        if (value == LOW) {
            startTime = millis();
        } else {
            const unsigned long endTime = millis() - startTime;
            Serial.print("elapsed time: ");
            Serial.println(endTime);
            if (endTime > 15) {
                count++;
                Serial.println(count);
                lcd.clear();
                lcd.print(count);
            }
        }
        prevVal = value;
    }
}

