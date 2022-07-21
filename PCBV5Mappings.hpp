#ifndef PCBV5MAPPINGS
#define PCBV5MAPPINGS

#include <msp430.h>
#include "pin.hpp"
#include "dac.hpp"
#include "adc.hpp"
#include "digipot.hpp"
#include <math.h>

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
const VoltageSensor repellerVoltageSensor = {TetherADC, IN0};
const VoltageSensor heaterVoltageSensor = {TetherADC, IN1};
// Nothing on channel 2
const CurrentSensor heaterCurrentSensor = {TetherADC, IN3};
const CurrentSensor cathodeOffsetCurrentSensor = {TetherADC, IN4};
const CurrentSensor tetherBiasCurrentSensor = {TetherADC, IN5};
const VoltageSensor tetherBiasVoltageSensor = {TetherADC, IN6};
const VoltageSensor cathodeOffsetVoltageSensor = {TetherADC, IN7};

const LMSTemperatureSensor lmsEmitterTemperatureSensor = {TemperatureADC, IN0};
const LMSTemperatureSensor lmsReceiverTemperatureSensor = {TemperatureADC, IN1};
const PayloadTemperatureSensor msp430TemperatureSensor = {TemperatureADC, IN2};
const PayloadTemperatureSensor heaterSupplyTemepratureSensor = {TemperatureADC, IN3};
const PayloadTemperatureSensor hvdcSuppliesTemperatureSensor = {TemperatureADC, IN4};
const PayloadTemperatureSensor tetherMonitoringTemperatureSensor = {TemperatureADC, IN5};
const PayloadTemperatureSensor tetherConnectorTemperatureSensor = {TemperatureADC, IN6};
const PayloadTemperatureSensor msp3v3RegulatorTemperatureSensor = {TemperatureADC, IN6};

const CurrentSensor pinpullerCurrentSensor = {MiscADC, IN0};
const VoltageSensor LMSReceiver1Sensor = {MiscADC, IN1};
const VoltageSensor LMSReceiver2Sensor = {MiscADC, IN2};
const VoltageSensor LMSReceiver3Sensor = {MiscADC, IN3};
const CurrentSensor ApertureCurrentSensor = {MiscADC, IN4};
//Nothing after channel 4

//DAC output channels
const DACChannel cathodeOffsetSupplyControlChannel = ChannelC;
const DACChannel tetherBiasSupplyControlChannel = ChannelD;

//Digipot output channels
const DigipotChannel heaterDigipotChannel = Channel1;

/* Sensor equations. Takes in the voltage reported at the ADC (in millivolts) and produces the voltage/current being sensed in millivolts/milliamps */

#define HEATER_VOLTAGE_EQ(v) (((int32_t)(v)*6200)/3000)
#define REPELLER_VOLTAGE_EQ(v) (((int32_t)(v)-2755)*102)
//#define REPELLER_VOLTAGE_EQ(v) ((((int32_t)(v)-98)*5000)/101000) // old
#define TETHER_BIAS_VOLTAGE_EQ(v) ((int32_t)(v)*106 + 805) 	//NOTE: Protection zener diode makes conversions non-linear at the high end,
															//This is not accounted for here. Check ADC Signal processing document for details
#define CATHODE_OFFSET_VOLTAGE_EQ(v) ((v)*-85.75+400430) //NOTE: Protection zener diode makes conversions non-linear at the high end.
																//This is not accounted for here. Check ADC Signal processing document for details

#define HEATER_CURRENT_EQ(v) ((v)/5) // TODO: Check this is correct
#define TETHER_BIAS_CURRENT_EQ(v) ((((int32_t)(v) - 1000) * 19608)/100000)
#define CATHODE_OFFSET_CURRENT_EQ(v) ((((int32_t)(v) - 2500) * 500) / 1000)

//Returns temperature in Kelvin
#define PAYLOAD_TEMPERATURE_EQ(v) 	(1028100/( 705+298*(uint32_t)(v)*10000/(5000-log(v)) )) //uses standard math lib for log, there are definitely better ways of doing this
#define LMS_TEMPERATURE_EQ(v) 		(1028100/( 705+298*(uint32_t)(v)*10000/(3300-log(v)) )) //uses standard math lib for log, there are definitely better ways of doing this

/* Supply maximums */
#define HEATER_MAX_VOLTAGE_MILLIVOLTS 12000
#define CATHODE_OFFSET_MAX_VOLTAGE_MILLIVOLTS 2550000
#define TETHER_BIAS_MAX_VOLTAGE_MILLIVOLTS 255000

/* Supply control equations */

//Takes in a target voltage (in millivolts) for the heater and calculates what resistance the digipot should be set to
#define HEATER_TARGET_VOLTAGE_TO_DIGIPOT_RESISTANCE(v) ( 75000 / (((float)v)/810 - 1) ) //float necessary for accuracy reasons

//Takes in a target voltage (in millivolts) for the tether bias / cathode offset supplies and determines what voltage the DAC needs to be set to.
#define TETHER_BIAS_TARGET_VOLTAGE_TO_DAC_VOLTAGE(v) ((v)/51)
#define CATHODE_OFFSET_TARGET_VOLTAGE_TO_DAC_VOLTAGE(v) ((v)/51)

#define ADC_VCC_VOLTAGE_MILLIVOLTS 5000
#define DAC_VCC_VOLTAGE_MILLIVOLTS 5000

#endif /* PCBV5MAPPINGS */
