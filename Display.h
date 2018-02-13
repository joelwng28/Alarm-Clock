/* ******** Display.h ************** 
 * Samuel Zhang, Zi Zhou Wang
 * 2/3/2018
 * Display and screen print functions
 * Lab 3
 * Saadallah
 * 2/10/2018
 */

#include <stdint.h>

//*************drawSec********************************************
//  Draws one thin line on the ST7735 color LCD (Seconds hand)
//  Inputs: (x1,y1) is the start point
//          (x2,y2) is the end point
// x1,x2 are horizontal positions, columns from the left edge
//               must be less than 128
//               0 is on the left, 126 is near the right
// y1,y2 are vertical positions, rows from the top edge
//               must be less than 160
//               159 is near the wires, 0 is the side opposite the wires
//        color 16-bit color, which can be produced by ST7735_Color565() 
// Output: none
void displaySec(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

//*************drawMin*******************************************
//  Draws two-pixel wide line on the ST7735 color LCD (Minutes hand)
//  Inputs: (x1,y1) is the start point
//          (x2,y2) is the end point
// x1,x2 are horizontal positions, columns from the left edge
//               must be less than 128
//               0 is on the left, 126 is near the right
// y1,y2 are vertical positions, rows from the top edge
//               must be less than 160
//               159 is near the wires, 0 is the side opposite the wires
//        color 16-bit color, which can be produced by ST7735_Color565() 
// Output: none
void displayMin(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

//*************drawHour********************************************
//  Draws four-pixel wide line on the ST7735 color LCD (Hour hand)
//  Inputs: (x1,y1) is the start point
//          (x2,y2) is the end point
// x1,x2 are horizontal positions, columns from the left edge
//               must be less than 128
//               0 is on the left, 126 is near the right
// y1,y2 are vertical positions, rows from the top edge
//               must be less than 160
//               159 is near the wires, 0 is the side opposite the wires
//        color 16-bit color, which can be produced by ST7735_Color565() 
// Output: none
void displayHour(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

//*************displaySW********************************************
//  Draws stopwatch screen
//  Inputs: none
//  Output: none
void diaplySW(void);

//*************displaySWBack********************************************
//  Draws stopwatch back screen
//  Inputs: none
//  Output: none
void displaySWBack(void);

//*************displaySWSRS********************************************
//  Draws stopwatch start/stop screen
//  Inputs: none
//  Output: none
void displaySWSRS(void);

//*************displaySWReset********************************************
//  Draws stopwatch reset screen
//  Inputs: none
//  Output: none
void displaySWReset(void);

//*************displayMain********************************************
// Draws the Main Screen
// Input: str, the mode to display at bottom center of screen
//  Output: none
void displayMain(char* str);

//*************displaySetTimeDefault********************************************
// Draws the set time screen template
// Input: none
//  Output: none
void displaySetTimeDefault(void);

//*************displaySetTimeHourSelect********************************************
// Draws the set time hour select screen
// Input: none
//  Output: none
void displaySetTimeHourSelect(void);

//*************displaySetTimeMinSelect********************************************
// Draws the set time hour select screen
// Input: none
//  Output: none
void displaySetTimeMinSelect(void);

//*************displaySetTimeHour********************************************
// Draws the set time hour screen
// Input: none
//  Output: none
void displaySetTimeHour(void);

//*************displaySetTimeMin********************************************
// Draws the set time min screen
// Input: none
//  Output: none
void displaySetTimeMin(void);

//*************displaySetTimeBack********************************************
// Draws the set time back screen
// Input: none
//  Output: none
void displaySetTimeBack(void);

//*************displayAlarm1Default********************************************
// Draws the alarm 1 default template
// Input: none
//  Output: none
void displayAlarm1Default(void);

//*************displayAlarm1HourSelect********************************************
// Draws the alarm 1 hour select screen
// Input: none
//  Output: none
void displayAlarm1HourSelect(void);

//*************displayAlarm1MinSelect********************************************
// Draws the alarm 1 min select screen
// Input: none
//  Output: none
void displayAlarm1MinSelect(void);

//*************displayAlarm1Hour********************************************
// Draws the alarm 1 hour screen
// Input: none
//  Output: none
void displayAlarm1Hour(void);

//*************displayAlarm1Min********************************************
// Draws the alarm 1 min screen
// Input: none
//  Output: none
void displayAlarm1Min(void);

//*************displayAlarm1Enable********************************************
// Draws the alarm 1 enable screen
// Input: none
//  Output: none
void displayAlarm1Enable(void);

//*************displayAlarm1Back********************************************
// Draws the alarm 1 back screen
// Input: none
//  Output: none
void displayAlarm1Back(void);

//*************displayAlarm2Default********************************************
// Draws the alarm 2 default template
// Input: none
//  Output: none
void displayAlarm2Default(void);

//*************displayAlarm2HourSelect********************************************
// Draws the alarm 2 hour select screen
// Input: none
//  Output: none
void displayAlarm2HourSelect(void);

//*************displayAlarm2MinSelect********************************************
// Draws the alarm 2 min select screen
// Input: none
//  Output: none
void displayAlarm2MinSelect(void);

//*************displayAlarm2Hour********************************************
// Draws the alarm 2 hour screen
// Input: none
//  Output: none
void displayAlarm2Hour(void);

//*************displayAlarm2Min********************************************
// Draws the alarm 2 min screen
// Input: none
//  Output: none
void displayAlarm2Min(void);

//*************displayAlarm2Enable********************************************
// Draws the alarm 2 enable screen
// Input: none
//  Output: none
void displayAlarm2Enable(void);

//*************displayAlarm2Back********************************************
// Draws the alarm 2 back screen
// Input: none
//  Output: none
void displayAlarm2Back(void);

//*************displayAlarmLock//*************displayAlarmLockStop********************************************
// Draws the alarm lock stop screen
// Input: none
//  Output: none********************************************
// Draws the alarm lock template
// Input: none
//  Output: none
void displayAlarmLock(void);

//*************displayAlarmLockSnooze********************************************
// Draws the alarm lock snooze screen
// Input: none
//  Output: none
void displayAlarmLockSnooze(void);


void displayAlarmLockStop(void);

