#include <mcp23s17.h>
#include <bcm2835.h>

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

#define  RESET RPI_GPIO_P1_07
#define  STBY RPI_GPIO_P1_11
#define  CONVST_A RPI_GPIO_P1_13
#define  BUSY_INT RPI_GPIO_P1_15
//#define  CS RPI_GPIO_P1_26

void configADS8556( )
{
	bcm2835_gpio_fsel(RESET, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(STBY, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(CONVST_A, BCM2835_GPIO_FSEL_OUTP);
	//bcm2835_gpio_fsel(CS, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(BUSY_INT, BCM2835_GPIO_FSEL_INPT);
	
	bcm2835_spi_begin();
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);     // The default
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                  // The default revisar el modo de cuncionamiento del integrado
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_16); // Review this code
	bcm2835_spi_chipSelect(BCM2835_SPI_CS1);                     // CS_0 	
	
	// Aquí el resto de pines
	
}                         

uint16_t readChannel(uint8_t channel)
{
	uint16_t* results;
	results= readAllChannels();
	return results[channel];
	
}   

uint32_t* readAllChannels(uint32_t control_register)
{
	uint32_t buffer [3];
	
	bcm2835_gpio_write(CONVST_A, HIGH);
	while(bcm2835_gpio_lev(BUSY_INT)); // waiting until device is not busy
	int i;
	for(i=0; i<3; i++){
		bcm2835_spi_transfernb(control_register,(*buffer+1),4); 
	}
	
	bcm2835_gpio_write(CONVST_A, LOW);

	return buffer;	
}

void updateFullCR(uint32_t control_register)
{
	bcm2835_spi_writenb(control_register,4); 
}

void updatePartialCR(uint32_t control_register)
{
	bcm2835_spi_writenb(control_register,1);
}
