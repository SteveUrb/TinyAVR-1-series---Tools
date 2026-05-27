#include "TinyTools.h"
#include <avr/io.h>
#include <util/delay.h>

static void DAC_setup(void){
	static bool FirstTime = true;
	if (FirstTime) {
	// DAC0 Voltage reference enabled
		VREF_CTRLB |= VREF_DAC0REFEN_bm;
		_delay_us(25);
	// Define pin PA6 for DAC converter
		PORTA.PIN6CTRL |= PORT_ISC_INPUT_DISABLE_gc;		// Interrupt en digital input uit
		PORTA.PIN6CTRL &= ~PORT_PULLUPEN_bm;				// Pull-up uit
	// Initiate DAC converter
		DAC0.CTRLA     |= DAC_ENABLE_bm;					// DAC converter enabled
		DAC0.CTRLA     |= DAC_OUTEN_bm; 					// Output Buffer enabled
		//DAC0.CTRLA |= DAC_RUNSTDBY_bm;					// Run in Standby sleep mode enabled - Optional
		FirstTime = false;
	}
}

static float DAC_Vreference(float Voltage){
    // Clamp voltage to valid range (0V to 4.34V)
    if (Voltage < 0.00) Voltage = 0.00;
    if (Voltage > 4.34) Voltage = 4.34;
	float Vreferentie;

    // Determine and set appropriate reference voltage
    if (Voltage < 0.55) {
        VREF_CTRLA = (VREF_CTRLA & ~VREF_DAC0REFSEL_gm) | VREF_DAC0REFSEL_0V55_gc;
		Vreferentie = 0.55F;
    } 
    else if (Voltage < 1.1) {
        VREF_CTRLA = (VREF_CTRLA & ~VREF_DAC0REFSEL_gm) | VREF_DAC0REFSEL_1V1_gc;
		Vreferentie = 1.10F;
    } 
    else if (Voltage < 1.5) {
        VREF_CTRLA = (VREF_CTRLA & ~VREF_DAC0REFSEL_gm) | VREF_DAC0REFSEL_1V5_gc;
		Vreferentie = 1.50F;
    } 
    else if (Voltage < 2.5) {
        VREF_CTRLA = (VREF_CTRLA & ~VREF_DAC0REFSEL_gm) | VREF_DAC0REFSEL_2V5_gc;
		Vreferentie = 2.50F;
    } 
    else {
        VREF_CTRLA = (VREF_CTRLA & ~VREF_DAC0REFSEL_gm) | VREF_DAC0REFSEL_4V34_gc;
		Vreferentie = 4.34F;
    }
	return Vreferentie;
}

void DAC_SetVoltage(float Voltage) {
	float Vreferentie = DAC_Vreference(Voltage);	// 
	DAC_setup();									// Runs once, check in DAC_setup
    DAC0.DATA = (uint8_t)(Voltage * 256.0f / Vreferentie);
}
