#include <LiquidCrystal.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 13     // Digital pin 13 connected to the DHT sensor 
#define DHTTYPE    DHT11     // DHT 11

// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int contrastPin = 9; //contrast pin
int contrast = 70;   //contrast level
int PB = 7;          //push button pin
int Display = 1;
int delayVal = 2000;

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

void setup() {

pinMode (7, INPUT_PULLUP);

//**********LCD CODE*******************//
  pinMode(contrastPin, OUTPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
 
//**********SENSOR CODE*******************//
 Serial.begin(9600);
  // Initialize device.
  dht.begin();
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
  // Set delay between sensor readings based on sensor details.
  /////////////delayMS = sensor.min_delay / 300;
delayMS = 200;

}

void loop() {

int buttonState = digitalRead(PB);
Serial.print("ButState = ");
Serial.println(buttonState);

Serial.print("Display# = ");
Serial.println(Display);

//**********LCD CODE*******************//
  analogWrite(contrastPin, contrast);
  
//**********SENSOR CODE*******************//

// Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }

float far = (event.temperature * 9/5) + 32;

//**********LCD PRINT THE SENSOR VALUES**********//

{
  if (buttonState == 0){  
    delay(delayVal);                        // delay to debounce switch

    Display = Display + 1;
    if(Display > 3){
      lcd.clear();
      Display = 1;
    }
    
    switch (Display) {
      case 1: {
        lcd.setCursor(0, 0);
    lcd.print(F("Temp: "));
    lcd.print(event.temperature);
    lcd.print(char(223));
    lcd.print(F("C"));
        break;
      }
        
      case 2: {
       lcd.setCursor(0, 0);
    lcd.print(F("Temp: "));
    lcd.print(far);
    lcd.print(char(223));
    lcd.print(F("F"));
        break;
      }
        
       case 3: {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("Hum: "));
    lcd.print(event.relative_humidity);
    lcd.print("%");
         break;
       }

    }
  }

}
}


/********* PART 1
dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    lcd.print(F("Error reading temperature!"));
  }
  else {
    lcd.setCursor(0, 0);
    lcd.print(F("Temp: "));
    lcd.print(event.temperature);
    lcd.print(char(223));
    lcd.print(F("C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    lcd.print(F("Error reading humidity!"));
  }
  else {
    lcd.setCursor(0, 1);
    lcd.print(F("Hum: "));
    lcd.print(event.relative_humidity);
    lcd.print(F("%"));

}
*************/

