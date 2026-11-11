#include<Arduino.h>
#include<stdbool.h>
#include"soil_moisture.h"

void setup() 
{
  pinMode(RELAY_PIN, OUTPUT);   // Set pin as output 
  Serial.begin(9600);           // Initialize serial communication between computer and Arduino
}

// The loop routine runs over and over again forever
void loop() 
{
    static double average_moisture = 0;   // Average reading of both sensors 

    static bool water_soil = false; // Whether watering process should begin

    static int valueSensor1 = 0;        // Analog input from sensor 1
    static int valueSensor2 = 0;        // Analog input from sensor 2

    Check_Soil_Moisture(&valueSensor1, &valueSensor2, &average_moisture); 

    if (average_moisture < 50) 
    {
        water_soil = true;
        Serial.println("Starting soil watering");
    }

    while (begin_watering)
    {
        Pump_Water(water_soil); // Pump water for one second
        delay(SOIL_SATURATION_TIME); // Wait for water to travel through soil
        Check_Soil_Moisture(&valueSensor1, &valueSensor2, &average_moisture); // Check moisture again
        if (average_moisture < WET_THRESHOLD) begin_watering = false;
    }
}

