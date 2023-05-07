/*
 This code is designed for an Arduino microcontroller board that has a DHT11 temperature 
and humidity sensor and an ultrasonic sensor connected to it. 
The code reads the temperature and humidity from the DHT11 sensor, 
calculates the speed of sound based on the temperature and humidity, and then uses the 
ultrasonic sensor to calculate the distance of an object in front of the sensor. 
The results are then displayed on both the serial monitor and an LCD screen. 
The code also includes error checking for out-of-range distances.
*/
#include <LiquidCrystal.h>

// Initialize the LCD library
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Include DHT Libraries from Adafruit
#include "DHT.h"

// Include NewPing Library
#include "NewPing.h"

// Define Constants
#define DHTPIN 13       // DHT-22 Output Pin connection
#define DHTTYPE DHT11   // DHT Type is DHT 11
#define TRIGGER_PIN  9
#define ECHO_PIN     8
#define MAX_DISTANCE 400

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// Define Variables
float hum;          // Stores humidity value in percent
float temp;         // Stores temperature value in Celcius
float duration;     // Stores HC-SR04 pulse duration value
float distance;     // Stores calculated distance in cm
float soundsp;      // Stores calculated speed of sound in M/S
float soundcm;      // Stores calculated speed of sound in cm/ms
int iterations = 5; // Number of readings to take when calculating median

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Start the serial communication
  Serial.begin(9600);

  // Initialize the DHT sensor
  dht.begin();
}

void loop() {
  // Delay so DHT-11 sensor can stabilize
  delay(500);

  // Get humidity and temperature readings
  hum = dht.readHumidity();
  temp = dht.readTemperature();

  // Calculate the speed of sound in M/S
  soundsp = 331.4 + (0.606 * temp) + (0.0124 * hum);

  // Convert speed of sound to cm/ms
  soundcm = soundsp / 10000;

  // Get the median duration for the ultrasonic sensor
  duration = sonar.ping_median(iterations);

  // Calculate the distance
  distance = (duration / 2) * soundcm;

  // Send the results to the Serial Monitor
  Serial.print("Sound: ");
  Serial.print(soundsp);
  Serial.print(" m/s, ");
  Serial.print("Humid: ");
  Serial.print(hum);
  Serial.print(" %, Temp: ");
  Serial.print(temp);
  Serial.print(" C, ");
  Serial.print("Distance: ");

  // Check if the distance reading is out of range
  if (distance >= 400 || distance <= 2) {
    Serial.print("Out of range");
  } else {
    Serial.print(distance);
    Serial.print(" cm");
    delay(50);
  }

  Serial.println(" ");

  // Send the results to the LCD display
  lcd.setCursor(0, 0);
  lcd.print("Distance=");

  // Check if the distance reading is out of range
  if (distance >= 400 || distance <= 2) {
    lcd.print("Out of range");
  } else {
    lcd.print(distance);
    lcd.print("cm");
    delay(50);
  }

  lcd.print(" ");
}