lokacija* generiranje(int n){
  Serial.println("fdsf");
  
  //izmedu 45 i 46 i 20 i 21
  lokacija *polje=new lokacija[n];
  Serial.println("fdsf");
    
  for(int i=0;i<n;i++){
    //polje[i]=lokacija(koor_1D(45,random(0,10000)/10000.0*60,random(0,10000)/10000.0*60,random(0,10000)/10000.0,32000),koor_1D(20,random(0,10000)/10000.0*60,random(0,10000)/10000.0*60,random(0,10000)/10000.0,32000));
    polje[i].setX(koor_1D(5,random(0,10000)/10000.0*60,random(0,10000)/10000.0*60,random(0,10000)/10000.0,32000));
    polje[i].setY(koor_1D(20,random(0,10000)/10000.0*60,random(0,10000)/10000.0*60,random(0,10000)/10000.0,32000));
    
    Serial.println(polje[i].getX().get_stupanj());
    Serial.println(polje[i].getX().get_minuta());
    Serial.println(polje[i].getX().get_sekunda());
    Serial.println(polje[i].getX().get_decimala());
    Serial.println();
    Serial.println(polje[i].getY().get_stupanj());
    Serial.println(polje[i].getY().get_minuta());
    Serial.println(polje[i].getY().get_sekunda());
    Serial.println(polje[i].getY().get_decimala());
    Serial.println();
    Serial.println();
    

  }
  return polje;
}
