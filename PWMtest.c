// PWMtest.c
// Runs on TM4C123
// Use PWM0/PB6 and PWM1/PB7 to generate pulse-width modulated outputs.
// Daniel Valvano
// March 28, 2014

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2014
  Program 6.7, section 6.3.2

 Copyright 2014 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
#include <stdint.h>
#include <stdio.h>
#include "PLL.h"
#include "newpwm.h"
#include "tm4c123gh6pm.h"
void WaitForInterrupt(void);  // low power mode
void delay(unsigned long halfsecs);
int main(void){
		PLL_Init();                      // bus clock at 16 MHz
  	PWM_Init_PA7(5000,250);         // 1ms / 20ms 
  while(1){
		delay(10);
		PWM_Duty_PA7(375);       // 1.5 ms 
		delay(10);
		PWM_Duty_PA7(500);       // 2 ms
		delay(10);
		PWM_Duty_PA7(250);     // 1 ms

  }
}
void delay(unsigned long halfsecs){
  unsigned long count;
  
  while(halfsecs > 0 ) { // repeat while there are still halfsecs to delay
    count = 1538460; // 400000*0.5/0.13 that it takes 0.13 sec to count down to zero
    while (count > 0) { 
      count--;
    } // This while loop takes approximately 3 cycles
    halfsecs--;
  }
}
