int d = 100;

void setup() {
	for (int a = 0; a < 256; ++a) {
		analogWrite(3, a);
		delay(d);
	}
	
	for (int a = 255; a >= 0; --a) {
		analogWrite(3, a);
		delay(d);
	}
	delay(200);
}

void loop() {
	int delta = 1;
	int direction = delta;
	int a = 2;
	while (true) {
		digitalWrite(a, HIGH);
		delay(d);
		digitalWrite(a, LOW);
		delay(d);
		if (a == 6){
			direction = -delta;
		} else if (a == 2) {
			direction = delta;
			
		}
		a += direction;
	}
}