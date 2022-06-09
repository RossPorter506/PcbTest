#ifndef PCBV5MAPPINGS
#define PCBV5MAPPINGS

#include "pin.hpp"

Pin<&P2DIR, &P2OUT, 1> redLED;
Pin<&P2DIR, &P2OUT, 2> yellowLED;
Pin<&P2DIR, &P2OUT, 3> greenLED;

Pin<&P4DIR, &P4OUT, 7> payloadSpiMiso;
Pin<&P4DIR, &P4OUT, 6> payloadSpiMosi;
Pin<&P4DIR, &P4OUT, 5> payloadSpiSck;

Pin<&P4DIR, &P4OUT, 4> emitterEnable;

#endif /* PCBV5MAPPINGS */
