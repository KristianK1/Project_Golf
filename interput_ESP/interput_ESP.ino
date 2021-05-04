void IRAM_ATTR ISR() {
  Serial.println("interputttt");
  delay(500);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(5, INPUT);
  attachInterrupt(4, ISR, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:

}
