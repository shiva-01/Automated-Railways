#include <SPI.h>
#include <RH_NRF24.h>
String a;
const char *msg;
RH_NRF24 nrf24;
uint8_t tno[]="12737";
void setup() 
{
  Serial.begin(9600);
  while (!Serial) ;
  if (!nrf24.init())
    Serial.println("init failed");
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");    
}


void loop()
{
  uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if (nrf24.waitAvailableTimeout(500))
  { 
    if (nrf24.recv(buf, &len))
    {
      Serial.print("Trains here are ");
      Serial.println((char*)buf);
      a = "127370 ";
      a+="184562 ";
      a.replace(' ','@');
      uint8_t b[a.length()+1];
      memcpy(b,a.c_str(),a.length()+1);
      nrf24.send(b, sizeof(b));
      nrf24.waitPacketSent();
    }
    else
    {
      Serial.println("recv failed");
    }
  }
  else
  {
    Serial.println("No reply, is nrf24_server running?");
  }
  delay(400);
}
