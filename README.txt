TinyTools is a library of functions for the tinyAVR 1-series microcontrollers from Microchip. 
These microcontrollers are extremely nice because they are readily available everywhere for 
around one euro or a bit more, they offer a comprehensive set of peripherals, and Microchip 
has thoroughly documented everything.

The drawback appears to be that they are used relatively little, which sometimes makes searching
for solutions to problems a bit more difficult. In the meantime, I have written various functions
for these tinyAVR 1-series microcontrollers. Some are general C/C++ functions, while others are 
specific to these MCUs and based on direct register manipulations. Over time, TinyTools will be 
expanded with these functions.

To start with:
DAC_SetVoltage(float)
Pin PA6 of all tinyAVR 1-series microcontrollers is the DAC output pin. The function sets the 
output voltage on pin PA6 to the desired voltage value, with automatic internal Vref selection
for maximum accuracy. Initial configuration is handled automatically within the function.
Voltage is limited between 0 and 4.34 volts with an accuracy of approximately 0.1 volt.
