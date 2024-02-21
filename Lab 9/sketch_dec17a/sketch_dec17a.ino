#define LED 38
unsigned char RecData;
unsigned int sts = 0, LED_No;
bool OnOff, All = 0;

void setup() {
    for(unsigned cnt = 0; cnt < 8; cnt++) {
      pinMode(LED + cnt, OUTPUT);
      digitalWrite(LED + cnt, LOW);
    }
    Serial2.begin(9600);
}

void loop() {
    if(Serial2.available() > 0) {
        RecData = (char)Serial2.read();
        switch(sts) {
            case 0 :
                if(RecData == '@')                
                    sts = 10;
                break;
            case 10 :
                if(RecData >= '1' && RecData <= '8') {
                    LED_No = RecData;
                    sts = 20;
                }
                else if(RecData == '0') {
                    All = 1;
                    sts = 20;
                }
                else {
                    sts = 0;
                    Serial2.println("NO_OK");
                }
                break;
            case 20 :
                if(RecData == ',')
                    sts = 30;
                else {
                    sts = 0;
                    Serial2.println("NO_OK");
                }
                break;
            case 30 :
                if(RecData == '0') {
                    OnOff = LOW;
                    sts = 40;
                }
                else if(RecData == '1') {
                    OnOff = HIGH;
                    sts = 40;
                }
                else {
                    sts = 0;
                    Serial2.println("NO_OK");
                }
                break;
            case 40 :
                if(RecData == '+') {
                    ExecuteCommand();
                    Serial2.println("OK");
                    sts = 0;
                }
                else {
                    sts = 0;
                    Serial2.println("NO_OK");
                }
                break;
                
            default:
                break;
        }       
    }       
}

void ExecuteCommand() {
    if(All == 1) {
        for(unsigned int cnt = 0; cnt < 8; cnt++)
            digitalWrite(LED + cnt, OnOff);
        All = 0;
        return;
    }
    LED_No -= '1';
    digitalWrite(LED + LED_No, OnOff);
}

