int GSM_power_pin=5;
int GPS_power_pin=6;

void GSM_power(int power){
  if(power==LOW){
    digitalWrite(GSM_power_pin, HIGH);
  }
  else{
    digitalWrite(GSM_power_pin, LOW);
  }
  return;
}

void GPS_power(int power){
  if(power==LOW){
    digitalWrite(GPS_power_pin, HIGH);
  }
  else{
    digitalWrite(GPS_power_pin, LOW);
  }
  return;
}
