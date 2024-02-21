#include <DueTimer.h>
#define R0 22
#define G0 30
#define B0 38

#define S0 46
#define S1 47
#define S2 48
#define EN 49

unsigned char RedData[][8] = {{0xFF, 0x81, 0x7E, 0x7E, 0x7E, 0x7E, 0x81, 0xFF},
                              {0xFF, 0xFF, 0xFF, 0xFF, 0x7D, 0x00, 0x7F, 0xFF},
                              {0xFF, 0x1D, 0x6E, 0x6E, 0x6E, 0x6E, 0x71, 0xFF},
                              {0xFF, 0xBD, 0x7E, 0x76, 0x67, 0x99, 0xFF, 0xFF},
                              {0xFF, 0xC7, 0xDB, 0xDD, 0xDE, 0x00, 0xDF, 0xFF},
                              {0xFF, 0x78, 0x76, 0x76, 0x76, 0x76, 0x8E, 0xFF},
                              {0xFF, 0x81, 0x6E, 0x6E, 0x6E, 0x6E, 0x9D, 0xFF},
                              {0xFF, 0xFF, 0x3E, 0xDE, 0xEE, 0xF6, 0xF8, 0xFF},
                              {0xFF, 0x91, 0x6E, 0x6E, 0x6E, 0x6E, 0x91, 0xFF},
                              {0xFF, 0xB1, 0x6E, 0x6E, 0x6E, 0x6E, 0x81, 0xFF}};
unsigned char GreenData[][8] = {{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
                                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
                                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
                                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
                                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
                                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
                                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
                                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
                                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
                                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};
unsigned char BlueData[][8] = {{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
                                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
                                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
                                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
                                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
                                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
                                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
                                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
                                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
                                {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};
unsigned char digit = 0;

void setup() {
    for(unsigned char cnt = 0; cnt < 8; cnt++) {
        pinMode(R0 + cnt, OUTPUT);
        digitalWrite(R0 + cnt, HIGH);
        pinMode(G0 + cnt, OUTPUT);
        digitalWrite(G0 + cnt, HIGH);
        pinMode(B0 + cnt, OUTPUT);
        digitalWrite(B0 + cnt, HIGH);
    }
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(EN, OUTPUT);
    digitalWrite(EN, HIGH);

    Timer1.attachInterrupt(Timer1_ISR);
    Timer1.start(2 * 1000);
    Timer2.attachInterrupt(Timer2_ISR);
    Timer2.start(1000 * 1000);
}

void Timer1_ISR() {
    static unsigned char turns = 0;
    unsigned char cnt;
    
    for(cnt = 0; cnt < 8; cnt++) {
        if(((RedData[digit][turns] >> cnt) & 0x01) == 0)
            digitalWrite(R0 + cnt, LOW);
        else
            digitalWrite(R0 + cnt, HIGH);
        if(((GreenData[digit][turns] >> cnt) & 0x01) == 0)
            digitalWrite(G0 + cnt, LOW);
        else
            digitalWrite(G0 + cnt, HIGH);
        if(((BlueData[digit][turns] >> cnt) & 0x01) == 0)
            digitalWrite(B0 + cnt, LOW);
        else
            digitalWrite(B0 + cnt, HIGH);
    }
    switch(turns) {
        case 0:           
            digitalWrite(S2, LOW);
            digitalWrite(S1, LOW);
            digitalWrite(S0, LOW);
            break;
        case 1:
            digitalWrite(S2, LOW);
            digitalWrite(S1, LOW);
            digitalWrite(S0, HIGH);
            break;
        case 2:
            digitalWrite(S2, LOW);
            digitalWrite(S1, HIGH);
            digitalWrite(S0, LOW);
            break;
        case 3:
            digitalWrite(S2, LOW);
            digitalWrite(S1, HIGH);
            digitalWrite(S0, HIGH);
            break;
        case 4:
            digitalWrite(S2, HIGH);
            digitalWrite(S1, LOW);
            digitalWrite(S0, LOW);
            break;
        case 5:
            digitalWrite(S2, HIGH);
            digitalWrite(S1, LOW);
            digitalWrite(S0, HIGH);
            break;
        case 6:
            digitalWrite(S2, HIGH);
            digitalWrite(S1, HIGH);
            digitalWrite(S0, LOW);
            break;
        case 7:
            digitalWrite(S2, HIGH);
            digitalWrite(S1, HIGH);
            digitalWrite(S0, HIGH);
            break;                                
    }
    if(++turns == 8)
        turns = 0;
}

void Timer2_ISR() {
    if(++digit == 10)
        digit = 0;
}
void loop() {

}
