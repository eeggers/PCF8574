//Example use of PCF8574

#include "pcf8574.h"


main(){

	//instantiate a new PCF8574 object.
	//on my machine, the i2c bus I want to talk to can be accessed via /dev/i2c-1.
	//the pcf8574 chip I want to talk to is at address 32 (0x20).
	//this is merely an example.
	//be exceptionally careful when experimenting. see license
	PCF8574 * device;
	device = new PCF8574("/dev/i2c-1", 0x20);
	//device will be set to 0xff by default, which activates the internal pullups
	//this is the correct state for reading
	
	//read a byte from device
	int a = device->getByte();

	//get the state of pin 4
	int b = device->getBit(4);

	//write a value to the device
	device->setByte(0xaa);

	//set pin 0 high
	device->setBit(0,1);

	//set pin 6 low
	device->setBit(6,0);

	//it may be wise to activate the internal pullups before deleting the object
	//the default destructor does not do this, for flexibility
	device->setByte(0xff);
	delete device;
}
