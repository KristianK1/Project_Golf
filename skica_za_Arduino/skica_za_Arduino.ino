#include <SoftwareSerial.h>
#include"klase.h"
#include"funkcije.h"
#include"stanja.h"

SoftwareSerial GSMSerial(10, 11);
SoftwareSerial GPSSerial(4,3);

lokacija trenutne_koor, prosle_koor, nove_koor;

void setup() {
  // put your setup code here, to run once:
  GSMSerial.begin(9600);
  GPSSerial.begin(9600);
//  mjesta=new Koordinate[broj_lokacija];
  int i;
  for(i=0;i<broj_lokacija;i++){
    //mjesta[i].set(1000,1000);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  /*if(citanje_ulaza())
  {
    //new_koor=GPS_read();
    if(trenutne_koor!=nove_koor){
      prosle_koor=trenutne_koor;
      trenutne_koor=prosle_koor;
    }
  }*/
}
