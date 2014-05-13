#include <stepper.h>

#define  RESET  RPI_GPIO_P1_22

void configSteppers(uint8_t frecuency)
{
	//switch (frequency)
	//{
		//default:
			_highTime=10;
			_lowTime=200;
		//break;
		
//	}
	
	
}

void steps_motor(uint8_t stepper, uint16_t steps, uint8_t direction)
{
	uint16_t i;
	for(i=0; i<steps; i++)
	{
		step(stepper, direction);
	}
}
void step(uint8_t stepper, uint8_t direction)
{
	switch (stepper)
	{
		case STEPPER_1:
			digitalWrite_bit(MOT1_DIR, direction);
			digitalWrite_bit(MOT1_STEP,1);
			bcm2835_delayMicroseconds(1);
			digitalWrite_bit(MOT1_STEP,0);
			bcm2835_delayMicroseconds(100); // aqui tengo que ver si el delay puede ser mas o menos
		break;
		case STEPPER_2:
			digitalWrite_bit(MOT2_DIR, direction);
			digitalWrite_bit(MOT2_STEP,1);
			bcm2835_delayMicroseconds(1);
			digitalWrite_bit(MOT2_STEP,0);
			bcm2835_delayMicroseconds(100); // aqui tengo que ver si el delay puede ser mas o menos
		break;
		case STEPPER_3:
			digitalWrite_bit(MOT3_DIR, direction);
			digitalWrite_bit(MOT3_STEP,1);
			bcm2835_delayMicroseconds(1);
			digitalWrite_bit(MOT3_STEP,0);
			bcm2835_delayMicroseconds(100); // aqui tengo que ver si el delay puede ser mas o menos
		break;
		case STEPPER_4:
			digitalWrite_bit(MOT4_DIR, direction);
			digitalWrite_bit(MOT4_STEP,1);
			bcm2835_delayMicroseconds(1);
			digitalWrite_bit(MOT4_STEP,0);
			bcm2835_delayMicroseconds(100); // aqui tengo que ver si el delay puede ser mas o menos
		break;
		case STEPPER_5:
			digitalWrite_bit((uint8_t)MOT5_DIR, (uint8_t)direction);
			digitalWrite_bit((uint8_t)MOT5_STEP,1);
			bcm2835_delayMicroseconds(1);
			digitalWrite_bit((uint8_t)MOT5_STEP,0);
			bcm2835_delayMicroseconds(100); // aqui tengo que ver si el delay puede ser mas o menos
		break;
		default:
		break;
	}
}
 

/*void run(uint16_t steps)
{	
	uint16_t i;
	for(i=0; i<steps; i++)
	{
		step();
		bcm2835_delayMicroseconds(1000);
	}
}

void step()
{
	digitalWrite_bit(2,1);
	bcm2835_delayMicroseconds(100);
	digitalWrite_bit(2,0);	
	
}
int main(int argc, char **argv)
{
  configMCP23s17(0);
  bcm2835_gpio_fsel(RESET, BCM2835_GPIO_FSEL_OUTP); 
  // bcm2835_gpio_fsel(RESET, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_write(RESET, HIGH);  
  //pinMode(1, HIGH); // sets pin 4 as an input
  pinMode_bit(1,0); // sets pin 16 as an output
  pinMode_bit(2,0);
  pinMode_bit(9,0);
  //pinMode(0B0000111100001111); // sets pins 1-4 and 9-12 as input, 5-8 and 13-16 as output

  pullupMode_bit(1,1); // enable the pull-up on pin 4
  pullupMode_bit(2,1);
  pullupMode_bit(9,1);
  //twochip.pullupMode(0B0000111100000000); // enable the pull-ups on pins 9-12

  //inputInvert_word(0xFFFF); // disable inversion on pin 4
  //twochip.inputInvert(0B0000000000001111); // enable inversion on pins 1-4
  
  int onevalue;
  //int twovalue;
  uint64_t cont;
  digitalWrite_bit(1,1);
  digitalWrite_bit(9,0);
  while(1)
  {
    /* cont= bcm2835_st_read();  
        digitalWrite_bit(1,0); // El motor  a derechas
	while(bcm2835_st_read<cont+10);
        // digitalWrite_bit(2,1);
        bcm2835_st_delay(0,100);
	// bcm2835_delayMicroseconds(400);	
	cont=bcm2835_st_read();
	// digitalWrite_bit(2,0); // set pin 16 to "HIGH
	while(bcm2835_st_read<cont+10);
	// bcm2835_delayMicroseconds(400);
	bcm2835_st_delay(0,100); 
	run(200);
	bcm2835_delay(1000);
	run(200);
	bcm2835_delay(1000);
	run(400);
	bcm2835_delay(1000);
	run(400);
	bcm2835_delay(1000);
  }
}
*/
