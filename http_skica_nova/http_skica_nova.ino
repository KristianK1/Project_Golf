#include <SoftwareSerial.h>
SoftwareSerial mySerial(4,5); // RX, TX

String *primljeno;
int *stage;
int *repeat;
long int *stamp;
String link="http://api.thingspeak.com/update?api_key=PY57W7KMYYBE2MDP&field1=";
int i=0;
int debugging=1;

int AsadrziB(String A, String B){
  /*Serial.print("A i B: |");
  Serial.print(A);
  Serial.print("| |");
  Serial.print(B);
  Serial.println("|");*/
  if(A.length()<B.length()) {
    return 0;
  }
  for(int i=0;i<=(A.length()-B.length());i++){
    String C="";
    for(int j=0;j<B.length();j++){
      C+=A[i+j];
    }
    if(C==B) return 1;
  }
  return 0;
}

void Send(SoftwareSerial *serial, String out){
  serial->println(out);
  Serial.println(out);
}

void Recive(SoftwareSerial *serial, String *recive){
  while(serial->available()){
    int c=serial->read();
    if(c!=10||c!=13) *recive=*recive+(char)c;
    //Serial.print((char)c);
  }
  //Serial.print(*recive);
}
int HtttP(SoftwareSerial *serial, int *stage, long int *timeStamp, String *recived, String link, int *repeat){
  switch(*stage){
    case 0: *recived="";
            while(serial->available()) serial->read();
            Send(serial, "AT");
            *timeStamp=millis();
            *stage=1;
            if(debugging) Serial.println("Stage 0");
            break;
    case 1: //Serial.println("Stage 1");
            if((millis()-*timeStamp)>100){
              Recive(serial, recived);
              //Serial.println(*recived);
              if(AsadrziB(*recived, "OK")){
                *stage=2;
                *repeat=0;
              }
            }
            if(millis()-*timeStamp>1000 && *stage!=2){
              *stage=0;
              *repeat++;
            }                
            if(*repeat>5) {
              *stage=0;
              *repeat=0;
              return 0;
            }
            break;
    case 2: *recived="";
            Send(serial, "AT+SAPBR=2,1");
            *timeStamp=millis();
            *stage=3;
            if(debugging) Serial.println("Stage 2");
            break;
    case 3: if(millis()-*timeStamp>200){
              Recive(serial, recived);
              Serial.println(*recived);
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
              *repeat++;
            }
            if(*repeat>5) {
              *stage=0;
              *repeat=0;
              return 0;
            }
            break;
    case 4: *recived="";
            Send(serial, "AT+SAPBR=1,1");
            *timeStamp=millis();
            *stage=5;
            if(debugging) Serial.println("Stage 4");
            break;
    case 5: if(millis()-*timeStamp>2000){
              Recive(serial, recived);
              if(AsadrziB(*recived, "OK")){
                *stage=6;
                *repeat=0;
              }
            }
            if(millis()-*timeStamp>15000 && *stage!=6){
              *stage=2;//4 , to je za onaj slucaj kad vrati samo "K"
              *repeat++;
            }
            if(*repeat>3) {
              *stage=0;
              *repeat=0;
              return 0;
            }
            break;
    case 6: *recived="";
            while(serial->available()) serial->read();
            delay(1000);
            
            Send(serial, "AT+HTTPTERM");
            *timeStamp=millis();
            *stage=7;
            if(debugging) Serial.println("Stage 6");
            break;
    case 7: if(millis()-*timeStamp>100){
              Recive(serial, recived);
              Serial.println(*recived);
              if(AsadrziB(*recived, "ERROR")){
                *stage=8;
                *repeat=0;
              }
            }
            if(millis()-*timeStamp>500 && *stage!=8){
              *stage=6;
              *repeat=*repeat+1;
            }
            if(*repeat>5) {
              *stage=0;
              *repeat=0;
              return 0;
            }
            break;
    case 8: *recived="";
            while(serial->available()) serial->read();
            delay(1000);
            
            Send(serial, "AT+HTTPINIT");
            *timeStamp=millis();
            *stage=9;
            if(debugging) Serial.println("Stage 8");
            break;
    case 9: if(millis()-*timeStamp>500){
              Recive(serial, recived);
              Serial.println(*recived);
              if(AsadrziB(*recived, "OK")){
                *stage=10;
                *repeat=0;
              }
            }
            if(millis()-*timeStamp>2000 && *stage!=8){
              *stage=8;
              *repeat=*repeat+1;
            }
            if(*repeat>5) {
              *stage=0;
              *repeat=0;
              return 0;
            }
            break;
            
    case 10: *recived="";
            while(serial->available()) serial->read();
            String link_AT="AT+HTTPPARA=\"URL\",\""+link+"\"";
            Serial.println(link_AT);
            Send(serial, link_AT);
            *timeStamp=millis();
            *stage=11;
            if(debugging) Serial.println("Stage 10");
            break;
    case 121: if(millis()-*timeStamp>100){
              Recive(serial, recived);
              Serial.println("oj");
              if(AsadrziB(*recived, "")){
                *stage=12;
                *repeat=0;
              }
            }
            if(millis()-*timeStamp>2000 && *stage!=12){
              *stage=10;
              *repeat=*repeat+1;
            }
            if(*repeat>3) {
              *stage=0;
              *repeat=0;
              return 0;
            }
            break;
    case 12: *recived="";
            Send(serial, "AT+HTTPPARA=\"CID\",1");
            *timeStamp=millis();
            *stage=13;
            if(debugging) Serial.println("Stage 12");
            break;
    case 13: if(millis()-*timeStamp>200){
              Recive(serial, recived);
              if(AsadrziB(*recived, "OK")){
                *stage=14;
                *repeat=0;
              }
            }
            if(millis()-*timeStamp>1000 && *stage!=14){
              *stage=12;
              *repeat++;
            }
            if(*repeat>3) {
              *stage=0;
              *repeat=0;
              return 0;
            }
            break;
    case 14: *recived="";
            Send(serial, "AT+HTTPACTION=0");
            *timeStamp=millis();
            *stage=15;
            if(debugging) Serial.println("Stage 14");
            break;
    case 15: if(millis()-*timeStamp>200){
              Recive(serial, recived);
              if(AsadrziB(*recived, "OK")){
                *stage=16;
                *repeat=0;
              }
            }
            if(millis()-*timeStamp>2000 && *stage!=16){
              *stage=14;
              *repeat++;
            }
            if(*repeat>3) {
              *stage=0;
              *repeat=0;
              return 0;
            }
            break;
    case 16: *recived="";
            Send(serial, "AT+HTTPREAD=0,20");
            *timeStamp=millis();
            *stage=17;
            if(debugging) Serial.println("Stage 16");
            break;
    case 17: if(millis()-*timeStamp>200){
              Recive(serial, recived);
              if(AsadrziB(*recived, "")){//prazno???
                *stage=18;
                *repeat=0;
              }
            }
            if(millis()-*timeStamp>2000 && *stage!=18){
              *stage=16;
              *repeat++;
            }
            if(*repeat>3) {
              *stage=0;
              *repeat=0;
              return 0;
            }
            break;
    case 18: *recived="";
            Send(serial, "AT+HTTPTERM");
            *timeStamp=millis();
            *stage=19;
            if(debugging) Serial.println("Stage 18");
            if(debugging) Serial.println(*stage);
            break;
    case 19: if(millis()-*timeStamp>200){
              Recive(serial, recived);
              if(AsadrziB(*recived, "OK")){
                return 1;
              }
            }
            if(millis()-*timeStamp>2000){
              *stage=18;
              *repeat++;
            }
            if(*repeat>3) {
              *stage=0;
              *repeat=0;
              return 0;
            }
            break;              
  }
  return 2;
}

void setup() {
  // put your setup code here, to run once:
  primljeno=new String("");
  stage=new int(0);
  repeat=new int(0);
  stamp=new long int(0);
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  //Serial.println(*stage);
  int q=HtttP(&mySerial, stage, stamp, primljeno, link+String(i), repeat);
  if(1==q){
    i++;
    Serial.println("Uspjesno poslano");
    delay(10000);
  }
  if(q==2) Serial.println("ne jos");
  if(q==0) {
    Serial.println("Failed");
    delay(10000);
  }
  delay(100);
}
