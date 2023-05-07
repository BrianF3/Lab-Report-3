/*
This code is for an Arduino connected to a DHT11 temperature and humidity sensor and a 16x2 character 
LCD display. The code reads the temperature and humidity from the sensor, 
displays them on the serial monitor, and shows them on the LCD display. 
If there is an error reading the sensor, an error message is displayed on 
both the serial monitor and the LCD display.
*/
// Include the required libraries
#include <Adafruit_Sensor.h>   // Library for using sensors
#include <DHT.h>               // Library for using DHT sensors
#include <DHT_U.h>             // Library for using DHT sensors
#include <LiquidCrystal.h>     // Library for using LCD display

// Define the pin and sensor type for DHT11
#define DHTPIN 13
#define DHTTYPE DHT11

// Create an instance of the DHT_Unified class
DHT_Unified dht(DHTPIN, DHTTYPE);

// Define the delay time in milliseconds
uint32_t delayMS;

// Define the pins for the LCD display
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

// Setup function runs once at the beginning of the program
void setup() {
  // Start serial communication
  Serial.begin(9600);

  // Initialize the DHT sensor
  dht.begin();

  // Initialize the LCD display
  lcd.begin(16, 2);

  // Create a custom character for the LCD display
  lcd.createChar(0,customChar);

  // Get the minimum delay time for the sensor
  sensors_event_t sensor;
  dht.temperature().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
}

// Loop function runs repeatedly until the program is stopped
void loop() {
  // Wait for the delay time
  delay(delayMS);

  // Get the temperature sensor event
  sensors_event_t event;
  dht.temperature().getEvent(&event);

  // Check if there is an error reading temperature
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    // Print the temperature reading to serial monitor
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }

  // Get the humidity sensor event
  dht.humidity().getEvent(&event);

  // Check if there is an error reading humidity
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    // Print the humidity reading to serial monitor
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }

  // Get the temperature sensor event
  dht.temperature().getEvent(&event);

  // Check if there is an error reading temperature
  if (isnan(event.temperature)) {
    // Print the error message to the LCD display
    lcd.setCursor(0,0);
    lcd.print(F("Error reading temperature!"));
  }
  else {
    // Print the temperature reading to the LCD display
    lcd.setCursor(0,0);
    lcd.print(F("Temp:"));
    lcd.print(event.temperature);
    lcd.print((char)223);
    lcd.print(F("C"));
  }

  // Get the humidity sensor event
  dht.humidity().getEvent(&event);

  // Check if there is an error reading humidity
  if (isnan(event.relative_humidity)){
    // Print the error message to the LCD display
    lcd.setCursor(0,1);
    lcd.print(F("Error reading humidity!"));
  }
  else {
    // Print the humidity reading to the LCD display
    lcd.setCursor(0,1);
    lcd.print(F("Hum:"));
    lcd.print(event.relative_humidity);
    lcd.print(F("%"));
  }
}