int trig=7;
int sn;
int echo=6;
long timeInMicro;
long distanceInCm;
#include <SoftwareSerial.h>
SoftwareSerial mySerial(4,5); //SIM800L Tx & Rx is connected to Arduino #3 & #2

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
float RXPin = 2, TXPin = 3;
float GPSBaud = 9600;

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

void setup(){
  sonar();
  Serial.begin(9600);
  ss.begin(GPSBaud);
  pinMode(7,OUTPUT);
  pinMode(6,INPUT);
 mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
 mySerial.println("AT+CMGS=\"+998947088686\"https://www.google.com/maps/place/"gps);//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print("Last Minute Engineers | lastminuteengineers.com"); //text content
  updateSerial();
  mySerial.write(26);
 }
 void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
void sonar()
{
 if(sn==300){tone(sn,1200);}
 if(sn==200){tone(sn,1200);delay(200);tone(sn,1200);}
 
 if(sn==100){tone(sn,1200);delay(200);tone(sn,1200);delay(200);tone(sn,1200);}
 
 if(sn==50){tone(sn,1200);delay(200);tone(sn,1200);delay(200);tone(sn,1200);tone(sn,1200);delay(200);}
 
else{noTone(sn);}
 digitalWrite(trig,LOW);
 delayMicroseconds(2);
 digitalWrite(trig,HIGH);
 delayMicroseconds(10);
 digitalWrite(trig,LOW);

 timeInMicro= pulseIn(echo,HIGH);

 distanceInCm = ((timeInMicro/29)/2);

 Serial.println(distanceInCm);
 delay(100);
 Serial.println("     ");
 }

void loop()
{
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      Serial.print("https://www.google.com/maps/place/");
      Serial.print(gps.location.lat(),6);
      Serial.print(",");
      Serial.println(gps.location.lng(),6);
    }
  }
}
