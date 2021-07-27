
#include "BluetoothSerial.h"

class Bluetooth_comm{
  protected:
  BluetoothSerial *SerialBT;
  int BT_state; //0 normal, 1 ignore
  
  String recived_chars;
  
  String question_request="T?";
  String end_request="T=111";
  String extend_request="T=222,";

  unsigned long int ignore_begin;
  int minutes_ignore;

  public:
  Bluetooth_comm(){
    SerialBT=new BluetoothSerial();
    
    //SerialBT->enableSSP();
    //SerialBT->begin("Project Golf", true); 
    SerialBT->begin("Project Golf"); 

    BT_state=0;
    recived_chars="";
  }
  virtual ~Bluetooth_comm(){
    delete (SerialBT);
  }

  void Bluetooth_loop(){
    reciveing();
    checking();
    
  }

  void Send_message(String mess){
    SerialBT->println(mess);
  }

  void clean_recived(){
    recived_chars="";
  }
  
  void reciveing(){
    while (SerialBT->available()){
      recived_chars+=(char)SerialBT->read();
    }
    if(recived_chars!="")
    Serial.println(recived_chars);
  }
  int AcontainsB(String A, String B){
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

  int getBTstate(){
    return BT_state;
  }
  
 void update_state(){
    if(millis()-ignore_begin>(minutes_ignore*1000*60)){
      Serial.println("Ignore ended");
      minutes_ignore=0;
      BT_state=0;
    }
  }
  void sendBTerror(){
    SerialBT->println("Error");
  }
  void sendBTstate(){
    if(BT_state==0){
      SerialBT->println("T=111");
    }
    if(BT_state==1){
      int seconds_left=(minutes_ignore*1000*60-(millis()-ignore_begin))/1000;
      int sssseconds_left=seconds_left;

      String number="";
      do{
        number=sssseconds_left%10+number;
        sssseconds_left/=10;
      }while(sssseconds_left>0);

      for(int i=number.length();i<6;i++){
        number="0"+number;
      }
      
      SerialBT->println("T=222,"+number);
    }
  }
  
  int checking(){
    if(AcontainsB(recived_chars, question_request)){
      clean_recived();
      update_state();
      sendBTstate();
      return 1;
    }
    else if(AcontainsB(recived_chars, end_request)){
      BT_state=0;
      minutes_ignore=0;
      clean_recived();
      sendBTstate();
      return 1;
    }
    else if(AcontainsB(recived_chars, extend_request)){
      for(int i=0;i<recived_chars.length()-8;i++){
        String tt="";
        int j;
        for(j=0;j<6;j++){
          tt+=recived_chars[i+j];
        }
        
        if(tt=extend_request){
          
          if(recived_chars[i+j]-48>9 || recived_chars[i+j]-48<0){
            sendBTerror();
            clean_recived();
            return 2;
          }
          minutes_ignore =100*(recived_chars[i+j]-48);
          
          
          if(recived_chars[i+j+1]-48>9 || recived_chars[i+j+1]-48<0){
            sendBTerror();
            clean_recived();
            return 2;
          }
          minutes_ignore+= 10*(recived_chars[i+j+1]-48);
          
          
          if(recived_chars[i+j+2]-48>9 || recived_chars[i+j+2]-48<0){
            sendBTerror();
            clean_recived();
            return 2;
          }
          minutes_ignore+=recived_chars[i+j+2]-48;
          
          ignore_begin=millis();
          BT_state=1;
          sendBTstate();
          clean_recived();
          return 1;
        }
      }
    }
    return 0;
  }  
};
