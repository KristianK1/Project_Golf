String base64="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.:";

String make_sending_code(int code){
  String binary="";
  
  switch (code){
    case 0: binary+=",";
            break;
    case 1: binary+="@";
            break;
    case 2: binary+="-";
            break;
    case 3: binary+="_";
            break;
    case 4: break; //samo nastavak zbog prijasnje pobude
    default: Serial.println("Sending code other than 0 1 2 3 4");
              break;
  }
  return binary;
}

String make_binary(double X_kor, double Y_kor){
  String binary="";
////////////////////////   X
  X_kor>=0? binary+="0": binary+="1";
  X_kor=fabs(X_kor);
  int rem=0;
  for(int i=7;i>=0;i--){
    rem=(int)X_kor/(int)(pow(2,i));
    X_kor-=rem*pow(2,i);
    rem>0? binary+="1": binary+="0";
  }
  rem=0;
  X_kor*=1000000;
  X_kor=round(X_kor);
  for(int i=20;i>=0;i--){
    rem=X_kor/(pow(2,i));
    X_kor-=rem*pow(2,i);
    rem>0? binary+="1": binary+="0";
  }
////////////////////  Y
  Y_kor>=0? binary+="0": binary+="1";
  Y_kor=fabs(Y_kor);
  rem=0;
  for(int i=6;i>=0;i--){
    rem=(int)Y_kor/(int)(pow(2,i));
    Y_kor-=rem*pow(2,i);
    rem>0? binary+="1": binary+="0";
  }
  rem=0;
  Y_kor*=1000000;
  Y_kor=round(Y_kor);
  for(int i=20;i>=0;i--){
    rem=Y_kor/(pow(2,i));
    Y_kor-=rem*pow(2,i);
    rem>0? binary+="1": binary+="0";
  }
  return binary;
}

String make_parity(String binary){
  int parity=0;
  String ret;
  for(int i=0;i<binary.length();i++){
    if(binary.charAt(i)==1) parity++;
  }
  parity=parity%2;
  parity? ret="1": ret="0";
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

String big_packet(double X_kor, double Y_kor, int code){
  String binary=make_binary(X_kor, Y_kor);
  binary+=make_parity(binary);
  Serial.println(binary);
  binary=binary_to_base64(binary);
  
  binary+=make_sending_code(code);
  Serial.println(binary);
  return binary;
}
