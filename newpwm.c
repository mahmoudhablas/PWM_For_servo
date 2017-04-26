#include <stdint.h>
#include "tm4c123gh6pm.h"
#define PWM_0_GENA_ACTCMPAD_ONE 0x000000C0  // Set the output signal to 1
#define PWM_0_GENA_ACTLOAD_ZERO 0x00000008  // Set the output signal to 0
#define PWM_0_GENB_ACTCMPBD_ONE 0x00000C00  // Set the output signal to 1
#define PWM_0_GENB_ACTLOAD_ZERO 0x00000008  // Set the output signal to 0

#define SYSCTL_RCC_USEPWMDIV    0x00100000  // Enable PWM Clock Divisor
#define SYSCTL_RCC_PWMDIV_M     0x000E0000  // PWM Unit Clock Divisor

//////////////////// PE5 ///////////////////////////////////

void PWM_Init_PE5(uint16_t period, uint16_t duty){
   SYSCTL_RCGCPWM_R |= 0x01;             // 1) activate PWM0
  SYSCTL_RCGCGPIO_R |= 0x10;            // 2) activate port E
  unsigned delay = SYSCTL_RCGCGPIO_R;
  GPIO_PORTE_AFSEL_R |= 0x20;           // enable alt funct on PE5
  GPIO_PORTE_PCTL_R &= ~0x0F00000;     // configure PE4 as PWM0
  GPIO_PORTE_PCTL_R |= 0x00400000;
  GPIO_PORTE_AMSEL_R &= ~0x20;          // disable analog functionality on PE5
  GPIO_PORTE_DEN_R |= 0x20;             // enable digital I/O on PE5
  SYSCTL_RCC_R = 0x00100000 |           // 3) use PWM divider
      (SYSCTL_RCC_R | (0x000E0000));   //    configure for /64 divider
  PWM0_2_CTL_R = 0;                     // 4) re-loading down-counting mode
  PWM0_2_GENB_R = 0xC08;                 // low on LOAD, high on CMPA down
  PWM0_2_LOAD_R = period - 1;           // 5) cycles needed to count down to 0
  PWM0_2_CMPB_R = duty - 1;             // 6) count value when output rises
  PWM0_2_CTL_R |= 0x00000001;           // 7) start PWM0
  PWM0_ENABLE_R |= 0x00000020;          // enable P?4/M0PWM
}
// change duty cycle of PB6
// duty is number of PWM clock cycles output is high  (2<=duty<=period-1)
void PWM_Duty_PE5(uint16_t duty){
  PWM0_2_CMPB_R = duty - 1;             // 6) count value when output rises
}

//////////////////////////////////////////////////////////////////////////////

/////////////////////// PB5 ////////////////////////////////////////////////

void PWM_Init_PB5(uint16_t period, uint16_t duty){
	
  SYSCTL_RCGCPWM_R |= 0x01;             // 1) activate PWM0
  SYSCTL_RCGCGPIO_R |= 0x02;            // 2) activate port B
  while((SYSCTL_PRGPIO_R&0x02) == 0){};
  GPIO_PORTB_AFSEL_R |= 0x20;           // enable alt funct on PB5
  GPIO_PORTB_PCTL_R &= ~0x0F00000;     // configure PB6 as PWM0
  GPIO_PORTB_PCTL_R |= 0x00400000;
  GPIO_PORTB_AMSEL_R &= ~0x20;          // disable analog functionality on PB5
  GPIO_PORTB_DEN_R |= 0x20;             // enable digital I/O on PB5
  SYSCTL_RCC_R = 0x00100000 |           // 3) use PWM divider
      (SYSCTL_RCC_R | (0x000E0000));   //    configure for /64 divider
  PWM0_1_CTL_R = 0;                     // 4) re-loading down-counting mode
  PWM0_1_GENB_R = 0xC08;                 // low on LOAD, high on CMPA down
  // PB6 goes low on LOAD
  // PB6 goes high on CMPA down
  PWM0_1_LOAD_R = period - 1;           // 5) cycles needed to count down to 0
  PWM0_1_CMPB_R = duty - 1;             // 6) count value when output rises
  PWM0_1_CTL_R |= 0x00000001;           // 7) start PWM0
  PWM0_ENABLE_R |= 0x00000008;          // enable PB4/M0PWM2
}
// change duty cycle of PB6
// duty is number of PWM clock cycles output is high  (2<=duty<=period-1)
void PWM_Duty_PB5(uint16_t duty){
  PWM0_1_CMPB_R = duty - 1;             // 6) count value when output rises
}

