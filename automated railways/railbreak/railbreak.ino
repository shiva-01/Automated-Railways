#include <SPI.h>
#include <RH_NRF24.h>
RH_NRF24 nrf24;

const int trig1= A0;
const int echo1= A1;
const int trig2= A2;
const int echo2= A3;
const int car=A4;
long duration;
int distance;
int d1,d2;
int pin=9;
int dist;
int israilbreak;

void setup() {
  Serial.begin(9600);
  pinMode(pin,INPUT);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(car,OUTPUT);
  while (!Serial) ;
  if (!nrf24.init())
    Serial.println("init failed");
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");    

}

void sendrailbreak()
{
  uint8_t data[] = "rail break detected";
  nrf24.send(data, sizeof(data));
  nrf24.waitPacketSent();
  uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  delay(400);
}

int retdistance(int trig,int echo){
digitalWrite(trig, LOW);
delayMicroseconds(2);
digitalWrite(trig, HIGH);
delayMicroseconds(10);
digitalWrite(trig, LOW);
duration = pulseIn(echo, HIGH);
distance= duration*0.034/2;
return distance;
}

int checkrailbreak(int dist1,int dist2){
  if(dist2>10)
    {
      if(dist1<9 && dist>4)
        return 0;
      else
        return 1;
    }
  else if(dist2<=10)
    {
      if(dist1>10 || dist1<5)
        return 1;
      else
        return 0;
    }
}

void loop() {
d1=retdistance(trig1,echo1);
d2=retdistance(trig2,echo2);
israilbreak=checkrailbreak(d1,d2);
if(israilbreak==0)
  {
    Serial.println("Rail break not detected");
    digitalWrite(car,HIGH);
  }
else
  {
    Serial.println("Detected rail break");
    sendrailbreak();
    digitalWrite(car,LOW);
  }
}
