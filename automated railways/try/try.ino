#include<Wire.h>
String a;
void setup() {
  Wire.begin();
  Serial.begin(9600);
}

String recsig(){
  Wire.requestFrom(8,20);
  while (Wire.available()) 
  {
    char c = Wire.read();
    a+=String(c);
  }
return a;
}

void loop() {
  Serial.println(recsig());
  a="";
}
