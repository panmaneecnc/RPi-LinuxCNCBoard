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
*	  
*    t = csvread('muestras.csv',:,1);
*    y = csvread('muestras.csv',:,2);
*    plot(t, y);
*/
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <native/task.h>
#include <native/timer.h>
#include <ads8556.h>


#define SAMPLES_NUM 200
#define PERIOD_US 100

RT_TASK adc_task; // ADC sampling task

void adc(void *arg)
{
	FILE *fp;
	RTIME start, now;
	uint32_t cr=  0xff0303ff;
    uint32_t cra= 0xff0131ff;
	uint16_t *canales;
	configADS8556();
	updateFullCR(&cr);
	
	/*
	* Arguments: &task (NULL=self),
	* start time,
	* period PERIOD_US expresed in ns
	*/
	printf("\nEn tarea");
	rt_task_set_periodic(NULL, TM_NOW, PERIOD_US*1000);	
	//printf("\nEl ciclo se marca a partir de hacer la tarea periodica");
	fp=fopen("samples.csv","w+");
	start=rt_timer_read();
	
	int i;	
	for(i=0; i< (int)SAMPLES_NUM; i++) {
		/*Here we start the peridiocity*/		
		rt_task_wait_period(NULL);
		
		/*Obtaining the time*/
		now=  rt_timer_read();
		canales=readAllChannels(&cr);
		fprintf(fp,"\n%d",i+1);
		fprintf(fp,",%f", (long)(now-start)/1000000);
		fprintf(fp,",%d,%d,%d,%d,%d,%d", *(canales), *(canales+1), *(canales+2), *(canales+3), *(canales+4), *(canales+5)); 
		 //printf("\nIteración %d: ,t= %f ms , A= %d, B= %d, C= %d, D=%d", i, (long)(now - start) / 1000000, *(canales), *(canales+1), *(canales+2), *(canales+3), *(canales+4), *(canales+5));
	}
	fclose(fp);
	printf("\n TErmina la tarea");	
	
	
		
}
void catch_signal(int sig)
{
	
	switch(sig)
	{
	case SIGTERM: // When it closes, we finished the SPI and the GPIO control
		bcm2835_spi_end();
		bcm2835_close(); 	
		break;	
	case SIGSTOP: // Also we need to close the SPI
		bcm2835_spi_end();
		bcm2835_close(); 	
		break;
	case SIGINT:
		
		break;
	default:
		break;
	}
}

int main(int argc, char* argv[])
{

	/* Here we activate the signal*/
	signal(SIGTERM, catch_signal);
	signal(SIGINT, catch_signal);
	
	/* Avoids memory swapping for this program */
	mlockall(MCL_CURRENT|MCL_FUTURE);
	
	/*We capture the star_time*/
	
	//start_time= rt_timer_read();
	/*
			* Arguments: &task,
			* name,
			* stack size (0=default),
			* priority (99=maximun priority),
			* mode (FPU, start suspended, ...)
			*/
	printf("\nCreamos tarea");
	rt_task_create(&adc_task, "adc_reading", 0, 99, 0);
	
	/*
	* Arguments: &task,
	* task function,
	* function argument
	*/
	
	rt_task_start(&adc_task, &adc, NULL);
	//pause();
	rt_task_delete(&adc_task);
	//create_marks_csv("samples", samples, SAMPLES_NUM);
	bcm2835_spi_end();
	bcm2835_close();
    printf("\nTodo cerrado"); 	
	return 0;	
	
}

