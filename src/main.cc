#include<Arduino.h>
#include<stdbool.h>
#include"Soil_Moisture.h"

// Arduino-specific variables and functions
void setup() 
{
  pinMode(PUMP_RELAY_PIN, OUTPUT); // Set pin as output 
  Serial.begin(9600);              // Initialize serial communication between computer and Arduino
}

// The loop routine runs over and over again forever
void loop() 
{
    Check_Soil_Moisture(&valueSensor1, &valueSensor2, &average_moisture); 

    if (average_moisture < DRY_THRESHOLD)
    {
        need_to_water_soil = true;
        Water_Until_Soil_Wet(WET_THRESHOLD);
    }
}

