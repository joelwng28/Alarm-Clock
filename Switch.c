/* ******** Switch.c ************** 
 * Samuel Zhang, Zi Zhou Wang
 * 2/3/2018
 * state machine transitions based off switch inputs
 * Lab 3
 * Saadallah
 * 2/10/2018
 */

#include "../inc/tm4c123gh6pm.h"
#include <stdint.h>
#include "AlarmClock.h"
#include "Sound.h"

#define PE4 (*((volatile uint32_t *)0x40024040))
#define PB4 (*((volatile uint32_t *)0x40005040))
#define PC4 (*((volatile uint32_t *)0x40006040))

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

//flags for timer to handle interrupts
static uint8_t PEIntFlag = 0;
static uint8_t PCIntFlag = 0;
static uint8_t PBIntFlag = 0;

//registers for holding previous state of ports to ensure no debouncing
volatile static unsigned long PELast;
volatile static unsigned long PCLast;
volatile static unsigned long PBLast;


//*************Timer0Arm********************************************
//  Initializes one-shot 20ms timer for debouncing
//  Inputs: None
//  Output: none
static void Timer0Arm(void){
	SYSCTL_RCGCTIMER_R |= 0x01;
  TIMER0_CTL_R = 0x00000000;    // 1) disable TIMER0A during setup
  TIMER0_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER0_TAMR_R = 0x0000001;    // 3) 1-SHOT mode
  TIMER0_TAILR_R = 320000;      // 4) 20ms reload value
  TIMER0_TAPR_R = 0;            // 5) bus clock resolution
  TIMER0_ICR_R = 0x00000001;    // 6) clear TIMER0A timeout flag
  TIMER0_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x80000000; // 8) priority 4
// interrupts enabled in the main program after all devices initialized
// vector number 35, interrupt number 19
  NVIC_EN0_R = 1<<19;           // 9) enable IRQ 19 in NVIC
  TIMER0_CTL_R = 0x00000001;    // 10) enable TIMER0A
	
}

//*************GPIOArm********************************************
//  Reenables switch interrupts
//  Inputs: None
//  Output: none
void GPIOArm(void) {
	if(PEIntFlag) {
		PELast = PE4;					//switch state
		PEIntFlag = 0;
		GPIO_PORTE_ICR_R = 0x10;      //clear flag4
		GPIO_PORTE_IM_R |= 0x10;      //arm interrupt on PE4 
		NVIC_PRI1_R = (NVIC_PRI1_R&0xFFFFFF00) | 0x000000A0;	//PortE priority = 5

	}
	else if(PCIntFlag) {
		PCLast = PC4;					//switch state
		PCIntFlag = 0;
		GPIO_PORTC_ICR_R = 0x10;      //clear flag4
		GPIO_PORTC_IM_R |= 0x10;      //arm interrupt on PC4 
		NVIC_PRI0_R = (NVIC_PRI0_R&0xFF00FFFF) | 0x00A00000; 	//PortC priority = 5

	}
	else if(PBIntFlag) {
		PBLast = PB4;					//switch state
		PBIntFlag = 0;
		GPIO_PORTB_ICR_R = 0x10;      //clear flag4
		GPIO_PORTB_IM_R |= 0x10;      //arm interrupt on PB4 

		NVIC_PRI0_R = (NVIC_PRI0_R&0xFFFF00FF) | 0x0000A000; 	//PortB priority = 5
		
	}
}

//*************Timer0A_Handler********************************************
//  Disarms Timer0A and reeanbles appropriate switch interrupt
//  Inputs: None
//  Output: none
void Timer0A_Handler(void){
  TIMER0_IMR_R = 0x00000000;    	// disarm timeout interrupt
  GPIOArm();   										// start GPIO
}


