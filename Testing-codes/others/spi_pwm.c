// spi_tonto.c
//
// Example program for bcm2835 library
// Shows how to interface with SPI to transfer a byte to and from an SPI device
//
// After installing bcm2835, you can build this 
// with something like:
// gcc -o spi spi.c -l bcm2835
// sudo ./spi
//
// Or you can test it before installing with:
// gcc -o spi -I ../../src ../../src/bcm2835.c spi.c
// sudo ./spi
//
// Author: Mike McCauley
// Copyright (C) 2012 Mike McCauley
// $Id: RF22.h,v 1.21 2012/05/30 01:51:25 mikem Exp $

#include "bcm2835.h"
#include <stdio.h>

// Pin asignament
#define  RESET RPI_GPIO_P1_07
#define  STBY RPI_GPIO_P1_11
#define  CONVST_A RPI_GPIO_P1_13
#define  BUSY_INT RPI_GPIO_P1_15
#define  CS RPI_GPIO_P1_26

int main(int argc, char **argv)
{
  // If you call this, it will not actually access the GPIO
  // Use for testing
  // bcm2835_set_debug(1);
  if (!bcm2835_init())
  return 1;
  // Pins asignations for ADC
  bcm2835_gpio_fsel(RESET, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(STBY, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(CONVST_A, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(CS, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(BUSY_INT, BCM2835_GPIO_FSEL_INPT);
  
  bcm2835_spi_begin();
  bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE2);                   // The default
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_8192); // The default
  bcm2835_spi_chipSelect(BCM2835_SPI_CS1 );                 // No quiero un CS
  //bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default
  // Send a byte to the slave and simultaneously read a byte back from the slave
  // If you tie MISO to MOSI, you should read back what was sent

  // Reset
  bcm2835_gpio_write(RESET, HIGH);
  bcm2835_gpio_write(CS, HIGH);
  bcm2835_gpio_write(STBY,HIGH);
  bcm2835_delay(1);
  bcm2835_gpio_write(RESET, LOW);
  printf("Iniciando rutina");
  // C31 CH_C 0 = Channel pair C disabled for next conversion (default) 1 = Channel pair C enabled
  // C30 CH_B 0 = Channel pair B disabled for next conversion (default) 1 = Channel pair B enabled
  // C29 CH_A 0 = Channel pair A disabled for next conversion (default) 1 = Channel pair A enabled
  // C28 RANGE_C 0 = Input voltage range selection for channel pair C: 4VREF (default) 1 = Input voltage range selection for channel pair C: 2VREF
  // C27 RANGE_B 0 = Input voltage range selection for channel pair B: 4VREF (default) 1 = Input voltage range selection for channel pair B: 2VREF
  // C26 RANGE_A 0 = Input voltage range selection for channel pair A: 4VREF (default) 1 = Input voltage range selection for channel pair A: 2VREF
  // C25 REF 0 = Internal reference source disabled (default) EN 1 = Internal reference source enabledx
  // C24 REFBUF 0 = Internal reference buffers enabled (default) 1 = Internal reference buffers disabled
  char conf_uno=0xFF;
  // C23 SEQ 0 = Sequential convert start mode disabled (default)  1 = Sequential convert start mode enabled (bit 11 must be '1' in this case)
  // C22 A-NAP 0 = Normal operation (default) Yes 1 = Auto-NAP feature enabled
  // C21 BUSY/INT 0 = BUSY/INT pin in normal mode (BUSY) (default) Yes 1 = BUSY/INT pin in interrupt mode (INT)
  // C20 BUSY L/H 0 = BUSY active high while INT active low (default) Yes 1 = BUSY active low while INT active high
  // C19 Don.t use This bit is always set to '0' .
  // C18 VREF 0 = Internal reference voltage: 2.5V (default) Yes 1 = Internal reference voltage: 3V
  // C17 READ_EN 0 = Normal operation (conversion results available on SDO_x) (default) Yes 1 = Control register contents output on SDO_x with next access
  // C16 C23:0_EN 0 = Control register bits C[31:24] update only (serial mode only) (default) Yes 1 = Entire control register update enabled (serial mode only)
  char conf_dos=0x03;
  // C15 PD_C 0 = Normal operation (default) Yes 1 = Power-down for channel pair C enabled (bit 31 must be '0' in this case)
  // C14 PD_B 0 = Normal operation (default) Yes 1 = Power-down for channel pair B enabled (bit 30 must be '0' in this case)
  // C13 PD_A 0 = Normal operation (default) Yes 1 = Power-down for channel pair A enabled (bit 29 must be '0' in this case)
  // C12 Don't use This bit is always '0' .
  // C11 CLKSEL 0 = Normal operation with internal conversion clock (mandatory in hardware mode) (default) No 1 = External conversion clock (applied through pin 27) used
  // C10 CLKOUT_EN 0 = Normal operation (default) No 1 = Internal conversion clock available at pin 27
  // C9 REFDAC[9] Bit 9 (MSB) of reference DAC value; default = 1 Yes
  // C8 REFDAC[8] Bit 8 of reference DAC value; default = 1 
  char conf_tres= 0xE0;
  // C7 REFDAC[7] Bit 7 of reference DAC value; default = 1 Yes
  // C6 REFDAC[6] Bit 6 of reference DAC value; default = 1 Yes
  // C5 REFDAC[5] Bit 5 of reference DAC value; default = 1 Yes
  // C4 REFDAC[4] Bit 4 of reference DAC value; default = 1 Yes
  // C3 REFDAC[3] Bit 3 of reference DAC value; default = 1 Yes
  // C2 REFDAC[2] Bit 2 of reference DAC value; default = 1 Yes
  // C1 REFDAC[1] Bit 1 of reference DAC value; default = 1 Yes
  // C0 REFDAC[0] Bit 0 (LSB) of reference DAC value; default = 1
  char conf_cuatro=0xFF;
  
  char tbuf[] ={0xff,0x03,0xe0, 0xff};
  char rbuf []={0x00, 0x00, 0x00 ,0x00};
  // char tbuf[] ="\xff\x11\x03\xff";
  // char rbuf[4];
  // Setup directives trasmition

  bcm2835_gpio_write(STBY, LOW);
  bcm2835_spi_transfernb( tbuf, rbuf, 4); //We send 4 bytes for upgrad
  bcm2835_gpio_write(STBY, HIGH);

  bcm2835_delay(100);
  uint8_t i;
  i=0;
  while(i<10)
  {
    uint8_t BUSY_LEVEL = bcm2835_gpio_lev(BUSY_INT);
    printf("\nEl nivel de busy es: %d", BUSY_LEVEL);
    bcm2835_delay(1000);
    i++;
  } 
 bcm2835_spi_end();
  bcm2835_close();
  return 0;
}
