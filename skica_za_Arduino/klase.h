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
  if(lhs.getX()!=rhs.getX()&&lhs.getY()!=rhs.getY()){  //treba provjeriti koliko grijesi, koliko odstupa na mjestu i kolike su grijske prijenosa
    return LOW;
  }
  return HIGH;
}
