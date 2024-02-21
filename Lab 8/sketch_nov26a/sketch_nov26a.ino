#include <DueTimer.h>
#define Abar 46
#define B 47
#define A 48
#define Bbar 49
#define VR_Pin A0
#define COM 4
#define SEG 8

const unsigned char number[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0xBf, 0xff};
int VR_Value;

void setup() {
    unsigned char cnt;

    for(cnt = 0; cnt < 8; cnt++) {
        pinMode(SEG + cnt, OUTPUT);
        digitalWrite(SEG + cnt, HIGH);
    }
    for(cnt = 0; cnt < 4; cnt++) {
        pinMode(COM + cnt, OUTPUT);
        digitalWrite(COM + cnt, HIGH);
    }
    
    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(Abar, OUTPUT);   
    pinMode(Bbar, OUTPUT);
    
    Timer1.attachInterrupt(Timer1_ISR);
    Timer1.start(1*1000);
    Timer2.attachInterrupt(Timer2_ISR);
    Timer2.start(5*1000);
}

void Timer1_ISR() {
    static int turns = 0, counter = 0;
          
    VR_Value = analogRead(VR_Pin) - 512; 
    if(++counter == 52)
        counter = 0;     
    
    if(VR_Value < 0) {
        VR_Value *= (-1);
        if(counter <= (VR_Value / 10)) {        
            if(++turns >= 8)
                turns = 0;
        }        
    }
    else if(VR_Value > 0) {
        if(counter <= (VR_Value / 10)) {
            if(--turns == (-1))
                turns = 7;
        }
    }
    else 
        turns = 8;                    
    
    switch(turns) {
        case 0:
            digitalWrite(A, HIGH);
            digitalWrite(B, LOW);
            digitalWrite(Abar, LOW);
            digitalWrite(Bbar, LOW);
            break;
        case 1:
            digitalWrite(A, HIGH);
            digitalWrite(B, HIGH);
            digitalWrite(Abar, LOW);
            digitalWrite(Bbar, LOW);
            break;
        case 2:
            digitalWrite(A, LOW);
            digitalWrite(B, HIGH);
            digitalWrite(Abar, LOW);
            digitalWrite(Bbar, LOW);
            break;
        case 3:
            digitalWrite(A, LOW);
            digitalWrite(B, HIGH);
            digitalWrite(Abar, HIGH);
            digitalWrite(Bbar, LOW);
            break;
        case 4:
            digitalWrite(A, LOW);
            digitalWrite(B, LOW);
            digitalWrite(Abar, HIGH);
            digitalWrite(Bbar, LOW);
            break;
        case 5:
            digitalWrite(A, LOW);
            digitalWrite(B, LOW);
            digitalWrite(Abar, HIGH);
            digitalWrite(Bbar, HIGH);
            break;
        case 6:
            digitalWrite(A, LOW);
            digitalWrite(B, LOW);
            digitalWrite(Abar, LOW);
            digitalWrite(Bbar, HIGH);
           break;
        case 7:
            digitalWrite(A, HIGH);
            digitalWrite(B, LOW);
            digitalWrite(Abar, LOW);
            digitalWrite(Bbar, HIGH);
            break;
        case 8:
            digitalWrite(A, LOW);
            digitalWrite(B, LOW);
            digitalWrite(Abar, LOW);
            digitalWrite(Bbar, LOW);
            break;
    }         
}

void Timer2_ISR() {
    static unsigned int ISRcnt = 0, ones = 0, tens = 0, hunds = 0, thus = 0;
    unsigned char cnt;

    for(cnt = 0; cnt < 4; cnt++)    
        digitalWrite(COM + cnt, HIGH);
        
    switch(ISRcnt % 4) {
        case 0:
            for(cnt = 0; cnt < 8; cnt++) {
                if((number[ones] & (0x01 << cnt)) != 0)
                    digitalWrite(SEG + cnt, HIGH);
                else
                    digitalWrite(SEG + cnt, LOW);
            }
            digitalWrite(COM + 3, LOW);
            break;
        case 1:
            for(cnt = 0; cnt < 8; cnt++) {
                if((number[tens] & (0x01 << cnt)) != 0)
                    digitalWrite(SEG + cnt, HIGH);
                else
                    digitalWrite(SEG + cnt, LOW);
            }
            digitalWrite(COM + 2, LOW);
            break;
        case 2:
            for(cnt = 0; cnt < 8; cnt++) {
                if((number[hunds] & (0x01 << cnt)) != 0)
                    digitalWrite(SEG + cnt, HIGH);
                else
                    digitalWrite(SEG + cnt, LOW);
            }
            digitalWrite(COM + 1, LOW);
            break;
        case 3:
            for(cnt = 0; cnt < 8; cnt++) {
                if((number[thus] & (0x01 << cnt)) != 0)
                    digitalWrite(SEG + cnt, HIGH);
                else
                    digitalWrite(SEG + cnt, LOW);
            }
            digitalWrite(COM, LOW);
            break;
    }
    if(++ISRcnt == 100){
        ISRcnt = 0;
        VR_Value = analogRead(VR_Pin) - 512;

        if(VR_Value < 0) {
            VR_Value *= (-1);
            thus = 10;
        }
        else
            thus = 11;
        
        hunds = VR_Value / 100;
        tens = VR_Value % 100 / 10;
        ones = VR_Value % 100 % 10;
    }
}

void loop() {

}
