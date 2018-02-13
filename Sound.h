/* ******** Sound.h ************** 
 * Samuel Zhang, Zi Zhou Wang
 * 2/6/2018
 * Port init for sound and output
 * Lab 3
 * Saadallah
 * 2/6/2018
 */
 
//************* Sound_Init********************************************
//  Initialize sound port (PE2)
//  Inputs: none
//  Output: none 
void Sound_Init(void);
 
//*************Sound_On********************************************
//  Toggle sound and run a delay for next toggle
//  Inputs: none
//  Output: none  
void Sound_On(void);

//************* Sound_Off********************************************
//  Turn off port so that it doesn't accidentally heat up the transistor
//  Inputs: none
//  Output: none 
void Sound_Off(void);
