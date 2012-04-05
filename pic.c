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
        for (i=0; i < 166; i++);
}

void swled(){
  LED_0 = LED_0 ? 0 : 1;
  delay_ms(100);
}

void main(void)
{
    unsigned char c,x,y,led;
    led = 0;
    LED_0 = led;

    // Initiate Osc with 8MHz (only relevant if you use the internal oscillator)
    //OSCCON = 0x70;
    
	  // Default all pins to digital
    ADCON1 |= 0x0F;
    
    
    initCDC();
    
    
    usb_init(cdc_device_descriptor, cdc_config_descriptor, cdc_str_descs, USB_NUM_STRINGS); // TODO: Remove magic with macro
    usb_start();
#if defined (USB_INTERRUPTS)
    //EnableUsbInterrupt(USB_TRN + USB_SOF + USB_UERR + USB_URST);
    EnableUsbInterrupt(USB_STALL + USB_IDLE + USB_TRN + USB_ACTIV + USB_SOF + USB_UERR + USB_URST);
    EnableUsbInterrupts();
#endif
    usbbufflush(); //flush USB input buffer system

#if 1
    // set pin to output
    TRISBbits.TRISB0 = 0;

    while(1)
    {
        LED_0 = 1;
        delay_ms(250);
        LED_0 = 0;
        delay_ms(250);
    }
#endif
    do
    {
#ifndef USB_INTERRUPTS
        //service USB tasks
        //Guaranteed one pass in polling mode
        //even when usb_device_state == CONFIGURED_STATE
        if (!TestUsbInterruptEnabled())
        {
            USBDeviceTasks();
        }
#endif
            swled();

        if ((usb_device_state < DEFAULT_STATE))
        { // JTR2 no suspendControl available yet || (USBSuspendControl==1) ){

        } else if (usb_device_state < CONFIGURED_STATE)
        {

        }else if((usb_device_state == CONFIGURED_STATE))
        {

        }
    } while (usb_device_state < CONFIGURED_STATE);

    #if 1

    while(1)
    {
        LED_0 = led;
        led = led ? 0 : 1;
#ifndef USB_INTERRUPTS
        //service USB tasks
        //Guaranteed one pass in polling mode
        //even when usb_device_state == CONFIGURED_STATE
        if (!TestUsbInterruptEnabled())
            USBDeviceTasks();
#endif
        usbbufservice(); //service USB buffer system

        if (usbbufgetbyte(&c) == 1)
        {
            WaitInReady();
            cdc_In_buffer[0] = c; //answer OK
            putUnsignedCharArrayUsbUsart(cdc_In_buffer, 1);
        }

    }
    
    #endif
    
    // set pin to output
    TRISBbits.TRISB0 = 0;
    
    // start a loop blinking the led
    while(1)
    {
        LED_0 = 1;
        delay_ms(250);
        LED_0 = 0;
        delay_ms(250);
    }
}
