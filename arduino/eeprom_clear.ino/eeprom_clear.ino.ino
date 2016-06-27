/*
 * EEPROM Clear
 *
 * Sets all of the bytes of the EEPROM to 0.
 * This example code is in the public domain.

 */

#include <EEPROM.h>

void setup()
{
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	
  // write a 0 to all 512 bytes of the EEPROM
  for (int i = 0; i < 512; i++) {
	  EEPROM.write(i, 0);
	  
	  digitalWrite(3 + ((i-1)%2), LOW);
	  digitalWrite(3 + (i%2), HIGH);
	  delay(50);
  }
	  
    
  // turn the LED on when we're done
  digitalWrite(2, HIGH);
}

void loop()
{
}
