#include <minishield.h>

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
    
    color(100, 0, 0);
    delay(800);
    color(255, 0, 0);
    delay(800);
    
    color(0, 100, 0);
    delay(800);
    color(0, 255, 0);
    delay(800);
    
    color(0, 0, 100);
    delay(800);
    color(0, 0, 255);
    delay(800);
    
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
 