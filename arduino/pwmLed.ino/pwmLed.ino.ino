void setup() {
	for (int i = 2; i <= 6; i++) {
		pinMode(i, OUTPUT);
	}
}

void fade(int pwmPin, int d, int highDuration) {
	const int skip = 2;
	int a = 0;
	for ( ; a < 256; a += skip) {
		analogWrite(pwmPin, a);
		delay(d);
	}
	
	for ( ; a >= 0; a -= skip) {
		analogWrite(pwmPin, a);
		delay(d);
	}
	delay(highDuration);
}	

void loop() {
	int delta = 1;
	int direction = delta;
	int a = 2;
	while (true) {
		fade(a, 1, 20);
		if (a == 6){
			direction = -delta;
		} else if (a == 2) {
			direction = delta;
			
		}
		a += direction;
	}

}
