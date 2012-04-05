#include <pic18fregs.h>
#define cfg(address) __code char __at __CONFIG##address _conf##address


// Set the __CONFIG words, see datasheet section 25.1: Configuration bits

cfg(1L) = _USBPLL_CLOCK_SRC_FROM_96MHZ_PLL_2_1L &             // USB clock from PLL
          _CPUDIV__OSC1_OSC2_SRC___1__96MHZ_PLL_SRC___2__1L & // CPUDIV = OSC1 ?
          _PLLDIV_DIVIDE_BY_5__20MHZ_INPUT__1L;               // PLLDIV = 4
cfg(1H) = _IESO_OFF_1H &               // IESO = OFF (disable oscillator switchover)
          _FCMEN_OFF_1H &              // FCMEN = OFF (fail-safe clock monitor disable)
          _OSC_HS__HS_PLL__USB_HS_1H;  // OSC = HSPLL (HS oscillator, PLL)
cfg(2L) = _BODEN_OFF_2L;               // (Brown out reset disabled)
cfg(2H) = _WDTPS_1_32768_2H &          // WDTPS = 32768 (watchdog timeout)
          _WDT_DISABLED_CONTROLLED_2H; // WDTEN = OFF   (disable watchdog)
cfg(3H) = _MCLRE_MCLR_OFF_RE3_ON_3H &  // Enable RE3, Disable MCLR (NOT FOR USB, BUT FOR LED)
          _LPT1OSC_OFF_3H;             // LPT1OSC = OFF (disable low-power for Timer1)
cfg(4L) = _ENHCPU_OFF_4L &   // XINST = OFF (disable extended instruction set)
          _ENICPORT_OFF_4L & // ICPRT = OFF (disable debug port)
          _STVR_ON_4L;       // STVREN = ON (reset on stack overflow)
cfg(5L) = _CP_0_OFF_5L;      // CP0 = OFF (disable code protection)
cfg(5H) = _CPD_OFF_5H &
          _CPB_OFF_5H;
cfg(6L) = _WRT_0_OFF_6L &
          _WRT_1_OFF_6L;
cfg(6H) = _WRTD_OFF_6H &
          _WRTB_OFF_6H &
          _WRTC_OFF_6H;
cfg(7L) = _EBTR_0_OFF_7L &
          _EBTR_1_OFF_7L;
cfg(7H) = _EBTRB_OFF_7H;


#pragma config T1DIG = ON
#pragma config DSBOREN = OFF
#pragma config DSWDTOSC = INTOSCREF
#pragma config RTCOSC = T1OSCREF
#pragma config DSWDTEN = OFF
#pragma config DSWDTPS = 8192
#pragma config IOL1WAY = OFF
#pragma config MSSP7B_EN = MSK7
#pragma config WPFP = PAGE_1
#pragma config WPEND = PAGE_0
#pragma config WPCFG = OFF
#pragma config WPDIS = OFF

