#ifndef SOIL_MOISTURE_H // ensures that this file is only created once
#define SOIL_MOISTURE_H

extern const int PUMP_TIME_LIMIT;      // time in milliseconds until pump shuts off
extern const int SOIL_SATURATION_TIME; // time in milliseconds to let water run through soil

extern const int DRY_THRESHOLD;        // sensor threshold to start watering soil
extern const int WET_THRESHOLD;        // sensor threshold to stop watering 

extern const int PUMP_RELAY_PIN;       // pin used to control pump relay  

extern int valueSensor1;               // analog input soil moisture sensor
extern int valueSensor2;
extern int average_moisture;           // average of moisture sensor readings

extern bool need_to_water_soil;


// Receives soil moisture and calculates the average reading from all sensors
void Check_Soil_Moisture(int* valueSensor1, int* valueSensor2, int* average_moisture);

// Turns on the water pump for "PUMP_TIME_LIMIT" milliseconds 
void Pump_Water(int PUMP_TIME_LIMIT);

// Waters the soil until the "WET_THRESHOLD" is met
void Water_Until_Soil_Wet(int WET_THRESHOLD);

#endif
