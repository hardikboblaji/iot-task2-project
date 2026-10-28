#include <Servo.h>

Servo hservo;  
Servo vservo;  

const int threshold = 25;     
const float maxStep   = 5; // for stable traking max step is in small steps of 5 degree
const int minAngle  = 0;
const int maxAngle  = 180;

int horizontalAngle = 90;
int verticalAngle   = 90;

void setup() {
  Serial.begin(9600);
  hservo.attach(10);
  vservo.attach(9);
  hservo.write(90);
  vservo.write(90);
}

void loop() {
  int topval   = analogRead(A2);
  int downval  = analogRead(A0);
  int leftval  = analogRead(A1);
  int rightval = analogRead(A3);

  int diffVerti = topval - downval;
  int diffHori = rightval - leftval;     

 
  if (abs(diffVerti) > threshold) {
    float stepVerti = map(abs(diffVerti), threshold, 1023, 1, maxStep);
    verticalAngle += (diffVerti > 0) ? stepVerti : -stepVerti;// if diff>0 top has more light so it'll go there and similar for diff<0
    verticalAngle = constrain(verticalAngle, minAngle, maxAngle);// so that angle of servo is always valid
    vservo.write(verticalAngle);//giving servo input
     Serial.print(" Vertical angle: "); Serial.println(verticalAngle);// values of angles if changed
  }

  if (abs(diffHori) > threshold) {
    float stepHori = map(abs(diffHori), threshold, 1023, 1, maxStep);
    horizontalAngle += (diffHori > 0) ? stepHori : -stepHori;
    horizontalAngle = constrain(horizontalAngle, minAngle, maxAngle);
    hservo.write(horizontalAngle);
     Serial.print(" Horizontal angle: "); Serial.print(horizontalAngle);
  }
// constants readings of LDR's 
  Serial.print("T: ");
  Serial.print(topval);
  Serial.print(" D:");
  Serial.print(downval);
  Serial.print(" L: ");
  Serial.print(leftval);
  Serial.print(" R: ");
  Serial.print(rightval);
  Serial.print("\n");

  delay(30);
}