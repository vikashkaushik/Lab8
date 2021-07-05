/*
 * Project Lab8
 * Description: Using proximity sensor it can light up the designated color LED, and use oled display based on the button pressed.
 * Author: Vikash Kaushik
 * Date: 7/4/21
 */
SYSTEM_THREAD(ENABLED);
#include <Wire.h>
#include "SparkFun_VCNL4040_Arduino_Library.h"
#include "oled-wing-adafruit.h"
OledWingAdafruit display;
VCNL4040 proximitySensor;
// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  // sets all the leds as outputs
  pinMode(D7,OUTPUT); 
  pinMode(D6,OUTPUT);
  pinMode(D5,OUTPUT);
  display.display();  // cause the display to be updated
  display.clearDisplay();
  display.setup();
  Serial.begin(9600); 
  Wire.begin();
  proximitySensor.begin(); //Initialize the sensor  
  proximitySensor.powerOnAmbient(); //Power up the ambient sensor

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  display.loop();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  
  unsigned int proxValue = proximitySensor.getProximity(); 
  Serial.println(proxValue);
  // blue far	
  if(proxValue <= (10))
  {
    digitalWrite(D7, HIGH);
    digitalWrite(D6, LOW);
    digitalWrite(D5, LOW);
    
  }
   // orange kinda close	
  if(proxValue > (11) && proxValue<1000)
  {
    
    digitalWrite(D6, HIGH);
    digitalWrite(D5, LOW);
    digitalWrite(D7, LOW);
  }
  //green very close	
  if(proxValue >= (1000) && proxValue>5000)
  {
    
    digitalWrite(D5, HIGH);
    digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);
  }
 
  // pressing a displays proximity value
  if (display.pressedA()) {
		display.clearDisplay();
    display.print("Proximity Value: ");
    display.print(proxValue);
    Serial.println();
    display.display(); 
  }
  // pressing b displays you the ambient light level	
  if (display.pressedB()) {
    display.clearDisplay();
		unsigned int ambientValue = proximitySensor.getAmbient(); 

    display.print("Ambient light level: ");
    display.println(ambientValue);
    display.display(); 
  }
  // pressing c displays the i2C address
  if (display.pressedC()) {
    display.clearDisplay();
		unsigned int i2CValue = proximitySensor.getID(); 

    display.print("I2C Address: ");
    display.println(i2CValue);
    display.display(); 
  }
  


  

}
