#ifndef SPI_HPP
#define SPI_HPP

enum ClockMode {
	DataOnRisingEdge,
	DataOnFallingEdge,
};

void initialisePeripheralSPI();
void InitialiseBitBangSPI();

void bitBangPeripheralSPISend(uint8_t len, uint32_t val);
uint32_t bitBangPeripheralSPIReceive(uint8_t len);
uint32_t bitBangPeripheralSPIDuplex(uint8_t len, uint32_t val);

#endif /* SPI_HPP */
