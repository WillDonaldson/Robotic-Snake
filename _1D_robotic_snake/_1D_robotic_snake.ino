#include <Servo.h>

Servo myServos[10]; //create 10 servos

float pi=3.14159;
int TotalNumberofServos=10; //change as required
float Shift = 2*pi/TotalNumberofServos; // Phase lag between segments
float Wavelengths, rads;
int InteriorAngle, SetpointAngle, MaxAngleDisplacement;

void setup() {
  Serial.begin(9600);
  //The following code can be cleaned up in a single for-loop if you solder the wires in a more continuous pattern than I did
  //Order of servos is such that myServos[0]=tail segment, and myServos[9]=head segment
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

  //Initialise snake in a straight line
  for(int i=0; i<10; i++){  
    myServos[i].write(90);
    delay(15); 
  }
  delay(1000);
}

void straightline(){
  for(int i=0; i<10; i++){  
    myServos[i].write(90);
    delay(100); 
  }
}

void Cshape(){
  for(int i=0; i<10; i++){  
    myServos[i].write(60);
    delay(100); 
  }
}

void ubend(){ 
  for(int i=0; i<10; i++){  
    if(i==4 or i==5){
      myServos[i].write(0);
      delay(100);
    }
    else{
      myServos[i].write(90);
      delay(100); 
    }
  } 
}

void ring(){
  InteriorAngle=180-360/(TotalNumberofServos+1); //general formula for a polygon with 3 or more vertices, +1 vertice between tail and head segment
  SetpointAngle=abs(InteriorAngle-90); //Offset the angle from the initial position of 90 degrees. 
  for(int i=0; i<10; i++){  
    myServos[i].write(SetpointAngle);
    delay(100); 
  }
}


void slither(int offset, int Amplitude, int Speed, float Wavelengths){
  MaxAngleDisplacement=abs(offset)+abs(Amplitude); //amount servo can rotate from the SetpointAngle without going out of the [0,180] degree range
  while(MaxAngleDisplacement>90){ //prevents a setpoint angle outside the rage of[0,180]
    Amplitude=abs(Amplitude)-1;
    MaxAngleDisplacement=abs(offset)+Amplitude;
  }
  for(int i=0; i<360; i++){
   rads=i*pi/180.0;     //convert from degrees to radians
   for(int j=0; j<10; j++){  
      myServos[j].write(90+offset+Amplitude*sin(Speed*rads+j*Wavelengths*Shift));
     }
   delay(10);
  }
}

void staticWave(int offset, int Amplitude, float Wavelengths){ 
  MaxAngleDisplacement=abs(offset)+abs(Amplitude); //amount servo can rotate from the SetpointAngle without going out of the [0,180] degree range
  while(MaxAngleDisplacement>90){ //prevents a setpoint angle outside the rage of[0,180]
    Amplitude=abs(Amplitude)-1;
    MaxAngleDisplacement=abs(offset)+Amplitude;
  }

  for(int j=0; j<10; j++){  
    myServos[j].write(90+offset+Amplitude*sin(j*Wavelengths*Shift));
    delay(15);
  }
}

void InchWorm(){
  for(int pos = 0; pos < 45; pos +=  1){
    myServos[0].write(90-pos);
    myServos[1].write(90+2*pos);
    myServos[2].write(90-pos);
    delay(10);
  }    

  for(int i=0; i<7; i+= 1){
    for(int pos = 0; pos < 45; pos +=  1){  
      myServos[i].write(45+pos);
      myServos[i+1].write(180-3*pos);
      myServos[i+2].write(45+3*pos);
      myServos[i+3].write(90-pos);
      delay(10);
    }    
  }
 
  for(int pos = 0; pos < 45; pos +=  1){  
    myServos[7].write(45+pos);
    myServos[8].write(180-2*pos);
    myServos[9].write(45+pos);
    delay(10);
  }  
}

void loop() {
  //comment and uncomment for the movement you want
  //as mentioned in the instructable, this code is skeletal in that there is no remote control function, stay tuned for version 2
  
  slither(0, 35, 2, 1.5);           // forwards slither
  //slither(10, 35, 2, 1.5);        // turning slither
  //slither(-10, 35, 1, 1.5);       // opposite direction turn
  //staticWave(0, 35, 0.5);         // 0.5 wavelengths
  //staticWave(0, 35, 1.0);         // 1.0 wavelengths
  //staticWave(0, 35, 1.5);         // 1.5 wavelengths
  //staticWave(0, 35, 2.0);         // 2.0 wavelengths
  //InchWorm();
  //ubend();
  //ring();
  //straightline();
  
  
}
