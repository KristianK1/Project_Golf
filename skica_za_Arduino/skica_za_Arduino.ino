#include <SoftwareSerial.h>
#include"klase.h"
#include"funkcije.h"
#include"stanja.h"
#include"paljenje_modula.h"

SoftwareSerial GSMSerial(10, 11);
SoftwareSerial GPSSerial(4,3);
//TinyGPS gps;

lokacija trenutno_online;

void setup() {
  // put your setup code here, to run once:
  GSMSerial.begin(9600);
  GPSSerial.begin(4800);
  mjesta=new lokacija[broj_lokacija];
  int i;
  for(i=0;i<broj_lokacija;i++){
    //mjesta[i].set(1000,1000);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  if(stanje==0){
    loop_mirnog_stanja();
  }
  if(stanje==1){
    loop_pobudenog_stanja();
  }
}
