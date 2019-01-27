volatile byte pulses;
unsigned int rpm;
unsigned long timeold;
unsigned int pulsesperturn=4;
int T3;
void setup() {
  // put your setup code here, to run once:
 pinMode(7,OUTPUT); //relay:
 pinMode(8,INPUT); //vibration sensor:
 pinMode(9,INPUT); //Ultrasonic 1:
 pinMode(10,INPUT); //ultrasonic 2:
 pinMode(11,INPUT); //rpm:
 pinMode(12,OUTPUT); //trigger to US 1:
 pinMode(13,OUTPUT); //trigger to US 2:
 attachInterrupt(11,counter,FALLING);
 pulses=0;
 rpm=0;
 timeold=0;
}

void loop() {
  // put your main code here, to run repeatedly:
  //vibration sensor:
  int vib=digitalRead(8);

  //US 1:
  digitalWrite(12,LOW);
  delayMicroseconds(2);
  digitalWrite(12,HIGH);
  delayMicroseconds(10);
  digitalWrite(12,LOW);
  int T1=pulseIn(9,HIGH);
  int D1=T1*(3.43/2);

  //US 2:
  digitalWrite(13,LOW);
  delayMicroseconds(2);
  digitalWrite(13,HIGH);
  delayMicroseconds(10);
  digitalWrite(13,LOW);
  int T2=pulseIn(10,HIGH);
  int D2=T2*(3.43/2);

  //rpm:
  if(millis() - timeold >= 1000){
    detachInterrupt(11);
    rpm=(60*1000/pulsesperturn)/(millis()-timeold)*pulses;
    timeold=millis;
    pulses=0;
    attachInterrupt(11,counter,FALLING);
    if(rpm=0){
      T3=pulseIn(rpm,LOW);
    }
  }

  //conditions:
  if(vib==HIGH&&(D1<=1||D2<=1)&&T3>20000){
    digitalWrite(7,HIGH);
  }
  else{
    digitalWrite(7,LOW);
  }
}

void counter(){
  pulses++;
}

