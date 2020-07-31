
























void test_jednakosti(){
  koor_1D fixed(2,21,22,0.21,90);
  koor_1D var(-3,0,0,0.0,90);
  int ban=0;
  while(true){
    if(var>=fixed&&ban==0){
      ban=1;
      Serial.println("Vece je");
      Serial.println(fixed.get_stupanj());
      Serial.println(fixed.get_minuta());
      Serial.println(fixed.get_sekunda());
      Serial.println(fixed.get_decimala());
    }
    var.set_decimala(var.get_decimala()+0.01);
    prefix(&var);
  }
}
