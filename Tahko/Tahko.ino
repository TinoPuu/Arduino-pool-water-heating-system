/*
In this project I made pool water heating system. We have two pumps that pump water into the tank and from there back into the pool.
The system checks the temperature of the water which is heated by the solar panels.
The system also controls water inlet and outlet.

Attention:
If you want to use this code for something, you have to install libraries which I use in this project also.
*/
//Libraries
#include <OneWire.h>
#include <DallasTemperature.h>

//Variables
const int WaterSurface = 2;       //Water surface sensor
const int WaterTemperature = 3;   // Water temperature sensor
const int WaterHotLed = 9;        //red led
const int WaterFull = 10;         //green led
const int WaterIn = 11;           //blue led
const int WaterOut = 12;          //yellow led
float tempCelsius;                // temperature in Celsius

OneWire oneWire(WaterTemperature);      
DallasTemperature tempSensor(&oneWire);

/*
 In the setup we have to tell which port we want to use.
*/
void setup() {
Serial.begin(9600);
pinMode(WaterHotLed, OUTPUT);      //red led
pinMode(WaterFull, OUTPUT);        //green led
pinMode(WaterIn, OUTPUT);          //blue led
pinMode(WaterOut, OUTPUT);         //yellow led
tempSensor.begin();
pinMode(WaterSurface, INPUT_PULLUP);
}

void loop() {
  /*
   Here we get the water temperature and we print it to serialmonitor. Because we want to make sure that everything works properly.
   For example, if your leds aren't working correctly or something else goes wrong, you can check the system status from serialmonitor.
  */
  tempSensor.requestTemperatures();             // send the command to get temperatures
  tempCelsius = tempSensor.getTempCByIndex(0);  // read temperature in Celsius
  Serial.print("Temperature: ");
  Serial.print(tempCelsius);    // print the temperature in Celsius
  Serial.println("°C");
  
  /*
  In this part we check if the water temperature is too low for the output pump.
  If the temperature is too low, then we blink red led. If the temperature is at the target level, then we put the red led on.
  */
  if(tempCelsius<30){
    Serial.println("Water temperature too low");
    digitalWrite(WaterHotLed, HIGH);
    delay(500);
    digitalWrite(WaterHotLed, LOW);
    }
  if(tempCelsius>50){
    Serial.println("Water temperature enough");
    digitalWrite(WaterHotLed, HIGH);
    }
   /*
  In this part we check if the tank is full. If it's not then we open the input pump. 
  If it is full and water temperature is still under the target, we just put the input pump off and the green led on.
  If water temperature is high enough and the watertank is full then we open output pump and 
  keep the red and green lights on until the water temperature or the water surface goes low enough.
  */
  
  if(digitalRead(WaterSurface)==HIGH){
    Serial.println("Water surface low");
    Serial.println("Water in");
    digitalWrite(WaterFull, LOW);
    digitalWrite(WaterOut, LOW);
    digitalWrite(WaterIn, HIGH);
    }
  if(digitalRead(WaterSurface)==LOW){
    Serial.println("Water surface high");
    digitalWrite(WaterIn, LOW);
    digitalWrite(WaterOut, LOW);
    digitalWrite(WaterFull, HIGH);
    }
    
  if(digitalRead(WaterSurface)==LOW && tempCelsius>30){
    Serial.println("Water surface high and temp enought");
    Serial.println("Water out");
    digitalWrite(WaterOut, HIGH);
    digitalWrite(WaterHotLed, HIGH);
    digitalWrite(WaterFull, HIGH);
    digitalWrite(WaterIn, LOW);
    }
  delay(1500);
  
}
