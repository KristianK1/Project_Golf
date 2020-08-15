#include <SoftwareSerial.h>
#include"funkcije.h"
#include"stanja.h"
//#include"testiranje.h"
//#include"test_operatora.h"
#include"test_odstupanje.h"
SoftwareSerial GSMSerial(10, 11);
SoftwareSerial GPSSerial(4,3);


unsigned long int timer_check;
int T_check=1*1000;
lokacija trenutno_online;

void setup() {  
  Serial.begin(1000000);
  Serial.println("DJESI");
  randomSeed(analogRead(A0));
  // put your setup code here, to run once:
  
  GSMSerial.begin(9600);
  GPSSerial.begin(4800);

  //test
  //testiranje();
  //test_jednakosti();
  //test end
  
  
  
  Serial.println("wrera aaa");
//
  int n=40;
  lokacija *polje;
  polje=generiranje(n);
  Serial.println("SREDNJA");

  /*lokacija srednja=srednja_vrijednost(polje,n);
  Serial.println("SREDNJA");

  Serial.println(srednja.getX().get_stupanj());
    Serial.println(srednja.getX().get_minuta());
    Serial.println(srednja.getX().get_sekunda());
    Serial.println(srednja.getX().get_decimala());
    Serial.println();
    Serial.println(srednja.getY().get_stupanj());
    Serial.println(srednja.getY().get_minuta());
    Serial.println(srednja.getY().get_sekunda());
    Serial.println(srednja.getY().get_decimala());
    Serial.println();
    Serial.println();
  Serial.println("END");*/

  
    lokacija ODSTUPANJE=srednje_apsolutno_odstupanje(polje, n);
    Serial.println(ODSTUPANJE.getX().get_stupanj());
    Serial.println(ODSTUPANJE.getX().get_minuta());
    Serial.println(ODSTUPANJE.getX().get_sekunda());
    Serial.println(ODSTUPANJE.getX().get_decimala());
    Serial.println();
    Serial.println(ODSTUPANJE.getY().get_stupanj());
    Serial.println(ODSTUPANJE.getY().get_minuta());
    Serial.println(ODSTUPANJE.getY().get_sekunda());
    Serial.println(ODSTUPANJE.getY().get_decimala());
    Serial.println();
    Serial.println();
    
  delete(polje);
  while(1);
//

  mjesta=new lokacija[broj_lokacija];
  int i;
  for(i=0;i<broj_lokacija;i++){
    //mjesta[i].set(1000,1000);
  }
  pinMode(GSM_power_pin, OUTPUT);
  pinMode(GPS_power_pin, OUTPUT);
  pinMode(bistabil_reset, OUTPUT);

  Serial.println("                 setup");
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
