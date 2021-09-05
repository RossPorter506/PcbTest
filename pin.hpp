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
    static void setAsOutput() {
       *direction |= (1 << pin);
    }
    static void setAsInput() {
       *direction &= ~(1 << pin);
    }
    static void ToggleDirection(){
       *direction ^= (1 << pin);
    }
    static void set() {
      *port |= (1 << pin);
    }
    static void clear() {
      *port &= ~(1 << pin);
    }
    static void toggle() {
        *port ^= (1 << pin);
    }
    static bool isHigh() {
        return (*port) & (1 << pin);
    }
    static bool isLow() {
        return !((*port) & (1 << pin));
    }
};

#endif /* PIN_HPP_ */
