#include <mcp23s17.h>

#define    HIGH          (1)
#define    LOW           (0)
#define    ON            (1)
#define    OFF           (0)
#define    OUTPUT        (0)
#define    INPUT         (1)

// Here we have things for the SPI bus configuration

#define    CLOCK_DIVIDER (2)           // SPI bus speed to be 1/2 of the processor clock speed - 8MHz on most Arduinos
#define    SS            (10)          // SPI bus slave select output to pin 10 - READ ARDUINO SPI DOCS BEFORE CHANGING!!!

// Control byte and configuration register information - Control Byte: "0100 A2 A1 A0 R/W" -- W=0

#define    OPCODEW       (0b01000000)  // Opcode for MCP23S17 with LSB (bit0) set to write (0), address OR'd in later, bits 1-3
#define    OPCODER       (0b01000001)  // Opcode for MCP23S17 with LSB (bit0) set to read (1), address OR'd in later, bits 1-3
#define    ADDR_ENABLE   (0b00001000)  // Configuration register for MCP23S17, the only thing we change is enabling hardware addressing


void configMCP23s17(uint8_t address)
{
  // If you call this, it will not actually access the GPIO
  // Use for testing
  // bcm2835_set_debug(1);
    while(!bcm2835_init());
    //return 1;
	_address     = address;
	_modeCache   = 0xFFFF;                // Default I/O mode is all input, 0xFFFF
	_outputCache = 0x0000;                // Default output state is all off, 0x0000
	_pullupCache = 0xFFFF;                // Default pull-up state is all off, 0x0000
	_invertCache = 0x0000;                // Default input inversion state is not inverted, 0x0000
	bcm2835_spi_begin();
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);     // The default
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                  // The default revisar el modo de cuncionamiento del integrado
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_16); // Review this code
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                     // CS_0 
	
}

void wordWrite(uint8_t reg, unsigned int word) {  // Accept the start register and word 
  ////configMCP23s17();
  ////PORTB &= 0b11111011;                            // Direct port manipulation speeds taking Slave Select LOW before SPI action 
  char buff[]= {((char)(OPCODEW | (_address << 1))), ((char)reg), ((char)(word)), ((char)(word >> 8))};
  //bcm2835_spi_transfer(OPCODEW | (_address << 1));// Send the MCP23S17 opcode, chip address, and write bit
  //bcm2835_spi_transfer(reg);                      // Send the register we want to write 
  //bcm2835_spi_transfer((uint8_t) (word));         // Send the low byte (register address pointer will auto-increment after write)
  //bcm2835_spi_transfer((uint8_t) (word >> 8));    // Shift the high byte down to the low byte location and send
  bcm2835_spi_transfern(buff, 4);
  ////PORTB |= 0b00000100;                            // Direct port manipulation speeds taking Slave Select HIGH after SPI action
  ////bcm2835_spi_end();

}

void byteWrite(uint8_t reg, uint8_t value) {      // Accept the register and byte
  //configMCP23s17();
  //PORTB &= 0b11111011;                            // Direct port manipulation speeds taking Slave Select LOW before SPI action
  char buff[]= {((char)(OPCODEW | (_address << 1))), ((char)reg), ((char)value)};
  //bcm2835_spi_transfer(OPCODEW | (_address << 1));// Send the MCP23S17 opcode, chip address, and write bit
  //bcm2835_spi_transfer(reg);                      // Send the register we want to write
  //bcm2835_spi_transfer(value);                    // Send the byte
   bcm2835_spi_transfern(buff, 3);
  //PORTB |= 0b00000100;                            // Direct port manipulation speeds taking Slave Select HIGH after SPI action
  //bcm2835_spi_end(); 	
}

void pinMode_bit(uint8_t pin, uint8_t mode) {  // Accept the pin # and I/O mode
  if (pin < 1 | pin > 16) return;               // If the pin value is not valid (1-16) return, do nothing and return
  if (mode == INPUT) {                          // Determine the mode before changing the bit state in the mode cache
    _modeCache |= 1 << (pin - 1);               // Since input = "HIGH", OR in a 1 in the appropriate place
  } else {
    _modeCache &= ~(1 << (pin - 1));            // If not, the mode must be output, so and in a 0 in the appropriate place
  }
  wordWrite(IODIRA, _modeCache);                // Call the generic word writer with start register and the mode cache
}