///////////////////////////////////////////////////////////////////

////////////////////// PD0 ///////////////////////////////////////


void PWM_Init_PD0(uint16_t period, uint16_t duty){
	SYSCTL_RCGCPWM_R |= SYSCTL_RCGCPWM_R1;             // 1) activate PWM1
  SYSCTL_RCGCGPIO_R |= 0x08;            // 2) activate port D
   unsigned delay = SYSCTL_RCGCGPIO_R;
  GPIO_PORTD_AFSEL_R |= 0x1;           // enable alt funct on PD0
  GPIO_PORTD_PCTL_R &= ~0x000000F;     // configure PD0 as PWM0
  GPIO_PORTD_PCTL_R |= 0x00000005;
  GPIO_PORTD_AMSEL_R &= ~0x01;          // disable analog functionality on PD0
  GPIO_PORTD_DEN_R |= 0x1;             // enable digital I/O on PD0
  SYSCTL_RCC_R = 0x00100000 |           // 3) use PWM divider
      (SYSCTL_RCC_R | (0x000E0000));   //    configure for /64 divider
  PWM1_0_CTL_R = 0;                     // 4) re-loading down-counting mode
  PWM1_0_GENA_R = 0xC8;                 // low on LOAD, high on CMPA down
  PWM1_0_LOAD_R = period - 1;           // 5) cycles needed to count down to 0
  PWM1_0_CMPA_R = duty - 1;             // 6) count value when output rises
  PWM1_0_CTL_R |= 0x00000001;           // 7) start PWM0
  PWM1_ENABLE_R |= 0x0000001;          // enable PB4/M0PWM2
}

void PWM_Duty_PD0(uint16_t duty){
  PWM1_0_CMPA_R = duty - 1;             // 6) count value when output rises
}

///////////////////////////////////////////////////////////////////////////

////////////////////////////// PD1 ////////////////////////////////////////

void PWM_Init_PD1(uint16_t period, uint16_t duty){
 	SYSCTL_RCGCPWM_R |= SYSCTL_RCGCPWM_R1;             // 1) activate PWM1
  SYSCTL_RCGCGPIO_R |= 0x08;            // 2) activate port D
   unsigned delay = SYSCTL_RCGCGPIO_R;
  GPIO_PORTD_AFSEL_R |= 0x2;           // enable alt funct on PD1
  GPIO_PORTD_PCTL_R &= ~0x00000F0;     // configure PD1 as PWM0
  GPIO_PORTD_PCTL_R |= 0x00000050;
  GPIO_PORTD_AMSEL_R &= ~0x02;          // disable analog functionality on PD1
  GPIO_PORTD_DEN_R |= 0x2;             // enable digital I/O on PD1
  SYSCTL_RCC_R = 0x00100000 |           // 3) use PWM divider
      (SYSCTL_RCC_R | (0x000E0000));   //    configure for /64 divider
  PWM1_0_CTL_R = 0;                     // 4) re-loading down-counting mode
  PWM1_0_GENB_R = 0xC08;                 // low on LOAD, high on CMPA down
  PWM1_0_LOAD_R = period - 1;           // 5) cycles needed to count down to 0
  PWM1_0_CMPB_R = duty - 1;             // 6) count value when output rises
  PWM1_0_CTL_R |= 0x00000001;           // 7) start PWM0
  PWM1_ENABLE_R |= 0x0000002;          // enable PB4/M0PWM2
}

