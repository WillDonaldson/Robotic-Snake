#include <Servo.h>
Servo myServos[10]; //create 10 servos

float pi=3.14159;
int TotalNumberofServos=10; //change as required 
int ServosPerSide=TotalNumberofServos/2;
float shift = 2*pi/ServosPerSide; // Phase lag between segments
int amplitude = 50;
int offset = 0;
float rads;
float Speed=2;
float Wavelengths=1.5;
int Multiplier;

void setup() {
  Serial.begin(9600);
  myServos[0].attach(A0);
  myServos[1].attach(A1);
  myServos[2].attach(A2);
  myServos[3].attach(A3);
  myServos[4].attach(A4);
  myServos[5].attach(A5);
  myServos[6].attach(4);
  myServos[7].attach(3);
  myServos[8].attach(8);
  myServos[9].attach(7);

}


void sidewind(String Direction){
   //works best with Wavelengths=1.5
  if(Direction=="Left"){ Multiplier=1; }
  else if(Direction=="Right"){ Multiplier=-1; }
  for(int i=0; i<360; i++){
   rads=i*pi/180.0;     //convert from degrees to radians
   for(int j=0; j<5; j++){  
      myServos[2*j].write(90+offset+amplitude*sin(Speed*rads+j*Wavelengths*shift-(Multiplier-1)*pi/4));   //moves servos in vertical plane
      myServos[2*j+1].write(90+offset+amplitude*sin(Speed*rads+j*Wavelengths*shift+(Multiplier+1)*pi/4)); //moves servos in horizontal plane
   }
   delay(10);
  }
}

void sidewindTurn(String Direction){
  if(Direction=="Left"){ Multiplier=1; }
  else if(Direction=="Right"){ Multiplier=-1; }
  for(int i=0; i<360; i++){
   rads=i*pi/180.0;     //convert from degrees to radians
   for(int j=0; j<3; j++){  
     myServos[2*j].write(90+offset+amplitude*sin(Speed*rads+j*Wavelengths*shift+(Multiplier+1)*pi/4));
     myServos[2*j+1].write(90+offset+amplitude*sin(Speed*rads+j*Wavelengths*shift-(Multiplier-1)*pi/4));
   }
   for(int j=3; j<5; j++){  
     myServos[2*j].write(90+offset+amplitude*sin(Speed*rads+j*Wavelengths*shift-(Multiplier-1)*pi/4));
     myServos[2*j+1].write(90+offset+amplitude*sin(Speed*rads+j*Wavelengths*shift+(Multiplier+1)*pi/4));
   }
   delay(10);
  }
}


void strike(){
  myServos[0].write(90);
  delay(10);
  myServos[1].write(0);
  delay(10);
  myServos[2].write(90);
  delay(10);
  myServos[3].write(180);
  delay(10);
  myServos[4].write(90);
  delay(10);
  myServos[5].write(0);
  delay(10);
  myServos[6].write(0);
  delay(10);
  myServos[7].write(130);
  delay(10);
  myServos[8].write(90);
  delay(10);
  myServos[9].write(180);
  delay(10);

  //wait 5 seconds before striking
  delay(5000);    //in future versions strikes will be activated by proximity sensors

  //strike by lunging forward
  myServos[7].write(80);
  delay(10);
  myServos[9].write(120);
  delay(200);

  //return to resting position
  myServos[7].write(130);
  delay(10);
  myServos[9].write(180);
  delay(10);
}

void loop() {
  //comment and uncomment for the movement you want
  //as mentioned in the instructable, this code is skeletal in that there is no remote control function, stay tuned for version 2

  sidewind("Left");  
  //sidewind("Right");
  //sidewindTurn("Left");
  //sidewindTurn("Right");
  //strike();
  
}
