/* ******** Display.c ************** 
 * Samuel Zhang, Zi Zhou Wang
 * 2/3/2018
 * Display and screen print functions
 * Lab 3
 * Saadallah
 * 2/10/2018
 */

#include <stdint.h>
#include "AlarmClock.h"
#include "ST7735.h"
#include <string.h>
#include "Globals.h"



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
void drawSec(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    float slope = 0;
    if (x2 == x1) { //if vertical line
        if(y2 >= y1) {
            for(uint16_t yPt = y1; yPt <= y2; yPt++) {
                ST7735_DrawPixel(x1, yPt, color);
            }
        }
        else {
            for(uint16_t yPt = y2; yPt <= y1; yPt++) {
                ST7735_DrawPixel(x2, yPt, color);
            }
        }
    }
    else if (y2 == y1) { //if horizontal line
        if(x2 >= x1) {
            for(uint16_t xPt = x1; xPt <= x2; xPt++) {
                ST7735_DrawPixel(xPt, y1, color);
            }
        }
        else {
            for(uint16_t xPt = x2; xPt <= x1; xPt++) {
                ST7735_DrawPixel(xPt, y2, color);
            }
        }
    }
    
    //all other cases have to do with relative positions of x1 and x2
    else if(x2 > x1 && y2 > y1) {
        if((x2 - x1) >= (y2 - y1)) {
            slope = ((float)y2-(float)y1)/((float)x2-(float)x1);    //calculate slope
            for(uint16_t xPt = x1; xPt <= x2; xPt++) {
                ST7735_DrawPixel(xPt, (y1 + ((slope)*((float)(xPt-x1)))),color);    //slope point formula
            }
        }
        else {
            slope = ((float)x2-(float)x1)/((float)y2-(float)y1);
            for(uint16_t yPt = y1; yPt <= y2; yPt++) {
                ST7735_DrawPixel(x1 + ((slope)*((float)(yPt-y1))), yPt, color);;
            }
        }
    }
    else if (x2 > x1 && y1 > y2) {
        if((x2 - x1) >= (y1 - y2)) {
            slope = ((float)y2-(float)y1)/((float)x2-(float)x1);    //calculate slope
            for(uint16_t xPt = x1; xPt <= x2; xPt++) {
                ST7735_DrawPixel(xPt, (y1 + ((slope)*((float)(xPt-x1)))),color); //slope point formula
            }
        }
        else {
            slope = ((float)x1-(float)x2)/((float)y1-(float)y2);
            for(uint16_t yPt = y2; yPt <= y1; yPt++) {
                ST7735_DrawPixel(x2 + ((slope)*((float)(yPt-y2))), yPt, color);       
            }
        }
    }
    else if (x1 > x2 && y2 > y1) {
        if((x1 - x2) >= (y2 - y1)) {
            slope = ((float)y1-(float)y2)/((float)x1-(float)x2);    //calculate slope
            for(uint16_t xPt = x2; xPt <= x1; xPt++) {
                ST7735_DrawPixel(xPt, (y2 + ((slope)*((float)(xPt-x2)))),color); //slope point formula
            }
        }
        else {
            slope = ((float)x2-(float)x1)/((float)y2-(float)y1);
            for(uint16_t yPt = y1; yPt <= y2; yPt++) {
                ST7735_DrawPixel(x1 + ((slope)*((float)(yPt-y1))), yPt, color);
            }
        }
    }
    else if (x1 > x2 && y1 > y2){
        if((x1 - x2) >= (y1 - y2)) {    
            slope = ((float)y1-(float)y2)/((float)x1-(float)x2);    //calculate slope
            for(uint16_t xPt = x2; xPt <= x1; xPt++) {
                ST7735_DrawPixel(xPt, (y2 + (uint16_t)((slope)*((float)(xPt-x2)))),color); //slope point formula
            }
        }
        else {
            slope = ((float)x1-(float)x2)/((float)y1-(float)y2);
            for(uint16_t yPt = y2; yPt <= y1; yPt++) {
                ST7735_DrawPixel(x2 + ((slope)*((float)(yPt-y2))), yPt, color);          
            }
        }
    }
}

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
void drawMin(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    float slope = 0;
    if (x2 == x1) { //if vertical line
        if(y2 >= y1) {
            for(uint16_t yPt = y1; yPt <= y2; yPt++) {
                ST7735_DrawPixel(x1, yPt, color);
                ST7735_DrawPixel(x1+1, yPt, color);
            }
        }
        else {
            for(uint16_t yPt = y2; yPt <= y1; yPt++) {
                ST7735_DrawPixel(x2, yPt, color);
                ST7735_DrawPixel(x2+1, yPt, color);
            }
        }
    }
    else if (y2 == y1) { //if horizontal line
        if(x2 >= x1) {
            for(uint16_t xPt = x1; xPt <= x2; xPt++) {
                ST7735_DrawPixel(xPt, y1, color);
                ST7735_DrawPixel(xPt+1, y1, color);
            }
        }
        else {
            for(uint16_t xPt = x2; xPt <= x1; xPt++) {
                ST7735_DrawPixel(xPt, y2, color);
                ST7735_DrawPixel(xPt+1, y2, color);
            }
        }
    }
    
    //all other cases have to do with relative positions of x1 and x2
    else if(x2 > x1 && y2 > y1) {
        if((x2 - x1) >= (y2 - y1)) {
            slope = ((float)y2-(float)y1)/((float)x2-(float)x1);    //calculate slope
            for(uint16_t xPt = x1; xPt <= x2; xPt++) {
                ST7735_DrawPixel(xPt, (y1 + ((slope)*((float)(xPt-x1)))),color);    //slope point formula
                ST7735_DrawPixel(xPt+1, (y1 + ((slope)*((float)(xPt-x1)))),color);
            }
        }
        else {
            slope = ((float)x2-(float)x1)/((float)y2-(float)y1);
            for(uint16_t yPt = y1; yPt <= y2; yPt++) {
                ST7735_DrawPixel(x1 + ((slope)*((float)(yPt-y1))), yPt, color);
                ST7735_DrawPixel(x1 + ((slope)*((float)(yPt-y1)))+1, yPt, color);
            }
        }
    }
    else if (x2 > x1 && y1 > y2) {
        if((x2 - x1) >= (y1 - y2)) {
            slope = ((float)y2-(float)y1)/((float)x2-(float)x1);    //calculate slope
            for(uint16_t xPt = x1; xPt <= x2; xPt++) {
                ST7735_DrawPixel(xPt, (y1 + ((slope)*((float)(xPt-x1)))),color); //slope point formula
                ST7735_DrawPixel(xPt+1, (y1 + ((slope)*((float)(xPt-x1)))),color);
            }
        }
        else {
            slope = ((float)x1-(float)x2)/((float)y1-(float)y2);
            for(uint16_t yPt = y2; yPt <= y1; yPt++) {
                ST7735_DrawPixel(x2 + ((slope)*((float)(yPt-y2))), yPt, color);
                ST7735_DrawPixel(x2 + ((slope)*((float)(yPt-y2)))+1, yPt, color);         
            }
        }
    }
    else if (x1 > x2 && y2 > y1) {
        if((x1 - x2) >= (y2 - y1)) {
            slope = ((float)y1-(float)y2)/((float)x1-(float)x2);    //calculate slope
            for(uint16_t xPt = x2; xPt <= x1; xPt++) {
                ST7735_DrawPixel(xPt, (y2 + ((slope)*((float)(xPt-x2)))),color); //slope point formula
                ST7735_DrawPixel(xPt+1, (y2 +((slope)*((float)(xPt-x2)))),color);
            }
        }
        else {
            slope = ((float)x2-(float)x1)/((float)y2-(float)y1);
            for(uint16_t yPt = y1; yPt <= y2; yPt++) {
                ST7735_DrawPixel(x1 + ((slope)*((float)(yPt-y1))), yPt, color);
                ST7735_DrawPixel(x1 + ((slope)*((float)(yPt-y1)))+1, yPt, color);
            }
        }
    }
    else if (x1 > x2 && y1 > y2){
        if((x1 - x2) >= (y1 - y2)) {    
            slope = ((float)y1-(float)y2)/((float)x1-(float)x2);    //calculate slope
            for(uint16_t xPt = x2; xPt <= x1; xPt++) {
                ST7735_DrawPixel(xPt, (y2 + (uint16_t)((slope)*((float)(xPt-x2)))),color); //slope point formula
                ST7735_DrawPixel(xPt+1, (y2 + (uint16_t)((slope)*((float)(xPt-x2)))),color);
            }
        }
        else {
            slope = ((float)x1-(float)x2)/((float)y1-(float)y2);
            for(uint16_t yPt = y2; yPt <= y1; yPt++) {
                ST7735_DrawPixel(x2 + ((slope)*((float)(yPt-y2))), yPt, color);
                ST7735_DrawPixel(x2 + ((slope)*((float)(yPt-y2)))+1, yPt, color);        
            }
        }
    }

}

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
void drawHour(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    float slope = 0;
    if (x2 == x1) { //if vertical line
        if(y2 >= y1) {
            for(uint16_t yPt = y1; yPt <= y2; yPt++) {
                ST7735_DrawPixel(x1, yPt, color);
                ST7735_DrawPixel(x1+1, yPt, color);
                ST7735_DrawPixel(x1, yPt+1, color);
                ST7735_DrawPixel(x1+1, yPt+1, color);
            }
        }
        else {
            for(uint16_t yPt = y2; yPt <= y1; yPt++) {
                ST7735_DrawPixel(x2, yPt, color);
                ST7735_DrawPixel(x2+1, yPt, color);
                ST7735_DrawPixel(x2, yPt+1, color);
                ST7735_DrawPixel(x2+1, yPt+1, color);
            }
        }
    }
    else if (y2 == y1) { //if horizontal line
        if(x2 >= x1) {
            for(uint16_t xPt = x1; xPt <= x2; xPt++) {
                ST7735_DrawPixel(xPt, y1, color);
                ST7735_DrawPixel(xPt+1, y1, color);
                ST7735_DrawPixel(xPt, y1+1, color);
                ST7735_DrawPixel(xPt+1, y1+1, color);
            }
        }
        else {
            for(uint16_t xPt = x2; xPt <= x1; xPt++) {
                ST7735_DrawPixel(xPt, y2, color);
                ST7735_DrawPixel(xPt+1, y2, color);
                ST7735_DrawPixel(xPt, y2+1, color);
                ST7735_DrawPixel(xPt+1, y2+1, color);
            }
        }
    }
    
    //all other cases have to do with relative positions of x1 and x2
    else if(x2 > x1 && y2 > y1) {
        if((x2 - x1) >= (y2 - y1)) {
            slope = ((float)y2-(float)y1)/((float)x2-(float)x1);    //calculate slope
            for(uint16_t xPt = x1; xPt <= x2; xPt++) {
                ST7735_DrawPixel(xPt, (y1 + ((slope)*((float)(xPt-x1)))),color);    //slope point formula
                ST7735_DrawPixel(xPt+1, (y1 + ((slope)*((float)(xPt-x1)))),color);
                ST7735_DrawPixel(xPt, (y1 + ((slope)*((float)(xPt-x1))))+1,color);
                ST7735_DrawPixel(xPt+1, (y1 + ((slope)*((float)(xPt-x1))))+1,color);
            }
        }
        else {
            slope = ((float)x2-(float)x1)/((float)y2-(float)y1);
            for(uint16_t yPt = y1; yPt <= y2; yPt++) {
                ST7735_DrawPixel(x1 + ((slope)*((float)(yPt-y1))), yPt, color);
                ST7735_DrawPixel(x1 + ((slope)*((float)(yPt-y1)))+1, yPt, color);
                ST7735_DrawPixel(x1 + ((slope)*((float)(yPt-y1))), yPt+1, color);
                ST7735_DrawPixel(x1 + ((slope)*((float)(yPt-y1)))+1, yPt+1, color);
            }
        }
    }
    else if (x2 > x1 && y1 > y2) {
        if((x2 - x1) >= (y1 - y2)) {
            slope = ((float)y2-(float)y1)/((float)x2-(float)x1);    //calculate slope
            for(uint16_t xPt = x1; xPt <= x2; xPt++) {
                ST7735_DrawPixel(xPt, (y1 + ((slope)*((float)(xPt-x1)))),color); //slope point formula
                ST7735_DrawPixel(xPt+1, (y1 + ((slope)*((float)(xPt-x1)))),color);
                ST7735_DrawPixel(xPt, (y1 + ((slope)*((float)(xPt-x1))))+1,color);
                ST7735_DrawPixel(xPt+1, (y1 + ((slope)*((float)(xPt-x1))))+1,color);
            }
        }
        else {
            slope = ((float)x1-(float)x2)/((float)y1-(float)y2);
            for(uint16_t yPt = y2; yPt <= y1; yPt++) {
                ST7735_DrawPixel(x2 + ((slope)*((float)(yPt-y2))), yPt, color);
                ST7735_DrawPixel(x2 + ((slope)*((float)(yPt-y2)))+1, yPt, color);
                ST7735_DrawPixel(x2 + ((slope)*((float)(yPt-y2))), yPt+1, color);
                ST7735_DrawPixel(x2 + ((slope)*((float)(yPt-y2)))+1, yPt+1, color);            
            }
        }
    }
    else if (x1 > x2 && y2 > y1) {
        if((x1 - x2) >= (y2 - y1)) {
            slope = ((float)y1-(float)y2)/((float)x1-(float)x2);    //calculate slope
            for(uint16_t xPt = x2; xPt <= x1; xPt++) {
                ST7735_DrawPixel(xPt, (y2 + ((slope)*((float)(xPt-x2)))),color); //slope point formula
                ST7735_DrawPixel(xPt+1, (y2 +((slope)*((float)(xPt-x2)))),color);
                ST7735_DrawPixel(xPt, (y2 + ((slope)*((float)(xPt-x2))))+1,color);
                ST7735_DrawPixel(xPt+1, (y2 + ((slope)*((float)(xPt-x2))))+1,color);
            }
        }
        else {
            slope = ((float)x2-(float)x1)/((float)y2-(float)y1);
            for(uint16_t yPt = y1; yPt <= y2; yPt++) {
                ST7735_DrawPixel(x1 + ((slope)*((float)(yPt-y1))), yPt, color);
                ST7735_DrawPixel(x1 + ((slope)*((float)(yPt-y1)))+1, yPt, color);
                ST7735_DrawPixel(x1 + ((slope)*((float)(yPt-y1))), yPt+1, color);
                ST7735_DrawPixel(x1 + ((slope)*((float)(yPt-y1)))+1, yPt+1, color);
            }
        }
    }
    else if (x1 > x2 && y1 > y2){
        if((x1 - x2) >= (y1 - y2)) {    
            slope = ((float)y1-(float)y2)/((float)x1-(float)x2);    //calculate slope
            for(uint16_t xPt = x2; xPt <= x1; xPt++) {
                ST7735_DrawPixel(xPt, (y2 + (uint16_t)((slope)*((float)(xPt-x2)))),color); //slope point formula
                ST7735_DrawPixel(xPt+1, (y2 + (uint16_t)((slope)*((float)(xPt-x2)))),color);
                ST7735_DrawPixel(xPt, (y2 + (uint16_t)((slope)*((float)(xPt-x2))))+1,color);
                ST7735_DrawPixel(xPt+1, (y2 + (uint16_t)((slope)*((float)(xPt-x2))))+1,color);
            }
        }
        else {
            slope = ((float)x1-(float)x2)/((float)y1-(float)y2);
            for(uint16_t yPt = y2; yPt <= y1; yPt++) {
                ST7735_DrawPixel(x2 + ((slope)*((float)(yPt-y2))), yPt, color);
                ST7735_DrawPixel(x2 + ((slope)*((float)(yPt-y2)))+1, yPt, color);
                ST7735_DrawPixel(x2 + ((slope)*((float)(yPt-y2))), yPt+1, color);
                ST7735_DrawPixel(x2 + ((slope)*((float)(yPt-y2)))+1, yPt+1, color);            
            }
        }
    }

}


