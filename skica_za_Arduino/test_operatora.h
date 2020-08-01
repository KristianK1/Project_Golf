
























void test_jednakosti(){
  koor_1D fixed(-89, -58, -2,-0.21, 90);
    koor_1D var(89, 59,  58, 0.0,  90);

  Serial.println(var.get_stupanj());
  Serial.println(var.get_minuta());
  Serial.println(var.get_sekunda());
  Serial.println(var.get_decimala());
  prefix(&var);
  Serial.println(var.get_stupanj());
  Serial.println(var.get_minuta());
  Serial.println(var.get_sekunda());
  Serial.println(var.get_decimala());
  Serial.println("\n\n\n");
  while(true){
    Serial.println("Provjera za stop");
    //f(fixed>=var) while(true);

    Serial.println("\n\n\n\n Novo:");
    var.set_decimala(var.get_decimala()+0.1);
    Serial.println("Provjera prije prefixa");
    Serial.println(var.get_stupanj());
    Serial.println(var.get_minuta());
    Serial.println(var.get_sekunda());
    Serial.println(var.get_decimala());
    
    Serial.println("prefix");
    prefix(&var);  
    Serial.println(var.get_stupanj());
    Serial.println(var.get_minuta());
    Serial.println(var.get_sekunda());
    Serial.println(var.get_decimala());
    Serial.println("");
    //Serial.println("pomak 0.1");
  }
}
