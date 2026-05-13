#include <Adafruit_LiquidCrystal.h>
#include <Keypad.h>

Adafruit_LiquidCrystal lcd(0);

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {11,10,9,8};
byte colPins[COLS] = {7,6,5,4};

Keypad k = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String num1 = "";
String num2 = "";
char op = 0;
bool secondnum = false;

void setup()
{
  lcd.begin(16,2);
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("Manual:");
  lcd.setCursor(0,1);
  lcd.print("A => +, B => -");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("C => *, D => /");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("# => Ans,* => AC");
  delay(1000);
  lcd.clear();
  lcd.print("0");
}

void loop()
{
  char key = k.getKey();
  if(key){
    if(key == '*'){
      lcd.clear();
      num1 = "";
      num2 = "";
      op = 0;
      secondnum = false;
      lcd.print("0");
    }
    else if(key >= '0' && key <= '9'){
      if(!secondnum){
        num1 += key;
        lcd.clear();
        lcd.print(num1);
      } else {
        num2 += key;
        lcd.setCursor(0,1);
        lcd.print(num2);
      }
    }
    else if(key == 'A'|| key == 'B'|| key == 'C' || key == 'D'){
      if(num1 != "" && num2 != ""){
        float n1 = num1.toFloat();
      float n2 = num2.toFloat();
      float result = 0;
      if(op == '+') result = n1+n2;
      else if(op == '-') result = n1-n2;
      else if(op == '*') result = n1*n2;
      else if(op == '/'){
        if(n2 == 0){
          lcd.clear();
          lcd.print("Error: /0");
          delay(2000);
          lcd.clear();
          lcd.print("0");
          num1 = ""; num2 = ""; op = 0; secondnum = false;
          return;
        }
        else result = n1/n2;
      }
        lcd.clear();
        num1 = String(result);
        lcd.print(num1);
        num2 = ""; secondnum = true;
      }
      else{
      	secondnum = true;
      	if(key == 'A') op = '+';
      	else if(key == 'B') op = '-';
      	else if(key == 'C') op = '*';
      	else op = '/';
      
      	lcd.setCursor(0,0);
      	lcd.print(num1);
      	lcd.print(op);
      }
    }
    else if(key == '#' && num1 != "" && num2 != ""){
      float n1 = num1.toFloat();
      float n2 = num2.toFloat();
      float result = 0;
      if(op == '+') result = n1+n2;
      else if(op == '-') result = n1-n2;
      else if(op == '*') result = n1*n2;
      else if(op == '/'){
        if(n2 == 0){
          lcd.clear();
          lcd.print("Error: /0");
          delay(2000);
          lcd.clear();
          lcd.print("0");
          num1 = ""; num2 = ""; op = 0; secondnum = false;
          return;
        }
        else result = n1/n2;
      }
      lcd.clear();
      lcd.print(result);
      num1 = ""; num2 = ""; op = 0; secondnum = false;
    }
  }
}
