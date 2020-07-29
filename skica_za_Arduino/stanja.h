#include"GPS.h"

int bistabil_out=2;
int bistabil_reset=9;

int stanje=1;  //MAIN STATE

int period_provjere_pobudeno_stanje=2;   //sekunde
unsigned long int period_isteka=60; //sekunde  (10*60)
unsigned long int timer_rada=period_isteka*1000;

//stanje==0 mirno_stanje
//stanje==1 pobudeno_stanje
bool valid;

void loop_mirnog_stanja(){
  if(digitalRead(bistabil_out)==1){
    stanje=1;
    timer_rada=millis()+period_isteka*1000;
    Serial.println(millis());
    Serial.println(timer_rada);
  }
  return;
}

void reset_bistabil(){
  digitalWrite(bistabil_reset, HIGH);
  delay(50);  //change to 2 ms
  digitalWrite(bistabil_reset, LOW);
  return;
}

void produzenje_pobudenog_stanja(){
  timer_rada=millis()+period_isteka*1000;
  return;
}

void loop_pobudenog_stanja(){
  //valid=GPS_update(mjesta);
  if(valid==LOW){
    //neispravno mjerenje
  }

  if(digitalRead(bistabil_out)==1){
    produzenje_pobudenog_stanja();
    reset_bistabil();
  }
  if(timer_rada<millis()){
    GPS_update(mjesta);   //zadnja provjera prije vracanja u mirno stanje, provjera brzine
    stanje=0;
    Serial.println("ugasio sam");
    
    Serial.print("timer_rada: ");
    Serial.println(timer_rada);
    
    Serial.print("millis: ");
    Serial.println(millis());

  } 
}
