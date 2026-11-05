#include<Arduino.h>
#include<stdbool.h>

#define PUMP_TIME_LIMIT 1000    // time in milliseconds until pump shuts off
#define SOIL_SATURATION_TIME 2000 // time to allow water to travel through soil

#define RELAY_PIN 1             // Output pin used for relay switching

#define DRY_THRESHOLD 50        // Dryness level to trigger initial watering
#define WET_THRESHOLD 300       // Wetness level to stop watering

void Check_Soil_Moisture(int* valueSensor1, int* valueSensor2);
void Pump_Water();

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

void Pump_Water()
{
    digitalWrite(RELAY_PIN, HIGH);  // turn on water pump 
    delay(PUMP_TIME_LIMIT);         // leave pump on for one second
    digitalWrite(RELAY_PIN, LOW);   // turn off water pump
};
