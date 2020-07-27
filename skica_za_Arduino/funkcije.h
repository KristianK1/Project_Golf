int ulaz1=A1;
int ulaz2=A2;

int input_time=0;

int istek_minute=3;

bool citanje_ulaza(){
  if(digitalRead(ulaz1)||digitalRead(ulaz2)){
    input_time=millis();
    return HIGH;
  }
  else if(input_time-millis()<(istek_minute*60*1000)){
      return HIGH;
  }
  else
    return LOW;
}
