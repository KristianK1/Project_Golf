//#include <SoftwareSerial.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

class SIM800L_KK{
private: 
  String *recived;
  int *stage;
  int *repeat;
  long int *timeStamp;
  //SoftwareSerial *serial;
  String link;

  int AsadrziB(String A, String B){
    /*Serial.print("A i B: |");
    Serial.print(A);
    Serial.print("| |");
    Serial.print(B);
    Serial.println("|");*/
    if(A.length()<B.length()) {
      return 0;
    }
    for(unsigned int i=0;i<=(A.length()-B.length());i++){
      String C="";
      for(unsigned int j=0;j<B.length();j++){
        C+=A[i+j];
      }
      if(C==B) return 1;
    }
    return 0;
  }
  void Send(String out){
    Serial2.println(out);
    SerialBT.println(out);
  }
  void Recive(String *recive){
    while(Serial2.available()){
      int c=Serial2.read();
      if(c!=10||c!=13) *recive=*recive+(char)c;
      //Serial.print((char)c);
    }
    //Serial.print(*recive);
  }   
  int Reset_happend(String recived) {
    if(AsadrziB(recived,"CPIN")) {
      return 1;
    }
    if(AsadrziB(recived,"Ready")){
      return 1;
    }
    if(AsadrziB(recived,"CALL")){
      return 1;
    }
    if(AsadrziB(recived,"SMS")){
      return 1;
    }
    return 0;
  }


public:
  SIM800L_KK(){
    Serial2.begin(9600);
    recived=new String();
    stage=new int();
    repeat=new int();
    timeStamp=new long int();
  }
  ~SIM800L_KK(){
    delete(recived);
    delete(stage);
    delete(repeat);
    delete(timeStamp);
  }
  void setLink(String new_link){
    link=new_link;
  }
  
