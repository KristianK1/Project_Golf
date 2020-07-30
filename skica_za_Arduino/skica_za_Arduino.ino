#include <SoftwareSerial.h>
#include"funkcije.h"
#include"stanja.h"

SoftwareSerial GSMSerial(10, 11);
SoftwareSerial GPSSerial(4,3);
//TinyGPS gps;

unsigned long int timer_check;
int T_check=1*1000;
lokacija trenutno_online;

void setup() {
  // put your setup code here, to run once:
  GSMSerial.begin(9600);
  GPSSerial.begin(4800);
  Serial.begin(9600);
  mjesta=new lokacija[broj_lokacija];
  int i;
  for(i=0;i<broj_lokacija;i++){
    //mjesta[i].set(1000,1000);
  }
  pinMode(GSM_power_pin, OUTPUT);
  pinMode(GPS_power_pin, OUTPUT);
  pinMode(bistabil_reset, OUTPUT);

  Serial.println("                 setup");
  Serial.println(sizeof(lokacija));
}

void loop() {
  // put your main code here, to run repeatedly:
  if(timer_check<millis()){
    timer_check=millis()+T_check;
    Serial.println("state run");
    if(stanje==0){
      Serial.println("mirno stanje");
      loop_mirnog_stanja();
    }
    else if(stanje==1){
      Serial.println("pobuđeno stanje");
      loop_pobudenog_stanja();
    }

  }
  
  
}
