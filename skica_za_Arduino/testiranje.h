


void testiranje(){
  Serial.println("                     pokrenuto testiranje");
  lokacija *lok1=new lokacija();
  lokacija *lok2=new lokacija();
  lokacija *lok=new lokacija();
  int i=0;
  while(true){
    i++;
    Serial.println(i);
    lok1->setY(koor_1D(random(0,180)-90, random(0,120)-60, random(0,120)-60, random(0,100000)/100000.0, 90));
    lok2->setY(koor_1D(random(0,180)-90, random(0,120)-60, random(0,120)-60, random(0,100000)/100000.0, 90));
    //prefix(&lok1->Y);
    //prefix(&lok2->Y);
    //prefix(&lok2->Y);
  
    lok1->setX(koor_1D(-30,-21,-47,-0.3217, 180));
    lok2->setX(koor_1D(47,22,33,0.4321, 180));
    lokacija zbroj;
    //zbroj=*lok2+*lok;
    //prefix(&zbroj.X);
    //prefix(&zbroj.Y);
    
    //*lok=*lok1-*lok2;     //OVOOOOOOOO
    prefix(&lok->X);
    prefix(&lok->Y);
    
    Serial.print("lok1= ");
    Serial.print(lok1->getY().get_stupanj());
    Serial.print("  ");
    Serial.print(lok1->getY().get_minuta());
    Serial.print("  ");
    Serial.print(lok1->getY().get_sekunda());
    Serial.print("  ");
    Serial.println(lok1->getY().get_decimala());
    
    Serial.print("lok2= ");
    Serial.print(lok2->getY().get_stupanj());
    Serial.print("  ");
    Serial.print(lok2->getY().get_minuta());
    Serial.print("  ");
    Serial.print(lok2->getY().get_sekunda());
    Serial.print("  ");
    Serial.println(lok2->getY().get_decimala());
    
    
    /*if(zbroj==*lok){
      Serial.println("Valja");
    }
    else{

      Serial.println("Ovdje sam");
      Serial.print("zbroj provjera= ");
      Serial.print(zbroj.getY().get_stupanj());
      Serial.print("  ");
      Serial.print(zbroj.getY().get_minuta());
      Serial.print("  ");
      Serial.print(zbroj.getY().get_sekunda());
      Serial.print("  ");
      Serial.println(zbroj.getY().get_decimala());
      
      Serial.print("lok1= ");
      Serial.print(lok1->getY().get_stupanj());
      Serial.print("  ");
      Serial.print(lok1->getY().get_minuta());
      Serial.print("  ");
      Serial.print(lok1->getY().get_sekunda());
      Serial.print("  ");
      Serial.println(lok1->getY().get_decimala());

      Serial.print("lok2= ");
      Serial.print(lok2->getY().get_stupanj());
      Serial.print("  ");
      Serial.print(lok2->getY().get_minuta());
      Serial.print("  ");
      Serial.print(lok2->getY().get_sekunda());
      Serial.print("  ");
      Serial.println(lok2->getY().get_decimala());
      
      Serial.print("lok= ");
      Serial.print(lok->getY().get_stupanj());
      Serial.print("  ");
      Serial.print(lok->getY().get_minuta());
      Serial.print("  ");
      Serial.print(lok->getY().get_sekunda());
      Serial.print("  ");
      Serial.println(lok->getY().get_decimala());
      Serial.println();
    }*/
    
    
    if(true){
      
    }
    else{
      Serial.println("Predznak ne valja");
      Serial.print("lok1= ");
      Serial.print(lok1->getY().get_stupanj());
      Serial.print("  ");
      Serial.print(lok1->getY().get_minuta());
      Serial.print("  ");
      Serial.print(lok1->getY().get_sekunda());
      Serial.print("  ");
      Serial.println(lok1->getY().get_decimala());

      Serial.print("lok2= ");
      Serial.print(lok2->getY().get_stupanj());
      Serial.print("  ");
      Serial.print(lok2->getY().get_minuta());
      Serial.print("  ");
      Serial.print(lok2->getY().get_sekunda());
      Serial.print("  ");
      Serial.println(lok2->getY().get_decimala());
      
      Serial.print("lok= ");
      Serial.print(lok->getY().get_stupanj());
      Serial.print("  ");
      Serial.print(lok->getY().get_minuta());
      Serial.print("  ");
      Serial.print(lok->getY().get_sekunda());
      Serial.print("  ");
      Serial.println(lok->getY().get_decimala());
      Serial.println();
    }
  }
  delete(lok1);
  delete(lok2);
  delete(lok);
}
