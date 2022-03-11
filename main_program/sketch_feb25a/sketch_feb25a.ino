int led1 = PB0;           // the PWM pin the LED is attached to
int led2 = PB1;

int pot1 = A2;
int pot2 = A3;

int readout1, readout2;
int led_value1, led_value2;
int old1=-10, old2=-10;

int diff1, diff2;
// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(pot1, INPUT);
  pinMode(pot2, INPUT);
  

  TCCR0B = (TCCR0B & 0b11111000) | 0b00000001;  //Ne diraj


  analogWrite(led1, 255);
  delay(100);
  analogWrite(led1, 70);
  delay(100);
  analogWrite(led1, 10);
  delay(100);
  
}

int mat[30] = {1,2,3,4,5,6,7,8,9,10,11,13,15,18,21,25,29,34,40,47,55,64,75,88,102,119,138,161,186,217};

// the loop routine runs over and over again forever:
int temp=0;
void loop() {
  //digitalWrite(led1, temp);
  
  //temp = temp ^1;
  readout1 = analogRead(pot1);
  readout2 = analogRead(pot2);

  if(readout1 < 62) analogWrite(led1, 0);
  else if(readout1 > 962) analogWrite(led1, 255);
  else{
    led_value1 = map(readout1, 62, 962, 0, 29);
    diff1 = led_value1 - old1;
    if(diff1>1 || diff1<-1){
      analogWrite(led1, mat[led_value1]);
      old1 = led_value1;
    }
  }

  if(readout2 < 62) analogWrite(led2, 0);
  else if(readout2 > 962) analogWrite(led2, 255);
  else{
    led_value2 = map(readout2, 62, 962, 0, 29);
    diff2 = led_value2 - old2;
    if(diff2>1 || diff2<-1){
      analogWrite(led2, mat[led_value2]);
      old2 = led_value2;
    }
  }


  delay(10*8);

  // set the brightness of pin 9:
  //analogWrite(led, 148.43 *pow (2.71, brightness/1023.0) - 143.43);

  // change the brightness for next time through the loop:
  //brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  //if (brightness <= 0 || brightness >= 255) {
  //  fadeAmount = -fadeAmount;
  //}
  // wait for 30 milliseconds to see the dimming effect
}