//*************displaySW********************************************
//  Draws stopwatch screen
//  Inputs: none
//  Output: none
void displaySW(){
	if(clock_Mode == 3) {
		ST7735_FillScreen(ST7735_WHITE);
		ST7735_SetTextColor(ST7735_BLACK);
		//Prints time in top left
		ST7735_SetCursor(0,0);
		if(global_Hour < 10){
			ST7735_OutUDec(0);
			ST7735_OutUDec(global_Hour);
		}
		else{
			ST7735_OutUDec(global_Hour);
		}
		ST7735_OutString(":");
		if(global_Min < 10){
			ST7735_OutUDec(0);
			ST7735_OutUDec(global_Min);
		}
		else{
			ST7735_OutUDec(global_Min);
		}
		
		ST7735_DrawStringWhiteBg(11, 0, "Stop Watch", ST7735_BLACK);
		ST7735_DrawStringWhiteBg(17, 15, "Back", ST7735_BLACK);
		ST7735_DrawStringWhiteBg(0, 14, "Start/Stop", ST7735_BLACK);
		ST7735_DrawStringWhiteBg(0, 15, "Reset", ST7735_BLACK);
		//Print Stop Watch Time
		ST7735_SetCursor(7,6);
		if(stopwatch_Hour < 10){
			ST7735_OutUDec(0);
			ST7735_OutUDec(stopwatch_Hour);
		}
		else{
			ST7735_OutUDec(stopwatch_Hour);
		}
		ST7735_OutString(":");
		if(stopwatch_Min < 10){
			ST7735_OutUDec(0);
			ST7735_OutUDec(stopwatch_Min);
		}
		else{
			ST7735_OutUDec(stopwatch_Min);
		}
		ST7735_OutString(":");
		if(stopwatch_Sec < 10){
			ST7735_OutUDec(0);
			ST7735_OutUDec(stopwatch_Sec);
		}
		else {
			ST7735_OutUDec(stopwatch_Sec);
		}
	}
	else {
		ST7735_FillScreen(ST7735_BLACK);
		ST7735_SetTextColor(ST7735_WHITE);
		//Prints time in top left
		ST7735_SetCursor(0,0);
		if(global_Hour < 10){
			ST7735_OutUDec(0);
			ST7735_OutUDec(global_Hour);
		}
		else{
			ST7735_OutUDec(global_Hour);
		}
		ST7735_OutString(":");
		if(global_Min < 10){
			ST7735_OutUDec(0);
			ST7735_OutUDec(global_Min);
		}
		else{
			ST7735_OutUDec(global_Min);
		}
		
		ST7735_DrawString(11, 0, "Stop Watch", 0xFFFF);
		ST7735_DrawString(17, 15, "Back", 0xFFFF);
		ST7735_DrawString(0, 14, "Start/Stop", 0xFFFF);
		ST7735_DrawString(0, 15, "Reset", 0xFFFF);
		//Print Stop Watch Time
		ST7735_SetCursor(7,6);
		if(stopwatch_Hour < 10){
			ST7735_OutUDec(0);
			ST7735_OutUDec(stopwatch_Hour);
		}
		else{
			ST7735_OutUDec(stopwatch_Hour);
		}
		ST7735_OutString(":");
		if(stopwatch_Min < 10){
			ST7735_OutUDec(0);
			ST7735_OutUDec(stopwatch_Min);
		}
		else{
			ST7735_OutUDec(stopwatch_Min);
		}
		ST7735_OutString(":");
		if(stopwatch_Sec < 10){
			ST7735_OutUDec(0);
			ST7735_OutUDec(stopwatch_Sec);
		}
		else{
			ST7735_OutUDec(stopwatch_Sec);
		}
	}
	
}	

