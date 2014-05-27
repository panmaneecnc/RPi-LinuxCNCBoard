/*    Copyright (C) 2013 GP Orcullo
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

#ifndef PICNC_H
#define PICNC_H

#define SPICLKDIV_8		8	/* ~31.25MHz */
#define SPICLKDIV_16	16	/* 15.625MHz */
#define SPICLKDIV_32	32	/* ~7.8125MHz */
#define SPICLKDIV_64	64	/* ~3.90625MHz */

#define NUMAXES			4		/* X Y Z A */

#define REQ_TIMEOUT		10000ul

#define SPIBUFSIZE		32		/* SPI buffer size */
#define BUFSIZE			(SPIBUFSIZE/4)

#define STEPBIT			23		/* bit location in DDS accum */
#define STEP_MASK		(1<<STEPBIT)

#define BASEFREQ		160000ul	/* Base freq of the PIC stepgen in Hz */
#define SYS_FREQ		(80000000ul)    /* 80 MHz */

#define PERIODFP 		((double)1.0 / (double)(BASEFREQ))
#define VELSCALE		((double)STEP_MASK * PERIODFP)
#define ACCELSCALE		(VELSCALE * PERIODFP)

#define get_position(a)		(rxBuf[1 + (a)])
#define get_inputs()		(rxBuf[1 + NUMAXES])
#define set_outputs		(txBuf[1 + NUMAXES])
#define get_adc(a)		(rxBuf[2 + NUMAXES + a])
#define update_velocity(a, b)	(txBuf[1 + (a)] = (b))

/* Broadcom defines */

#define BCM2835_PERI_BASE	0x20000000
#define BCM2835_GPIO_BASE	(BCM2835_PERI_BASE + 0x200000) /* GPIO controller */
#define BCM2835_SPI_BASE	(BCM2835_PERI_BASE + 0x204000) /* SPI controller */

#define BCM2835_GPFSEL0		*(gpio)
#define BCM2835_GPFSEL1		*(gpio + 1)
#define BCM2835_GPFSEL2		*(gpio + 2)
#define BCM2835_GPFSEL3		*(gpio + 3)
#define BCM2835_GPFSEL4		*(gpio + 4)
#define BCM2835_GPFSEL5		*(gpio + 5)
#define BCM2835_GPSET0		*(gpio + 7)
#define BCM2835_GPSET1		*(gpio + 8)
#define BCM2835_GPCLR0		*(gpio + 10)
#define BCM2835_GPCLR1		*(gpio + 11)
#define BCM2835_GPLEV0		*(gpio + 13)
#define BCM2835_GPLEV1		*(gpio + 14)
#define BCM2835_GPEDS0		*(gpio + 16)
#define BCM2835_GPEDS1		*(gpio + 17)
#define BCM2835_GPREN0		*(gpio + 19)
#define BCM2835_GPREN1		*(gpio + 20)
#define BCM2835_GPFEN0		*(gpio + 22)
#define BCM2835_GPFEN1		*(gpio + 23)
#define BCM2835_GPAREN0		*(gpio + 31)
#define BCM2835_GPAREN1		*(gpio + 32)
#define BCM2835_GPAFEN0		*(gpio + 34)
#define BCM2835_GPAFEN1		*(gpio + 35)


#define BCM2835_SPICS 		*(spi + 0)
#define BCM2835_SPIFIFO     *(spi + 1)
#define BCM2835_SPICLK 		*(spi + 2)


#define SPI_CS_LEN_LONG		0x02000000
#define SPI_CS_DMA_LEN		0x01000000
#define SPI_CS_CSPOL2		0x00800000
#define SPI_CS_CSPOL1		0x00400000
#define SPI_CS_CSPOL0		0x00200000
#define SPI_CS_RXF		0x00100000
#define SPI_CS_RXR		0x00080000
#define SPI_CS_TXD		0x00040000
#define SPI_CS_RXD		0x00020000
#define SPI_CS_DONE		0x00010000
#define SPI_CS_LEN		0x00002000
#define SPI_CS_REN		0x00001000
#define SPI_CS_ADCS		0x00000800
#define SPI_CS_INTR		0x00000400
#define SPI_CS_INTD		0x00000200
#define SPI_CS_DMAEN		0x00000100
#define SPI_CS_TA		0x00000080
#define SPI_CS_CSPOL		0x00000040
#define SPI_CS_CLEAR_RX		0x00000020
#define SPI_CS_CLEAR_TX		0x00000010
#define SPI_CS_CPOL		0x00000008
#define SPI_CS_CPHA		0x00000004
#define SPI_CS_CS_10		0x00000002
#define SPI_CS_CS_01		0x00000001
#define SPI_CS_CS_00		0x00000000

#define PAGE_SIZE		(4*1024)
#define BLOCK_SIZE		(4*1024)

/*MCP23s17 deffinitions*/

#define    IODIRA    (0x00)      // MCP23x17 I/O Direction Register
#define    IODIRB    (0x01)      // 1 = Input (default), 0 = Output

#define    IPOLA     (0x02)      // MCP23x17 Input Polarity Register
#define    IPOLB     (0x03)      // 0 = Normal (default)(low reads as 0), 1 = Inverted (low reads as 1)

#define    GPINTENA  (0x04)      // MCP23x17 Interrupt on Change Pin Assignements
#define    GPINTENB  (0x05)      // 0 = No Interrupt on Change (default), 1 = Interrupt on Change

#define    DEFVALA   (0x06)      // MCP23x17 Default Compare Register for Interrupt on Change
#define    DEFVALB   (0x07)      // Opposite of what is here will trigger an interrupt (default = 0)

#define    INTCONA   (0x08)      // MCP23x17 Interrupt on Change Control Register
#define    INTCONB   (0x09)      // 1 = pin is compared to DEFVAL, 0 = pin is compared to previous state (default)

#define    IOCON     (0x0A)      // MCP23x17 Configuration Register
//                   (0x0B)      //     Also Configuration Register

#define    GPPUA     (0x0C)      // MCP23x17 Weak Pull-Up Resistor Register
#define    GPPUB     (0x0D)      // INPUT ONLY: 0 = No Internal 100k Pull-Up (default) 1 = Internal 100k Pull-Up 

#define    INTFA     (0x0E)      // MCP23x17 Interrupt Flag Register
#define    INTFB     (0x0F)      // READ ONLY: 1 = This Pin Triggered the Interrupt

#define    INTCAPA   (0x10)      // MCP23x17 Interrupt Captured Value for Port Register
#define    INTCAPB   (0x11)      // READ ONLY: State of the Pin at the Time the Interrupt Occurred

#define    GPIOA     (0x12)      // MCP23x17 GPIO Port Register
#define    GPIOB     (0x13)      // Value on the Port - Writing Sets Bits in the Output Latch

#define    OLATA     (0x14)      // MCP23x17 Output Latch Register
#define    OLATB     (0x15)      // 1 = Latch High, 0 = Latch Low (default) Reading Returns Latch State, Not Port Value!

#define    MCP_ADDR      (0b00000000)  // Opcode for MCP23S17 with LSB (bit0) set to write (0), address OR'd in later, bits 1-3
#define    OPCODEW       (0b01000000)  // Opcode for MCP23S17 with LSB (bit0) set to write (0), address OR'd in later, bits 1-3
#define    OPCODER       (0b01000001)  // Opcode for MCP23S17 with LSB (bit0) set to read (1), address OR'd in later, bits 1-3
#define    ADDR_ENABLE   (0b00001000)  // Configuration register for MCP23S17, the only thing we change is enabling hardware addressing

#endif
