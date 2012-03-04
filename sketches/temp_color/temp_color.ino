#define LED_R 10
#define LED_G 11
#define LED_B 9

#define TEMP 3

void setup()
{
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  
  Serial.begin(9600); 
  color(0,0,0);
}

float t;

void loop()
{  
  t = analogRead(3) * 0.488281 - 273;
  Serial.println(t);
  temp(t, -40, 40);
}

void color(byte r, byte g, byte b)
{
  Serial.print(r, HEX);
  Serial.print(g, HEX);
  Serial.println(b, HEX);

  analogWrite(LED_R, r);
  analogWrite(LED_G, g);
  analogWrite(LED_B, b);
}


// zobrazí barvu na pøechodu #00F -> #FFF -> #F00
//                           MINV ->   0  -> MAXV
void temp(float v, int minv, int maxv)
{
  byte t;
  
  if (v > 0)
  {
    t = 0xFF - (byte)(0xFF * v/maxv);
    color(255, t, t);
  }
  else
  {
    t = 0xFF + (byte)(0xFF * v/minv);
    color(t, t, 255);
  }
}
