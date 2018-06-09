#include <Servo.h>

Servo myServos[10]; //create 10 servos
int pos, i;

void setup() {
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
  delay(1000); //wait 1 second

  //Sweep each servo individually between [0,180] degrees before returning to a straight line
  for(int i=0; i<10; i++){ 
    for (pos = 0; pos <= 180; pos += 1) { 
      myServos[i].write(pos);              
      delay(15);                       
    }
    for (pos = 180; pos >= 0; pos -= 1) { 
      myServos[i].write(pos);             
      delay(15);                      
    }
    myServos[i].write(90);
    delay(200);
  }
  
}

void loop(){  
}

