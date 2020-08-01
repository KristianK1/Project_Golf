class koor_1D {
    friend koor_1D divide(koor_1D, int);
    friend bool operator>=(const koor_1D&, const koor_1D&);
    friend bool operator==(const koor_1D& lhs, const koor_1D& rhs);
    friend koor_1D& operator-(const koor_1D&, const koor_1D&);
    friend koor_1D& operator+(const koor_1D&, const koor_1D&);
    friend void prefix(koor_1D*);
  private:
    int stupanj;
    int minuta;
    int sekunda;
    double decimala_sekunde;
    int maks;   //za X je 180, za Y je 90
  public:
    koor_1D(): stupanj(0), minuta(0), sekunda(0), decimala_sekunde(0.0), maks(0) {}
    koor_1D(int mStupnjevi, int mMinute, int mSekunde, double mDecimala, int mmaks): stupanj(mStupnjevi), minuta(mMinute), sekunda(mSekunde), decimala_sekunde(mDecimala), maks(mmaks) {}
    int get_stupanj() {
      return stupanj;
    }
    int get_minuta() {
      return minuta;
    }
    int get_sekunda() {
      return sekunda;
    }
    double get_decimala() {
      return decimala_sekunde;
    };

    void set_stupanj(int new_stupanj) {
      stupanj = new_stupanj;
    }
    void set_minuta(int new_minuta) {
      minuta = new_minuta;
    }
    void set_sekunda(int new_sekunda) {
      sekunda = new_sekunda;
    }
    void set_decimala(double new_decimala) {
      decimala_sekunde = new_decimala;
    }

    void koor_abs() {
      prefix(this);
      if (stupanj < 0) {
        stupanj *= -1;
        minuta *= -1;
        sekunda *= -1;
        decimala_sekunde *= -1;
      }
    }

};

koor_1D divide(koor_1D lhs, int rhs) {
  koor_1D ret;
  ret.maks = lhs.maks;
  if (rhs > 0) {
    ret.stupanj = lhs.stupanj / rhs;
    lhs.stupanj -= ret.stupanj * rhs;

    lhs.minuta += lhs.stupanj * 60;
    ret.minuta = (int)(lhs.minuta / rhs);
    lhs.minuta -= ret.minuta * rhs;

    lhs.sekunda += lhs.minuta * 60;
    ret.sekunda = (int)(lhs.sekunda / rhs);
    lhs.sekunda -= ret.sekunda * rhs;

    lhs.decimala_sekunde += lhs.sekunda * 1.0;
    ret.decimala_sekunde = lhs.decimala_sekunde / rhs;
  }
}


bool operator>=(const koor_1D& lhs, const koor_1D& rhs) {
  /*if(lhs.stupanj>rhs.stupanj) return true;
    else if(lhs.stupanj<rhs.stupanj)return false;
    else {
    if(lhs.minuta>rhs.minuta) return true;
    else if(lhs.minuta<rhs.minuta)return false;
    else{
      if(lhs.sekunda>rhs.sekunda) return true;
      else if(lhs.sekunda<rhs.sekunda)return false;
      else{
        if(lhs.decimala_sekunde>=rhs.decimala_sekunde) return true;
        else if(lhs.decimala_sekunde<rhs.decimala_sekunde)return false;
      }
    }
    }*/
  long int lhss = (long int)lhs.get_stupanj() * 3600 + lhs.get_minuta() * 60 + lhs.get_sekunda() + (int)lhs.get_decimala();
  long int rhss = (long int)rhs.get_stupanj() * 3600 + rhs.get_minuta() * 60 + rhs.get_sekunda() + (int)rhs.get_decimala();
  //Serial.print("YOOOOOOOOO: "); Serial.println(rhss);
  //Serial.print("YOOOOOO LHS: "); Serial.println(lhss);
  if (lhss > rhss) {
    return true;
  }
  else if (lhss < rhss) {
    return false;
  }
  else {
    //Serial.println("fuck");
    return (lhs.get_decimala() >= rhs.get_decimala());

  }
}

bool operator==(const koor_1D& lhs, const koor_1D& rhs) {
  if (lhs.get_stupanj() == rhs.get_stupanj()) {
    if (lhs.get_minuta() == rhs.get_minuta()) {
      if (lhs.get_sekunda() == rhs.get_sekunda()) {
        if ((lhs.get_decimala() - rhs.get_decimala() < 0.001) && (lhs.get_decimala() - rhs.get_decimala() > -0.001)) {
          return true;
        }
      }
    }
  }
  return false;
}


