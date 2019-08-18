// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_DHT.h>

// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_DHT.h>

#include "Adafruit_DHT.h"

// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#define DHTPIN 2     // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11		// DHT 11 
//#define DHTTYPE DHT22		// DHT 22 (AM2302)
//#define DHTTYPE DHT21		// DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

int value = 0;
int gas_sen = D3;

int photosensor = A0; 
int analogvalue = 0;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
	Serial.begin(9600); 
    pinMode(gas_sen, OUTPUT);
    pinMode(photosensor, OUTPUT);
    dht.begin();
	Serial.println("Serial port initialized . . . ");
	Serial.println(" **** The Lonely Programmer **** ");
    Serial.println("Gas Sensor initialized . . . ");
    Serial.println("Photodiode initialized . . . ");
    Serial.println("DHT initialized . . . ");
}

void loop() {
	float h = dht.getHumidity();
    // Read temperature as Celsius
	float t = dht.getTempCelcius();
	
	if (isnan(h) || isnan(t)) {
		h = 0.00;
		t = h;
	}

	Serial.print("Humid: "); 
	Serial.print(h);
	Serial.print("% - ");
	Serial.print("Temp: "); 
	Serial.print(t);
	Serial.println("*C ");
	
	value = digitalRead(gas_sen);
    Serial.print("Gas Sensor: ");
    Serial.println(value);
    
    analogvalue = analogRead(photosensor);
    Serial.print("Light: ");
    Serial.println(analogvalue);
    
	Serial.println(Time.timeStr());
	Serial.println();
	
	char data[256];
  
    snprintf(data, sizeof(data), "{ \"temp\":%.2f, \"humid\":%.2f, \"gas\":%d, \"light\":\"%d\" }",
       t, h, value, analogvalue);
  
    // Trigger the integration
    Particle.publish("Firebase", data, PRIVATE);
    // Wait 10 seconds
    delay(10000);
}



