#include <GY6050.h>  // Library for GYRO
#include <Wire.h>
#include <Servo.h>

Servo myservo;   // Servo controlled by MPU6050
Servo myservo1;  // Second servo performing a sweeping motion

int X = 0;
int Y = 0;
GY6050 gyro(0x68);  // Initialize GYRO

void setup() {
  Wire.begin();            // Initialize GYRO
  gyro.initialisation();
  delay(100);

  myservo.attach(9);   // Attach first servo to pin 9
  myservo1.attach(10); // Attach second servo to pin 10
}

void loop() {
  // Get gyro data and map it to servo angles
  X = map(gyro.refresh('A', 'X'), -90, 90, 0, 180);
  Y = map(gyro.refresh('A', 'Y'), -90, 90, 0, 180);
  
  myservo.write(Y);  // Move first servo based on gyro Y-axis
  delay(15);         // Small delay for stability

  // Sweep second servo smoothly without blocking
  static int pos = 0;
  static int step = 1;

  myservo1.write(pos);  
  pos += step;

  if (pos >= 180 || pos <= 0) {
    step = -step;  // Reverse direction when limits are reached
  }

  delay(10);
}