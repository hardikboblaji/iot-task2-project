#include <Servo.h>

Servo myservo; 

int short_cnt = 0;
int long_cnt = 0;

void setup() {
  pinMode(9, OUTPUT); // trig pin  on pin 9
  pinMode(8, INPUT);  // echo pin on pin 8
  myservo.attach(6);  // servo on pin 6
  myservo.write(90);  
  Serial.begin(9600);
}

void loop() {
  digitalWrite(9, LOW);
  delayMicroseconds(2);
  digitalWrite(9, HIGH);
  delayMicroseconds(10);
  digitalWrite(9, LOW);

  // Calculate distance in cm
  long dist = pulseIn(8, HIGH) * 0.034 / 2;

  // check if  object is within range
  if (dist > 2 && dist < 250) {
    Serial.print("Distance: ");
    Serial.println(dist);

    //  based on lenght threshold =75 cm
    if (dist < 75) {
      myservo.write(0);  // move servo left for short object
      short_cnt++;
      Serial.println("short");
    } else {
      myservo.write(180); // move servo right for long object
      long_cnt++;
      Serial.println("long");
    }

    // no. of item in each sort
    Serial.print("Bin A (Short): "); Serial.println(short_cnt);
    Serial.print("Bin B (Long): "); Serial.println(long_cnt);

    delay(2000);       //  sorting take time
    myservo.write(90); // Reset servo to center
    
  }
  
  delay(1000);
}