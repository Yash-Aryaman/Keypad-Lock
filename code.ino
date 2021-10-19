#include <Keypad.h>
#include <Servo.h>
#include<LiquidCrystal.h>

#define codeLength 4
int servoPin = 8; 
Servo Servo1;

int redPin= 12;
int greenPin = 9;

char Code[codeLength];
char PassW[codeLength]="123";
byte keycount=0;

const byte ROWS = 3; 
const byte COLS = 3; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'}
};

byte rowPins[ROWS] = {7, 6, 5}; 
byte colPins[COLS] = {4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

void setup(){
  Serial.begin(9600);
  Servo1.attach(servoPin);
  lcd.begin(16, 2);
  pinMode(redPin, OUTPUT);
  digitalWrite(redPin,HIGH);
  pinMode(greenPin, OUTPUT);
  digitalWrite(greenPin,LOW);
}
  
void loop(){
  char customKey = customKeypad.getKey();
  if(customKey){
    Code[keycount]=customKey;
    Serial.print(Code[keycount]);
    keycount++;
  };
  if(keycount==codeLength-1){
    Serial.println(" ");
    
    if(strcmp(Code,PassW)==0){
      Servo1.write(0); 
      digitalWrite(redPin,LOW);
      digitalWrite(greenPin,HIGH);
      lcd.print("     OPEN");
      Serial.println("Correct");
      delay(5000);
      digitalWrite(greenPin,LOW);
      digitalWrite(redPin,HIGH);
      Servo1.write(90);
      lcd.clear();
    }
       else{
         Serial.println("Incorrect");
         lcd.print("   Incorrect");
         digitalWrite(redPin,LOW);
         delay(500);
         digitalWrite(redPin,HIGH);
         delay(500);        
         digitalWrite(redPin,LOW);
         delay(500);
         digitalWrite(redPin,HIGH);
         delay(500);
         digitalWrite(redPin,LOW);
         delay(500);
         digitalWrite(redPin,HIGH);
         Servo1.write(90); 
         delay(2000);
         lcd.clear();
       }
    
    deleteCount();
  }
}
  
void deleteCount(){
  while(keycount !=0){
    Code[keycount--]=0;
  }
  return;
}
