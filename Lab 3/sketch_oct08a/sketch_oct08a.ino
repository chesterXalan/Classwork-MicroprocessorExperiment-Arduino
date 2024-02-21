#include <DueTimer.h>
#define COM1 4
#define COM2 5
#define COM3 6
#define COM4 7
#define Seg7_A 8

const unsigned char number[]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void Timer1_10msISR(){
    static unsigned int cnt10ms=0, ones=0, tens=0, turns=0;
    unsigned char cnt;
    if((turns%2)==0){
        for(cnt=0; cnt<8; cnt++){
            if((number[ones]&(0x01<<cnt))!=0)
                    digitalWrite(Seg7_A+cnt, HIGH);
                else
                    digitalWrite(Seg7_A+cnt, LOW);
        }
        digitalWrite(COM1, HIGH);
        digitalWrite(COM2, HIGH);
        digitalWrite(COM3, HIGH);
        digitalWrite(COM4, LOW);
    }
    else{
        for(cnt=0; cnt<8; cnt++){
            if((number[tens]&(0x01<<cnt))!=0)
                    digitalWrite(Seg7_A+cnt, HIGH);
                else
                    digitalWrite(Seg7_A+cnt, LOW);
        }
        digitalWrite(COM1, HIGH);
        digitalWrite(COM2, HIGH);
        digitalWrite(COM3, LOW);
        digitalWrite(COM4, HIGH);
    }
    turns++;
    cnt10ms++;
    if(cnt10ms==100){
        cnt10ms=0;
        ones++;
        if(ones==10){
            ones=0;
            tens++;
            if(tens==10)
                tens=0;
        }
        if(tens==2&&ones==4){
            tens=0;
            ones=0;
        }
    }
}

void setup() {
    unsigned int cnt;
    for(cnt=0; cnt<8; cnt++){
        pinMode(Seg7_A+cnt, OUTPUT);
        digitalWrite(Seg7_A+cnt, HIGH);
    }
    for(cnt=0; cnt<4; cnt++){
        pinMode(COM1+cnt, OUTPUT);
        digitalWrite(COM1+cnt, HIGH);
    }
    Timer1.attachInterrupt(Timer1_10msISR);
    Timer1.start(2*1000);
}

void loop() {

}

