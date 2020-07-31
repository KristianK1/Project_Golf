


void testiranje(){
  Serial.println("                     pokrenuto testiranje");
  lokacija *lok1=new lokacija();
  lokacija *lok2=new lokacija();
  lokacija *lok=new lokacija();
  int i=0;
  while(1){
    i++;
    //if(i%1000==0){
      Serial.println(i);
    //}
    lok1->setY(koor_1D(random(0,180)-90, random(0,120)-60, random(0,120)-60, random(0,100000)/100000.0, 90));
    lok2->setY(koor_1D(random(0,180)-90, random(0,120)-60, random(0,120)-60, random(0,100000)/100000.0, 90));
    lok1->setY(prefix(lok1->getY()));
    lok2->setY(prefix(lok2->getY()));
    //lok2->getY().prefix();
  
    lok1->setX(koor_1D(-30,-21,-47,-0.3217, 180));
    lok2->setX(koor_1D(47,22,33,0.4321, 180));
    
    *lok=*lok1-*lok2;
    /*Serial.print("lok1= ");
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
    Serial.println(lok2->getY().get_decimala());*/
    
    
    if((lok2->getY()+lok->getY())==lok1->getY()){
      //Serial.println("Valja");
    }
    else{
      Serial.println("Ovdje sam");
      Serial.print("zbroj provjera= ");
      Serial.print((lok2->getY()+lok->getY()).get_stupanj());
      Serial.print("  ");
      Serial.print((lok2->getY()+lok->getY()).get_minuta());
      Serial.print("  ");
      Serial.print((lok2->getY()+lok->getY()).get_sekunda());
      Serial.print("  ");
      Serial.println((lok2->getY()+lok->getY()).get_decimala());
      
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
    
    lokacija LOL=*lok;
    lok->setX(prefix(lok->getX()));
    
    if(LOL.getX()==lok->getX()){
      
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
}