//*************Switches_Init********************************************
//  Initialize "Up" "Down" and "Select" Switches
//  Inputs: None
//  Output: none
void Switches_Init(void) {
	//initialize PE4 (this will be the switch for "Select")
	SYSCTL_RCGCGPIO_R |= 0x16; 	//activate clock for Port E and Port C and Port B
	GPIO_PORTE_DIR_R &= ~0x10; 	//make PE4 in
	GPIO_PORTE_DEN_R |= 0x10;		//digital enable PE4
	GPIO_PORTE_AFSEL_R &= ~0x10; 	// disable alt funct on PE4
	GPIO_PORTE_AMSEL_R &= ~0x10;	// disable analog on PE4
	GPIO_PORTE_PCTL_R &= ~0x000F0000; // configure PE4 as GPIO
	GPIO_PORTE_IS_R &= ~0x10;		//PE4 is edge sensitive
	GPIO_PORTE_IBE_R |= 0x10;	//PE4 is both edges
	GPIO_PORTE_IM_R |= 0x10; 		//arm interrupt on PE4
	NVIC_PRI1_R = (NVIC_PRI1_R&0xFFFFFF00) | 0x000000A0;	//PortE priority = 5
	//initialize PC4 (this will be the switch for "Up")
	GPIO_PORTC_DIR_R &= ~0x10; 	//make PC4 in
	GPIO_PORTC_DEN_R |= 0x10;		//digital enable PC4
	GPIO_PORTC_AFSEL_R &= ~0x10; 	// disable alt funct on PC4
	GPIO_PORTC_AMSEL_R &= ~0x10;	// disable analog on PC4
	GPIO_PORTC_PCTL_R &= ~0x000F0000; // configure PE4 as GPIO
	GPIO_PORTC_IS_R &= ~0x10;		//PC4 is edge sensitive
	GPIO_PORTC_IBE_R |= 0x10;	//PC4 is both edges
	GPIO_PORTC_IM_R |= 0x10; 		//arm interrupt on PC4
	NVIC_PRI0_R = (NVIC_PRI0_R&0xFF00FFFF) | 0x00A00000; 	//PortC priority = 5
	//initialize PB4 (this will be the siwtch for "Down")
	GPIO_PORTB_DIR_R &= ~0x10; 	//make PB4 in
	GPIO_PORTB_DEN_R |= 0x10;		//digital enable PB4
	GPIO_PORTB_AFSEL_R &= ~0x10; 	// disable alt funct on PB4
	GPIO_PORTB_AMSEL_R &= ~0x10;	// disable analog on PB4
	GPIO_PORTB_PCTL_R &= ~0x000F0000; // configure PB4 as GPIO
	GPIO_PORTB_IS_R &= ~0x10;		//PB4 is edge sensitive
	GPIO_PORTB_IBE_R |= 0x10;	//PB4 is both edges
	GPIO_PORTB_IM_R |= 0x10; 		//arm interrupt on PB4
	NVIC_PRI0_R = (NVIC_PRI0_R&0xFFFF00FF) | 0x0000A000; 	//PortB priority = 5
	
	NVIC_EN0_R = 16;				//Enable interrupts for PortE
	NVIC_EN0_R = 4;				//Enable interrupts for PortC
	NVIC_EN0_R = 2;				//Enable interrupts for PortB

	PELast = PE4;					//Set initial state
	PBLast = PB4;					//Set initial state
	PCLast = PC4;					//Set initial state
}

long sr;	//for critical sections

