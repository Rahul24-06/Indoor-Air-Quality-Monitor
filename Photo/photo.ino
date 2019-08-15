int photosensor = A0; 
int analogvalue;

void setup() {
    Serial.begin(9600); 
	pinMode(photosensor, OUTPUT);
    Serial.println("Serial port initialized . . . ");
	Serial.println(" **** The Lonely Programmer **** ");
    Serial.println("Photodiode initialized . . . ");
}

void loop() {
    analogvalue = analogRead(photosensor);
    Serial.print("Light: ");
    Serial.println(analogvalue);
	delay(500);
}