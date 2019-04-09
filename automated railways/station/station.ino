#include <Wire.h>
char a[20];
String sig,b;
void setup() {
  Serial.begin(9600);
  Wire.begin(8);
  Wire.onRequest(requestEvent);
}

void loop() {
  Serial.println(recsig());
  delay(100);
  sig="";
}

String recsig(){
  Wire.requestFrom(8,2);
  while (Wire.available()) 
  {
    char c = Wire.read();
    sig+=String(c);
  }
return sig;
}

void requestEvent() {
  b = "127370 ";
  b+="184562 ";
  b.replace(' ','@');
  b.toCharArray(a,sizeof(a));
  Wire.write(a);
  delay(500);
  sig="";
}