koor_1D& operator-(const koor_1D& lhs, const koor_1D& rhs) {
  koor_1D ret;
  ret.maks = lhs.maks;
  if (lhs.maks != rhs.maks) {
    return ret;
  }
  if (lhs >= rhs) {
    ret.decimala_sekunde += lhs.decimala_sekunde - rhs.decimala_sekunde;
    while (ret.decimala_sekunde < 0) {
      ret.decimala_sekunde += 1;
      ret.sekunda -= 1;
    }
    while (ret.decimala_sekunde >= 1) {
      ret.decimala_sekunde -= 1;
      ret.sekunda += 1;
    }

    ret.sekunda += lhs.sekunda - rhs.sekunda;
    while (ret.sekunda < 0) {
      ret.sekunda += 60;
      ret.minuta -= 1;
    }
    while (ret.sekunda >= 60) {
      ret.sekunda -= 60;
      ret.minuta += 1;
    }

    ret.minuta += lhs.minuta - rhs.minuta;
    while (ret.minuta < 0) {
      ret.minuta += 60;
      ret.stupanj -= 1;
    }
    while (ret.minuta >= 60) {
      ret.minuta -= 60;
      ret.stupanj += 1;
    }
    ret.stupanj += lhs.stupanj - rhs.stupanj;
  }
  else {
    ret.decimala_sekunde += lhs.decimala_sekunde - rhs.decimala_sekunde;
    while (ret.decimala_sekunde > 0) {
      ret.decimala_sekunde -= 1;
      ret.sekunda += 1;
    }
    while (ret.decimala_sekunde <= -1) {
      ret.decimala_sekunde += 1;
      ret.sekunda -= 1;
    }

    ret.sekunda += lhs.sekunda - rhs.sekunda;
    while (ret.sekunda > 0) {
      ret.sekunda -= 60;
      ret.minuta += 1;
    }
    while (ret.sekunda <= -60) {
      ret.sekunda += 60;
      ret.minuta -= 1;
    }
    ret.minuta = +lhs.minuta - rhs.minuta;
    while (ret.minuta > 0) {
      ret.minuta -= 60;
      ret.stupanj += 1;
    }
    while (ret.minuta <= -60) {
      ret.minuta += 60;
      ret.stupanj -= 1;
    }
    ret.stupanj = +lhs.stupanj - rhs.stupanj;
    while (ret.stupanj > ret.maks) {
      ret.stupanj -= 2 * ret.maks;
    }

    while (ret.stupanj < -1 * ret.maks) {
      ret.stupanj += 2 * ret.maks;
    }

  }

  //ukonit pola ovog iznad jer je uklopljeno u prefix
  prefix(&ret);
  return ret;
}

koor_1D& operator+(const koor_1D& lhs, const koor_1D& rhs) {
  koor_1D ret;
  ret.decimala_sekunde = lhs.decimala_sekunde + rhs.decimala_sekunde;
  ret.sekunda = lhs.sekunda + rhs.sekunda;
  ret.minuta = lhs.minuta + rhs.minuta;
  ret.stupanj = lhs.stupanj + rhs.stupanj;
  prefix(&ret);
  return ret;
}

void prefix(koor_1D *kor) {
  bool ispravno=false;
  if (*kor == koor_1D(0, 0, 0, 0.0, kor->maks)) {
    /*if (kor->decimala_sekunde < 0) {
      kor->decimala_sekunde *= -1;
    }*/
    return kor;
  }
  while(ispravno==false){
    ispravno=true;
    if (*kor >= koor_1D(0, 0, 0, 0.0, kor->maks)) {
      //Serial.println("vece od nule");
      //while(kor->decimala_sekunde < 0||kor->decimala_sekunde >= 1||kor->sekunda < 0||kor->sekunda >=60||kor->minuta < 0||kor->minuta>=60||kor->stupanj < 0||kor->stupanj >= kor->maks){
        //Serial.println("eo me");
        while (kor->decimala_sekunde < 0) {
          //Serial.println("Decimala <0");
          kor->decimala_sekunde += 1;
          kor->sekunda -= 1;
          ispravno=false;
        }
        while (kor->decimala_sekunde >= 1) {
          //Serial.println("Decimala >=1");
          kor->decimala_sekunde -= 1;
          kor->sekunda += 1;
          ispravno=false;
        }
    
        while (kor->sekunda < 0) {
          //Serial.println("sekunda <0");
          kor->minuta -= 1;
          kor->sekunda += 60;
          ispravno=false;
        }
        while (kor->sekunda >= 60) {
          //Serial.println("Sekunda >6=0");
          kor->minuta += 1;
          kor->sekunda -= 60;
          ispravno=false;
        }
    
        while (kor->minuta < 0) {
          //Serial.println("Minuta <0");
          kor->stupanj -= 1;
          kor->minuta += 60;
          ispravno=false;
        }
        while (kor->minuta >= 60) {
          //Serial.println("Minuta >=60");
          kor->stupanj += 1;
          kor->minuta -= 60;
          ispravno=false;
        }
    
        while (kor->stupanj < 0) {
          //Serial.println("Stupanj <0");
          kor->stupanj += 2 * kor->maks;
          ispravno=false;
        }
        while (kor->stupanj >= kor->maks) {  //>=
          //Serial.println("Stupanj >maks");
          kor->stupanj -= 2 * kor->maks;
          ispravno=false;
        }
      //}
    }
    else if(*kor >= koor_1D(0, 0, 0, 0.0, kor->maks)==0){
      //Serial.println("manje od nule");
      //while(kor->decimala_sekunde <= -1||kor->decimala_sekunde > 0.001||kor->sekunda <= -60||kor->sekunda > 0||kor->minuta <= -60||kor->minuta > 0||kor->stupanj < -1 * kor->maks||kor->stupanj > 0){
          while (kor->decimala_sekunde <= -1) {
            kor->decimala_sekunde += 1.0;
            kor->sekunda -= 1;
            ispravno=false;
          }
          while (kor->decimala_sekunde > 0.001) {
            kor->decimala_sekunde -= 1;
            kor->sekunda += 1;
            ispravno=false;
          }
      
          while (kor->sekunda <= -60) {
            kor->minuta -= 1;
            kor->sekunda += 60;
            ispravno=false;
          }
          while (kor->sekunda > 0) {
            kor->minuta += 1;
            kor->sekunda -= 60;
            ispravno=false;
          }
      
          while (kor->minuta <= -60) {
            kor->stupanj -= 1;
            kor->minuta += 60;
            ispravno=false;
          }
      
          while (kor->minuta > 0) {
            kor->stupanj += 1;
            kor->minuta -= 60;
            ispravno=false;
          }
      
          while (kor->stupanj < (-1 * kor->maks)) { //<=
            kor->stupanj += 2 * kor->maks;
            ispravno=false;
          }
          while (kor->stupanj > 0) {
            kor->stupanj -= 2 * kor->maks;
            ispravno=false;
          }
     //}
  }
  }
  return kor;
}





