  int access(){
    String link_AT="";
    switch(*stage){
      case 0: *recived="";
              while(Serial2.available()) Serial2.read();
              Send("AT");

              *timeStamp=millis();
              *stage=1;
              if(true) SerialBT.println("Stage 0");
              break;
      case 1: //Serial.println("Stage 1");
              if((millis()-*timeStamp)>100){
                Recive(recived);              
                if(Reset_happend(*recived)) {
                  *stage=0;
                  *repeat=0;
                  return 3;
                }
                //Serial.println(*recived);
                if(AsadrziB(*recived, "OK")){
                  *stage=2;
                  *repeat=0;
                }
              }
              if(millis()-*timeStamp>1000 && *stage!=2){
                *stage=0;
                (*repeat)++;
              }                
              if(*repeat>5) {
                *stage=0;
                *repeat=0;
                return 0;
              }
              break;
      case 2: *recived="";
              Send("AT+SAPBR=2,1");
              *timeStamp=millis();
              *stage=3;
              if(true) SerialBT.println("Stage 2");
              break;
      case 3: if(millis()-*timeStamp>200){
                Recive(recived);              
                if(Reset_happend(*recived)) {
                  *stage=0;
                  *repeat=0;
                  return 3;
                }
                if(AsadrziB(*recived, "1,3")){
                  *stage=4;
                  *repeat=0;
                }
                else if(AsadrziB(*recived, "1,1")){
                  *stage=6;
                  *repeat=0;
                }
              }
              if(millis()-*timeStamp>1500 && *stage!=4){
                *stage=2;
                (*repeat)++;
              }
              if(*repeat>5) {
                *stage=0;
                *repeat=0;
                return 0;
              }
              break;
      case 4: *recived="";
              Send("AT+SAPBR=1,1");
              *timeStamp=millis();
              *stage=5;
              if(true) SerialBT.println("Stage 4");
              break;
      case 5: if(millis()-*timeStamp>1000){
                Recive(recived);
                if(Reset_happend(*recived)) {
                  *stage=0;
                  *repeat=0;
                  return 3;
                }
                if(AsadrziB(*recived, "OK")){
                  *stage=6;
                  *repeat=0;
                }
                else if(AsadrziB(*recived, "ERROR")){
                  *stage=2;
                  *repeat=0;
                }
              }
              if(millis()-*timeStamp>20000 && *stage!=6){
                *stage=2;//4 , to je za onaj slucaj kad vrati samo "K"
                (*repeat)++;
              }
              if(*repeat>1) {
                *stage=0;
                *repeat=0;
                return 0;
              }
              break;
      case 6: *recived="";
              while(Serial2.available()) Serial2.read();
              delay(1000);
              
              Send("AT+HTTPTERM");
              *timeStamp=millis();
              *stage=7;
              if(true) SerialBT.println("Stage 6");
              break;
      case 7: if(millis()-*timeStamp>100){
                Recive(recived);              
                if(Reset_happend(*recived)) {
                  *stage=0;
                  *repeat=0;
                  return 3;
                }
                SerialBT.println(*recived);
                if(AsadrziB(*recived, "ERROR")){
                  *stage=8;
                  *repeat=0;
                }
              }
              if(millis()-*timeStamp>500 && *stage!=8){
                *stage=6;
                (*repeat)++;
              }
              if(*repeat>5) {
                *stage=0;
                *repeat=0;
                return 0;
              }
              break;
      case 8: *recived="";
              while(Serial2.available()) Serial2.read();
              delay(1000);
              
              Send("AT+HTTPINIT");
              *timeStamp=millis();
              *stage=9;
              if(true) SerialBT.println("Stage 8");
              break;
      case 9: if(millis()-*timeStamp>500){
                Recive(recived);              
                if(Reset_happend(*recived)) {
                  *stage=0;
                  *repeat=0;
                  return 3;
                }
                SerialBT.println(*recived);
                if(AsadrziB(*recived, "OK")){
                  *stage=10;
                  *repeat=0;
                }
              }
              if(millis()-*timeStamp>2000 && *stage!=8){
                *stage=8;
                (*repeat)++;
              }
              if(*repeat>5) {
                *stage=0;
                *repeat=0;
                return 0;
              }
              break;
              
      case 10: *recived="";
              while(Serial2.available()) Serial2.read();
              link_AT="AT+HTTPPARA=\"URL\",\""+link+"\"";
              
              Send(link_AT);
              *timeStamp=millis();
              *stage=11;
              if(true) SerialBT.println("Stage 10");
              break;
      case 11: SerialBT.println("Stage 121");
              if(millis()-*timeStamp>100){
                Recive(recived);              
                if(Reset_happend(*recived)) {
                  *stage=0;
                  *repeat=0;
                  return 3;
                }
                SerialBT.println("oj");
                if(AsadrziB(*recived, "")){
                  *stage=12;
                  *repeat=0;
                }
              }
              if(millis()-*timeStamp>2000 && *stage!=12){
                *stage=10;
                (*repeat)++;
              }
              if(*repeat>3) {
                *stage=0;
                *repeat=0;
                return 0;
              }
              break;
      case 12: *recived="";
              Send("AT+HTTPPARA=\"CID\",1");
              *timeStamp=millis();
              *stage=13;
              if(true) SerialBT.println("Stage 12");
              break;
      case 13: if(millis()-*timeStamp>200){
                Recive(recived);              
                if(Reset_happend(*recived)) {
                  *stage=0;
                  *repeat=0;
                  return 3;
                }
                if(AsadrziB(*recived, "OK")){
                  *stage=14;
                  *repeat=0;
                }
              }
              if(millis()-*timeStamp>1000 && *stage!=14){
                *stage=12;
                (*repeat)++;
              }
              if(*repeat>3) {
                *stage=0;
                *repeat=0;
                return 0;
              }
              break;
      case 14: *recived="";
              Send("AT+HTTPACTION=0");
              *timeStamp=millis();
              *stage=15;
              if(true) SerialBT.println("Stage 14");
              break;
      case 15: if(millis()-*timeStamp>200){
                Recive(recived);              
                if(Reset_happend(*recived)) {
                  *stage=0;
                  *repeat=0;
                  return 3;
                }
                if(AsadrziB(*recived, "OK")){
                  *stage=16;
                  *repeat=0;
                }
              }
              if(millis()-*timeStamp>2000 && *stage!=16){
                *stage=14;
                (*repeat)++;
              }
              if(*repeat>3) {
                *stage=0;
                *repeat=0;
                return 0;
              }
              break;
      case 16: *recived="";
              Send("AT+HTTPREAD=0,5");//0,20?
              *timeStamp=millis();
              *stage=17;
              if(true) SerialBT.println("Stage 16");
              break;
      case 17: if(millis()-*timeStamp>200){
                Recive(recived);              
                if(Reset_happend(*recived)) {
                  *stage=0;
                  *repeat=0;
                  return 3;
                }
                if(AsadrziB(*recived, "")){//prazno???
                  *stage=18;
                  //return 1;
                  *repeat=0;
                }
                /*int success=0;
                //provjeravanje sadrzaja stranice
                for(int broj=1;broj<10;broj++){
                  if(AsadrziB(*recived,""+(char)(broj+48))){
                    SerialBT.println("SADRZI BROJ:"+(char)(broj+48));
                    success=1;

                    //delay(3000);
                    //return 4;         
                  }
                }
                if(success==0){
                   *stage=0;
                   *repeat=0;
                   SerialBT.println("FALSE POSITIVE");
                }
                else{
                  SerialBT.println("\n\nsykeeeeeeee");
                  
                }*/
              }
              if(millis()-*timeStamp>2000 && *stage!=18){
                *stage=16;
                (*repeat)++;
              }
              if(*repeat>3) {
                *stage=0;
                *repeat=0;
                return 0;
              }
              break;
      case 18: *recived="";
              Send("AT+HTTPTERM");
              *timeStamp=millis();
              *stage=19;
              if(true) SerialBT.println("Stage 18");
              if(true) SerialBT.println(*stage);
              break;
      case 19: if(millis()-*timeStamp>100){
                Recive(recived);              
                if(Reset_happend(*recived)) {
                  *stage=0;
                  *repeat=0;
                  return 3;
                }
                if(AsadrziB(*recived, "ERROR")){
                  *stage=0;
                  *repeat=0;
                  return 1;
                }
              }
              if(millis()-*timeStamp>500){
                *stage=18;
                (*repeat)++;
              }
              if(*repeat>5) {
                *stage=0;
                *repeat=0;
                return 0;
              }
              break;        
  }
  return 2;
  }
};
