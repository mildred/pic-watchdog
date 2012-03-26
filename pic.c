#include "pic18fregs.h"

#define LED_0              PORTBbits.RB0
#define TRIS_0             TRISBbits.TRISB0

// Set the __CONFIG words, see datasheet section 25.1: Configuration bits

// To use the internal oscillator, change CONFIG1H to _OSC_INTOSC__INTOSC_CLK0_RA6___USB_EC_1H

#define cfg(address) __code char __at __CONFIG##address

cfg(1H) _conf0 = _OSC_HS__USB_HS_1H;
//__code char __at __CONFIG2L _conf1 = _BODEN_OFF_2L;
//__code char __at __CONFIG2H _conf2 = _WDT_DISABLED_CONTROLLED_2H;
cfg(3H) _conf3 = _MCLRE_MCLR_OFF_RE3_ON_3H;
cfg(4L) _conf4 = _LVP_OFF_4L;
//__code char __at __CONFIG5L _conf5 = _CP_0_OFF_5L & _CP_1_OFF_5L;
//__code char __at __CONFIG5H _conf6 = _CPD_OFF_5H & _CPB_OFF_5H;
//__code char __at __CONFIG6L _conf7 = _WRT_0_OFF_6L & _WRT_1_OFF_6L;
//__code char __at __CONFIG6H _conf8 = _WRTD_OFF_6H & _WRTB_OFF_6H & _WRTC_OFF_6H;
//__code char __at __CONFIG7L _conf9 = _EBTR_0_OFF_7L & _EBTR_1_OFF_7L;
//__code char __at __CONFIG7H _conf10 = _EBTRB_OFF_7H;

void delay_ms(long ms)
{
    long i;
    
    while (ms--)
        for (i=0; i < 166; i++);
}

void main(void)
{
    // Initiate Osc with 8MHz (only relevant if you use the internal oscillator)
    //OSCCON = 0x70;
    
	  // Default all pins to digital
    ADCON1 |= 0x0F;

    // set pin to output
    TRIS_0 = 0;
        
    // start a loop blinking the led
    while(1)
    {
        LED_0 = 1;
        delay_ms(250);
        LED_0 = 0;
        delay_ms(250);
    }
}
