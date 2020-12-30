#include <SoftwareSerial.h>

SoftwareSerial mySerial(4,5); // RX, TX

int slanje(SoftwareSerial serial, String out, String expect){
  serial.begin(9600);
  String recive;
  serial.println(out);
  while(serial.available()==false);
  delay(5);
  Serial.println("HEJ");
  
  while(serial.available()){
    int c=serial.read();
    if(c!=10&&c!=13) recive+=(char)c;
    //Serial.println((char)c);
  }
  Serial.println(recive);
  
  if(recive==expect) return 1;
  return 0;
}

/*int HTTP(String link){
  while(mySerial.available()) mySerial.read();
  Serial.println("jedan");
  slanje(mySerial, "AT","OK");
  Serial.println("dva");
  slanje(mySerial, "AT+CFUN=1","OK");
  Serial.println("tri");
  slanje(mySerial, "AT+ASPBR=3,1,\"GPRS\"","OK");
  Serial.println("cetiri");
  slanje(mySerial, "AT+CSTT=\"TM\",\"\",\"\"","OK");
  Serial.println("pet");
  //slanje(mySerial, "AT+SAPBR=1,1","OK");
  slanje(mySerial, "AT+HTTPINIT","OK");
  Serial.println("sest");
  slanje(mySerial, "AT+HTTPPARA=\"CID\",1","OK");
  String link_AT;
  link_AT+="AT+HTTPPARA=\"URL\",\"";
  link_AT+=link;
  link_AT+="\"";
  slanje(mySerial,link_AT,"");
  Serial.println("sedam");
  slanje(mySerial, "AT+HTTPACTION=0","OK");
  Serial.println("osam");
  slanje(mySerial, "AT+HTTPREAD","");
  Serial.println("devet");
  slanje(mySerial, "AT+HTTPTERM","OK");
    
}*/

int HTTP(String link){
  while(mySerial.available()) mySerial.read();
  Serial.println("jedan");
  slanje(mySerial, "AT","OK");
  delay(1000);
  
  Serial.println("dva");
  slanje(mySerial, "AT+CREG?","OK");
  delay(1000);
  
  Serial.println("dva i po");
  
  slanje(mySerial, "AT+CSTT=\"TM\",\"\",\"\"","OK");
  delay(1000);
  
  Serial.println("tri");
  slanje(mySerial, "AT+SAPBR=2,1","OK");
  delay(1000);
  
  Serial.println("cetiri");
  slanje(mySerial, "AT+SAPBR=1,1","OK");
  delay(1000);
  
  Serial.println("pet");
  slanje(mySerial, "AT+HTTPINIT","OK");
  delay(1000);
  
  Serial.println("sest");
  String link_AT;
  link_AT+="AT+HTTPPARA=\"URL\",\"";
  link_AT+=link;
  link_AT+="\"";
  slanje(mySerial,link_AT,"");
  delay(1000);
  
  Serial.println("sedam");
  slanje(mySerial, "AT+HTTPPARA=\"CID\",1","OK");
  delay(1000);
  
  Serial.println("sedam i po");
  slanje(mySerial, "AT+HTTPACTION=0","OK");
  delay(1000);
  
  Serial.println("osam");
  slanje(mySerial, "AT+HTTPREAD","");
  delay(1000);
  
  Serial.println("devet");
  slanje(mySerial, "AT+HTTPTERM","OK");
  delay(1000);
    
}



void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  mySerial.begin(9600);
  HTTP("http://api.thingspeak.com/update?api_key=PY57W7KMYYBE2MDP&field1=22");
}



void loop() { // run over and over
}
