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

#define PIN_PARAMS functionMSB, functionLSB, direction, port, pin

template< volatile uint8_t* functionMSB, volatile uint8_t* functionLSB, volatile uint8_t* direction, volatile uint8_t* port, uint8_t pin >
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
    static Pin setAsOutput() {
       *direction |= (1 << pin);
       return Pin<PIN_PARAMS>(); // for operator chaining
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
      *port |= (1 << pin);
      return Pin<PIN_PARAMS>();
    }
    static Pin clear() {
      *port &= ~(1 << pin);
      return Pin<PIN_PARAMS>();
    }
    static Pin toggle() {
        *port ^= (1 << pin);
        return Pin<PIN_PARAMS>();
    }
    static bool isHigh() {
        return (*port) & (1 << pin);
    }
    static bool isLow() {
        return !((*port) & (1 << pin));
    }
};

#endif /* PIN_HPP_ */
