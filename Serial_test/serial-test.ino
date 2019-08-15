int var = 0;
void setup() {
	Serial.begin(9600); 
	Serial.println("Serial port initialized . . . ");
	Serial.println(" **** The Lonely Programmer **** ");
}

void loop() {
    Serial.println(var);
	delay(500);
	var+=1;
}
