#include "minishield.h"

#define END while(1);
#define LOG(x) Serial.println(x)
#define ERR(x) {Serial.print("\nERR: "); Serial.println(x); err();}
#define OK(x) {Serial.print("   "); Serial.println(x); ok();}

void setup()
{
    Serial.begin(9600);
    minishield_setup();
    
    Serial.println("----- TEST -----\n");
}

void loop()
{
    LOG("1) LED test");
    
    #define LTIME 300
    
    color(100, 0, 0);
    delay(LTIME);
    color(255, 0, 0);
    delay(LTIME);
    
    color(0, 100, 0);
    delay(LTIME);
    color(0, 255, 0);
    delay(LTIME);
    
    color(0, 0, 100);
    delay(LTIME);
    color(0, 0, 255);
    delay(LTIME);
    
    color(0, 0, 0);
    
    LOG("   done.\n");
    delay(1000);
    
    // -----------------------------------------------------------------------
    
    LOG("2) BTN test");
    
    if (btnA() == 1 || btnB() == 1) ERR("Button unexpected pressed");
    
    // press BTN_A
    while (btnA() == 0) {
        if (btnB() == 1) ERR("BTN_B pressed");
    }
    OK("BTN_A pressed");
    
    // press BTN_B
    while (btnB() == 0) {
        if (btnA() == 1) ERR("BTN_A pressed");
    }
    OK("BTN_B pressed");
    
    LOG("   done.\n");
    delay(500);
    
    // -----------------------------------------------------------------------
    
    LOG("3) Temp test");
    
    float t = getTemp();
    
    LOG(rawTemp());
    LOG(t);
    
    if (t < 15 || t > 35) ERR("Temp out of range");
    
    OK("done.\n");
    delay(500);
    
    // -----------------------------------------------------------------------
    
    LOG("4) IO");
    
    LOG("   D -> A");
    
    pinMode(A4, INPUT);
    pinMode(A5, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    if (digitalRead(A4) == HIGH || digitalRead(A5) == HIGH) ERR("HIGH");
    
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    if (digitalRead(A4) == HIGH || digitalRead(A5) == LOW) ERR("D2 LOW");
    
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    if (digitalRead(A4) == LOW || digitalRead(A5) == HIGH) ERR("D2 LOW");
    
    LOG("   A -> D");
    
    pinMode(A4, OUTPUT);
    pinMode(A5, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    
    digitalWrite(A4, LOW);
    digitalWrite(A5, LOW);
    if (digitalRead(2) == HIGH || digitalRead(3) == HIGH) ERR("HIGH");
    
    digitalWrite(A4, HIGH);
    digitalWrite(A5, LOW);
    if (digitalRead(2) == HIGH || digitalRead(3) == LOW) ERR("D2 LOW");
    
    digitalWrite(A4, LOW);
    digitalWrite(A5, HIGH);
    if (digitalRead(2) == LOW || digitalRead(3) == HIGH) ERR("D2 LOW");
    
    OK("done.\n");
    
    // -----------------------------------------------------------------------
    
    ok();
    
    while (1) {
        LOG(getTemp());
        delay(1000);
    }
}


void err()
{
    color(50, 0, 0);
    END
}
 
void ok()
{
    color(0, 50, 0);
    delay(500);
    color(0, 0, 0);
}
 