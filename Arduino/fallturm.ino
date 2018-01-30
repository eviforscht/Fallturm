#define button2Pin 2
#define button3Pin 3

unsigned long time;

byte button2State;
byte button3State;

void setup() {
  Serial.begin(9600);
  digitalWrite(button2Pin,LOW);
  pinMode(button2Pin, INPUT);
  digitalWrite(button2Pin,HIGH);
  digitalWrite(button3Pin,LOW);
  pinMode(button3Pin, INPUT);
  digitalWrite(button3Pin,HIGH);
  
}

void loop() {
  button2State = digitalRead(button2Pin);
  button3State = digitalRead(button3Pin);
  while (button2State == LOW) {
    button2State = digitalRead(button2Pin);
    delay(10);
  }
  time = millis();
  Serial.print("Sensor 1: ");
  Serial.println(time);
  
  while (button3State == LOW) { 
    button3State = digitalRead(button3Pin);
    delay(10);
  }
  time = millis();
  Serial.print("Sensor 2: ");
  Serial.println(time);
  
}
