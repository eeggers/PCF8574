#ifndef PCF8574_H
#define PCF8574_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

class PCF8574{
 private:
  int address;
  unsigned char state;
  char I2CBusLocation[256];
 public:
  PCF8574();
  PCF8574(char *, int);//i2cbuslocation, address
  ~PCF8574();
  void setByte(char);
  void setBit(int,int);//pin,value
  char getByte();
  int getBit(int);//pin

  int getAddress(){return address;}
  void setAddress(int address){this->address = address;}
  char * getI2CBusLocation(){return I2CBusLocation;}
  void setI2CBusLocation(char * I2CBusLocation){strcpy(this->I2CBusLocation, I2CBusLocation);}
};


#endif
