#include<Arduino.h>
#include<stdbool.h>

/******************************Constants***************************************************/

const int PUMP_TIME_LIMIT = 1000; // time in milliseconds until pump shuts off
const int SOIL_SATURATION_TIME = 2000; // time in milliseconds to let water run through soil

const int DRY_THRESHOLD = 50; // sensor threshold to start watering soil
const int WET_THRESHOLD = 300;// sensor threshold to stop watering

const int PUMP_RELAY_PIN = 1;


/*******************************Variables***************************************************/

int valueSensor1 = 0; // analog sensor input from soil moisture sensor
int valueSensor2 = 0; // analog sensor input from soil moisture sensor
int average_moisture = 0; // average of the soil moisture sensor readings 

bool need_to_water_soil = false; // determines if soil needs to be watered


/*****************************Functions***************************************************/

void Check_Soil_Moisture(int* valueSensor1, int* valueSensor2, int* average_moisture)
{
    // Checks soil moisture sensor and prints values to computer terminal
    *valueSensor1 = analogRead(A0);
    *valueSensor2 = analogRead(A1);

    Serial.println("valueSensor1: ");
    Serial.println(*valueSensor1);
    Serial.println("valueSensor2: ");
    Serial.println(*valueSensor2);
};


void Pump_Water(int PUMP_TIME_LIMIT)
{
    digitalWrite(RELAY_PIN, HIGH);  // turn on water pump 
    delay(PUMP_TIME_LIMIT);         // leave pump on for one second
    digitalWrite(RELAY_PIN, LOW);   // turn off water pump
};


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
};
