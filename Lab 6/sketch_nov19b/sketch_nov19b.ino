#define LED_Pin 4
unsigned int PWM_Value = 0;

void setup() {   

}

void loop() {
    analogWrite(LED_Pin, PWM_Value);
    PWM_Value += 5;
    if(PWM_Value >= 250) {
        while(1){
            PWM_Value -= 5;
            analogWrite(LED_Pin, PWM_Value);
            if(PWM_Value == 0)    break;
        }     
    }  
    delay(100);
}
