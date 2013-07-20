Example use of PCF8574.cpp:

#include "pcf8574.h"

...

//instantiate a new PCF8574 device.
PCF8574 * device;
device = new PCF8574("/dev/i2c-1", 0x32);

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

