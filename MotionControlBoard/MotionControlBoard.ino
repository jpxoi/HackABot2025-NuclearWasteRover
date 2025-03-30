#include <AFMotor.h>
#include <Servo.h>

#define Speed 250

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

Servo servo1; // Camera servo (up/down)
Servo servo2; // Arm servo (open/close)

const int trigPin = 12;
const int echoPin = 11;

const int level1 = 20;  // Farther distance
const int level2 = 10;  // Medium distance
const int level3 = 5;  // Closer distance
const int minDistance = 3;  // Very close, continuous beep

long duration;
int distance;

void setup()
{
  motor1.setSpeed(Speed);
  motor2.setSpeed(Speed);
  motor3.setSpeed(Speed);
  motor4.setSpeed(Speed);

  // Attach servos to pins 9 and 10
  servo1.attach(10);
  servo2.attach(9);

  // Set initial positions of servos
  servo1.write(180);
  servo2.write(120);

  // Set Ultrasonic Sensor
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  Serial.begin(9600); // Starts the serial communication
}

void loop()
{
  if (Serial.available() > 0)
  {
    char value = Serial.read();
    Serial.println(value);

    // Control servos based on received value
    if (value == 'U') { // Camera Up
      servo1.write(150);
    }
    else if (value == 'D') { // Camera Down
      servo1.write(90);
    }
    else if (value == 'C') { // Camera Center
      servo1.write(120);
    }
    else if (value == 'O') { // Open hand
      servo2.write(180);
    }
    else if (value == 'H') { // Close hand (half)
      servo2.write(120);
    }
    else if (value == 'G') { // Close hand fully (grab)
      servo2.write(60);
    }
    else if (value == 'F') { // Forward
      forward();
    }
    else if (value == 'B') { // Backward
      backward();
    }
    else if (value == 'L') { // Left
      left();
    }
    else if (value == 'R') { // Right
      right();
    }
    else if (value == 'S') { // Stop
      Stop();
    }
    else { // Default - stop movement
      Stop();
    }
  }

  // Measure distance
  distance = getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Send appropriate signals based on distance
  if (distance <= level1 && distance > level2) {
    Serial.println("BEEP_SLOW");  // Slow beeps
  } 
  else if (distance <= level2 && distance > level3) {
    Serial.println("BEEP_MEDIUM");  // Medium beeps
  } 
  else if (distance <= level3 && distance > minDistance) {
    Serial.println("BEEP_FAST");  // Fast beeps
  } 
  else if (distance <= minDistance) {
    Serial.println("CONTINUOUS_BEEP");  // Continuous beep
  }

  delay(100);  // Small delay for stability
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;  // Calculate distance in cm
  return distance;
}

void forward()
{
  // Move motors to drive forward
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void backward()
{
  // Move motors to drive backward
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void left()
{
  // Move motors to turn left
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}

void right()
{
  // Move motors to turn right
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
}

void Stop()
{
  // Stop all motors
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}