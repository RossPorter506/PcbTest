#ifndef PCBV4MAPPINGS
#define PCBV4MAPPINGS

#include <msp430.h>
#include "pin.hpp"


// Shorthand for defining Pins
#define PORT1 &P1SEL0, &P1SEL1, &P1DIR, &P1OUT, &P1IN
#define PORT2 &P2SEL0, &P2SEL1, &P2DIR, &P2OUT, &P2IN
#define PORT3 &P3SEL0, &P3SEL1, &P3DIR, &P3OUT, &P3IN
#define PORT4 &P4SEL0, &P4SEL1, &P4DIR, &P4OUT, &P4IN
#define PORT5 &P5SEL0, &P5SEL1, &P5DIR, &P5OUT, &P5IN
#define PORT6 &P6SEL0, &P6SEL1, &P6DIR, &P6OUT, &P6IN

Pin<PORT2, 1> redLED;
Pin<PORT2, 2> yellowLED;
Pin<PORT2, 3> greenLED;

Pin<PORT4, 7> payloadSpiMiso;
Pin<PORT4, 6> payloadSpiMosi;
Pin<PORT4, 5> payloadSpiSck;

Pin<PORT6, 4> heaterDigipotChipSelect; // used to control the heater supply
Pin<PORT6, 3> dacChipSelect; // DAC outputs are used to control the cathode offset and tether bias supply's target voltages
Pin<PORT6, 2> tetherMeasurementADCChipSelect; //ADC1, measures voltages and currents from tether circuitry
Pin<PORT6, 0> boardTemperatureADCChipSelect; //ADC2, measures board temperatures
Pin<PORT5, 4> miscADCChipSelect; //ADC0, measures everything else

Pin<PORT4, 2> obcSpiMiso;
Pin<PORT4, 3> obcSpiMosi;
Pin<PORT4, 1> obcSpiSck;
Pin<PORT4, 0> obcSpiChipSelect;
Pin<PORT2, 0> OBCSpiChipSelectInterrupt;

Pin<PORT6, 6> payloadEnable; // turn on tether payload devices
Pin<PORT4, 4> heaterEnable;
Pin<PORT3, 0> cathodeSwitch; // connects cathode offset+ to exterior
Pin<PORT6, 1> tetherSwitch; // connects tether bias+ to tether

Pin<PORT5, 2> deploySense1;
Pin<PORT3, 1> deploySense2;
Pin<PORT5, 3> pinpullerDeploySense;

Pin<PORT3, 2> burnWire1;
Pin<PORT3, 3> burnWire1Backup;
Pin<PORT5, 0> burnWire2;
Pin<PORT5, 1> burnWire2Backup;

Pin<PORT3, 4> tetherLMSReceiverEnable;
Pin<PORT3, 5> tetherLMSLEDsEnable;

#endif /* PCBV4MAPPINGS */
