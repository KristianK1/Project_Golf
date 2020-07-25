unsigned long int timer=0;
double naboj=0;
int T=1000;
double R=100;
int sekunde=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(timer-micros()>T){
    timer=micros();
    struja=(analogRead(A0)*5/1.024)/R; //mA
    naboj+=1.0*T/1000000*struja;
  }
  if(millis()-sekunde*1000>1000){
    sekunde=(int)millis()/1000;
    Serial.print(naboj);
    Serial.println(" mAs (mili amper sekunda)");
  }
}
