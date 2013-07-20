#include <iostream>
#include "pcf8574.h"

using namespace std;

int main(){
  char busLocation[256];
  int address;
  cout << "Please enter the location of the i2c bus (eg /dev/i2c-1): " ;
  cin.getline(busLocation, 256);
  cout << "Please enter the address of the PCF8574 you wish to address (base 10): ";
  cin >> address;
  cout << "Addressing device " << address << " on I2C bus " << busLocation << endl;
  cout << "Enter -1 to exit" << endl;
  PCF8574 * device;
  device = new PCF8574(busLocation, address);

  int i = 0;

  while(i != -1){
    cout << "Value to write: ";
    cin >> i;
    if(i >= 0) device->setByte(i);
  }
  delete device;
  return 0;
}
