#include <bcm2835.h>
#include <mcp23s17.h>
#include <stdio.h>

#define  RESET  RPI_GPIO_P1_22

#define  MOT1_DIR  7
#define  MOT1_STEP 8
#define  MOT2_DIR  5
#define  MOT2_STEP 6
#define  MOT3_DIR  3
#define  MOT3_STEP 4
#define  MOT4_DIR  1
#define  MOT4_STEP 2
#define  MOT5_DIR  15
#define  MOT5_STEP 16
#define  PWM_2 10

int main(int argc, char **argv)
{
  configMCP23s17(0);
  bcm2835_gpio_fsel(RESET, BCM2835_GPIO_FSEL_OUTP); 
  // bcm2835_gpio_fsel(RESET, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_write(RESET, HIGH);  
  //pinMode(1, HIGH); // sets pin 4 as an input
  pinMode_bit(PWM_2,LOW); // sets pin 16 as an output
  //pinMode_bit(2,0);
  //pinMode_bit(9,0);
  //pinMode(0B0000111100001111); // sets pins 1-4 and 9-12 as input, 5-8 and 13-16 as output

  pullupMode_bit(PWM_2,HIGH); // enable the pull-up on pin 4
  //pullupMode_bit(2,1);
  //pullupMode_bit(9,1);
  //twochip.pullupMode(0B0000111100000000); // enable the pull-ups on pins 9-12

  //inputInvert_word(0xFFFF); // disable inversion on pin 4
  //twochip.inputInvert(0B0000000000001111); // enable inversion on pins 1-4
  
  int onevalue;
  //int twovalue;
  uint64_t cont;
  //digitalWrite_bit(1,1);
  //digitalWrite_bit(9,0);
  while(1)
  {
    /* cont= bcm2835_st_read();  
        digitalWrite_bit(1,0); // El motor  a derechas
	while(bcm2835_st_read<cont+10);
        // digitalWrite_bit(2,1);
        bcm2835_st_delay(0,100);
	// bcm2835_delayMicroseconds(400);	
	cont=bcm2835_st_read();
	// digitalWrite_bit(2,0); // set pin 16 to "HIGH*/
	
	printf("%x ",bcm2835_st_read());

	// bcm2835_delayMicroseconds(400);
	//bcm2835_st_delay(0,100); 
    //digitalWrite_bit(PWM_2, LOW);
    // bcm2835_delayMicroseconds(500);
    //  digitalWrite_bit(PWM_2, HIGH);
    //	bcm2835_delayMicroseconds(500);
  }
}
