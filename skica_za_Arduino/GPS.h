#include<math.h>
#include <TinyGPS.h>
#include"klase.h"
#include"paljenje_modula.h"
TinyGPS gps;

int broj_lokacija = 5;
int br_ponavljanja=5;  //za dobivanje slicnih mjerenja
lokacija *mjesta;



bool GPS_mjerenje(lokacija* novo_mjerenje, lokacija mjesta[]) { //jos jedan argument je broj_lokacija koji je globalna varijabla
  lokacija *mjerenja = new lokacija[5];
  float flat, flon;
  unsigned long age;
  int i;
  bool valid=true;


  GPS_power(1);
  for (i = 0; i < br_ponavljanja; i++) {
    gps.f_get_position(&flat, &flon, &age);
    mjerenja[i].setY(koor_1D((int)flat, (int)(flat * 60), (int)(flat * 60 * 60), flat - (int)(flat * 60 * 60), 32000));
    mjerenja[i].setX(koor_1D((int)flon, (int)(flon * 60), (int)(flon * 60 * 60), flat - (int)(flon * 60 * 60), 32000));
    if((TinyGPS::GPS_INVALID_F_ANGLE == flat) || (TinyGPS::GPS_INVALID_F_ANGLE == flon)==0){
      delete(mjerenja);
      return LOW;
    }
  }
  GPS_power(0);
  lokacija srednja=srednja_vrijednost(mjerenja, br_ponavljanja);
  lokacija odstupanje=srednje_apsolutno_odstupanje(mjerenja, br_ponavljanja);
  if(srednja_udaljenost_metri(srednja, odstupanje)>50){
    delete(mjerenja);
    return false; 
  }
  else{
    *novo_mjerenje=srednja;
    delete(mjerenja);
    return true;
  }


  
  //print_float(flat, TinyGPS::GPS_INVALID_F_ANGLE, 10, 6);
  //print_float(flon, TinyGPS::GPS_INVALID_F_ANGLE, 11, 6);
  novo_mjerenje->setY(koor_1D((int)flat, (int)(flat * 60), (int)(flat * 60 * 60), flat - (int)(flat * 60 * 60), 90));
  novo_mjerenje->setX(koor_1D((int)flon, (int)(flon * 60), (int)(flon * 60 * 60), flat - (int)(flon * 60 * 60), 180));
  //dodati predznak
  //moze i ocitati brzinu, neka brzina moze produziti timer pobudenog stanja
        
  
  delete(mjerenja);
  //return (TinyGPS::GPS_INVALID_F_ANGLE == flat) || (TinyGPS::GPS_INVALID_F_ANGLE == flon); //valjda

return false;
}

bool GPS_update(lokacija *mjesta) {
  Serial.println("ulaz u GPS update");
  lokacija *novo_mjerenje = new lokacija();
  bool valid;
  Serial.println("Ulazak u GPS_mjerenje");
  valid=GPS_mjerenje(novo_mjerenje, mjesta);
  Serial.println("Izlazak iz GPS_mjerenje");
  if (valid == HIGH) {
    int i;
    for (i = broj_lokacija - 1; i > 0; i--) {
      mjesta[i] = mjesta[i - 1];
    }
    mjesta[0] = *novo_mjerenje;
  }
  else if (valid == LOW) {
    //Serial.println("Nevaljalo mjerenje zbog nekog razloga");
  }
  Serial.println("Izlazak iz GPS_update");
  delete(novo_mjerenje);
  return valid;
}
