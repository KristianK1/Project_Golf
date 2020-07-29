class koor_1D{
  friend koor_1D divide(koor_1D, int);
  friend bool operator>=(koor_1D, koor_1D);
  friend koor_1D operator-(koor_1D, koor_1D);
  friend koor_1D operator+(koor_1D, koor_1D);
  
  private:
    int stupanj;
    int minuta;
    int sekunda;
    double decimala_sekunde;
    int maks;   //za X je 180, za Y je 90
  public:
    koor_1D(): stupanj(0), minuta(0), sekunda(0), decimala_sekunde(0.0), maks(0){}
    koor_1D(int mStupnjevi, int mMinute, int mSekunde, double mDecimala, int mmaks): stupanj(mStupnjevi), minuta(mMinute), sekunda(mSekunde), decimala_sekunde(mDecimala), maks(mmaks){}
    int get_stupanj(){ return stupanj;}
    int get_minuta(){ return minuta;}
    int get_sekunda(){ return sekunda;}
    double get_decimala(){ return decimala_sekunde;};

    void set_stupanj(int new_stupanj){ stupanj=new_stupanj;}
    void set_minuta(int new_minuta){ minuta=new_minuta;}
    void set_sekunda(int new_sekunda){ sekunda=new_sekunda;}
    void set_decimala(double new_decimala){ decimala_sekunde=new_decimala;}

    void prefix(){
      if(stupanj>0){
        if(decimala_sekunde<=-1){
          decimala_sekunde+=1;
          sekunda-=1;
        }
        if(decimala_sekunde<0){
          decimala_sekunde+=1;
          sekunda-=1;
        }
        if(decimala_sekunde>=1){
          decimala_sekunde-=1;
          sekunda+=1;
        }
        
        if(sekunda<=-60){
          minuta+=1;
          sekunda+=60;
        }
        if(sekunda<0){
          minuta+=1;
          sekunda+=60;
        }
        if(sekunda>60){
          minuta-=1;
          sekunda-=60;
        }

        if(minuta<=-60){
          stupanj+=1;
          minuta+=60;
        }
        if(minuta<0){
          stupanj+=1;
          minuta+=60;
        }
        if(minuta>60){
          stupanj-=1;
          minuta-=60;
        }

        if(stupanj<-1*maks){
          stupanj+=2*maks;
        }
        if(stupanj>maks){
          stupanj-=2*maks;
        }
      }
    }

  koor_abs(){
    prefix();
    if(stupanj<0){
      stupanj*=-1;
      minuta*=-1;
      sekunda*=-1;
      decimala_sekunde*=-1;
    }
  }
  
};

koor_1D divide(koor_1D lhs, int rhs){
  koor_1D ret;
  ret.maks=lhs.maks;
  if(rhs>0){
    ret.stupanj=lhs.stupanj/rhs;
    lhs.stupanj-=ret.stupanj*rhs;
    
    lhs.minuta+=lhs.stupanj*60;
    ret.minuta=(int)(lhs.minuta/rhs);
    lhs.minuta-=ret.minuta*rhs;

    lhs.sekunda+=lhs.minuta*60;
    ret.sekunda=(int)(lhs.sekunda/rhs);
    lhs.sekunda-=ret.sekunda*rhs;

    lhs.decimala_sekunde+=lhs.sekunda*1.0;
    ret.decimala_sekunde=lhs.decimala_sekunde/rhs;
  }
}


bool operator>=(koor_1D lhs, koor_1D rhs){
  lhs.prefix();
  rhs.prefix();
  
  if(lhs.stupanj>rhs.stupanj) return true;
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
  }
}

koor_1D operator-(koor_1D lhs, koor_1D rhs){
  
  koor_1D ret;
  if(lhs.maks==rhs.maks){
    rhs.maks=lhs.maks; 
  }
  else{
    return ret;
  }
  if(lhs>=rhs){
    ret.decimala_sekunde=lhs.decimala_sekunde-rhs.decimala_sekunde;
    if(ret.decimala_sekunde<0){
      ret.decimala_sekunde+=1;
      rhs.sekunda+=1;
    }

    ret.sekunda=lhs.sekunda-rhs.sekunda;
    if(ret.sekunda<0){
      ret.sekunda+=60;
      rhs.minuta+=1;
    }
    
    ret.minuta=lhs.minuta-rhs.minuta;
    if(ret.minuta<0){
      ret.minuta+=60;
      rhs.stupanj+=1;
    }
    ret.stupanj=lhs.stupanj-rhs.stupanj;
  }
  else{
    ret.decimala_sekunde=lhs.decimala_sekunde-rhs.decimala_sekunde;
    if(ret.decimala_sekunde>0){
      ret.decimala_sekunde-=1;
      lhs.sekunda+=1;
    }

    ret.sekunda=lhs.sekunda-rhs.sekunda;
    if(ret.sekunda>0){
      ret.sekunda-=60;
      lhs.minuta+=1;
    }
    
    ret.minuta=lhs.minuta-rhs.minuta;
    if(ret.minuta>0){
      ret.minuta-=60;
      lhs.stupanj+=1;
    }
    ret.stupanj=lhs.stupanj-rhs.stupanj;

    if(ret.stupanj>ret.maks){
      ret.stupanj-=2*ret.maks;
    }
    if(ret.stupanj<-1*ret.maks){
      ret.stupanj+=2*ret.maks;
    }
  }
  return ret;
}

