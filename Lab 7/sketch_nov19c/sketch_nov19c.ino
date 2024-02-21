#include <DueTimer.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(32, 31, 30, 22, 23, 24, 25, 26, 27, 28, 29);

#define COM 4
#define SEG 8
#define VR_Pin A0
int VR_Value;
const unsigned char number[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0xBf, 0xff}; 

void setup() {
    unsigned int cnt;
    
    analogReference(AR_DEFAULT);
    lcd.begin(20, 2);

    for(cnt = 0; cnt < 8; cnt++) {
        pinMode(SEG + cnt, OUTPUT);
        digitalWrite(SEG + cnt, HIGH);
    }
    for(cnt = 0; cnt < 4; cnt++) {
        pinMode(COM + cnt, OUTPUT);
        digitalWrite(COM + cnt, HIGH);
    }
    
    Timer1.attachInterrupt(Timer1_ISR);
    Timer1.start(100*1000);
    Timer2.attachInterrupt(Timer2_ISR);
    Timer2.start(2*1000);
}

void Timer1_ISR() {
    lcd.setCursor(4, 0);
    lcd.print("    ");
    
    VR_Value = analogRead(VR_Pin);            
    if(VR_Value < 10) {
        lcd.setCursor(7, 0);       
        lcd.print(VR_Value, DEC);
    }
    else if(VR_Value < 100 && VR_Value >= 10) {
        lcd.setCursor(6, 0);
        lcd.print(VR_Value, DEC);
    }
    else if(VR_Value < 1000 && VR_Value >= 100) {
        lcd.setCursor(5, 0);
        lcd.print(VR_Value, DEC);
    }
    else {
        lcd.setCursor(4, 0);    
        lcd.print(VR_Value, DEC);
    }
}

void Timer2_ISR() {
    static unsigned int ISRcnt = 0, ones = 0, tens = 0, hunds = 0, thus = 0;
    unsigned cnt;

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
    if(++ISRcnt == 500){
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
