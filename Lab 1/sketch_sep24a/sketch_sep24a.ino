#define LED1 38
#define S1 30
#define SCAN_TIME 100

void setup(){
  for(int i = 0; i < 4; i++){
    pinMode(LED1 + i, OUTPUT);  
    digitalWrite(LED1 + i, LOW);
    pinMode(S1 + i, INPUT);
  } 
}

void loop(){
  for(int i = 0; i < 4; i++){
    if (digitalRead(S1 + i) == HIGH)
      digitalWrite(LED1 + i, HIGH);
      delay(SCAN_TIME * 2);
      if(digitalRead(S1 + i) == HIGH)
      }
  }
}

