/*
	Stepper definitions for using the library stepper
*/

#ifndef STEPPER_h
#define STEPPER_h

// This is the pin asignation for using the mcp23s17 library with our board

#define  STEPPER_1 1
#define  STEPPER_2 2
#define  STEPPER_3 3
#define  STEPPER_4 4
#define  STEPPER_5 5

#define  MOT1_DIR  7
#define  MOT1_STEP 8
#define  MOT2_DIR  5
#define  MOT2_STEP 6
#define  MOT3_DIR  3
#define  MOT3_STEP 4
#define  MOT4_DIR  15
#define  MOT4_STEP 16
#define  MOT5_DIR  1
#define  MOT5_STEP 2


#define  PWM_1 11
#define  PWM_2 10
#define  PWM_3 13
#define  PWM_4 14


#include <mcp23s17.h>



void configSteppers(uint8_t frecuency);
void steps_motor(uint8_t stepper, uint16_t step, uint8_t direction);
void step(uint8_t stepper, uint8_t direction);

uint64_t _highTime;
uint64_t _lowTime;
		
#endif //MCP23S17
