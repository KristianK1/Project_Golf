#include <SoftwareSerial.h>

SoftwareSerial mySerial(4,5); // RX, TX

int AsadrziB(String A, String B){
  for(int i=0;i<(A.length()-B.length());i++){
    String C="";
    for(int j=0;j<B.length();j++){
      C+=A[i+j];
    }
    if(C==B) return 1;
  }
  return 0;
}


String slanje(SoftwareSerial serial, String out, int Delay){
  serial.begin(9600);
  String recive="";
  serial.println(out);
  delay(Delay);
  while(serial.available()==false);
  
  while(serial.available()){
    int c=serial.read();
    if(c!=10||c!=13) recive+=(char)c;
    //Serial.println((char)c);
  }
  if(out=="AT+HTTPREAD=0,10")
  Serial.println(recive);
  return recive;
}

int HTTP(String link){
  while(mySerial.available()) mySerial.read(); //flush
  int i=0;
  String link_AT="";
  link_AT+="AT+HTTPPARA=\"URL\",\"";
  link_AT+=link;
  link_AT+="\"";

  for(i=0;i<10 && (slanje(mySerial, "AT", 50)=="OK") ;i++) delay(50);
  if(i>=10) return 0;
    
  for(i=0;i<10 && (slanje(mySerial, "AT+CREG?", 100)=="OK") ;i++) delay(50);
  if(i==10) return 0;
  Serial.println("oj");
  
  int skip1_1=0;
  for(i=0;i<10;i++){
    String rezultat=slanje(mySerial, "AT+SAPBR=2,1",1000);
    if(AsadrziB(rezultat,"1,1")){
      skip1_1=1;
      break;
    }
    else if(AsadrziB(rezultat,"1,3")){
      skip1_1=0;
      //break;
    }
  }
  Serial.println("oj1");
  if(skip1_1==0){
    for(i=0;i<5 && (slanje(mySerial, "AT+SAPBR=1,1",6000)=="OK") ;i++) delay(1000);
    if(i==5) return 0;
  }

  
  for(i=0;i<4 && (slanje(mySerial, "AT+HTTPINIT",1000)=="OK") ;i++) delay(50);
  if(i==4) return 0;
    Serial.println("oj2");
    
  for(i=0;i<4 && (slanje(mySerial, link_AT,50)=="OK") ;i++) delay(50);
  if(i==4) return 0;
  Serial.println("oj3");
  
  for(i=0;i<4 && (slanje(mySerial, "AT+HTTPPARA=\"CID\",1",50)=="OK") ;i++) delay(50);
  if(i==4) return 0;  
    Serial.println("oj4");
    
  for(i=0;i<4 && (AsadrziB(slanje(mySerial, "AT+HTTPACTION=0", 50),"200")) ;i++) delay(50);
  if(i==4) return 0;
  Serial.println("oj5");
  
  for(i=0;i<4 && (slanje(mySerial, "AT+HTTPREAD=0,10", 2000)=="OK") ;i++) delay(50);
  if(i==4) return 0;
  Serial.println("oj6");
  
  //for(i=0;i<4 && (slanje(mySerial, "AT+HTTPTERM", 50)=="") ;i++) delay(50);
  //if(i==4) return 0;

  return 1;
}



void setup() {
  // Open serial communications and wait for port to open:
  pinMode(2,1);
  digitalWrite(2,HIGH);
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(2000);
}

String link="http://api.thingspeak.com/update?api_key=PY57W7KMYYBE2MDP&field1=";
int i=1;
void loop() {
  String LINK=link+String(i);
  
  Serial.println(HTTP(LINK)? "uspjelo":"Nespjelo");
  Serial.println(i);
  i++;
  digitalWrite(2,LOW);
  delay(1000);
  digitalWrite(2,HIGH);
  delay(10000);
  Serial.print("\n\n\n\n\n\n\n\n\nNovi broj je: "); Serial.println(i);
}
