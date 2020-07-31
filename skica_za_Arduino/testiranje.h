


void testiranje(){
  Serial.println("                     pokrenuto testiranje");
  lokacija *lok1=new lokacija();
  lokacija *lok2=new lokacija();
  lokacija *lok=new lokacija();
  while(1){
    lok1->setY(koor_1D(random(0,180)-90, random(0,120)-60, random(0,120)-60, random(0,100000)/100000.0, 90));
    lok2->setY(koor_1D(random(0,180)-90, random(0,120)-60, random(0,120)-60, random(0,100000)/100000.0, 90));
  
  
    lok1->setX(koor_1D(-30,-21,-47,-0.3217, 180));
    lok2->setX(koor_1D(47,22,33,0.4321, 180));
    
    *lok=*lok1-*lok2;
    /*Serial.print("X= ");
    Serial.print(lok->getX().get_stupanj());
    Serial.print("  ");
    Serial.print(lok->getX().get_minuta());
    Serial.print("  ");
    Serial.print(lok->getX().get_sekunda());
    Serial.print("  ");
    Serial.println(lok->getX().get_decimala());*/
    if(lok2->getX()+lok->getX()==lok1->getX()){
      //Serial.println("Valja");
    }
    else{
      Serial.print("lok1= ");
      Serial.print(lok1->getX().get_stupanj());
      Serial.print("  ");
      Serial.print(lok1->getX().get_minuta());
      Serial.print("  ");
      Serial.print(lok1->getX().get_sekunda());
      Serial.print("  ");
      Serial.println(lok1->getX().get_decimala());

      Serial.print("lok2= ");
      Serial.print(lok2->getX().get_stupanj());
      Serial.print("  ");
      Serial.print(lok2->getX().get_minuta());
      Serial.print("  ");
      Serial.print(lok2->getX().get_sekunda());
      Serial.print("  ");
      Serial.println(lok2->getX().get_decimala());
      
      Serial.print("lok= ");
      Serial.print(lok->getX().get_stupanj());
      Serial.print("  ");
      Serial.print(lok->getX().get_minuta());
      Serial.print("  ");
      Serial.print(lok->getX().get_sekunda());
      Serial.print("  ");
      Serial.println(lok->getX().get_decimala());
      Serial.println();
    }
  }
}
