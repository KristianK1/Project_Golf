#include<math.h>

int broj_lokacija=5;
Koordinate *mjesta;

double udaljenost(Koordinate &K, double X, double Y){
  return sqrt(pow(K.getX()-X,2)+pow(K.getY()-Y,2));
}

bool GPS_mjerenje(Koordinate* mjer, Koordinate *mjesta){
  
  mjer->set(18,45);  //primjer, ovdje treba ubaciti mjerenje
  bool vjerodostojnost=1;

  
  if(vjerodostojnost==1){
    //provjera mjerenja
    if(mjer->getX()<=180&&mjer->getX()>=-180&&mjer->getY()<90&&mjer->getY()>-90){
      //racunje srednje vrijednosti zadnji broj_lokacija+1 mjerenja
      int br=0;
      double Xavg=0, Yavg=0, sigma=0;
      int i;
  
      Xavg+=mjer->getX();
      Yavg+=mjer->getY();
      br++;
      for(i=0;i<broj_lokacija;i++){
        if(mjesta[i].getX()<=180&&mjesta[i].getX()>=-180&&mjesta[i].getY()<90&&mjesta[i].getY()>-90){
          br++;
          Xavg+=mjesta[i].getX();
          Yavg+=mjesta[i].getY();
        }
      }
      Xavg/=br;
      Yavg/=br;
  
      br=0;
  
      sigma+=udaljenost(*mjer, Xavg, Yavg);
      br++;
      //racunanje devijacije zadnjih broj_lokacija+1 mjerenja
      for(i=0;i<broj_lokacija;i++){
        if(mjesta[i].getX()<=180&&mjesta[i].getX()>=-180&&mjesta[i].getY()<90&&mjesta[i].getY()>-90){
          br++;
          sigma+=udaljenost(mjesta[i], Xavg,Yavg);
        }
      }
      sigma/=br;
      sigma=sqrt(sigma);
      return sigma;
    }
    else Serial.println("Primljena totalno kriva koordinata (nije na zemlji)");
  }
}


bool GPS_update(Koordinate *mjesta){
  Koordinate *novo_mjerenje=new Koordinate();
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
