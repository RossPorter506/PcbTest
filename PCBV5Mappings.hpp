#ifndef PCBV4MAPPINGS
#define PCBV4MAPPINGS

#include <msp430.h>
#include "pin.hpp"
#include "dac.hpp"
#include "adc.hpp"
#include "digipot.hpp"


// Shorthand for defining Pins
#define PORT1 &P1SEL0, &P1SEL1, &P1DIR, &P1REN, &P1OUT, &P1IN
#define PORT2 &P2SEL0, &P2SEL1, &P2DIR, &P2REN, &P2OUT, &P2IN
#define PORT3 &P3SEL0, &P3SEL1, &P3DIR, &P3REN, &P3OUT, &P3IN
#define PORT4 &P4SEL0, &P4SEL1, &P4DIR, &P4REN, &P4OUT, &P4IN
#define PORT5 &P5SEL0, &P5SEL1, &P5DIR, &P5REN, &P5OUT, &P5IN
#define PORT6 &P6SEL0, &P6SEL1, &P6DIR, &P6REN, &P6OUT, &P6IN

Pin<PORT2, 1> redLEDPin;
Pin<PORT2, 2> yellowLEDPin;
Pin<PORT2, 3> greenLEDPin;

Pin<PORT4, 7> payloadSpiMisoPin;
Pin<PORT4, 6> payloadSpiMosiPin;
Pin<PORT4, 5> payloadSpiSckPin;

Pin<PORT6, 4> heaterDigipotChipSelectPin; // used to control the heater supply
Pin<PORT6, 3> dacChipSelectPin; // DAC outputs are used to control the cathode offset and tether bias supply's target voltages
Pin<PORT6, 2> tetherMeasurementADCChipSelectPin; //ADC1, measures voltages and currents from tether circuitry
Pin<PORT6, 0> boardTemperatureADCChipSelectPin; //ADC2, measures board temperatures
Pin<PORT5, 4> miscADCChipSelectPin; //ADC0, measures everything else

Pin<PORT4, 2> obcSpiMisoPin;
Pin<PORT4, 3> obcSpiMosiPin;
Pin<PORT4, 1> obcSpiSckPin;
Pin<PORT4, 0> obcSpiChipSelectPin;
Pin<PORT2, 0> OBCSpiChipSelectInterruptPin;

Pin<PORT6, 6> payloadEnablePin; // turn on tether payload devices
Pin<PORT4, 4> heaterEnablePin;
Pin<PORT3, 0> cathodeSwitchPin; // connects cathode offset+ to exterior
Pin<PORT6, 1> tetherSwitchPin; // connects tether bias+ to tether

Pin<PORT5, 2> deploySense1Pin;
Pin<PORT3, 1> deploySense2Pin;
Pin<PORT5, 3> pinpullerDeploySensePin;

Pin<PORT3, 2> burnWire1Pin;
Pin<PORT3, 3> burnWire1BackupPin;
Pin<PORT5, 0> burnWire2Pin;
Pin<PORT5, 1> burnWire2BackupPin;

Pin<PORT3, 4> tetherLMSReceiverEnablePin;
Pin<PORT3, 5> tetherLMSLEDsEnablePin;

//ADC Inputs
const Sensor repellerVoltageSensor = {TetherADC, IN0};
const Sensor heaterVoltageSensor = {TetherADC, IN1};
// Nothing on channel 2
const Sensor heaterCurrentSensor = {TetherADC, IN3};
const Sensor cathodeOffsetCurrentSensor = {TetherADC, IN4};
const Sensor tetherBiasCurrentSensor = {TetherADC, IN5};
const Sensor tetherBiasVoltageSensor = {TetherADC, IN6};
const Sensor cathodeOffsetVoltageSensor = {TetherADC, IN7};

const Sensor lmsEmitterTemperatureSensor = {TemperatureADC, IN0};
const Sensor lmsReceiverTemperatureSensor = {TemperatureADC, IN1};
const Sensor msp430TemperatureSensor = {TemperatureADC, IN2};
const Sensor heaterSupplyTemepratureSensor = {TemperatureADC, IN3};
const Sensor hvdcSuppliesTemperatureSensor = {TemperatureADC, IN4};
const Sensor tetherMonitoringTemperatureSensor = {TemperatureADC, IN5};
const Sensor tetherConnectorTemperatureSensor = {TemperatureADC, IN6};
const Sensor msp3v3RegulatorTemperatureSensor = {TemperatureADC, IN6};

const Sensor pinpullerCurrentSensor = {MiscADC, IN0};
const Sensor LMSReceiver1Sensor = {MiscADC, IN1};
const Sensor LMSReceiver2Sensor = {MiscADC, IN2};
const Sensor LMSReceiver3Sensor = {MiscADC, IN3};
const Sensor ApertureCurrentSensor = {MiscADC, IN4};
//Nothing after channel 4

//DAC Outputs
const DACChannel cathodeOffsetSupplyControlChannel = ChannelA;
const DACChannel tetherBiasSupplyControlChannel = ChannelB;

//Digipot Outputs
const DigipotChannel heaterDigipotChannel = Channel1;

#endif /* PCBV4MAPPINGS */
