#include"GPS.h"

int bistabil_out=2;
int bistabil_reset=9;

int stanje=1;  //MAIN STATE


unsigned long int timer_rada;
int period_provjere_pobudeno_stanje=45;   //sekunde
int period_isteka=10; //minute
//stanje==0 mirno_stanje
//stanje==1 pobudeno_stanje
bool valid;

void loop_mirnog_stanja(){
  if(digitalRead(bistabil_out)==1){
    stanje=1;
    timer_rada=millis()+period_isteka*60;
  }
  return;
}

void loop_pobudenog_stanja(){
//  valid=GPS_update(mjesta);
  if(valid==LOW){
    //neispravno mjerenje
  }

  
  if(digitalRead(2)==1){
    timer_rada=millis()+period_isteka*60*1000;
  }
  if(timer_rada<millis()){
    //check_GPS();   //zadnja provjera prije vracanja u mirno stanje
    stanje=0;
  }
  
}
