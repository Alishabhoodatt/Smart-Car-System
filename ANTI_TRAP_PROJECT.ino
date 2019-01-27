#include<SoftwareSerial.h>
SoftwareSerial sim(10,11);
int timeout;
String _buffer;
String number = "9130101272";
const int sensor=A1; // Assigning analog pin A1 to variable 'sensor'
float tempc;  //variable to store temperature in degree Celsius
float vout;  //temporary variable to hold sensor reading

void setup() {
  // put your setup code here, to run once:
delay (7000);
_buffer.reserve(50);
int i;
for(i=6;i<10;i++)
pinMode(i,INPUT);
pinMode(A1,INPUT);
pinMode(12,OUTPUT);
Serial.begin(9600);
sim.begin(9600);
Serial.println("system started...");
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite (12,LOW);
delayMicroseconds(2);
digitalWrite(12,HIGH);
delayMicroseconds(10);
digitalWrite (12,LOW);

int d1;
int d2;
int t1;
int t2;

t1=pulseIn(7,HIGH);
t2=pulseIn(8,HIGH);
d1=t1*0.0343/2;
d2=t2*0.0343/2;

int PIRout = digitalRead(9);

int vibration = digitalRead(6);

vout=analogRead(sensor);
vout=(vout*500)/1023;
tempc=vout; // Storing value in Degree Celsius

Serial.print("in DegreeC=");
Serial.print("\t");
Serial.print(tempc);
Serial.println();
delay(1000); //Delay of 1 second for ease of viewing 

if (PIRout==1 && tempc>=40 && d1==d2<=12 && vibration==0 );
  {Serial.println("warning!,there is someone trapped inside the car");
  SendMessage();
  delay(100000);
  }
}
void SendMessage(){
  ("sending message");
  sim.println("AT+CMGF=1"); // SETS THE GSM IN TEXT MODE
  delay(1000);
  Serial.println("set sms no. ");
  sim.println("AT+CMGS=\""+number+"\"\r");
  delay(1000);
  String SMS ="WARNING!SOMBODY IS TRAPPED INSIDE YOUR CAR NO.4444,SAVE THEM QUICKLY";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);
  delay(1000);
  _buffer = _readSerial();
}
String _readSerial(){
  timeout=0;
  while(!sim.available() && timeout < 12000)
  {delay(13);
  timeout++;
  }
  if (sim.available()){
    return sim.readString();
  }
}





