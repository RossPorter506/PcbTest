#ifndef SPI_HPP
#define SPI_HPP

void initialisePeripheralSPI();
void InitialiseBitBangSPI();

void bitBangPeripheralSPI(uint8_t len, uint32_t val);


#endif /* SPI_HPP */
