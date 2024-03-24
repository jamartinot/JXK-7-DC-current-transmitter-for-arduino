#include <Arduino.h>

const int analogPin = 13; // Analog pin for sensor input, UPDATE TO CORRECT ONE!
const int numReadings = 1000; // Number of readings to average for RMS calculation
const float calibrationOffset = -0.5; // Calibration offset value

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 bits per second
}

void loop() {
  long sumOfSquares = 0; // Long to hold the sum of the squares of each reading
  
  // Take a number of readings and sum their squares
  for (int i = 0; i < numReadings; i++) {
    int sensorValue = analogRead(analogPin);
    sumOfSquares += (long)sensorValue * sensorValue;
    delay(1); // Short delay between readings
  }
  
  // Calculate the mean of the sum of the squares
  float meanOfSquares = (float)sumOfSquares / numReadings;
  
  // Calculate the true RMS value
  float trueRMS = sqrt(meanOfSquares);
  
  // Convert the trueRMS analog value to current
  float current = 0.0;
  if (trueRMS > 200) {  //idle analog value, default 200 adjust if needed!
      current = (trueRMS - 200) / 60.0; //analog value-idle analog value times analog increment per 1A. Adjust idle analog value(200) and analog increment(60) if needed. 
  }

  // Apply calibration offset
  current += calibrationOffset;

  // Print the calibrated current to the serial port with one decimal precision
  Serial.println(current, 1);
  
  // Pause before taking the next set of readings
  delay(400);
}
