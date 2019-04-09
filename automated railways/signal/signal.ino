#include <SPI.h>
#include <RH_NRF24.h>
#include<Wire.h>
char *a,*tid;
String tno;
String sign;
RH_NRF24 nrf24;
void setup() 
{
  Serial.begin(9600);
  while (!Serial); 
  if (!nrf24.init())
    Serial.println("init failed");
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");
  Wire.begin(8);
}

void rbdetected()
{
  Wire.onRequest(requestEvent);
}

void requestEvent() {
  Wire.write("t1");
  delay(500);
}

String recsig(){
  Wire.requestFrom(8,20);
  while (Wire.available())
  {
    char c = Wire.read();
    tno+=String(c);
  }
return tno;
}
/*
void transsig(String al)
{
  uint8_t tr[al.length()+1];
  memcpy(tr,al.c_str(),al.length()+1);
  nrf24.send(tr, sizeof(tr));
  nrf24.waitPacketSent();
}
*/
void loop()
{
  sign=recsig();
  if (nrf24.available())
  {
    uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (nrf24.recv(buf, &len))
    {
      a=(char*)buf;
      if(a="rail break detected")
        {
          Serial.println("rail break detected");
          rbdetected();
        }
    }
  }
  else
//    Serial.println("not working");
//    transsig(sign);*/
  tno="";
}

