/*This code uses an ultrasonic sensor to measure the distance between the sensor and an object in front of it. 
The measured distance value is displayed on an LCD screen and also printed to the Serial Monitor. Additionally, 
the code includes a feature to handle the case where the measured distance is out of range, 
printing a message instead of the distance value.
*/
#include <HCSR04.h> // Include the ultrasonic sensor library
UltraSonicDistanceSensor distanceSensor(9, 8); // Initialize sensor that uses digital pins 9 and 8.

#define trigpin 9 // Define the trigger pin as 9 for convenience
#define echopin 8 // Define the echo pin as 8 for convenience

#include <LiquidCrystal.h> // Include the LCD library
// Specify the pins on the Arduino board that are connected to the LCD's RS, EN, D4, D5, D6, and D7 pins.
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; 
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Initialize the LCD

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  lcd.begin(16, 2); // Initialize the LCD screen with 16 columns and 2 rows
}

void loop() {
  // Every 500 milliseconds, measure the distance and display it on both the Serial Monitor and LCD screen.
  Serial.print("Distance = ");
  float distance = distanceSensor.measureDistanceCm(); // Get the distance from the ultrasonic sensor
  if (distance >= 400 || distance <= 2) { 
// If the measured distance is out of range, print a message on both the Serial Monitor and LCD screen
    Serial.println("Out of Range");
    lcd.clear(); // Clear the LCD screen
    lcd.setCursor(0, 0); // Set the cursor to the first row and first column
    lcd.print("Out of Range"); // Display the message "Out of Range" on the LCD screen
  } else { // If the measured distance is within range, print it on both the Serial Monitor and LCD screen
    Serial.print(distance);
    Serial.println(" cm");
    lcd.clear(); // Clear the LCD screen
  }
}
