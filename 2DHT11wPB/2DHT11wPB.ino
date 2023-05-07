/* This code uses a DHT11 sensor to measure temperature and 
humidity values, and displays them on an LCD screen. 
It also includes a pushbutton that allows you to switch between 
Celsius and Fahrenheit temperature readings, as well as humidity values.
*/

// Include Adadruit_Sensor library for working with sensors
#include <Adafruit_Sensor.h>

// Include DHT library for working with DHT11 sensor
#include <DHT.h>
#include <DHT_U.h>

// Include LiquidCrystal library for managing with LCD screen
#include <LiquidCrystal.h>

// Define the pin number for DHT11
#define DHTPIN 13

// Define the type of DHT sensor being used
#define DHTTYPE DHT11

// Create a DHT object to work with DHT sensor
DHT_Unified dht(DHTPIN, DHTTYPE);

// Define an unsigned integer for a delay in milliseconds
uint32_t delayMS;

// Define variables for a push button
const int PB = 7;
int buttonState = LOW;
int lastButtonState = HIGH;
int PBcount = 0;

// Declare a variable to hold temperature in Fahrenheit
float Ftemp;

// Initialize the library by associating any needed LCD interfere pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // Initialize PB as an INPUT_PULLUP
   pinMode(PB, INPUT_PULLUP);  
  // Initialize Serial Monitor with baud rate of 9600
  Serial.begin(9600);   
  // Initialize DHT sensor
  dht.begin();
  // Set up the LCD's number of columns and rows 
  lcd.begin(16, 2);
 

  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
}

void loop() {
  // Read the state of the pushbutton and store the result in the buttonState variable
  buttonState = digitalRead(PB);
  
  // Check if the button state has changed (was just pressed)
  if (buttonState != lastButtonState) {
    // Add a debounce delay to prevent false readings from the button
    delay(50);
    
    // If the button has been pressed, increment the button press count
    if (buttonState == HIGH) {
      PBcount++;
      
      // Reset PBcount to 1 if it reaches the maximum count of 4
      if (PBcount == 4) {
        PBcount = 1;
      }
    }
  }
  
  // Switch statement to handle the different cases of the pushbutton press
  switch (PBcount) {
    case 1:   // Display temperature in Celsius
      sensors_event_t event;
      dht.temperature().getEvent(&event);
      
      // Check if the temperature reading is a valid number
      if (isnan(event.temperature)) {
        // If temperature is not a number then it will print an error message
        Serial.println(F("Error reading temperature!"));
      }
      else {   // Display the temperature value on the LCD screen in Celsius with a degree symbol
        lcd.setCursor(0,0);
        lcd.print(F("Temp: "));
        lcd.print(event.temperature);
        lcd.print((char)223);
        lcd.print(F("C"));
        lcd.print("  ");
      }
      break;
    
    case 2:   // Display humidity
      dht.humidity().getEvent(&event);
      
      // Check if the humidity reading is a valid number
      if (isnan(event.relative_humidity)) {
        // If humidity is not a number then it will print an error message
        Serial.println(F("Error reading humidity!"));
      }
      else {   // Display the humidity value on the LCD screen
        lcd.setCursor(0,0);
        lcd.print(F("Hum: "));
        lcd.print(event.relative_humidity);
        lcd.print("%");
        lcd.print("  ");
      }
      break; 

    case 3:   // Display temperature in Fahrenheit
      dht.temperature().getEvent(&event);
      
      // Check if the temperature reading is a valid number
      if (isnan(event.temperature)) {
        // If temperature is not a number then it will print an error message
        Serial.println(F("Error reading temperature!"));
      }
      else {   
        // Display the temperature value on the LCD screen in Fahrenheit with a degree symbol
        Ftemp = (event.temperature * 1.8) + 32.0;  // Convert Celsius to Fahrenheit
        lcd.setCursor(0,0);
        lcd.print(F("Temp: "));
        lcd.print(Ftemp);
        lcd.print((char)223);
        lcd.print(F("F"));
        lcd.print("  ");
      }
      break; 
  }
  
  // Store the current state of the pushbutton for the next cycle
  lastButtonState = buttonState;
}