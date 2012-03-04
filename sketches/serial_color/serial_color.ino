#define LED_R 10
#define LED_G 11
#define LED_B 9

void setup()
{
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  
  Serial.begin(9600);
  color(0,0,0);
}

void loop()
{
  parse();
}

void color(byte r, byte g, byte b)
{
  analogWrite(LED_R, r);
  analogWrite(LED_G, g);
  analogWrite(LED_B, b);
}

void parse()
{
  char buffer[7] = {0};
  
  if (Serial.find("#"))
  {
    readBytes(buffer, 6);
    unsigned long c = strtoul(buffer, NULL, HEX);
    
    byte r = (c & 0xFF0000) >> 16;
    byte g = (c & 0x00FF00) >> 8;
    byte b = (c & 0x0000FF);
    
    Serial.print(r, HEX);
    Serial.print(g, HEX);
    Serial.println(b, HEX);

    color(r, g, b);
  }
}

void readBytes(char* buffer, size_t len)
{
  if (len < 1) return;
  size_t index = 0;
  while (index < len) 
  {
    int c = Serial.read();
    if (c < 0) continue;
    *buffer++ = (char) c;
    index++;
  }
  return;
}