#define radius_zemlje 6371000
#define pi 3.14159265358979323846264338327950288


class lokacija {
    friend void testiranje();
  private:
    koor_1D X;
    koor_1D Y;
  public:
    lokacija(): X(1000, 0, 0, 0.0, 180), Y(1000, 0, 0, 0.0, 90) {}
    koor_1D getX() {
      return X;
    }
    koor_1D getY() {
      return Y;
    }
    void setX(koor_1D x) {
      X = x;
    }
    void setY(koor_1D y) {
      Y = y;
    }
    void lokacija_abs() {
      X.koor_abs();
      Y.koor_abs();
    }
};

lokacija operator+(const lokacija& lhs, const lokacija& rhs) {
  lokacija ret;
  ret.setX(lhs.getX() + rhs.getX());
  ret.setY(lhs.getY() + rhs.getY());
  return ret;
}

lokacija& operator-(const lokacija& lhs, const lokacija& rhs) {
  lokacija ret;
  ret.setX(lhs.getX() - rhs.getX());
  ret.setY(lhs.getY() - rhs.getY());
  return ret;
}

bool operator==(const lokacija& lhs, const lokacija& rhs) {
  if (lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY()) return true;
  return false;
}
lokacija divide_lokacija(const lokacija& lhs, int rhs) {
  lokacija ret;
  ret.setX(divide(lhs.getX(), rhs));
  ret.setY(divide(lhs.getY(), rhs));
}



lokacija srednja_vrijednost(lokacija* polje, int n) {
  lokacija srednja;
  int i;
  for (i = 0; i < n; i++) {
    srednja = srednja + polje[i];
  }
  srednja = divide_lokacija(srednja, n);
}

lokacija srednje_apsolutno_odstupanje(lokacija *polje, int n) {
  lokacija srednja = srednja_vrijednost(polje, n);
  lokacija odstupanje;
  int i;
  for (i = 0; i < n; i++) {
    lokacija razlika = polje[i] - srednja;
    razlika.lokacija_abs();
    odstupanje = odstupanje + razlika;
  }
  odstupanje = divide_lokacija(odstupanje, n);
  return odstupanje;
}

double srednja_udaljenost_metri(lokacija srednja, lokacija odstupanje) {
  double metar_X = 0, metar_Y = 0;
  if (odstupanje.getX().get_stupanj() != 0 && odstupanje.getY().get_stupanj() != 0) {
    //barem 79 metar_ nije bas moguce
  }
  metar_Y += (double)odstupanje.getY().get_stupanj() * radius_zemlje * pi / 180;
  metar_Y += (double)odstupanje.getY().get_minuta() * radius_zemlje * pi / 180 / 60;
  metar_Y += (double)odstupanje.getY().get_sekunda() * radius_zemlje * pi / 180 / 60 / 60;
  metar_Y += (double)odstupanje.getY().get_decimala() * radius_zemlje * pi / 180 / 60 / 60; //sumnjivi izracuni zbog nepreciznosti double-a

  metar_X += (double)odstupanje.getX().get_stupanj() * radius_zemlje * pi / 180 * cos((float)(srednja.getY().get_stupanj() / 180 * pi));
  metar_X += (double)odstupanje.getX().get_minuta() * radius_zemlje * pi / 180 / 60 * cos((float)(srednja.getY().get_stupanj() / 180 * pi));
  metar_X += (double)odstupanje.getX().get_sekunda() * radius_zemlje * pi / 180 / 60 / 60 * cos((float)(srednja.getY().get_stupanj() / 180 * pi));
  metar_X += (double)odstupanje.getX().get_decimala() * radius_zemlje * pi / 180 / 60 / 60 * cos((float)(srednja.getY().get_stupanj() / 180 * pi));

  return sqrt(pow(metar_X, 2) + pow(metar_Y, 2));
}
