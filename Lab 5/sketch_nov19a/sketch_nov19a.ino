#include <DueTimer.h>
#include <LiquidCrystal.h>
char text[] = "Hello World!        ";
LiquidCrystal lcd(32, 31, 30, 22, 23, 24, 25, 26, 27, 28, 29);

void Timer2ISR(){
    static unsigned int ISRcnt = 0, second = 5, second2 = 0, minute = 5, minute2 = 9, hour = 2, hour2 = 3;
    char temp;
    ++ISRcnt;
    if(ISRcnt == 10){
        ISRcnt = 0;
            
        lcd.setCursor(11, 0);
        lcd.print(":");
        lcd.setCursor(8, 0);
        lcd.print(":");
        
        lcd.setCursor(13, 0);
        lcd.print(second2, 10);
        lcd.setCursor(12, 0);
        lcd.print(second, 10);
        lcd.setCursor(10, 0);
        lcd.print(minute2, 10);    
        lcd.setCursor(9, 0);
        lcd.print(minute, 10);
        lcd.setCursor(7, 0);
        lcd.print(hour2, 10);       
        lcd.setCursor(6, 0);
        lcd.print(hour, 10); 
          
        if(++second2 == 10){
            second2 = 0;  
            if(++second == 6){
                second = 0;
                if(++minute2 == 10){
                    minute2 = 0;
                    if(++minute = 6){
                        minute = 0;
                        if(++hour2 == 10){
                            hour2 = 0;
                            ++hour;
                        }
                    }                  
                }
            }                                       
        }
        if(hour == 2 && hour2 == 4){
            hour = 0;
            hour2 = 0;
        }        
    }
    if(ISRcnt == 5){
        temp = text[0];
        for(int i = 0; i < 19; i++) text[i] = text[i+1];
        text[19] = temp;
        lcd.setCursor(0, 1);
        lcd.print(text);
    }   
}
void setup() {
    lcd.begin(20, 2);
    Timer2.attachInterrupt(Timer2ISR);
    Timer2.start(100 * 1000);   
}

void loop() { 

}
