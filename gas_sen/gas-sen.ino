int value = 0;
int gas_sen = D3;

void setup() {
	Serial.begin(9600); 
	pinMode(gas_sen, OUTPUT);
	Serial.println("Serial port initialized . . . ");
	Serial.println(" **** The Lonely Programmer **** ");
    Serial.println("Gas Sensor initialized . . . ");
}

void loop() {
    value = digitalRead(gas_sen);
    Serial.print("Gas Sensor: ");
    Serial.println(value);
	delay(500);
}
