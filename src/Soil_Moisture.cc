#include<Arduino.h>
#include<stdbool.h>

/******************************Constants***************************************************/

const int PUMP_TIME_LIMIT = 1000;      // time in milliseconds until pump shuts off
const int SOIL_SATURATION_TIME = 2000; // time in milliseconds to let water run through soil

const int DRY_THRESHOLD = 50;          // sensor threshold to start watering soil
const int WET_THRESHOLD = 300;         // sensor threshold to stop watering

const int PUMP_RELAY_PIN = 1;          // pin used to control pump relay


/*******************************Variables***************************************************/

int valueSensor1 = 0;            // analog sensor input from soil moisture sensor
int valueSensor2 = 0;            // analog sensor input from soil moisture sensor
int average_moisture = 0;        // average of the soil moisture sensor readings 

bool need_to_water_soil = false; // determines if soil needs to be watered


/*****************************Functions***************************************************/

// Reads the soil moisture sensor values and calculates the average reading
void Check_Soil_Moisture(int* valueSensor1, int* valueSensor2, int* average_moisture)
{
    *valueSensor1 = analogRead(A0); // Soil moisture sensor reading as analog input 
    *valueSensor2 = analogRead(A1);

    *average_moisture = (*valueSensor1 + *valueSensor2) / 2;

    Serial.println("valueSensor1: ");
    Serial.println(*valueSensor1);
    Serial.println("valueSensor2: ");
    Serial.println(*valueSensor2);
    Serial.println("average_moisture: ");
    Serial.println(*average_moisture);
}


// Pumps water for "PUMP_TIME_LIMIT" milliseconds
void Pump_Water(int PUMP_TIME_LIMIT)
{
    digitalWrite(RELAY_PIN, HIGH);  // turn on water pump 
    Serial.println();
    Serial.println("Pump on");

    delay(PUMP_TIME_LIMIT);         // leave pump on for "PUMP_TIME_LIMIT" milliseconds 

    digitalWrite(RELAY_PIN, LOW);   // turn off water pump
    Serial.println("Pump off");
}


// Uses Check_Soil_Moisture() and Pump_Water() to water soil until "WET_THRESHOLD" is met
void Water_Until_Soil_Wet(int WET_THRESHOLD)
{
    while (need_to_water_soil)
    {
        Pump_Water(PUMP_TIME_LIMIT);
        delay(SOIL_SATURATION_TIME); 
        Check_Soil_Moisture(&valueSensor1, &valueSensor2, &average_moisture);

        if (average_moisture >= WET_THRESHOLD)
        {
            need_to_water_soil = false;
            break;
        }
    }
}
