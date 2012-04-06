#include <pic18fregs.h>
#include "usb_config.h"
#include "GenericTypeDefs.h"
#include <usb_stack.h>
#include <cdc.h>
#include <cdc_descriptors.h>

#define LED_0              PORTBbits.RB0

void delay_ms(long ms)
{
    long i;
    
    while (ms--)
        for (i=0; i < 335; i++);
}

void swled(){
  LED_0 = LED_0 ? 0 : 1;
  delay_ms(100);
}

void main(void)
{
    // Default all pins to digital
    ADCON1 |= 0x0F;

    // set pin to output
    TRISBbits.TRISB0 = 0;
    
    // start a loop blinking the led
    while(1)
    {
        LED_0 = 1;
        delay_ms(1000);
        LED_0 = 0;
        delay_ms(1000);
    }
}
