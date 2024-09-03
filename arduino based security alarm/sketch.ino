#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(10, 11, 12, 13, A0, A1);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String correctPasscode = "1234";
String enteredPasscode = "";

int attemptCounter = 0;
const int maxAttempts = 3;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Enter Password:");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') { 
      if (enteredPasscode == correctPasscode) {
        lcd.clear();
        lcd.print("Access Granted");
      } else {
        lcd.clear();
        lcd.print("Access Denied");
        attemptCounter++;
        delay(2000);
        if (attemptCounter >= maxAttempts) {
          lcd.clear();
          lcd.print("System Locked");
          while (true); 
        }
      }
      enteredPasscode = "";
      lcd.setCursor(0, 1);
      lcd.print("Attempts: ");
      lcd.print(attemptCounter);
      delay(2000);
      lcd.clear();
      lcd.print("Enter Password:");
    } else if (key == '*') { 
      enteredPasscode = "";
      lcd.clear();
      lcd.print("Enter Password:");
    } else { 
      if (enteredPasscode.length() < 4) {
        enteredPasscode += key;
        lcd.setCursor(enteredPasscode.length() - 1, 1);
        lcd.print("*");
      }
    }
  }
}
