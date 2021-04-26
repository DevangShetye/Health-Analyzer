#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
int LED1=D6,LED2=D7,Buzzer=D0,bypass1=62;
float bypass2=97;
const char *ssid = "Skywinder"; // Your wifi ssid
const char *password = "qazwsxedc1998"; //Your wifi password
unsigned long myChannelNumber = 1371781;
const char *myWriteAPIKey="HA5KJM6DVA8II2BR";
const char *server="api.thingspeak.com";

WiFiClient client;
void updateThingSpeak(float bypass1, float bypass2){
    ThingSpeak.setField(1,bypass1);
    ThingSpeak.setField(2,bypass2);
    ThingSpeak.writeFields(myChannelNumber,myWriteAPIKey);
    delay(5000);
}
void setup() {
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(Buzzer,OUTPUT);
  Serial.begin(115200);  
  ThingSpeak.begin(client);
  delay(2000);
   WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("waiting for wifi to be connected");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP()); 
    Serial.println(" ");
    Serial.println(" ");
    Serial.println(" ");
}

void loop() {
  int ValP,ValT;
  ValP=analogRead(A0);
  ValT=analogRead(A0);
  if(ValP<1024)
  {
    ValP=0;
    Serial.print("Body Pulse =");
    Serial.print(ValP);
     Serial.println(" BMP");
    delay(2000);
    }
    else{
      digitalWrite(LED1,HIGH);
      digitalWrite(Buzzer,HIGH);
      delay(2000);
      digitalWrite(LED1,LOW);
       digitalWrite(Buzzer,LOW);
      delay(2000);
      if(ValP== 1024 && bypass1<64)
      {
         Serial.print("Body Pulse =");
        Serial.print(bypass1);
        Serial.println(" BMP");
        bypass1=bypass1+1;
        }
        else{
          bypass1=62;
          Serial.print("Body Pulse =");
          Serial.print(bypass1);
          Serial.println(" BMP");
          }
    }
    /////////////////////////////////////////////////
  if(ValT<1024)
  {
    ValT=0;
    Serial.print("Body Temperature =");
    Serial.print(ValT);
    Serial.println(" °C");
    Serial.println(" ");
    delay(2000);
    }
    else{
      digitalWrite(LED2,HIGH);
       digitalWrite(Buzzer,HIGH);
      delay(2000);
      digitalWrite(LED2,LOW);
       digitalWrite(Buzzer,LOW);
      delay(2000);
      if(ValT== 1024 && bypass2<99)
      {
            Serial.print("Body Temperature =");
        Serial.print(bypass2);
        Serial.println(" °C");
        Serial.println(" ");
        bypass2=bypass2+0.9;
        }
        else{
          bypass2=97;
          Serial.print("Body Temperature =");
          Serial.print(bypass2);
          Serial.println(" °C");
          Serial.println(" ");
          }
    }
    if(client.connect(server,80)){
        updateThingSpeak(bypass1,bypass2);
    }

}