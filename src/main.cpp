#include <Arduino.h>

#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include "calc.h"
#define ROWS 4
#define COLS 4
char keys[ROWS][COLS] = {
  {'1','2', '3' ,'='},
  {'4','5','6' ,'+'},
  {'7','8', '9', '-'},
  { '0', 'c', '*', '/'},
};

byte rowPins[ROWS] = {5, 6, 7, 9};    // R1 - R4
byte colPins[COLS] = {4, 3, 2, 8};    // C1 - C4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.cursor();
  lcd.blink();
}
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

byte cursRow = 0;
byte cursCol = 0;
optString expr = optString();
void setDefaultCursor() {
  cursRow = 0;
  cursCol = 0;
}
static bool clickedEq = false;
void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.print("Key: ");
    Serial.println(key);
    if (key != '=' && clickedEq) {
      lcd.clear();
      setDefaultCursor();
      clickedEq = false;
    }
    else if (key == '=' && clickedEq) {
      return;
    }

    if (key == 'c') {
      lcd.clear();
      setDefaultCursor();
      expr = "";
      return;
    }
    lcd.setCursor(cursCol, cursRow);
    const char lastSymbol = expr[expr.len() - 1];
    if (key == '=' && !clickedEq) {
      for (char i = expr.len() - 1; i < expr.len(); i--)
      {
        char c = expr[i];
        if (isdigit(c) && isOperator(c)) {
            expr.del(i);
        }
      }
      const double result = calc(expr);
      expr = "";
      lcd.clear();

      lcd.print(result);
      clickedEq = true;
      return;
    }

    if (isOperator(lastSymbol) && isOperator(key)) {
      if (lastSymbol != key) {
        if (cursCol == 0 && cursRow == 1) {
          cursCol = 15;
          cursRow = 0;
        } else if (cursCol > 0) {
          cursCol--;
        }

        lcd.setCursor(cursCol, cursRow);
        lcd.print(key);
        cursCol++;
      }
      return;
    }
    lcd.print(key);

    if (cursCol >= 15) {
      cursCol = 0;
      if (cursRow < 1) {
        cursRow++;
        return;
      }
      cursRow--;
    } else {
      cursCol++;
    }
    Serial.println(key);
        Serial.println("IN1:");
    for (size_t i = 0; expr[i] != '\0'; i++)
    {
        Serial.print(expr[i]);
    }
        Serial.println("OUT1");
    expr += key;
    for (char i = 0; expr[i] != '\0'; i++) {
      Serial.print(expr[i]);
    }
  }
}