/*
 * pin.hpp
 *
 *  Created on: 24/08/2021
 *      Author: ross
 */

#ifndef PIN_HPP_
#define PIN_HPP_
#include <stdint.h>

enum PinFunction{
    gpio = 0,
    primary = 1,
    secondary = 2,
    tertiary = 3
};

#define PIN_PARAMS functionMSB, functionLSB, direction, pullResistorEnable, portOut, portIn, pin

template< volatile uint8_t* functionMSB, volatile uint8_t* functionLSB, volatile uint8_t* direction, volatile uint8_t* pullResistorEnable, volatile uint8_t* portOut, volatile uint8_t* portIn, uint8_t pin>
struct Pin {
    static Pin setFunction(PinFunction fn) {
        switch(fn){
        case gpio:
            *functionMSB &= ~pin;
            *functionLSB &= ~pin;
            break;
        case primary:
            *functionMSB &= ~pin;
            *functionLSB |= pin;
            break;
        case secondary:
            *functionMSB |= pin;
            *functionLSB &= ~pin;
            break;
        case tertiary:
            *functionMSB |= pin;
            *functionLSB |= pin;
            break;
        default: break;
        }
       return Pin<PIN_PARAMS>(); // for operator chaining
    }
    static PinFunction getCurrentFunction() {
    	bool primaryFn = !!(*functionMSB & (1 << pin));
    	bool secondaryFn = !!(*functionLSB & (1 << pin));
    	if (primaryFn && secondaryFn){
    		return tertiary;
    	}
    	else if (primaryFn && !secondaryFn){
    		return secondary;
    	}
    	else if (!primaryFn && secondaryFn){
			return primary;
		}
    	else {
    		return gpio;
    	}
    }
    static bool isOutput() {
		return (*direction & (1 << pin));
	}
    static bool isInput() {
		return !(*direction & (1 << pin));
	}
    static Pin setAsOutput() {
       *direction |= (1 << pin);
       return Pin<PIN_PARAMS>();
    }
    static Pin setAsInput() {
       *direction &= ~(1 << pin);
       return Pin<PIN_PARAMS>();
    }
    static Pin ToggleDirection(){
       *direction ^= (1 << pin);
       return Pin<PIN_PARAMS>();
    }
    static Pin set() {
      *portOut |= (1 << pin);
      return Pin<PIN_PARAMS>();
    }
    static Pin clear() {
      *portOut &= ~(1 << pin);
      return Pin<PIN_PARAMS>();
    }
    static Pin setToValue(bool value) {
		if (value){
			*portOut |= (1 << pin);
		}
		else{
			*portOut &= ~(1 << pin);
		}
		return Pin<PIN_PARAMS>();
	}
    static Pin toggle() {
        *portOut ^= (1 << pin);
        return Pin<PIN_PARAMS>();
    }
    static bool isHigh() {
        return (*portIn) & (1 << pin);
    }
    static bool isLow() {
        return !((*portIn) & (1 << pin));
    }
    static bool value() {
		return (*portIn) & (1 << pin);
	}
};

#endif /* PIN_HPP_ */