//*************GPIOPortE_Handler********************************************
//  Executes all state transitions for "Select" button
//  Inputs: None
//  Output: none
void GPIOPortE_Handler(void) {
	GPIO_PORTE_IM_R &= ~0x10;		//disarm intterupt on PE4
	PEIntFlag = 1;
	if(!PELast) {
		sr = StartCritical();						//start critical section
		switch(current_State) {
			case MAINTOGGLE:				
				if(clock_Mode != 3) {
					clock_Mode++;
				}
				else {
					clock_Mode = 0;
				}				
				break;
			case MAINSETTIME:
				current_State = SETTIMEHHOVER;
				break;
			case MAINALARM1:
				current_State = A1HHOVER;
				break;
			case MAINALARM2:
				current_State = A2HHOVER;
				break;
			case MAINSTOPWATCH:
				current_State = SWTOGGLE;
				break;
			case SETTIMEHHOVER:
				current_State = SETTIMEH;
				break;
			case SETTIMEH:
				current_State = SETTIMEHHOVER;
				break;
			case SETTIMEMHOVER:
				current_State = SETTIMEM;
				break;
			case SETTIMEM:
				current_State = SETTIMEMHOVER;
				break;
			case SETTIMEBACK:
				current_State = MAINSETTIME;
				break;
			case A1HHOVER:
				current_State = A1H;
				break;
			case A1H:
				current_State = A1HHOVER;
				break;
			case A1MHOVER:
				current_State = A1M;
				break;
			case A1M:
				current_State = A1MHOVER;
				break;
			case A1ENABLE:				
				if(alarm1_Enable) {
					alarm1_Enable = 0;
				}
				else {
					alarm1_Enable = 1;
				}			
				break;
			case A1BACK:
				current_State = MAINALARM1;
				break;
			case A2HHOVER:
				current_State = A2H;
				break;
			case A2H:
				current_State = A2HHOVER;
				break;
			case A2MHOVER:
				current_State = A2M;
				break;
			case A2M:
				current_State = A2MHOVER;
				break;
			case A2ENABLE:	
				if(alarm2_Enable) {
					alarm2_Enable = 0;
				}
				else {
					alarm2_Enable = 1;
				}
				break;
			case A2BACK:
				current_State = MAINALARM2;
				break;
			case SWTOGGLE:		
				if(stopwatch_Enable) {
					stopwatch_Enable = 0;
				}
				else {
					stopwatch_Enable = 1;
				}			
				break;
			case SWRESET:				
				stopwatch_Hour = 0;
				stopwatch_Min = 0;
				stopwatch_Sec = 0;				
				break;
			case SWBACK:
				current_State = MAINSTOPWATCH;
				break;
			case ALARMSNOOZE:
				current_State = MAINTOGGLE;
				snooze_Enable = 1;
				snooze_Sec = global_Sec;
				if(global_Min == 59) {
					snooze_Min = 0;
					if(global_Hour == 23) {
						snooze_Hour = 0;
					}
					else {
						snooze_Hour = global_Hour;
					}
				}
				else {
					snooze_Min = global_Min + 1;
				}
				alarm_Lock = 0;
				Sound_Off();
				break;
			case ALARMSTOP:
				current_State = MAINTOGGLE;
				alarm_Lock = 0;
				Sound_Off();
				break;
		}
		EndCritical(sr);						//end critical section
		interrupt_Flag = 1;
	}
	
	Timer0Arm();								//start one shot
}

//*************GPIOPortC_Handler********************************************
//  Executes all state transitions for "Up" button
//  Inputs: None
//  Output: none
void GPIOPortC_Handler(void) {
	GPIO_PORTC_IM_R &= ~0x10;		//disarm intterupt on PC4
	PCIntFlag = 1;
	if(!PCLast) {
		sr = StartCritical();						//start critical section
		switch(current_State) {
			case MAINTOGGLE:
				current_State = MAINSTOPWATCH;
				break;
			case MAINSETTIME:
				current_State = MAINTOGGLE;
				break;
			case MAINALARM1:
				current_State = MAINSETTIME;
				break;
			case MAINALARM2:
				current_State = MAINALARM1;
				break;
			case MAINSTOPWATCH:
				current_State = MAINALARM2;
				break;
			case SETTIMEHHOVER:
				current_State = SETTIMEBACK;
				break;
			case SETTIMEH:
				if(global_Hour == 0) {
					global_Hour = 23;
				}
				else {
					global_Hour--;
				}
				break;
			case SETTIMEMHOVER:
				current_State = SETTIMEHHOVER;
				break;
			case SETTIMEM:
				if(global_Min == 0) {
					global_Min = 59;
				}
				else {
					global_Min--;
				}
				break;
			case SETTIMEBACK:
				current_State = SETTIMEMHOVER;
				break;
			case A1HHOVER:
				current_State = A1BACK;
				break;
			case A1H:
				if(alarm1_Hour == 0) {
					alarm1_Hour = 23;
				}
				else {
					alarm1_Hour--;
				}
				break;
			case A1MHOVER:
				current_State = A1HHOVER;
				break;
			case A1M:
				if(alarm1_Min == 0) {
					alarm1_Min = 59;
				}
				else {
					alarm1_Min--;
				}
				break;
			case A1ENABLE:
				current_State = A1MHOVER;
				break;
			case A1BACK:
				current_State = A1ENABLE;
				break;
			case A2HHOVER:
				current_State = A2BACK;
				break;
			case A2H:
				
				if(alarm2_Hour == 0) {
					alarm2_Hour = 23;
				}
				else {
					alarm2_Hour--;
				}	
				break;
			case A2MHOVER:
				current_State = A2HHOVER;
				break;
			case A2M:
				
				if(alarm2_Min == 0) {
					alarm2_Min = 59;
				}
				else {
					alarm2_Min--;
				}
				break;
			case A2ENABLE:
				current_State = A2MHOVER;
				break;
			case A2BACK:
				current_State = A2ENABLE;
				break;
			case SWTOGGLE:
				current_State = SWBACK;
				break;
			case SWRESET:
				current_State = SWTOGGLE;
				break;
			case SWBACK:
				current_State = SWRESET;
				break;
			case ALARMSNOOZE:
				current_State = ALARMSTOP;
				break;
			case ALARMSTOP:
				current_State = ALARMSNOOZE;
				break;
		}
		EndCritical(sr);				//end critical section
		interrupt_Flag = 1;
	}
	
	Timer0Arm();								//start one shot
}

