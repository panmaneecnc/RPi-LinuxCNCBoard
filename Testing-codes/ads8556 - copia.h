/*
  MCP23S17.h  Version 0.1
  Microchip MCP23S17 SPI I/O Expander Class for Arduino
  Created by Cort Buffington & Keith Neufeld
  March, 2011

  Features Implemented (by word and bit):
    I/O Direction
    Pull-up on/off
    Input inversion
    Output write
    Input read

  Interrupt features are not implemented in this version
  byte based (portA, portB) functions are not implemented in this version

  NOTE:  Addresses below are only valid when IOCON.BANK=0 (register addressing mode)
         This means one of the control register values can change register addresses!
         The default values is 0, so that's how we're using it.

         All registers except ICON (0xA and 0xB) are paired as A/B for each 8-bit GPIO port.
         Comments identify the port's name, and notes on how it is used.

         *THIS CLASS ENABLES THE ADDRESS PINS ON ALL CHIPS ON THE BUS WHEN THE FIRST CHIP OBJECT IS INSTANTIATED!

  USAGE: All Read/Write functions except wordWrite are implemented in two different ways.
         Individual pin values are set by referencing "pin #" and On/Off, Input/Output or High/Low where
         portA represents pins 0-7 and portB 8-15. So to set the most significant bit of portB, set pin # 15.
         To Read/Write the values for the entire chip at once, a word mode is supported buy passing a
         single argument to the function as 0x(portB)(portA). I/O mode Output is represented by 0.
         The wordWrite function was to be used internally, but was made public for advanced users to have
         direct and more efficient control by writing a value to a specific register pair.
*/

#ifndef ADS8556_h
#define ADS8556_h

// MACROSS for control register

#define    CH_C_EN   		(0x80000000)      // MCP23x17 I/O Direction Register
#define    CH_B_EN   		(0x40000000)      // 1 = Input (default), 0 = Output
#define    CH_A_EN   		(0x20000000)      // 1 = Input (default), 0 = Output
#define    RANGE_C_2VREF 	(0x10000000)      // MCP23x17 I/O Direction Register
#define    RANGE_B_2VREF	(0x08000000)      // 1 = Input (default), 0 = Output
#define    RANGE_A_2VREF   	(0x04000000)      // 1 = Input (default), 0 = Output
#define    REF_EN		    (0x02000000)      // MCP23x17 Input Polarity Register
#define    REF_BUF_EN	    (0x01000000)      // MCP23x17 Input Polarity Register
#define    SEQ_EN		    (0x00800000)      // MCP23x17 Input Polarity Register
#define    AUTO_NAP_EN	    (0x00400000)      // MCP23x17 Input Polarity Register
#define    INT_EN		    (0x00200000)      // MCP23x17 Input Polarity Register
#define    BUSY_LOW			(0x00100000)      // MCP23x17 Input Polarity Register
#define    VREF_3V		    (0x00040000)      // MCP23x17 Input Polarity Register
#define    READ_NC		    (0x00020000)      // MCP23x17 Input Polarity Register
#define    ENTIRE_CR_UPD    (0x00010000)      // MCP23x17 Input Polarity Register
#define    PD_C_EN   		(0x00008000)      // MCP23x17 I/O Direction Register
#define    PD_B_EN   		(0x00004000)      // 1 = Input (default), 0 = Output
#define    PD_A_EN   		(0x00002000)      // 1 = Input (default), 0 = Output
#define    EXT_CCLK			(0x00000800)      // 1 = Input (default), 0 = Output
#define    INT_CCLK_AV   	(0x00000400)      // 1 = Input (default), 0 = Output

#define    CH_C_DIS   		(0x7FFFFFFF)      // MCP23x17 I/O Direction Register
#define    CH_B_DIS   		(0xBFFFFFFF)      // 1 = Input (default), 0 = Output
#define    CH_A_DIS   		(0xDFFFFFFF)      // 1 = Input (default), 0 = Output
#define    RANGE_C_4VREF	(0xEFFFFFFF)      // MCP23x17 I/O Direction Register
#define    RANGE_B_4VREF	(0xF7FFFFFF)      // MCP23x17 I/O Direction Register
#define    RANGE_A_4VREF	(0xFBFFFFFF)      // MCP23x17 I/O Direction Register
#define    REF_DIS     		(0xFDFFFFFF)      // 0 = Normal (default)(low reads as 0), 1 = Inverted (low reads as 1)
#define    REF_BUF_DIS 		(0xFEFFFFFF)      // 0 = Normal (default)(low reads as 0), 1 = Inverted (low reads as 1)
#define    SEQ_EN		    (0xFF7FFFFF)      // MCP23x17 Input Polarity Register
#define    NOR_OP		    (0xFFBFFFFF)      // MCP23x17 Input Polarity Register
#define    BUSY_EN		    (0xFFDFFFFF)      // MCP23x17 Input Polarity Register
#define    BUSY_HIGH		(0xFFEFFFFF)      // MCP23x17 Input Polarity Register
#define    VREF_2_5V	    (0xFFFBFFFF)      // MCP23x17 Input Polarity Register
#define    READ_NOR		    (0xFFFDFFFF)      // MCP23x17 Input Polarity Register
#define    PARTIAL_CR_UPD   (0xFFFEFFFF)      // MCP23x17 Input Polarity Register
#define    PD_C_DIS   		(0xFFFF7FFF)      // MCP23x17 I/O Direction Register
#define    PD_B_DIS   		(0xFFFFBFFF)      // 1 = Input (default), 0 = Output
#define    PD_A_DIS  		(0xFFFFDFFF)      // 1 = Input (default), 0 = Output
#define    INT_CCLK			(0xFFFFF7FF)      // 1 = Input (default), 0 = Output
#define    NORM_CCLK	   	(0xFFFFFBFF)      // 1 = Input (default), 0 = Output

//#include "WProgram.h"
#include <bcm2835.h>
//class MCP {
  //public:
    void configADS8556(uint8_t);                            // Constructor to instantiate a discrete IC as an object, argument is the address (0-7) of the MCP23S17
    uint16_t readChannel(uint8_t);   // Typically only used internally, but allows the user to write any register pair if needed, so it's public
    uint16_t* readAllChannels();        // Typically only used internally, but allows the user to write any register if needed, so it's public
    void updateFullCR(uint32_t);          // Sets the mode (input or output) of a single I/O pin
    void updatePartialCR(uint32_t);              // Sets the mode (input or output) of all I/O pins at once 
    
	//private:
    uint8_t _address;                        // Address of the MCP23S17 in use
    unsigned int _modeCache;                 // Caches the mode (input/output) configuration of I/O pins
    unsigned int _pullupCache;               // Caches the internal pull-up configuration of input pins (values persist across mode changes)
    unsigned int _invertCache;               // Caches the input pin inversion selection (values persist across mode changes)
    unsigned int _outputCache;               // Caches the output pin state of pins
// };
		
#endif //MCP23S17
