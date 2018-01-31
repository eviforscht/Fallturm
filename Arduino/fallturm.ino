#define button2Pin 2
#define button3Pin 3
#define button4Pin 4
#define button5Pin 5
#define button6Pin 6
#define button7Pin 7
#define button8Pin 8
#define button9Pin 9

unsigned long time;

byte button2State;
byte button3State;
byte button4State;
byte button5State;
byte button6State;
byte button7State;
byte button8State;
byte button9State;

void setup() {
  Serial.begin(9600);
  digitalWrite(button2Pin,LOW);
  pinMode(button2Pin, INPUT);
  digitalWrite(button2Pin,HIGH);
  digitalWrite(button3Pin,LOW);
  pinMode(button3Pin, INPUT);
  digitalWrite(button3Pin,HIGH);
  digitalWrite(button4Pin,LOW);
  pinMode(button4Pin, INPUT);
  digitalWrite(button4Pin,HIGH);
  digitalWrite(button5Pin,LOW);
  pinMode(button5Pin, INPUT);
  digitalWrite(button5Pin,HIGH);
  digitalWrite(button6Pin,LOW);
  pinMode(button6Pin, INPUT);
  digitalWrite(button6Pin,HIGH);  
  digitalWrite(button7Pin,LOW);
  pinMode(button7Pin, INPUT);
  digitalWrite(button7Pin,HIGH);  
  digitalWrite(button8Pin,LOW);
  pinMode(button8Pin, INPUT);
  digitalWrite(button8Pin,HIGH);  
  digitalWrite(button9Pin,LOW);
  pinMode(button9Pin, INPUT);
  digitalWrite(button9Pin,HIGH);  
  
}

void loop() {
  button2State = digitalRead(button2Pin);
  button3State = digitalRead(button3Pin);
  button4State = digitalRead(button4Pin);
  button5State = digitalRead(button5Pin);
  button6State = digitalRead(button6Pin);
  button7State = digitalRead(button7Pin);
  button8State = digitalRead(button8Pin);
  button9State = digitalRead(button9Pin);

  while (button2State == LOW) {
    button2State = digitalRead(button2Pin);
    delay(10);
  }
  time = millis();
  Serial.print("24;0;");
  Serial.println(time);
  
  while (button3State == LOW) { 
    button3State = digitalRead(button3Pin);
    delay(10);
  }
  time = millis();
  Serial.print("48;1;");
  Serial.println(time);
  
  while (button4State == LOW) { 
    button4State = digitalRead(button4Pin);
    delay(10);
  }
  time = millis();
  Serial.print("72;2;");
  Serial.println(time);
  
  while (button5State == LOW) { 
    button5State = digitalRead(button5Pin);
    delay(10);
  }
  time = millis();
  Serial.print("96;3;");
  Serial.println(time);
  
  while (button6State == LOW) { 
    button6State = digitalRead(button6Pin);
    delay(10);
  }
  time = millis();
  Serial.print("120;4;");
  Serial.println(time);
  
  while (button7State == LOW) { 
    button7State = digitalRead(button7Pin);
    delay(10);
  }
  time = millis();
  Serial.print("144;5;");
  Serial.println(time);
  
  while (button8State == LOW) { 
    button8State = digitalRead(button8Pin);
    delay(10);
  }
  time = millis();
  Serial.print("168;6;");
  Serial.println(time);
  
  
  while (button9State == LOW) { 
    button9State = digitalRead(button9Pin);
    delay(10);
  }
  time = millis();
  Serial.print("192;7;");
  Serial.println(time);

}
