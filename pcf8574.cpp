#include "pcf8574.h"

PCF8574::PCF8574(char * I2CBusLocation, int address){
  strcpy(this->I2CBusLocation, I2CBusLocation);
  this->address = address;
  this->state = 0xff;
  setByte(state);
}

void PCF8574::setByte(unsigned char value){
  struct i2c_smbus_ioctl_data data;
  data.read_write = I2C_SMBUS_WRITE;
  data.size       = I2C_SMBUS_BYTE;
  data.data       = NULL;
  data.command    = value;

  int device;
  if((device = open(I2CBusLocation, O_RDWR)) == -1){
    fprintf(stderr,
      "ERROR: PCF8574::setByte failed to open i2c bus at %s\n", I2CBusLocation);
    exit(EXIT_FAILURE);
  }

  ioctl(device, I2C_SLAVE, address);
  ioctl(device, I2C_SMBUS, &data);
  close(device);
  state = value;
}

void PCF8574::setBit(int pin, int value){
  char mask = 0x01 << pin;
  setByte(value?(state | mask):(state & (~mask)));
}

unsigned char PCF8574::getByte(){
  union i2c_smbus_data data_union;
  struct i2c_smbus_ioctl_data data;
  data.read_write = I2C_SMBUS_READ;
  data.size       = I2C_SMBUS_BYTE;
  data.data       = &data_union;
  data.command    = 0;

  int device;
  if((device = open(I2CBusLocation, O_RDWR)) == -1){
    fprintf(stderr,
      "ERROR: PCF8574::getByte failed to open i2c bus at %s\n", I2CBusLocation);
    exit(EXIT_FAILURE);
  }

  ioctl(device, I2C_SLAVE, address);
  ioctl(device, I2C_SMBUS, &data);
  close(device);
  return data_union.byte; 
}

int PCF8574::getBit(int pin){
  char mask = 0x01 << pin;
  return getByte()&mask?1:0;
}

PCF8574::~PCF8574(){
  //  setByte(0xff);//return chip to default state
}
