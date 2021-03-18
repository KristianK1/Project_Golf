#include"codes.h"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("\n\n\n\n");
  
  double X_kor=179.123456789132;
  double Y_kor= 89.123456784565;
  int code=3;  // [0 15]  4bita
  String packet=big_packet(X_kor, Y_kor, code);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
