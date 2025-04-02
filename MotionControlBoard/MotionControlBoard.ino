#include <AFMotor.h>
#include <Servo.h>
#include <SoftwareSerial.h>// import the serial library

#define Speed 250

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

Servo servo1; // Arm servo (up/down)
Servo servo2; // Gripper servo (open/close)

void setup()
{
  Serial.begin(9600);

  motor1.setSpeed(Speed);
  motor2.setSpeed(Speed);
  motor3.setSpeed(Speed);
  motor4.setSpeed(Speed);

  // Attach servos to pins 9 and 10
  servo1.attach(10);
  servo2.attach(9);

  // Set initial positions of servos
  servo1.write(100);

  testServos();
}

void loop()
{
  if (Serial.available() > 0)
  {
    char value = Serial.read();

    Serial.print("Received: ");
    Serial.println(value);

    // Control servos based on received value
    if (value == 'A') { // Arm up
      servo1.write(150);
    }
    else if (value == 'D') { // Arm Down
      servo1.write(90);
    }
    else if (value == 'E') { // Arm Center
      servo1.write(120);
    }
    else if (value == 'H') { // Open hand
      servo2.write(180);
    }
    else if (value == 'I') { // Close hand (half)
      servo2.write(120);
    }
    else if (value == 'J') { // Close hand fully (grab)
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
}

void forward()
{
  // Move motors to drive forward
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}

void backward()
{
  // Move motors to drive backward
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
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

void testServos()
{
  servo2.write(180);
  delay(1000);
  servo2.write(120);
  delay(1000);
  servo2.write(90);
  delay(1000);
  servo2.write(60);
  delay(30);
}
