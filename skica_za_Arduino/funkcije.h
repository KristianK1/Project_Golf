int ulaz1=7;
int ulaz2=8;

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
