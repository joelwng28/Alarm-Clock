/* ******** Sound.c ************** 
 * Samuel Zhang, Zi Zhou Wang
 * 2/6/2018
 * Port init for sound and output
 * Lab 3
 * Saadallah
 * 2/6/2018
 */
 

#define PE2 	(*((volatile uint32_t *)0x40024010))
 
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

//************* Sound_Init********************************************
//  Initialize sound port (PE2)
//  Inputs: none
//  Output: none 
void Sound_Init() {
	SYSCTL_RCGCGPIO_R |= 0x10;								//active Port E
	while((SYSCTL_PRGPIO_R&0x10) == 0){};			//wait for Port to activate
	GPIO_PORTE_DIR_R |= 0x04;             		// make PE2 output
	GPIO_PORTE_AFSEL_R &= ~0x04;          		// disable alt funct on PE2
	GPIO_PORTE_AMSEL_R &= ~0x04;							// disable analog on PE2
	GPIO_PORTE_PCTL_R &= ~0x000000F00;				//PCTL GPIO on PE2
	GPIO_PORTE_DEN_R |= 0x04;             		// enable digital I/O on PE2
	
		
	PE2 = 0x00;
}

//*************Sound_On********************************************
//  Toggle sound and run a delay for next toggle
//  Inputs: none
//  Output: none  
void Sound_On() {
	PE2 ^= 0x04;
	for(int i = 0; i < 100000; i++) {}		//delay produces sound
}

//************* Sound_Off********************************************
//  Turn off port so that it doesn't accidentally heat up the transistor
//  Inputs: none
//  Output: none 
void Sound_Off() {
	PE2 = 0x00;
}


