#ifndef PCBV4MAPPINGS
#define PCBV4MAPPINGS

#include "pin.hpp"

// Shorthand
#define PORT1 &P1SEL0, &P1SEL1, &P1DIR, &P1OUT
#define PORT2 &P2SEL0, &P2SEL1, &P2DIR, &P2OUT
#define PORT3 &P3SEL0, &P3SEL1, &P3DIR, &P3OUT
#define PORT4 &P4SEL0, &P4SEL1, &P4DIR, &P4OUT
#define PORT5 &P5SEL0, &P5SEL1, &P5DIR, &P5OUT
#define PORT6 &P6SEL0, &P6SEL1, &P6DIR, &P6OUT

Pin<PORT2, 1> redLED;
Pin<PORT2, 2> yellowLED;
Pin<PORT2, 3> greenLED;

Pin<PORT4, 7> payloadSpiMiso;
Pin<PORT4, 6> payloadSpiMosi;
Pin<PORT4, 5> payloadSpiSck;

Pin<PORT4, 4> emitterEnable;

#endif /* PCBV4MAPPINGS */