void PWM_Duty_PD1(uint16_t duty){
  PWM1_0_CMPB_R = duty - 1;             // 6) count value when output rises
}

///////////////////////////////////////////////////////////////////////////

//////////////////////// PA6 /////////////////////////////////////////////

void PWM_Init_PA6(uint16_t period, uint16_t duty){
	
 	SYSCTL_RCGCPWM_R |= SYSCTL_RCGCPWM_R1;             // 1) activate PWM1
  SYSCTL_RCGCGPIO_R |= 0x01;            // 2) activate port A
 unsigned delay = SYSCTL_RCGCGPIO_R;
  GPIO_PORTA_AFSEL_R |= 0x40;           // enable alt funct on PA6
  GPIO_PORTA_PCTL_R &= ~0x0F000000;     // configure PA6 as PWM1
  GPIO_PORTA_PCTL_R |=  0x05000000;
  GPIO_PORTA_AMSEL_R &= ~0x040;          // disable analog functionality on PA6
  GPIO_PORTA_DEN_R |= 0x40;             // enable digital I/O on PA6
  SYSCTL_RCC_R = 0x00100000 |           // 3) use PWM divider
      (SYSCTL_RCC_R | (0x000E0000));   //    configure for /64 divider
  PWM1_1_CTL_R = 0;                     // 4) re-loading down-counting mode
  PWM1_1_GENA_R = 0xC8;                 // low on LOAD, high on CMPA down
  PWM1_1_LOAD_R = period - 1;           // 5) cycles needed to count down to 0
  PWM1_1_CMPA_R = duty - 1;             // 6) count value when output rises
  PWM1_1_CTL_R |= 0x00000001;           // 7) start PWM1
  PWM1_ENABLE_R |= 0x0000004;          // enable PA6/M0PWM2
}

void PWM_Duty_PA6(uint16_t duty){
  PWM1_1_CMPA_R = duty - 1;             // 6) count value when output rises
}
/////////////////////////////////////////////////////////////////////////////


//////////////////////// PA7 /////////////////////////////////////////////

void PWM_Init_PA7(uint16_t period, uint16_t duty){
	SYSCTL_RCGCPWM_R |= SYSCTL_RCGCPWM_R1;             // 1) activate PWM1
  SYSCTL_RCGCGPIO_R |= 0x01;            // 2) activate port A
  unsigned delay = SYSCTL_RCGCGPIO_R;
  GPIO_PORTA_AFSEL_R |= 0x80;           // enable alt funct on PA6
  GPIO_PORTA_PCTL_R &= ~0xF0000000;     // configure PD1 as PWM0
  GPIO_PORTA_PCTL_R |=  0x50000000;
  GPIO_PORTA_AMSEL_R &= ~0x080;          // disable analog functionality on PA6
  GPIO_PORTA_DEN_R |= 0x80;             // enable digital I/O on PA6
  SYSCTL_RCC_R = 0x00100000 |           // 3) use PWM divider
      (SYSCTL_RCC_R | (0x000E0000));   //    configure for /64 divider
  PWM1_1_CTL_R = 0;                     // 4) re-loading down-counting mode
  PWM1_1_GENB_R = 0xC08;                 // low on LOAD, high on CMPA down
  PWM1_1_LOAD_R = period - 1;           // 5) cycles needed to count down to 0
  PWM1_1_CMPB_R = duty - 1;             // 6) count value when output rises
  PWM1_1_CTL_R |= 0x00000001;           // 7) start PWM0
  PWM1_ENABLE_R |= 0x0000008;          // enable PB4/M0PWM2
}

void PWM_Duty_PA7(uint16_t duty){
  PWM1_1_CMPB_R = duty - 1;             // 6) count value when output rises
}
//////////////////////////////////////////////////////////////////////////////
