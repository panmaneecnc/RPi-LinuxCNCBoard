#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stepper.h>

int main (int argc, char **argv) {
    int c;
    int digit_optind = 0;
    int aopt = 0, bopt = 0;
    char *copt = 0, *dopt = 0;
	uint16_t steps;
	uint8_t motor;
    while ( (c = getopt(argc, argv, "m:s:")) != -1) {
        int this_option_optind = optind ? optind : 1;
		switch (c) {
        case 'm':
            printf ("option m with value '%s'\n", optarg);
            dopt = optarg;
			motor=atoi(dopt);
            break;
		case 's':
            printf ("option s with value '%s'\n", optarg);
            dopt = optarg;
			steps=atoi(dopt);
            break;	
        case '?':
            break;
        default:
            printf ("?? getopt returned character code 0%o ??\n", c);
        }
    }
	
    printf("\n Stepper %d: %d steps", motor, steps);
    configSteppers(0);
	steps_motor(motor, steps, 0);
	exit (0);
}