//*************GPIOPortB_Handler********************************************
//  Executes all state transitions for "Down" button
//  Inputs: None
//  Output: none
void GPIOPortB_Handler(void) {
	GPIO_PORTB_IM_R &= ~0x10;		//disarm intterupt on PB4
	PBIntFlag = 1;
	if(!PBLast) {
		sr = StartCritical();						//start critical section
		switch(current_State) {
			case MAINTOGGLE:
				current_State = MAINSETTIME;
				break;
			case MAINSETTIME:
				current_State = MAINALARM1;
				break;
			case MAINALARM1:
				current_State = MAINALARM2;
				break;
			case MAINALARM2:
				current_State = MAINSTOPWATCH;
				break;
			case MAINSTOPWATCH:
				current_State = MAINTOGGLE;
				break;
			case SETTIMEHHOVER:
				current_State = SETTIMEMHOVER;
				break;
			case SETTIMEH:
				if(global_Hour == 23) {
					global_Hour = 0;
				}
				else {
					global_Hour++;
				}
				break;
			case SETTIMEMHOVER:
				current_State = SETTIMEBACK;
				break;
			case SETTIMEM:
				
				if(global_Min == 59) {
					global_Min = 0;
				}
				else {
					global_Min++;
				}
				
				break;
			case SETTIMEBACK:
				current_State = SETTIMEHHOVER;
				break;
			case A1HHOVER:
				current_State = A1MHOVER;
				break;
			case A1H:
				if(alarm1_Hour == 23) {
					alarm1_Hour = 0;
				}
				else {
					alarm1_Hour++;
				}
				break;
			case A1MHOVER:
				current_State = A1ENABLE;
				break;
			case A1M:
				
				if(alarm1_Min == 59) {
					alarm1_Min = 0;
				}
				else {
					alarm1_Min++;
				}
				
				break;
			case A1ENABLE:
				current_State = A1BACK;
				break;
			case A1BACK:
				current_State = A1HHOVER;
				break;
			case A2HHOVER:
				current_State = A2MHOVER;
				break;
			case A2H:
				
				if(alarm2_Hour == 23) {
					alarm2_Hour = 0;
				}
				else {
					alarm2_Hour++;
				}
				
				break;
			case A2MHOVER:
				current_State = A2ENABLE;
				break;
			case A2M:
				
				if(alarm2_Min == 59) {
					alarm2_Min = 0;
				}
				else {
					alarm2_Min++;
				}
				
				break;
			case A2ENABLE:
				current_State = A2BACK;
				break;
			case A2BACK:
				current_State = A2HHOVER;
				break;
			case SWTOGGLE:
				current_State = SWRESET;
				break;
			case SWRESET:
				current_State = SWBACK;
				break;
			case SWBACK:
				current_State = SWTOGGLE;
				break;
			case ALARMSNOOZE:
				current_State = ALARMSTOP;
				break;
			case ALARMSTOP:
				current_State = ALARMSNOOZE;
				break;
		}
		EndCritical(sr);						//end critical section
		interrupt_Flag = 1;		
	}
	
	Timer0Arm();								//start one shot
}

