#include <DueTimer.h>
#define LED 38
#define SW 30
#define SEG 8
#define COM 4
#define SPK 2

const unsigned char number[]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void setup() {
    unsigned char cnt;
    for(cnt=0; cnt<8; cnt++){
        pinMode(LED+cnt, OUTPUT);
        digitalWrite(LED+cnt, LOW);
    }
    Timer1.attachInterrupt(Timer1_100msISR);
    Timer1.start(100*1000);

    for(cnt=0; cnt<4; cnt++)    pinMode(SW+cnt, INPUT);

    for(cnt=0; cnt<8; cnt++){
        pinMode(SEG+cnt, OUTPUT);
        digitalWrite(SEG+cnt, HIGH);
    }
    for(cnt=0; cnt<4; cnt++){
        pinMode(COM+cnt, OUTPUT);
        digitalWrite(COM+cnt, HIGH);
    }
    pinMode(SPK, OUTPUT);
    Timer2.attachInterrupt(Timer2_1msISR);
    Timer2.start(1*1000); 
}

void Timer1_100msISR(){
    static unsigned int cnt100ms=0;
    if(cnt100ms%2<1)    digitalWrite(LED, HIGH);
    else    digitalWrite(LED, LOW);
    if(cnt100ms%4<2)    digitalWrite(LED+1, HIGH);
    else    digitalWrite(LED+1, LOW);
    if(cnt100ms%10<5)   digitalWrite(LED+2, HIGH);
    else    digitalWrite(LED+2, LOW);
    if(cnt100ms%20<10)    digitalWrite(LED+3, HIGH);
    else    digitalWrite(LED+3, LOW);
    if(++cnt100ms==40)    cnt100ms=0;
}

void loop(){
    unsigned char cnt;    
    for(cnt=0; cnt<4; cnt++){        
        if(digitalRead(SW+cnt)==HIGH)   digitalWrite(LED+4+cnt, HIGH);
        else    digitalWrite(LED+4+cnt, LOW);
    }
    delay(200);
}

void Timer2_1msISR(){
    static unsigned int cnt1ms=0, ones=6, tens=5, hunds=3, thous=2, turns=0, SPKenble;
    unsigned char cnt;
    switch(turns){
        case 0: for(cnt=0; cnt<8; cnt++){
                    if((number[ones]&(0x01<<cnt))!=0)    digitalWrite(SEG+cnt, HIGH);
                    else    digitalWrite(SEG+cnt, LOW);
                }
                digitalWrite(COM, HIGH);    digitalWrite(COM+1, HIGH);
                digitalWrite(COM+2, HIGH);    digitalWrite(COM+3, LOW);
                break;      
        case 1: for(cnt=0; cnt<8; cnt++){
                    if((number[tens]&(0x01<<cnt))!=0)    digitalWrite(SEG+cnt, HIGH);
                    else    digitalWrite(SEG+cnt, LOW);
                }
                digitalWrite(COM, HIGH);    digitalWrite(COM+1, HIGH);
                digitalWrite(COM+2, LOW);    digitalWrite(COM+3, HIGH);
                break;
        case 2: for(cnt=0; cnt<8; cnt++){
                    if((number[hunds]&(0x01<<cnt))!=0)    digitalWrite(SEG+cnt, HIGH);
                    else    digitalWrite(SEG+cnt, LOW);
                }
                digitalWrite(COM, HIGH);    digitalWrite(COM+1, LOW);
                digitalWrite(COM+2, HIGH);    digitalWrite(COM+3, HIGH);
                break;
        case 3: for(cnt=0; cnt<8; cnt++){
                    if((number[thous]&(0x01<<cnt))!=0)    digitalWrite(SEG+cnt, HIGH);
                    else    digitalWrite(SEG+cnt, LOW);
                }
                digitalWrite(COM, LOW);    digitalWrite(COM+1, HIGH);
                digitalWrite(COM+2, HIGH);    digitalWrite(COM+3, HIGH);
                break;
    }
    if(++turns==4)    turns=0;
    
    cnt1ms++;
    if(tens==0&ones==0){
        if(cnt1ms>=0&cnt1ms<100)    SPKenble=1;
        else if(cnt1ms>=200&cnt1ms<300)   SPKenble=1;
        else    SPKenble=0;
    }  
    if(SPKenble==1){
        if(cnt1ms%2==0)   digitalWrite(SPK, HIGH);
        else    digitalWrite(SPK, LOW);       
    }
    else    digitalWrite(SPK, LOW);
    
    if(cnt1ms==1000){
        cnt1ms=0;
        if(++ones==10){
            ones=0;
            if(++tens==6){
                tens=0;
                if(++hunds==10){
                    hunds=0;
                    thous++;                       
                }
            }
        }        
    }
    if(thous==2&hunds==4&tens==0&ones==0){
        ones=0;   tens=0;
        hunds=0;    thous=0;           
    }
}
