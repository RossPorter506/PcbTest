/*
 * pin.hpp
 *
 *  Created on: 24/08/2021
 *      Author: ross
 */

#ifndef PIN_HPP_
#define PIN_HPP_
#include <stdint.h>

template< volatile uint8_t* direction, volatile uint8_t* port, uint8_t pin >
struct Pin {
    static Pin setAsOutput() {
       *direction |= (1 << pin);
       return Pin<direction, port, pin>(); // for operator chaining
    }
    static Pin setAsInput() {
       *direction &= ~(1 << pin);
       return Pin<direction, port, pin>(); // for operator chaining
    }
    static Pin ToggleDirection(){
       *direction ^= (1 << pin);
       return Pin<direction, port, pin>();
    }
    static Pin set() {
      *port |= (1 << pin);
      return Pin<direction, port, pin>();
    }
    static Pin clear() {
      *port &= ~(1 << pin);
      return Pin<direction, port, pin>();
    }
    static Pin toggle() {
        *port ^= (1 << pin);
        return Pin<direction, port, pin>();
    }
    static bool isHigh() {
        return (*port) & (1 << pin);
    }
    static bool isLow() {
        return !((*port) & (1 << pin));
    }
};

#endif /* PIN_HPP_ */