//*************displaySWBack********************************************
//  Draws stopwatch back screen
//  Inputs: none
//  Output: none
void displaySWBack(){
	displaySW();
	ST7735_DrawString(17, 15, "Back", ST7735_YELLOW);
}

//*************displaySWSRS********************************************
//  Draws stopwatch start/stop screen
//  Inputs: none
//  Output: none
void displaySWSRS(){
	displaySW();
	ST7735_DrawString(0, 14, "Start/Stop", ST7735_YELLOW);
}

//*************displaySWReset********************************************
//  Draws stopwatch reset screen
//  Inputs: none
//  Output: none
void displaySWReset(){
	displaySW();
	ST7735_DrawString(0, 15, "Reset", ST7735_YELLOW);
}

//*************displayMain********************************************
// Draws the Main Screen
// Input: str, the mode to display at bottom center of screen
//  Output: none
void displayMain(char* str){
	uint16_t mode = 0;
	//Prints clock based on clock mode
	if(clock_Mode == 3){
		ST7735_FillScreen(ST7735_WHITE);
		ST7735_SetTextColor(ST7735_BLACK);
		ST7735_DrawBitmap(24, 119, clock3, 80, 80);
		mode = 0x0000;
	}
	else{
		ST7735_FillScreen(ST7735_BLACK);
		ST7735_SetTextColor(ST7735_WHITE);
		if(clock_Mode == 0){
			ST7735_DrawBitmap(24, 119, clock, 80, 80);
		}
		if(clock_Mode == 1){
			ST7735_DrawBitmap(24, 119, clock1, 80, 80);
		}
		if(clock_Mode == 2){
			ST7735_DrawBitmap(24, 119, clock2, 80, 80);
		}
		mode = 0xFFFF;
	}
	drawSec(62 ,79, secX[global_Sec], secY[global_Sec], mode);
	drawMin(62 ,79, minX[global_Min], minY[global_Min], mode);
	drawHour(62 ,79, hourX[(global_Hour%12)*5+(global_Min/12)], hourY[(global_Hour%12)*5+(global_Min/12)], mode);
	
	//Prints time in top left
	ST7735_SetCursor(0,0);
	if(global_Hour < 10){
		ST7735_OutUDec(0);
		ST7735_OutUDec(global_Hour);
	}
	else{
		ST7735_OutUDec(global_Hour);
	}
	ST7735_OutString(":");
	if(global_Min < 10){
		ST7735_OutUDec(0);
		ST7735_OutUDec(global_Min);
	}
	else{
		ST7735_OutUDec(global_Min);
	}
	
	//Prints "Home in top right
	ST7735_DrawString(17, 0, "Home", mode);
	
	//Prints mode in bottom center
	if(strlen(str) < 8){
		ST7735_DrawString(7, 15, str, mode);
	}
	else{
		ST7735_DrawString(6, 15, str, mode);
	}
	
	//Prints alarm indicators
	if(!alarm1_Enable){
		ST7735_DrawString(0, 13, "A1", mode);
	}
	else{
		if(clock_Mode == 3) {
			ST7735_DrawStringWhiteBg(0, 13, "A1", ST7735_RED);
		}
		else {
			ST7735_DrawString(0, 13, "A1", ST7735_RED);
		}
	}
	if(!alarm2_Enable){
		ST7735_DrawString(0, 14, "A2", mode);
	}
	else{
		if(clock_Mode == 3) {
			ST7735_DrawStringWhiteBg(0, 14, "A2", ST7735_RED);
		}
		else {
			ST7735_DrawString(0, 14, "A2", ST7735_RED);
		}
	}
	if(!snooze_Enable){
		ST7735_DrawString(0, 15, "S", mode);
	}
	else{
		if(clock_Mode == 3) {
			ST7735_DrawStringWhiteBg(0, 15, "S", ST7735_RED);
		}
		else {
			ST7735_DrawString(0, 15, "S", ST7735_RED);
		}
	}
}

