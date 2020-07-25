#include <avr/sleep.h>

int miliseconds=2*60*1000;
void setup() {
  // put your setup code here, to run once:
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);  
  sleep_enable();
  sleep_cpu ();  
}

void loop() {
  // put your main code here, to run repeatedly:

} 
