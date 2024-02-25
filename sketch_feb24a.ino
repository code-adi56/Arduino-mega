/* Arduino code for bluetooth data & npk ,pH,moisture*/
#include<stdio.h>
#include<ArduinoJson.h>
#include<SoftwareSerial.h>

// for RE and DE pins
#define RE 8
#define DE 7

//NPK values
const byte nitro[] = {0x01,0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte phos[] = {0x01,0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte pota[] = {0x01,0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};

 byte values[11];
 SoftwareSerial bluetooth(10,11);
 StaticJsonDocument<256> doc;
 char payload[256];
 void setup()
 {
  Serial.begin(9600);
  bluetooth.begin(9600);
  Serial1.begin(9600);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  delay(500);
 }

void loop()
{
  if (bluetooth.available())
  { 
    int moistureValue = analogRead(A0);
    int pHValue = analogRead(A1);
 
    byte nitroValue = nitrogen();
    int n = nitroValue & 0xFF; 
    delay(250);
    byte phosphorousValue = phosphorous();
    int p = phosphorousValue & 0xFF;
    delay(250);
    byte potassiumValue = potassium();
    int k = potassiumValue & 0xFF;
    delay(250);
    doc["Moisture"] = moistureValue;
    doc["pHValue"] = pHValue;
    doc["NPKValue"] = n;
    doc["PhosphorousValue"] = p;
    doc["PotassiumValue"] = k;
    
      serializeJsonPretty(doc, payload);
      Serial.println(payload);
      bluetooth.println(payload);
  }
    delay(5000);
  
  
}
byte nitrogen(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(Serial1.write(nitro,sizeof(nitro))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values[i] = Serial1.read();
    Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}
 
byte phosphorous(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(Serial1.write(phos,sizeof(phos))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values[i] = Serial1.read();
    Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}
 
byte potassium(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(Serial1.write(pota,sizeof(pota))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values[i] = Serial1.read();
    Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}


