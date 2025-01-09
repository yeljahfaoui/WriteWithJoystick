#include <LiquidCrystal.h>

#define VRX_PIN A0
#define VRY_PIN A1
#define SW_PIN 7
#define deadzone 300

const char alphabet[] = {
  ' ',
  'A',
  'B',
  'C',
  'D',
  'E',
  'F',
  'G',
  'H',
  'I',
  'J',
  'K',
  'L',
  'M',
  'N',
  'O',
  'P',
  'Q',
  'R',
  'S',
  'T',
  'U',
  'V',
  'W',
  'X',
  'Y',
  'Z'
};

byte pointer[] = {
  B00000,
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00100,
  B00000
};

char text[16];

LiquidCrystal lcd(12 ,11, 5, 4, 3, 2);
int alphabetIndex = 0;
int currentHorizontalCursor = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(SW_PIN, INPUT_PULLUP);

  lcd.print("welcome !");
  lcd.createChar(0 ,pointer);

  delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.setCursor(0,0);

  int xValue = analogRead(VRX_PIN);
  int yValue = analogRead(VRY_PIN);

  if(yValue >= 0 && yValue < 512 - deadzone) {
    alphabetIndex--;
    if(alphabetIndex < 0) {
      alphabetIndex = 26;
    }

  } else if(yValue >= 512 + deadzone && yValue < 1024) {
    alphabetIndex++;
    if(alphabetIndex > 26) {
      alphabetIndex = 0;
    }
    
  }
  
  if(xValue >= 0 && xValue < 512 - deadzone) {
    currentHorizontalCursor--;
    alphabetIndex = 0;
    if(currentHorizontalCursor < 0) {
      currentHorizontalCursor = 15;
    }

  } else if(xValue >= 512 + deadzone && xValue < 1024) {
    currentHorizontalCursor++;
    alphabetIndex = 0;
    if(currentHorizontalCursor > 15) {
      currentHorizontalCursor = 0;
    }
    
  }

  lcd.setCursor(currentHorizontalCursor, 0);
  lcd.setCursor(currentHorizontalCursor, 1);
  lcd.write(byte(0));

  text[currentHorizontalCursor] = alphabet[alphabetIndex];

  for(int i = 0; i < 16; i++) {
    lcd.setCursor(i, 0);
    if(text[i] != NULL) {
      lcd.print(text[i]);
    }
  }

  Serial.print("X = ");
  Serial.print(xValue);
  Serial.print(", Y = ");
  Serial.println(yValue);

  delay(200);
}
