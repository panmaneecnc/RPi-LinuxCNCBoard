#ifndef ADS8556_h
#define ADS8556_h

// MACROSS for control register

#define CH_A0 0
#define CH_A1 1
#define CH_B0 2
#define CH_B1 3
#define CH_C0 4
#define CH_C1 5

#define  RESET_ADC RPI_V2_GPIO_P1_07
#define  STBY_ADC RPI_V2_GPIO_P1_11
#define  CONVST_A_ADC RPI_V2_GPIO_P1_13
#define  BUSY_INT_ADC RPI_V2_GPIO_P1_15

#include <bcm2835.h>

    int configADS8556();                            // Constructor to instantiate a discrete IC as an object, argument is the address (0-7) of the MCP23S17
    uint16_t readChannel(uint8_t, uint32_t);   // Typically only used internally, but allows the user to write any register pair if needed, so it's public
    uint16_t *readAllChannels(uint32_t);        // Typically only used internally, but allows the user to write any register if needed, so it's public
    char* updateFullCR(char*);          // Sets the mode (input or output) of a single I/O pin
    void updatePartialCR(uint32_t);              // Sets the mode (input or output) of all I/O pins at once 

#endif //ADS8556.H
