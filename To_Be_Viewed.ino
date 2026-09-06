#include <Servo.h>

Servo servo1;
Servo servo2;



// Infrared receiver signal line
const int IR1_PIN = 22;
const int IR2_PIN = 23;

// Servo signal line
const int SERVO1_PIN = 9;
const int SERVO2_PIN = 10;




// Servo 1 preset angles
const int SERVO1_START = 20;
const int SERVO1_STEP1 = 55;
const int SERVO1_STEP2 = 75;
const int SERVO1_STEP3 = 95;
const int SERVO1_STEP4 = 115;
const int SERVO1_STEP5 = 135;
const int SERVO1_STEP6 = 155;

// Servo 2 preset angles
const int SERVO2_START = 20;
const int SERVO2_STEP1 = 55;
const int SERVO2_STEP2 = 75;
const int SERVO2_STEP3 = 95;
const int SERVO2_STEP4 = 115;
const int SERVO2_STEP5 = 135;
const int SERVO2_STEP6 = 155;




int count1 = 0;
int count2 = 0;


// Random
int moveLimit1;
int moveLimit2;


// Record the last state of infrared
bool lastDetected1 = false;
bool lastDetected2 = false;


// Prevent duplicate counting of a single
unsigned long lastTriggerTime1 = 0;
unsigned long lastTriggerTime2 = 0;

const unsigned long debounceTime = 300;



void setup() {

  Serial.begin(9600);


  // Infrared 
  pinMode(IR1_PIN, INPUT_PULLUP);
  pinMode(IR2_PIN, INPUT_PULLUP);


  // Servo
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);


  // original position
  servo1.write(SERVO1_START);
  servo2.write(SERVO2_START);


  // Random
  randomSeed(analogRead(A0));


  // Randomly decide how many times to move first in this round
  moveLimit1 = random(3, 7);
  moveLimit2 = random(3, 7);


  Serial.println("======================");
  Serial.println("System Ready");

  Serial.print("Servo 1 will move ");
  Serial.print(moveLimit1);
  Serial.println(" times");

  Serial.print("Servo 2 will move ");
  Serial.print(moveLimit2);
  Serial.println(" times");

  Serial.println("======================");


  delay(1000);
}




void loop() {

  int sensor1 = digitalRead(IR1_PIN);
  int sensor2 = digitalRead(IR2_PIN);



  bool detected1 = (sensor1 == HIGH);
  bool detected2 = (sensor2 == HIGH);




  // Infrared 1 → Servo 1

  if (detected1 &&
      !lastDetected1 &&
      millis() - lastTriggerTime1 > debounceTime) {

    lastTriggerTime1 = millis();

    count1++;

    Serial.print("Sensor 1 Count = ");
    Serial.println(count1);


    if (count1 <= moveLimit1) {

      moveServo1(count1);

    }

    //  Next trigger → return to original position
    else {

      servo1.write(SERVO1_START);

      Serial.println("SERVO 1 RESET");


      count1 = 0;


      // Next round reshuffle randomly
      moveLimit1 = random(3, 7);


      Serial.print("Next Servo 1 will move ");
      Serial.print(moveLimit1);
      Serial.println(" times");
    }
  }




  // Infrared 2 → Servo 2

  if (detected2 &&
      !lastDetected2 &&
      millis() - lastTriggerTime2 > debounceTime) {

    lastTriggerTime2 = millis();

    count2++;

    Serial.print("Sensor 2 Count = ");
    Serial.println(count2);


    if (count2 <= moveLimit2) {

      moveServo2(count2);

    }

    // Next trigger → return to original position
    else {

      servo2.write(SERVO2_START);

      Serial.println("SERVO 2 RESET");


      count2 = 0;


      // Next round reshuffle randomly
      moveLimit2 = random(3, 7);


      Serial.print("Next Servo 2 will move ");
      Serial.print(moveLimit2);
      Serial.println(" times");
    }
  }



  lastDetected1 = detected1;
  lastDetected2 = detected2;


  delay(10);
}




// Servo 1 moves
void moveServo1(int stepNumber) {

  if (stepNumber == 1) {
    servo1.write(SERVO1_STEP1);
  }

  else if (stepNumber == 2) {
    servo1.write(SERVO1_STEP2);
  }

  else if (stepNumber == 3) {
    servo1.write(SERVO1_STEP3);
  }

  else if (stepNumber == 4) {
    servo1.write(SERVO1_STEP4);
  }

  else if (stepNumber == 5) {
    servo1.write(SERVO1_STEP5);
  }

  else if (stepNumber == 6) {
    servo1.write(SERVO1_STEP6);
  }
}



// Servo 2 moves
void moveServo2(int stepNumber) {

  if (stepNumber == 1) {
    servo2.write(SERVO2_STEP1);
  }

  else if (stepNumber == 2) {
    servo2.write(SERVO2_STEP2);
  }

  else if (stepNumber == 3) {
    servo2.write(SERVO2_STEP3);
  }

  else if (stepNumber == 4) {
    servo2.write(SERVO2_STEP4);
  }

  else if (stepNumber == 5) {
    servo2.write(SERVO2_STEP5);
  }

  else if (stepNumber == 6) {
    servo2.write(SERVO2_STEP6);
  }
}