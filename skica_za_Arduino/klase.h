class koor_1D{
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
    koor_1D(): stupanj(0), minuta(0), sekunda(0), decimala_sekunde(0.0), maks(0){
      
    }
    koor_1D(int mStupnjevi, int mMinute, int mSekunde, double mDecimala, int mmaks): stupanj(mStupnjevi), minuta(mMinute), sekunda(mSekunde), decimala_sekunde(mDecimala), maks(mmaks){
      
    }
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
};

bool operator>=(koor_1D lhs, koor_1D rhs){
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













class Koordinate{
  friend bool operator!=(Koordinate &lhs, Koordinate &rhs);
  private:
    double x;
    double y;
  public:
    Koordinate():x(0), y(0){}
    Koordinate(double mX, double mY): x(mX), y(mY){}
    
    void set(double x_new, double y_new){
      //provjera jesu li dobre brojke (dobra hemisfera itd.)
      x=x_new;
      y=y_new;
    }
    double getX(){
      return x;
    }
    double getY(){
      return y;
    }
    void operator=(Koordinate &rhs){
      x=rhs.getX();
      y=rhs.getY();
    }
};

bool operator!=(Koordinate &lhs, Koordinate &rhs){
  if(lhs.getX()!=rhs.getX()&&lhs.getY()!=rhs.getY()){  //treba provjeriti koliko grijesi, koliko odstupa na mjestu i kolike su greske prijenosa
    return LOW;
  }
  return HIGH;
}

Koordinate& operator-(Koordinate &lhs, Koordinate &rhs){
  
  
}
