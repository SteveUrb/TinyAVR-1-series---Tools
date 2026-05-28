/*

Example of using the DAC_SetVoltage() function from the TinyTools library.
Using the DAC converter, the voltage on pin PA6 is varied between 1.5 and
2.3 volts to vary the brightness of an LED.
Because the DAC pin PA6 is not designed to source current, a buffer opamp
based on, for example, the LM358 (max. 10–20 mA) is used.

Urb (c) 2026

*/


#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>
#include "TinyTools.h"


float VoltageMin = 1.50f;
float VoltageMax = 2.30f;
float Step       = 0.01f;
bool  Upwards    = true;
float Voltage    = VoltageMin;

void setup(){}

void loop() {
    DAC_SetVoltage(Voltage);
    _delay_ms(20);
    if(Upwards) {
        Voltage += Step;
        if (Voltage >= VoltageMax) Upwards = false;
    } else {
        Voltage -= Step;
        if (Voltage <= VoltageMin) Upwards = true;
    }
}
