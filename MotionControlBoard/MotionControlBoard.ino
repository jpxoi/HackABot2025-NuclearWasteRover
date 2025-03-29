#include <AFMotor.h>
#include <Servo.h>

#define Speed 250

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

Servo servo1;
Servo servo2;

const int trigPin = 12;
const int echoPin = 11;

const int level1 = 10;  // Farther distance
const int level2 = 5;  // Medium distance
const int level3 = 3;  // Closer distance
const int minDistance = 2;  // Very close, continuous beep

long duration;
int distance;

void setup()
{
  Serial.begin(9600);

  // Set the speed of all motors
  motor1.setSpeed(Speed);
  motor2.setSpeed(Speed);
  motor3.setSpeed(Speed);
  motor4.setSpeed(Speed);

  // Attach servos to pins 9 and 10
  servo1.attach(10);
  servo2.attach(9);

  // Set initial positions of servos
  servo1.write(180);
  servo2.write(180);

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
    if (value == '1')
    {
      servo1.write(70);
      servo2.write(180 - 70);
    }
    else if (value == '2')
    {
      servo1.write(80);
      servo2.write(180 - 80);
    }
    else if (value == '3')
    {
      servo1.write(90);
      servo2.write(180 - 90);
    }
    else if (value == '4')
    {
      servo1.write(100);
      servo2.write(180 - 100);
    }
    else if (value == '5')
    {
      servo1.write(120);
      servo2.write(180 - 120);
    }
    else if (value == '6')
    {
      servo1.write(140);
      servo2.write(180 - 140);
    }
    else if (value == '7')
    {
      servo1.write(150);
      servo2.write(180 - 150);
    }
    else if (value == '8')
    {
      servo1.write(160);
      servo2.write(180 - 160);
    }
    else if (value == '9')
    {
      servo1.write(170);
      servo2.write(180 - 170);
    }
    else if (value == 'F')
    {
      forward();
    }
    else if (value == 'B')
    {
      backward();
    }
    else if (value == 'L')
    {
      left();
    }
    else if (value == 'R')
    {
      right();
    }
    else
    {
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
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
}

void backward()
{
  // Move motors to drive backward
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}

void left()
{
  // Move motors to turn left
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void right()
{
  // Move motors to turn right
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
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