koor_1D operator+(koor_1D lhs, koor_1D rhs){
  koor_1D ret;
  ret.decimala_sekunde=lhs.decimala_sekunde+rhs.decimala_sekunde;
  ret.sekunda=lhs.sekunda+rhs.sekunda;
  ret.minuta=lhs.minuta+rhs.minuta;
  ret.stupanj=lhs.stupanj+rhs.stupanj;

  return ret;
}
















#define radius_zemlje 6371000
#define pi 3.14159265358979323846264338327950288


class lokacija{
  private:
    koor_1D X;
    koor_1D Y;
  public:
    lokacija():X(1000,0,0,0.0,180), Y(1000,0,0,0.0,90){}
    koor_1D getX(){ return X;}
    koor_1D getY(){ return Y;}
    void setX(koor_1D x){ X=x;}
    void setY(koor_1D y){ Y=y;}
    void lokacija_abs(){
      X.koor_abs();
      Y.koor_abs();
    }
};

lokacija operator+(lokacija lhs, lokacija rhs){
  lokacija ret;
  ret.setX(lhs.getX()+rhs.getX());
  ret.setY(lhs.getY()+rhs.getY());
  return ret;
}

lokacija operator-(lokacija lhs, lokacija rhs){
  lokacija ret;
  ret.setX(lhs.getX()-rhs.getX());
  ret.setY(lhs.getY()-rhs.getY());
  return ret;
}

lokacija divide_lokacija(lokacija lhs, int rhs){
  lokacija ret;
  ret.setX(divide(lhs.getX(), rhs));
  ret.setY(divide(lhs.getY(), rhs));
}


lokacija srednja_vrijednost(lokacija* polje, int n){
  lokacija srednja;
  int i;
  for(i=0;i<n;i++){
    srednja=srednja+polje[i];
  }
  srednja=divide_lokacija(srednja, n);
}

lokacija srednje_apsolutno_odstupanje(lokacija *polje, int n){
  lokacija srednja=srednja_vrijednost(polje, n);
  lokacija odstupanje;
  int i;
  for(i=0;i<n;i++){
    lokacija razlika=polje[i]-srednja;
    razlika.lokacija_abs();
    odstupanje=odstupanje+razlika;
  }
  odstupanje=divide_lokacija(odstupanje,n);
  return odstupanje;
}

double srednja_udaljenost_metri(lokacija srednja, lokacija odstupanje){
  double metar_X=0, metar_Y=0;
  if(odstupanje.getX().get_stupanj()!=0&&odstupanje.getY().get_stupanj()!=0){
    //barem 79 metar_ nije bas moguce
  }
  metar_Y+=(double)odstupanje.getY().get_stupanj()*radius_zemlje*pi/180;
  metar_Y+=(double)odstupanje.getY().get_minuta()*radius_zemlje*pi/180/60;
  metar_Y+=(double)odstupanje.getY().get_sekunda()*radius_zemlje*pi/180/60/60;
  metar_Y+=(double)odstupanje.getY().get_decimala()*radius_zemlje*pi/180/60/60;    //sumnjivi izracuni zbog nepreciznosti double-a

  metar_X+=(double)odstupanje.getX().get_stupanj()*radius_zemlje*pi/180*cos((float)(srednja.getY().get_stupanj()/180*pi));
  metar_X+=(double)odstupanje.getX().get_minuta()*radius_zemlje*pi/180/60*cos((float)(srednja.getY().get_stupanj()/180*pi));
  metar_X+=(double)odstupanje.getX().get_sekunda()*radius_zemlje*pi/180/60/60*cos((float)(srednja.getY().get_stupanj()/180*pi));
  metar_X+=(double)odstupanje.getX().get_decimala()*radius_zemlje*pi/180/60/60*cos((float)(srednja.getY().get_stupanj()/180*pi));
    
  return sqrt(pow(metar_X,2)+pow(metar_Y,2));
}
