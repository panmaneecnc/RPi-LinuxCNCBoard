/**   Copyright (C) 2013 Rodolfo Boris Oporto Quisbert
*
*    This file is part of rpi_rboq project
*
*    This program is free software; you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation; either version 2 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software
*    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
*/

#include "ads8556.h"
#include <endian.h>


int configADS8556(  )
{
	if (!bcm2835_init()){
	  printf("Problems SPI");
	  return 1;
	}
	bcm2835_gpio_fsel(RESET_ADC, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(STBY_ADC, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(CONVST_A_ADC, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(BUSY_INT_ADC, BCM2835_GPIO_FSEL_INPT);
	
	// Reset
	//bcm2835_gpio_write(RESET, HIGH);
	bcm2835_gpio_write(STBY_ADC,HIGH);
	//bcm2835_delay(1);
	bcm2835_gpio_write(RESET_ADC, LOW);
	
	bcm2835_spi_begin();
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST); // The default
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE2);            // The default revisar el modo de cuncionamiento del integrado          
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_32); // Review this code
	bcm2835_spi_chipSelect(BCM2835_SPI_CS1);                     // CS_0 	
	
}                         

uint16_t readChannel(uint8_t channel, uint32_t control_register)
{
	uint16_t* results;
	results= readAllChannels(&control_register);
	//return results[channel];
	return (results+channel);
}   

uint16_t *arrange(uint16_t * buffer)
{
	uint8_t buffer_ret[12];
	int i;
	for(i=0; i<12; i++)
	{
		if(i%2){
			buffer_ret[i]=(uint8_t)((buffer[(i/2)-1]&0xFF00)>>8);
		}
		else
		{
			buffer_ret[i]=(uint8_t)((buffer[i/2]&0x00FF)<<8);
		}
	}
	return buffer_ret;
}

uint16_t *readAllChannels(uint32_t control_register)
{
    
	uint32_t buffer[3];
	
	bcm2835_gpio_write(CONVST_A_ADC, HIGH);
	// Para busy control
	uint8_t busy;
	busy=HIGH;
	while(busy==HIGH)
	{
			busy=bcm2835_gpio_lev(BUSY_INT_ADC);
	}
	
	int j;
	for(j=0; j<3; j++){
	    bcm2835_spi_transfernb(control_register, &buffer[j], 4);
	}
	
	bcm2835_gpio_write(CONVST_A_ADC, LOW);	
	
	uint16_t buffer_ret[6];
	for(j=0; j<6; j++)
	{
		if(j%2)
		{
			buffer_ret[j]=((buffer[(j-1)/2] & 0xff000000UL)>>24) | ((buffer[(j-1)/2] & 0x00ff0000UL)>>8) ;
		}
		else
		{
			buffer_ret[j]=((buffer[j/2] & 0x0000ff00UL)>>8) | ((buffer[j/2] & 0x000000ffUL)<<8);//(buffer[(j)/2] );//& 0xffff0000UL)>> 16;
		}
		
	}
	
	return buffer_ret;	
}



	
char* updateFullCR(char* control_register)
{
	char control_readed[4];
	bcm2835_spi_transfernb(control_register,control_readed,4); 
	//bcm2835_spi_transfernb(control_register, ret, 4);
	return control_readed;
}

void updatePartialCR(uint32_t control_register)
{
	bcm2835_spi_writenb(control_register,1);
}

/*uint16_t *readTest(uint32_t control_register)
{
	//char buffer[3][2] ;
	uint16_t *
	bcm2835_gpio_write(CONVST_A, HIGH);
	
	uint8_t busy;
	busy=HIGH;
	while(busy==HIGH)
	{
		busy=bcm2835_gpio_lev(BUSY_INT);
	}
	//bcm2835_gpio_clr_ren(BUSY_INT);
	//while(bcm2835_gpio_eds(BUSY_INT)==LOW);
	//bcm2835_gpio_fen(BUSY_INT); 	
	//while(bcm2835_gpio_eds(BUSY_INT)==LOW);		
	
	int i;
	for(i=0; i<6; i++){
	  bcm2835_spi_transfernb(control_register, *buffer[i], 4); 
	}
	
	bcm2835_gpio_write(CONVST_A, LOW);
	
	for(i=0; i<)
}
*/