//*************displaySetTimeDefault********************************************
// Draws the set time screen template
// Input: none
//  Output: none
void displaySetTimeDefault() {
	ST7735_SetCursor(0,0);
	if(clock_Mode == 3) {
		ST7735_FillScreen(ST7735_WHITE);
		ST7735_SetTextColor(ST7735_BLACK);
		if(global_Hour <10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(global_Hour);
		ST7735_OutChar(':');
		if(global_Min<10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(global_Min);
		
		ST7735_DrawStringWhiteBg(13,0,"Set Time",ST7735_BLACK);
		ST7735_DrawStringWhiteBg(17,15,"Back",ST7735_BLACK);
		
		ST7735_SetCursor(8,6);
		if(global_Hour <10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(global_Hour);
		ST7735_OutChar(':');
		if(global_Min<10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(global_Min);

		
	}
	else {
		ST7735_FillScreen(ST7735_BLACK);
		ST7735_SetTextColor(ST7735_WHITE);
		if(global_Hour <10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(global_Hour);
		ST7735_OutChar(':');
		if(global_Min<10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(global_Min);
		
		ST7735_DrawString(13,0,"Set Time",ST7735_WHITE);
		ST7735_DrawString(17,15,"Back",ST7735_WHITE);
		
		ST7735_SetCursor(8,6);
		if(global_Hour <10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(global_Hour);
		ST7735_OutChar(':');
		if(global_Min<10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(global_Min);
	}
}

//*************displaySetTimeHourSelect********************************************
// Draws the set time hour select screen
// Input: none
//  Output: none
void displaySetTimeHourSelect() {
	displaySetTimeDefault();
	
	//draw X indicating selected
	drawHour(49,50,55,55,ST7735_RED);
	drawHour(55,50,49,55,ST7735_RED);
	
	//set hour to yellow
	ST7735_SetTextColor(ST7735_YELLOW);
	ST7735_SetCursor(8,6);
	if(global_Hour <10) {
		ST7735_OutUDec(0);
	}
	ST7735_OutUDec(global_Hour);
}

//*************displaySetTimeMinSelect********************************************
// Draws the set time min select screen
// Input: none
//  Output: none
void displaySetTimeMinSelect() {
	displaySetTimeDefault();
	
	//draw X indicating selected
	drawHour(67,50,73,55,ST7735_RED);
	drawHour(73,50,67,55,ST7735_RED);

	//set minute to yellow
	ST7735_SetTextColor(ST7735_YELLOW);
	ST7735_SetCursor(11,6);
	if(global_Min <10) {
		ST7735_OutUDec(0);
	}
	ST7735_OutUDec(global_Min);
}

//*************displaySetTimeHour********************************************
// Draws the set time hour screen
// Input: none
//  Output: none
void displaySetTimeHour() {
	displaySetTimeDefault();
	
	//set hour to yellow
	ST7735_SetTextColor(ST7735_YELLOW);
	ST7735_SetCursor(8,6);
	if(global_Hour <10) {
		ST7735_OutUDec(0);
	}
	ST7735_OutUDec(global_Hour);
	
}
//*************displaySetTimeMin********************************************
// Draws the set time min screen
// Input: none
//  Output: none
void displaySetTimeMin() {
	displaySetTimeDefault();
	
	//set minute to yellow
	ST7735_SetTextColor(ST7735_YELLOW);
	ST7735_SetCursor(11,6);
	if(global_Min <10) {
		ST7735_OutUDec(0);
	}
	ST7735_OutUDec(global_Min);
	
}
//*************displaySetTimeBack********************************************
// Draws the set time back screen
// Input: none
//  Output: none
void displaySetTimeBack() {
	displaySetTimeDefault();
	ST7735_DrawString(17,15,"Back",ST7735_YELLOW);
}

//*************displayAlarm1Default********************************************
// Draws the alarm 1 default template
// Input: none
//  Output: none
void displayAlarm1Default() {
	ST7735_SetCursor(0,0);
	
	if(clock_Mode == 3) {
		ST7735_FillScreen(ST7735_WHITE);
		ST7735_SetTextColor(ST7735_BLACK);
		if(global_Hour <10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(global_Hour);
		ST7735_OutChar(':');
		if(global_Min<10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(global_Min);
		
		ST7735_DrawStringWhiteBg(14,0,"Alarm 1",ST7735_BLACK);
		if(alarm1_Enable) {
			ST7735_DrawStringWhiteBg(0,15,"Disable",ST7735_BLACK);
		}
		else {
			ST7735_DrawStringWhiteBg(0,15,"Enable ",ST7735_BLACK);
		}
		ST7735_DrawStringWhiteBg(17,15,"Back",ST7735_BLACK);
		
		ST7735_SetCursor(8,6);
		if(alarm1_Hour <10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(alarm1_Hour);
		ST7735_OutChar(':');
		if(alarm1_Min<10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(alarm1_Min);

		
	}
	else {
		ST7735_FillScreen(ST7735_BLACK);
		ST7735_SetTextColor(ST7735_WHITE);
		if(global_Hour <10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(global_Hour);
		ST7735_OutChar(':');
		if(global_Min<10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(global_Min);
		
		ST7735_DrawString(14,0,"Alarm 1",ST7735_WHITE);
		if(alarm1_Enable) {
			ST7735_DrawString(0,15,"Disable",ST7735_WHITE);
		}
		else {
			ST7735_DrawString(0,15,"Enable ",ST7735_WHITE);
		}
		ST7735_DrawString(17,15,"Back",ST7735_WHITE);
		
		ST7735_SetCursor(8,6);
		if(alarm1_Hour <10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(alarm1_Hour);
		ST7735_OutChar(':');
		if(alarm1_Min<10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(alarm1_Min);
	}
}

//*************displayAlarm1HourSelect********************************************
// Draws the alarm 1 hour select screen
// Input: none
//  Output: none
void displayAlarm1HourSelect() {
	displayAlarm1Default();
	
	//draw X indicating selected
	drawHour(49,50,55,55,ST7735_RED);
	drawHour(55,50,49,55,ST7735_RED);
	
	//set hour to yellow
	ST7735_SetTextColor(ST7735_YELLOW);
	ST7735_SetCursor(8,6);
	if(alarm1_Hour <10) {
		ST7735_OutUDec(0);
	}
	ST7735_OutUDec(alarm1_Hour);
}

//*************displayAlarm1MinSelect********************************************
// Draws the alarm 1 min select screen
// Input: none
//  Output: none
void displayAlarm1MinSelect() {
	displayAlarm1Default();
	
	//draw X indicating selected
	drawHour(67,50,73,55,ST7735_RED);
	drawHour(73,50,67,55,ST7735_RED);

	//set minute to yellow
	ST7735_SetTextColor(ST7735_YELLOW);
	ST7735_SetCursor(11,6);
	if(alarm1_Min <10) {
		ST7735_OutUDec(0);
	}
	ST7735_OutUDec(alarm1_Min);
}

//*************displayAlarm1Hour********************************************
// Draws the alarm 1 hour screen
// Input: none
//  Output: none
void displayAlarm1Hour() {
	displayAlarm1Default();
	
	//set hour to yellow
	ST7735_SetTextColor(ST7735_YELLOW);
	ST7735_SetCursor(8,6);
	if(alarm1_Hour <10) {
		ST7735_OutUDec(0);
	}
	ST7735_OutUDec(alarm1_Hour);
	
}

//*************displayAlarm1Min********************************************
// Draws the alarm 1 min screen
// Input: none
//  Output: none
void displayAlarm1Min() {
	displayAlarm1Default();
	
	//set minute to yellow
	ST7735_SetTextColor(ST7735_YELLOW);
	ST7735_SetCursor(11,6);
	if(alarm1_Min <10) {
		ST7735_OutUDec(0);
	}
	ST7735_OutUDec(alarm1_Min);
	
}

//*************displayAlarm1Enable********************************************
// Draws the alarm 1 enable screen
// Input: none
//  Output: none
void displayAlarm1Enable() {
	displayAlarm1Default();
	if(alarm1_Enable) {
		ST7735_DrawString(0,15,"Disable",ST7735_YELLOW);
	}
	else {
		ST7735_DrawString(0,15,"Enable ",ST7735_YELLOW);
	}
}

//*************displayAlarm1Back********************************************
// Draws the alarm 1 back screen
// Input: none
//  Output: none
void displayAlarm1Back() {
	displayAlarm1Default();
	ST7735_DrawString(17,15,"Back",ST7735_YELLOW);
}

//*************displayAlarm2Default********************************************
// Draws the alarm 2 default template
// Input: none
//  Output: none
void displayAlarm2Default() {
	ST7735_SetCursor(0,0);
	if(clock_Mode == 3) {
		ST7735_FillScreen(ST7735_WHITE);
		ST7735_SetTextColor(ST7735_BLACK);
		if(global_Hour <10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(global_Hour);
		ST7735_OutChar(':');
		if(global_Min<10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(global_Min);
		
		ST7735_DrawStringWhiteBg(14,0,"Alarm 2",ST7735_BLACK);
		if(alarm2_Enable) {
			ST7735_DrawStringWhiteBg(0,15,"Disable",ST7735_BLACK);
		}
		else {
			ST7735_DrawStringWhiteBg(0,15,"Enable ",ST7735_BLACK);
		}
			
		ST7735_DrawStringWhiteBg(17,15,"Back",ST7735_BLACK);
		
		ST7735_SetCursor(8,6);
		if(alarm2_Hour <10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(alarm2_Hour);
		ST7735_OutChar(':');
		if(alarm2_Min<10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(alarm2_Min);

		
	}
	else {
		ST7735_FillScreen(ST7735_BLACK);
		ST7735_SetTextColor(ST7735_WHITE);
		if(global_Hour <10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(global_Hour);
		ST7735_OutChar(':');
		if(global_Min<10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(global_Min);
		
		ST7735_DrawString(14,0,"Alarm 2",ST7735_WHITE);
		if(alarm2_Enable) {
			ST7735_DrawString(0,15,"Disable",ST7735_WHITE);
		}
		else {
			ST7735_DrawString(0,15,"Enable ",ST7735_WHITE);
		}
		ST7735_DrawString(17,15,"Back",ST7735_WHITE);
		
		ST7735_SetCursor(8,6);
		if(alarm2_Hour <10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(alarm2_Hour);
		ST7735_OutChar(':');
		if(alarm2_Min<10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(alarm2_Min);
	}
}

//*************displayAlarm2HourSelect********************************************
// Draws the alarm 2 hour select screen
// Input: none
//  Output: none
void displayAlarm2HourSelect() {
	displayAlarm2Default();
	
	//draw X indicating selected
	drawHour(49,50,55,55,ST7735_RED);
	drawHour(55,50,49,55,ST7735_RED);
	
	//set hour to yellow
	ST7735_SetTextColor(ST7735_YELLOW);
	ST7735_SetCursor(8,6);
	if(alarm2_Hour <10) {
		ST7735_OutUDec(0);
	}
	ST7735_OutUDec(alarm2_Hour);
}

//*************displayAlarm2MinSelect********************************************
// Draws the alarm 2 min select screen
// Input: none
//  Output: none
void displayAlarm2MinSelect() {
	displayAlarm2Default();
	
	//draw X indicating selected
	drawHour(67,50,73,55,ST7735_RED);
	drawHour(73,50,67,55,ST7735_RED);

	//set minute to yellow
	ST7735_SetTextColor(ST7735_YELLOW);
	ST7735_SetCursor(11,6);
	if(alarm2_Min <10) {
		ST7735_OutUDec(0);
	}
	ST7735_OutUDec(alarm2_Min);
}

//*************displayAlarm2Hour********************************************
// Draws the alarm 2 hour screen
// Input: none
//  Output: none
void displayAlarm2Hour() {
	displayAlarm2Default();
	
	//set hour to yellow
	ST7735_SetTextColor(ST7735_YELLOW);
	ST7735_SetCursor(8,6);
	if(alarm2_Hour <10) {
		ST7735_OutUDec(0);
	}
	ST7735_OutUDec(alarm2_Hour);
	
}

//*************displayAlarm2Min********************************************
// Draws the alarm 2 min screen
// Input: none
//  Output: none
void displayAlarm2Min() {
	displayAlarm2Default();
	
	//set minute to yellow
	ST7735_SetTextColor(ST7735_YELLOW);
	ST7735_SetCursor(11,6);
	if(alarm2_Min <10) {
		ST7735_OutUDec(0);
	}
	ST7735_OutUDec(alarm2_Min);
	
}

//*************displayAlarm2Enable********************************************
// Draws the alarm 2 enable screen
// Input: none
//  Output: none
void displayAlarm2Enable() {
	displayAlarm2Default();
	if(alarm2_Enable) {
		ST7735_DrawString(0,15,"Disable",ST7735_YELLOW);
	}
	else {
		ST7735_DrawString(0,15,"Enable ",ST7735_YELLOW);
	}
}

//*************displayAlarm2Back********************************************
// Draws the alarm 2 back screen
// Input: none
//  Output: none
void displayAlarm2Back() {
	displayAlarm2Default();
	ST7735_DrawString(17,15,"Back",ST7735_YELLOW);
}

//*************displayAlarmLock********************************************
// Draws the alarm lock template
// Input: none
//  Output: none
void displayAlarmLock(){
	if(clock_Mode == 3) {
		ST7735_FillScreen(ST7735_WHITE);
		ST7735_SetTextColor(ST7735_BLACK);
		ST7735_SetCursor(0,0);
		if(global_Hour <10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(global_Hour);
		ST7735_OutChar(':');
		if(global_Min<10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(global_Min);
		ST7735_DrawStringWhiteBg(7, 6, "WAKE UP", ST7735_BLACK);
		ST7735_DrawStringWhiteBg(0, 15, "Snooze", ST7735_BLACK);
		ST7735_DrawStringWhiteBg(17, 15, "Stop", ST7735_BLACK);
			
	}
	else {
		ST7735_FillScreen(ST7735_BLACK);
		ST7735_SetTextColor(ST7735_WHITE);
		ST7735_SetCursor(0,0);
		if(global_Hour <10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(global_Hour);
		ST7735_OutChar(':');
		if(global_Min<10) {
			ST7735_OutUDec(0);
		}
		ST7735_OutUDec(global_Min);
		ST7735_DrawString(7, 6, "WAKE UP", ST7735_WHITE);
		ST7735_DrawString(0, 15, "Snooze", ST7735_WHITE);
		ST7735_DrawString(17, 15, "Stop", ST7735_WHITE);
	}
}

//*************displayAlarmLockSnooze********************************************
// Draws the alarm lock snooze screen
// Input: none
//  Output: none
void displayAlarmLockSnooze(){
	displayAlarmLock();
	ST7735_DrawString(0, 15, "Snooze", ST7735_YELLOW);
}

//*************displayAlarmLockStop********************************************
// Draws the alarm lock stop screen
// Input: none
//  Output: none
void displayAlarmLockStop(){
	displayAlarmLock();
	ST7735_DrawString(17, 15, "Stop", ST7735_YELLOW);
}

