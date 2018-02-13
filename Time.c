/* ******** Time.c ************** 
 * Samuel Zhang, Zi Zhou Wang
 * 2/7/2018
 * Handles time for clock
 * Lab 3
 * Saadallah
 * 2/6/2018
 */
 
#include "../inc/tm4c123gh6pm.h"
#include "AlarmClock.h"
#include "Switch.h"

#define PF1                     (*((volatile uint32_t *)0x40025008))

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

static uint32_t fifth = 0;		//global varirable for keeping track of seconds



//************* SysTick_Init********************************************
//  Enable built in SysTick timer for global clock incrementer
//  Inputs: none
//  Output: none
void SysTick_Init(){
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 16000000;
	NVIC_ST_CURRENT_R = 0;
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000; //Priority 2
	NVIC_ST_CTRL_R = 7;
}

//************* SysTick_Handler********************************************
//  Update global time and check for alarm set offs
//  Inputs: none
//  Output: none
void SysTick_Handler(void){
	PF1 ^= 0x02;
	long sr = StartCritical();
	fifth++;
	if(fifth == 5){
		if(current_State <= MAINSTOPWATCH) { //if we are on the main screen we need to update screen
			interrupt_Flag = 1;
		}
		fifth = 0;
		global_Sec++;
		if(global_Sec == 60){
			interrupt_Flag = 1;
			global_Sec = 0;
			global_Min++;
		}
		if(global_Min == 60){
			global_Min = 0;
			global_Hour++;
		}
		global_Hour = global_Hour%24;
		if((global_Hour == alarm1_Hour && global_Min == alarm1_Min && global_Sec == alarm1_Sec && alarm1_Enable) ||
			 (global_Hour == alarm2_Hour && global_Min == alarm2_Min && global_Sec == alarm2_Sec && alarm2_Enable))		//turn on alarm if alarm1 or alarm2 go off
		{
			interrupt_Flag = 1;
			current_State = ALARMSNOOZE;
			alarm_Lock = 1;
		}
		if((global_Hour == snooze_Hour && global_Min == snooze_Min && global_Sec == snooze_Sec && snooze_Enable)) {	//turn on alarm if snooze goes off
			current_State = ALARMSNOOZE;
			interrupt_Flag = 1;
			alarm_Lock = 1;
			snooze_Enable = 0;
		}
	}
	EndCritical(sr);
}

//*************Heartbeat_Init********************************************
//  Initialize heartbeat for system operation display
//  Inputs: none
//  Output: none
void Heartbeat_Init(void) {
	SYSCTL_RCGCGPIO_R |= 0x00000020; 	// activate clock for port F
  while((SYSCTL_PRGPIO_R & 0x00000020) == 0){};
	GPIO_PORTF_DIR_R |= 0x02;					//PF1 output
	GPIO_PORTF_DEN_R |= 0x02;					//enable digital IO on PF1
	PF1 = 0x02;
}
