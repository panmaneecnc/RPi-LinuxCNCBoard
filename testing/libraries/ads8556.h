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
#ifndef ADS8556_h
#define ADS8556_h

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

    int configADS8556();                           
    uint16_t readChannel(uint8_t, uint32_t);   
    uint16_t *readAllChannels(uint32_t);        
    char* updateFullCR(char*);          
    void updatePartialCR(uint32_t);              

#endif //ADS8556.H
