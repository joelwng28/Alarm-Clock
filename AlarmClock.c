/* ******** AlarmClock.c ************** 
 * Samuel Zhang, Zi Zhou Wang
 * 2/3/2018
 * Main for alarm clock, displays state machine outputs
 * Lab 3
 * Saadallah
 * 2/10/2018
 */

#include <stdint.h>
#include <stdio.h>
#include "string.h"
#include "ST7735.h"
#include "../inc/tm4c123gh6pm.h"
#include "PLL.h"
#include "Timer3.h"
#include "Sound.h"
#include "Globals.h"
#include "Time.h"
#include "AlarmClock.h"
#include "Display.h"
#include "Switch.h"

uint8_t current_State = MAINTOGGLE; //default state is Main Screen with Toggle Menu

//Global Variables for Representing Time
uint8_t global_Hour = 0; uint8_t global_Min = 0; uint8_t global_Sec = 0;
uint8_t alarm1_Hour = 0; uint8_t alarm1_Min = 0; uint8_t alarm1_Sec = 0; uint8_t alarm1_Enable = 0;
uint8_t alarm2_Hour = 0; uint8_t alarm2_Min = 0; uint8_t alarm2_Sec = 0; uint8_t alarm2_Enable = 0;
uint8_t snooze_Hour = 0; uint8_t snooze_Min = 0; uint8_t snooze_Sec = 0; uint8_t snooze_Enable = 0;
uint8_t stopwatch_Hour = 0; uint8_t stopwatch_Min = 0; uint8_t stopwatch_Sec = 0; uint8_t stopwatch_Enable = 0;

uint8_t clock_Mode = 0; //Global variable for determining which clock face (0-3)

uint8_t interrupt_Flag = 0;

uint8_t alarm_Lock = 0;


void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode



int main(void){
	PLL_Init(Bus80MHz);                   // 80 MHz
	ST7735_InitR(INITR_REDTAB);
	SysTick_Init();
	Timer3_Init();
	Sound_Init();
	Switches_Init();
	Heartbeat_Init();
	EnableInterrupts();
	alarm1_Enable =1;
	alarm1_Min = 1;
	global_Sec = 55;

	while(1){
		if(alarm_Lock) {				//alarm lock overrides all other states
			switch(current_State) {
				case ALARMSNOOZE:
					displayAlarmLockSnooze();
					break;
				case ALARMSTOP:
					displayAlarmLockStop();
					break;
			}
			Sound_On();
			for(int i = 0; i < 100000; i++) {}
		}
		else {
			Sound_Off();
			switch(current_State) {
				case MAINTOGGLE:
					displayMain("Toggle");
					break;
				case MAINSETTIME:
					displayMain("Set Time");
					break;
				case MAINALARM1:
					displayMain("Alarm 1");
					break;
				case MAINALARM2:
					displayMain("Alarm 2");
					break;
				case MAINSTOPWATCH:
					displayMain("Stopwatch");
					break;
				case SETTIMEHHOVER:
					displaySetTimeHourSelect();
					break;
				case SETTIMEH:
					displaySetTimeHour();
					break;
				case SETTIMEMHOVER:
					displaySetTimeMinSelect();
					break;
				case SETTIMEM:
					displaySetTimeMin();
					break;
				case SETTIMEBACK:
					displaySetTimeBack();
					break;
				case A1HHOVER:
					displayAlarm1HourSelect();
					break;
				case A1H:
					displayAlarm1Hour();
					break;
				case A1MHOVER:
					displayAlarm1MinSelect();
					break;
				case A1M:
					displayAlarm1Min();
					break;
				case A1ENABLE:
					displayAlarm1Enable();
					break;
				case A1BACK:
					displayAlarm1Back();
					break;
				case A2HHOVER:
					displayAlarm2HourSelect();
					break;
				case A2H:
					displayAlarm2Hour();
					break;
				case A2MHOVER:
					displayAlarm2MinSelect();
					break;
				case A2M:
					displayAlarm2Min();
					break;
				case A2ENABLE:
					displayAlarm2Enable();
					break;
				case A2BACK:
					displayAlarm2Back();
					break;
				case SWTOGGLE:
					displaySWSRS();
					break;
				case SWRESET:
					displaySWReset();
					break;
				case SWBACK:
					displaySWBack();
					break;
				case ALARMSNOOZE:
					displayAlarmLockSnooze();
					break;
				case ALARMSTOP:
					displayAlarmLockStop();
					break;
		}
	}
	while(interrupt_Flag == 0) {			//wait for interrupt that requires changing the screen
		if(alarm_Lock) {		//play sound if we're in alarm lock mode
				Sound_On();
			}
	}
	long sr = StartCritical();
	interrupt_Flag = 0;
	EndCritical(sr);
		
	}

}






