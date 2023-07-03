/*
 * miniproject3.c
 *
 *  Created on: Oct 7, 2021
 *      Author: Hana Khater
 */

#include "lcd.h"
#include "gpio.h"
#include "lm35_sensor.h"
#include "adc.h"
#include "dc_motor.h"
#include "pwm_timer0.h"
#include "std_types.h"

#include <avr/io.h>

uint16 Temperature;
int main()
{
	/*Use internal voltage = 2.56 Volt as required with prescaler 8 */
	ADC_ConfigType ADC_Config = { INTERNAL_VOLTAGE , F_CPU_8 } ;
	ADC_init(&ADC_Config) ;
	DcMotor_Init();
	LCD_init();
	/* Moving the cursor so the string can be printed in the middle of the screen */
	LCD_moveCursor(1,2);
	LCD_displayString ("Temp =     C");

	while(1)
	{
		Temperature = LM35_getTemperature();

		if(Temperature < 30 )
		{
			DcMotor_Rotate(STOP , LOGIC_LOW);
			LCD_moveCursor(0,2);
			LCD_displayString ("Fan is OFF");
			LCD_moveCursor(1,9);
			LCD_intgerToString (Temperature);
			LCD_displayCharacter(' ');
		}
		else if(Temperature >= 30 && Temperature <60 )
		{
			DcMotor_Rotate(CLOCKWISE , 25);
			LCD_moveCursor(0,2);
			LCD_displayString ("Fan is  ON");
			LCD_moveCursor(1,9);
			LCD_intgerToString (Temperature);
			LCD_displayCharacter(' ');
		}
		else if(Temperature >=60 && Temperature <90 )
		{
			DcMotor_Rotate(CLOCKWISE , 50);
			LCD_moveCursor(0,2);
			LCD_displayString ("Fan is  ON");
			LCD_moveCursor(1,9);
			LCD_intgerToString (Temperature);
			LCD_displayCharacter(' ');
		}
		else if(Temperature >=90 && Temperature <120 )
		{
			DcMotor_Rotate(CLOCKWISE , 75);
			LCD_moveCursor(0,2);
			LCD_displayString ("Fan is  ON");
			LCD_moveCursor(1,9);
			LCD_intgerToString (Temperature);
			LCD_displayCharacter(' ');
		}
		else if(Temperature > 120 )
		{
			DcMotor_Rotate(CLOCKWISE , 100);
			LCD_moveCursor(0,2);
			LCD_displayString ("Fan is  ON");
			LCD_moveCursor(1,9);
			LCD_intgerToString (Temperature);
			LCD_displayCharacter(' ');

		}
	}
}

