#include <DueTimer.h>
#define COM1 4
#define COM2 5
#define COM3 6
#define COM4 7
#define Seg7_A 8
#define SPEAKER 2

const unsigned char number[]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void Timer1_1msISR(){
    static unsigned int cnt10ms=0, ones=6, tens=5, hunds=3, thous=2, turns=0;
    unsigned char cnt;   
    switch(turns){
        case 0:
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
            break;
        case 1:
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
            break;
        case 2:
            for(cnt=0; cnt<8; cnt++){
                if((number[hunds]&(0x01<<cnt))!=0)
                    digitalWrite(Seg7_A+cnt, HIGH);
                else
                    digitalWrite(Seg7_A+cnt, LOW);
            }
            digitalWrite(COM1, HIGH);
            digitalWrite(COM2, LOW);
            digitalWrite(COM3, HIGH);
            digitalWrite(COM4, HIGH);
            break;
        case 3:
            for(cnt=0; cnt<8; cnt++){
                if((number[thous]&(0x01<<cnt))!=0)
                    digitalWrite(Seg7_A+cnt, HIGH);
                else
                    digitalWrite(Seg7_A+cnt, LOW);
            }
            digitalWrite(COM1, LOW);
            digitalWrite(COM2, HIGH);
            digitalWrite(COM3, HIGH);
            digitalWrite(COM4, HIGH);
            break;
    }
    if(++turns==4)
        turns=0;
    if(++cnt10ms==1000){
        cnt10ms=0;
        if(++ones==10){
            ones=0;
            if(++tens==6){
                tens=0;
                if(++hunds==4){
                    hunds=0;
                    if(++thous==3)
                        thous=0;
                }
            }
        }
    }
    if(thous==2&&hunds==4&&tens==6&&ones==10){
        thous=0;
        hunds=0;
        tens=0;
        ones=0;
    }
}

void Timer2_10msISR(){
    static unsigned int cnt10ms=0, SPKenable;
    cnt10ms++;
    if(cnt10ms>=100)
        cnt10ms=0;
    if(cnt10ms>=0&&cnt10ms<10)
        SPKenable=1;
    else
        SPKenable=0;
    if(SPKenable==1){
        if(cnt10ms%2==0)
            digitalWrite(SPEAKER, HIGH); 
        else
            digitalWrite(SPEAKER, LOW);  
    }
    else
        digitalWrite(SPEAKER, LOW);   
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
    pinMode(SPEAKER, OUTPUT);
    Timer1.attachInterrupt(Timer1_1msISR);
    Timer1.start(1*1000);
    Timer2.attachInterrupt(Timer2_10msISR);
    Timer2.start(10*1000);
}

void loop() {

}

