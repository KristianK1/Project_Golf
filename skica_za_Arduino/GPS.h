#include<math.h>
#include <TinyGPS.h>

TinyGPS gps;

int broj_lokacija=5;

lokacija *mjesta;

bool GPS_mjerenje(lokacija* novo_mjerenje, lokacija mjesta[]){  //jos jedan argument je broj_lokacija koji je globalna varijabla
  float flat, flon;
  unsigned long age;
  gps.f_get_position(&flat, &flon, &age);
  //print_float(flat, TinyGPS::GPS_INVALID_F_ANGLE, 10, 6);
  //print_float(flon, TinyGPS::GPS_INVALID_F_ANGLE, 11, 6);
  novo_mjerenje->setY(koor_1D((int)flat, (int)(flat*60), (int)(flat*60*60),flat-(int)(flat*60*60), 90));
  novo_mjerenje->setX(koor_1D((int)flon, (int)(flon*60), (int)(flon*60*60),flat-(int)(flon*60*60), 180));
  //dodati predznak
  //moze i ocitati brzinu, neka brzina moze produziti timer pobudenog stanja
  
  return (TinyGPS::GPS_INVALID_F_ANGLE==flat)||(TinyGPS::GPS_INVALID_F_ANGLE==flon);  //valjda
}

bool GPS_update(lokacija *mjesta){
  lokacija *novo_mjerenje=new lokacija();
  bool valid=GPS_mjerenje(novo_mjerenje, mjesta);
  
  if(valid==HIGH){
    int i;
    for(i=broj_lokacija-1; i>0;i--){
      mjesta[i]=mjesta[i-1];
    }
    mjesta[0]=*novo_mjerenje;
  }
  else if(valid==LOW){
    Serial.println("Nevaljalo mjerenje zbog nekog razloga");
  }
}
