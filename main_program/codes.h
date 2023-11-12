#include "thingspeak_API_key.h"
#include "Thingspeak_chars.h"
#include "btObjectHolder.h"

class codes{
protected:

  String base64="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.:";
  String Link_field1="http://api.thingspeak.com/update?api_key=" + thingspeak_API_key + "&field1=";

    String make_sending_code(int code){
      String binary="";
      
      switch (code){
        case 0: binary+=""; // NISTA
                break;
        case 1: binary+=Unlock_char; // GOT UNLOCKED
                break;
        case 2: binary+=lights_still_on; //LIGHTS STILL ON
                break;
        case 3: binary+=left_unlocked; //STILL UNLOCKED
                break;
        case 4: binary+=device_reset; //reset
                break; 
        case 5: binary+=car_hit; //hit
                break;
        case 6: binary+=powerSupply12_unavailable;
                break;
      }
      return binary;
    }

    String make_binary(double X_kor, double Y_kor){
      String binary="";
    ////////////////////////   X
      X_kor>=0? binary+="0": binary+="1";  //1
      X_kor=fabs(X_kor);
      int rem=0;
      for(int i=7;i>=0;i--){
        rem=(int)X_kor/(int)(pow(2,i));
        X_kor-=rem*pow(2,i);
        rem>0? binary+="1": binary+="0";   //8
      }
      Serial.println("X kor int="+binary);
      rem=0;
      X_kor*=1000000;
      X_kor=round(X_kor);
      for(int i=19;i>=0;i--){
        rem=X_kor/(pow(2,i));
        X_kor-=rem*pow(2,i);
        rem>0? binary+="1": binary+="0";  //20
      }
      
      Serial.println("X kor int + dec="+binary);
    ////////////////////  Y
      Y_kor>=0? binary+="0": binary+="1";  //1
      Y_kor=fabs(Y_kor);
      rem=0;
      for(int i=6;i>=0;i--){
        rem=(int)Y_kor/(int)(pow(2,i));
        Y_kor-=rem*pow(2,i);
        rem>0? binary+="1": binary+="0";  //7
      }
      rem=0;
      Y_kor*=1000000;
      Y_kor=round(Y_kor);
      for(int i=19;i>=0;i--){
        rem=Y_kor/(pow(2,i));
        Y_kor-=rem*pow(2,i);
        rem>0? binary+="1": binary+="0";  //20
      }
      return binary;
    }

    String make_parity(String binary){
      int parity=0;
      String ret;
      for(int i=0;i<binary.length();i++){
        if(binary.charAt(i)==1) parity++;  //1
      }
      parity=parity%8;
      parity/4? ret+="1": ret=+"0";
      parity%4/2? ret+="1": ret=+"0";
      parity%2? ret+="1": ret=+"0";
      return ret;
    }

    String binary_to_base64(String binary){
      //expectred size 60
      String coded;
      for(int i=0;i<10;i++){
        int sign=0;
        for(int j=0;j<6;j++){
          sign+=pow(2,5-j)*(binary.charAt(6*i+j)=='1'? 1:0);
        }
        coded+=base64.charAt(sign);
      }
      return coded;
    }

    String small_packet(int code){
      String binary=make_sending_code(code);
      //Serial.println(binary);
      return binary;
    }

    
public:
  codes(){
    // if(mainSerialBT != NULL){
    //   mainSerialBT->println("ended CODES constructor");
    //   delay(2000);
    // }
  }
  ~codes(){}

  String big_packet(double X_kor, double Y_kor, int code){
    String binary=make_binary(X_kor, Y_kor);
    binary+=make_parity(binary);
    //Serial.println(binary);
    binary=binary_to_base64(binary);
    
    binary+=make_sending_code(code);
    //Serial.println(binary);
    return binary;
  }

  String string_to_link(String input){
    String link = Link_field1 + input;
    return link;
  }

  String loc_to_link(double locX, double locY, int code){
    //code=4;
    String link=Link_field1+big_packet(locX, locY, code);
    return link;
  }



  String small_link(int code){
    String link=Link_field1+small_packet(code);
    return link;
  }
};


