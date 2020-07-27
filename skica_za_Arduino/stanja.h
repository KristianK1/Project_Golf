int bistabil_out=2;
int bistabil_reset=9;

int stanje=1;
unsigned long int timer_rada;

//stanje==0 mirno_stanje
//stanje==1 pobudeno_stanje

void loop_mirnog_stanja{
  if(digitalRead(bistabil)==1){
    stanje=1;
  }
  return;
}

void loop_pobudenog_stanja{
  if(digitalRead(2)==1
}
