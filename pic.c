#include <pic18fregs.h>
#include "usb_config.h"
#include "GenericTypeDefs.h"
#include <usb_stack.h>
#include <cdc.h>
#include <cdc_descriptors.h>

#define USB_INTERRUPTS 1

#define LED0               PORTBbits.RB0
#define LED1               PORTBbits.RB1
#define LED2               PORTBbits.RB2
#define LED3               PORTBbits.RB3

#define swled(LED) (((LED) = (LED) ? 0 : 1), delay_ms(500))

void delay_ms(long ms)
{
  long i;
  while (ms--)
    for (i=0; i < 335; i++);
}

void main(void)
{
    unsigned char c,x,y,led;
    unsigned long l;
    
	  // Default all pins to digital
    ADCON1 |= 0x0F;

    // Disable USB external transceiver to allow RB1/RB2
    UCFGbits.UTRDIS = 0;
    
    // set pin to output
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;

    LED0 = 1;
    LED1 = LED2 = LED3 = 0;
    
    // TODO: Remove magic with macro
    usb_init(cdc_device_descriptor, cdc_config_descriptor, cdc_str_descs, USB_NUM_STRINGS);
    usb_start();
    
    initCDC();
    usbbufflush();
    
    do {
        if (!TestUsbInterruptEnabled())
            USBDeviceTasks();

        switch(usb_device_state){
            case DETACHED_STATE:
                LED1 = 0; LED2 = 0; LED3 = 0;
            case ATTACHED_STATE:
                LED1 = 0; LED2 = 0; LED3 = 1;
            case POWERED_STATE:
                LED1 = 0; LED2 = 1; LED3 = 0;
            case DEFAULT_STATE:
                LED1 = 0; LED2 = 1; LED3 = 1;
            case ADR_PENDING_STATE:
                LED1 = 1; LED2 = 0; LED3 = 0;
            case ADDRESS_STATE:
                LED1 = 1; LED2 = 0; LED3 = 1;
            case CONFIGURED_STATE:
                LED1 = 1; LED2 = 1; LED3 = 0;
        }
    } while (usb_device_state < CONFIGURED_STATE);

    while(1);
#if 0

    // Initiate Osc with 8MHz (only relevant if you use the internal oscillator)
    //OSCCON = 0x70;
    
    
    
    initCDC();
    
    
    // TODO: Remove magic with macro
    usb_init(cdc_device_descriptor, cdc_config_descriptor, cdc_str_descs, USB_NUM_STRINGS);

    usb_start();

#if defined (USB_INTERRUPTS)
    //EnableUsbInterrupt(USB_TRN + USB_SOF + USB_UERR + USB_URST);
    EnableUsbInterrupt(USB_STALL + USB_IDLE + USB_TRN + USB_ACTIV + USB_SOF + USB_UERR + USB_URST);
    EnableUsbInterrupts();
#endif

    usbbufflush(); //flush USB input buffer system

    led = UCFGbits.UTRDIS;
    
    
    LED0=0;
    LED1=0;
    LED2=0;
    LED3=0;
    
    while(1){
      LED1 = LED1 ? 0 : 1;
      for(l = 0; l < 10; ++l);
    }
    
    LED0=1;
    LED1=1;
    LED2=1;
    LED3=1;
    delay_ms(500);    
#if 0
    while(1)
    {
        LED0 = 1;
        delay_ms(250);
        LED0 = 0;
        delay_ms(250);
    }
#endif
    LED0 = 0;
    LED1 = 0;
    LED2 = 0;
    LED3 = 0;
    delay_ms(500);
    while(1);
    
    do
    {   LED2=1;
        LED3 = 0;
#ifndef USB_INTERRUPTS
        //service USB tasks
        //Guaranteed one pass in polling mode
        //even when usb_device_state == CONFIGURED_STATE
        if (!TestUsbInterruptEnabled())
        {
            USBDeviceTasks();
            LED3 = 1;
        }
#endif

        if ((usb_device_state < DEFAULT_STATE))
        { // JTR2 no suspendControl available yet || (USBSuspendControl==1) ){
          LED0=1;
          LED1=0;
        } else if (usb_device_state < CONFIGURED_STATE)
        {
          LED0=1;
          LED1=1;
        }else if((usb_device_state == CONFIGURED_STATE))
        {
          LED0=0;
          LED1=1;
        }
        LED2=0;
        delay_ms(1000);
    } while (usb_device_state < CONFIGURED_STATE);

    LED0 = 0;
    LED1 = 0;
    LED2 = 1;
    #if 1

    while(1)
    {
        LED0 = led;
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
    
    // Disable USB external transceiver to allow RB1/RB2
    UCFGbits.UTRDIS = 0;
    
    // set pin to output
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    
    // start a loop blinking the led
    while(1)
    {
        LED0 = 1;
        delay_ms(250);
        LED0 = 0;
        delay_ms(250);
    }
#endif
}
