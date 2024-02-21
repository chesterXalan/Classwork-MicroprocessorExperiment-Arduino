#include <DueTimer.h>
#define LED1 38
#define LED2 39

void Timer1_100msISR(){
    static unsigned int cnt100ms=0;

    if((cnt100ms%2)<1)    digitalWrite(LED1, HIGH);
    else    digitalWrite(LED1, LOW);
    cnt100ms++;
    Serial.write("+"); 
    if(cnt100ms==2)    cnt100ms=0;    
}

void Timer2_500msISR(){
    static unsigned int cnt500ms=0;

    if((cnt500ms%2)<1)   digitalWrite(LED2, HIGH);
    else    digitalWrite(LED2, LOW);
    cnt500ms++;   
    Serial.write(".");
    if(cnt500ms==2)    cnt500ms=0;   
}

void setup(){
    pinMode(LED1, OUTPUT);    digitalWrite(LED1, LOW);
    pinMode(LED2, OUTPUT);    digitalWrite(LED2, LOW);
    Timer1.attachInterrupt(Timer1_100msISR);
    Timer1.start(100*1000);
    Timer2.attachInterrupt(Timer2_500msISR);
    Timer2.start(500*1000);
    
    Serial.begin(9600);
}

void loop(){
  
}

