/*
 * dc_motor.c
 *
 *  Created on: Oct 7, 2021
 *      Author: Hana
 */

#include "dc_motor.h"
#include "gpio.h"

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

/* Description :
 * 1. Responsible to setup the direction for the two motor pins through GPIO driver
 * 2. Stop DC motor at the beginning through GPIO driver
 */

void DcMotor_Init(void)
{
  GPIO_setupPinDirection(DC_PORT ,DC_PIN_A , PIN_OUTPUT);
  GPIO_setupPinDirection(DC_PORT ,DC_PIN_B , PIN_OUTPUT);
  GPIO_writePin(DC_PORT ,DC_PIN_A , LOGIC_LOW);
  GPIO_writePin(DC_PORT ,DC_PIN_B , LOGIC_LOW);
}

/* Description :
 * 1. Responsible to rotate the motor clock-wise or anti clock-wise or stop the motor
 * based on the state input state value
 * 2. Send the required duty cycle to the PWM driver based on the required speed value
 */

void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
  switch(state)
  {
  case STOP :
	  GPIO_writePin(DC_PORT ,DC_PIN_A , LOGIC_LOW);
	  GPIO_writePin(DC_PORT ,DC_PIN_B , LOGIC_LOW);
	  break;
  case CLOCKWISE :
  	  GPIO_writePin(DC_PORT ,DC_PIN_A , LOGIC_HIGH);
  	  GPIO_writePin(DC_PORT ,DC_PIN_B , LOGIC_LOW);
  	  break;
  case ANTI_CLOCKWISE :
  	  GPIO_writePin(DC_PORT ,DC_PIN_A , LOGIC_LOW);
  	  GPIO_writePin(DC_PORT ,DC_PIN_B , LOGIC_HIGH);
  	  break;
  }

  switch(speed)
  {
  case 0 :
	  PWM_Timer0_Start(0);
	  break;
 /* 25% duty cycle */
  case 25 :
	  PWM_Timer0_Start(64);
	  break;
 /* 50% duty cycle */
  case 50 :
	  PWM_Timer0_Start(128);
	  break;
 /* 75% duty cycle */
  case 75 :
	  PWM_Timer0_Start(192);
	  break;
/* 100% duty cycle */
  case 100 :
	  PWM_Timer0_Start(255);
	  break;
  }

}
