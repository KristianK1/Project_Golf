void testiranje(){
  Serial.println("                     pokrenuto testiranje");
  lokacija *lok1=new lokacija();
  lokacija *lok2=new lokacija();
  lokacija *lok=new lokacija();
  lok1->setY(koor_1D(45, 33, 21, 0.2158, 90));
  lok2->setY(koor_1D(43, 53, 37, 0.8349, 90));

  lok1->setX(koor_1D(19, 7, 21, 0.1037, 180));
  lok2->setX(koor_1D(13, 8, 43, 0.3749, 180));
  
  *lok=*lok1-*lok2;
  Serial.print("X= ");
  Serial.print(lok->getX().get_stupanj());
  Serial.print("  ");
  Serial.print(lok->getX().get_minuta());
  Serial.print("  ");
  Serial.print(lok->getX().get_sekunda());
  Serial.print("  ");
  Serial.println(lok->getX().get_decimala());
  
  Serial.print("Y= ");
  Serial.print(lok->getY().get_stupanj());
  Serial.print("  ");
  Serial.print(lok->getY().get_minuta());
  Serial.print("  ");
  Serial.print(lok->getY().get_sekunda());
  Serial.print("  ");
  Serial.println(lok->getY().get_decimala());
  
  
  while(1);
}