void pinMode_word(unsigned int mode) {         // Accept the wordÉ
  wordWrite(IODIRA, mode);                // Call the the generic word writer with start register and the mode cache
  _modeCache = mode;
}

void pullupMode_bit(uint8_t pin, uint8_t mode) {
  if (pin < 1 | pin > 16) return;
  if (mode == ON) {
    _pullupCache |= 1 << (pin - 1);
  } else {
    _pullupCache &= ~(1 << (pin -1));
  }
  wordWrite(GPPUA, _pullupCache);
}

void pullupMode_word(unsigned int mode) { 
  wordWrite(GPPUA, mode);
  _pullupCache = mode;
}


// INPUT INVERSION SETTING FUNCTIONS - BY WORD AND BY PIN

void inputInvert_bit(uint8_t pin, uint8_t mode) {
  if (pin < 1 | pin > 16) return;
  if (mode == ON) {
    _invertCache |= 1 << (pin - 1);
  } else {
    _invertCache &= ~(1 << (pin - 1));
  }
  wordWrite(IPOLA, _invertCache);
}

void inputInvert_word(unsigned int mode) { 
  wordWrite(IPOLA, mode);
  _invertCache = mode;
}


// WRITE FUNCTIONS - BY WORD AND BY PIN

void digitalWrite_bit(uint8_t pin, uint8_t value) {
  if (pin < 1 | pin > 16) return;
  if (pin < 1 | pin > 16) return;
  if (value) {
    _outputCache |= 1 << (pin - 1);
  } else {
    _outputCache &= ~(1 << (pin - 1));
  }
  wordWrite(GPIOA, _outputCache);
}

void digitalWrite_word(unsigned int value) { 
  wordWrite(GPIOA, value);
  _outputCache = value;
}


// READ FUNCTIONS - BY WORD, BYTE AND BY PIN

unsigned int digitalRead_word(void) {       // This function will read all 16 bits of I/O, and return them as a word in the format 0x(//PORTB)(portA)
  //configMCP23s17();
  unsigned int value = 0;                   // Initialize a variable to hold the read values to be returned
  //PORTB &= 0b11111011;                      // Direct port manipulation speeds taking Slave Select LOW before SPI action
  
  //bcm2835_spi_transfer(OPCODER | (_address << 1));  // Send the MCP23S17 opcode, chip address, and read bit
  //bcm2835_spi_transfer(GPIOA);                      // Send the register we want to read
  //value = bcm2835_spi_transfer(0x00);               // Send any byte, the function will return the read value (register address pointer will auto-increment after write)
  //value |= (bcm2835_spi_transfer(0x00) << 8);       // Read in the "high byte" (//PORTB) and shift it up to the high location and merge with the "low byte"
  char buff[]= {((char)(OPCODER | (_address << 1))), ((char)GPIOA)}; 
  bcm2835_spi_transfern(buff, 2);
  //PORTB |= 0b00000100;                      // Direct port manipulation speeds taking Slave Select HIGH after SPI action
  //bcm2835_spi_end();
    // REvisar esto para ver que funcione
	return value;                             // Return the constructed word, the format is 0x(//PORTB)(portA) 
}

uint8_t byteRead(uint8_t reg) {        // This function will read a single register, and return it
  //configMCP23s17();
  uint8_t value = 0;                        // Initialize a variable to hold the read values to be returned
  //PORTB &= 0b11111011;                      // Direct port manipulation speeds taking Slave Select LOW before SPI action
  bcm2835_spi_transfer(OPCODER | (_address << 1));  // Send the MCP23S17 opcode, chip address, and read bit
  bcm2835_spi_transfer(reg);                        // Send the register we want to read
  value = bcm2835_spi_transfer(0x00);               // Send any byte, the function will return the read value
  //PORTB |= 0b00000100;                      // Direct port manipulation speeds taking Slave Select HIGH after SPI action
  //bcm2835_spi_end();
  return value;                             // Return the constructed word, the format is 0x(register value)
}

uint8_t digitalRead_bit(uint8_t pin) {              // Return a single bit value, supply the necessary bit (1-16)
    if (pin < 1 | pin > 16) return 0x0;                  // If the pin value is not valid (1-16) return, do nothing and return
    return digitalRead_word() & (1 << (pin - 1)) ? HIGH : LOW;  // Call the word reading function, extract HIGH/LOW information from the requested pin
}

