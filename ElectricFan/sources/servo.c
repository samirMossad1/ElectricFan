


#include "../includes/servo.h"
#include "../includes/gpio.h"


#define SERVO_getCompareValue(angle) ( ( (angle*31)/(45.0) )+187 )

static bool timer1_pwmMode_init(const TIMER_CHANNEL);



bool SERVO_init(const SERVO_configStruct* SERVO_configStructPtr)
{

	if(SERVO_configStructPtr == NULL_PTR)
		return FALSE;

	GPIO_pinConfigStruct GPIO_pin;

	if(SERVO_configStructPtr->SERVO_PIN == SERVO_OC1A)
	{

		GPIO_pin.PORT=PORT_D;
		GPIO_pin.PIN=PIN_5;
		GPIO_pin.PIN_TYPE=_OUTPUT;
		timer1_pwmMode_init(_CHANNEL_A);


	}
	else
	{

		GPIO_pin.PORT=PORT_D;
		GPIO_pin.PIN=PIN_4;
		GPIO_pin.PIN_TYPE=_OUTPUT;
		timer1_pwmMode_init(_CHANNEL_B);

	}


	GPIO_pinInit(&GPIO_pin);


	return TRUE;
}







void SERVO_rotate(const SERVO_configStruct* SERVO_structPtr,suint8_t servoAngle_t)
{

	if(SERVO_structPtr == NULL_PTR)	return;


	if(SERVO_structPtr->SERVO_PIN == SERVO_OC1A )
	{
		TIMER1A_COMPARE_REGISTER=(uint16_t)SERVO_getCompareValue(servoAngle_t);
	}
	else
	{
		TIMER1B_COMPARE_REGISTER=(uint16_t)SERVO_getCompareValue(servoAngle_t);
	}

}




static bool timer1_pwmMode_init(const TIMER_CHANNEL TIMER_CHAN)
{

	TIMER1_COUNT_REGISTER=TIMER_1_CLEAR_MASK;
	TIMER1_INPUT_CAPTURE_REGISTER=SERVO_TOP_VALUE_ICR1_FCPU_8MHZ_WITH_PRESCALAR_64;

	if(TIMER_CHAN==_CHANNEL_A)
	{
		TIMER1A_COMPARE_REGISTER=SERVO_COMPARE_VALUE_RELATIVE_TO_ZERO_POSTION;
		TIMER1A_CONTROL_REGISTER|=TIMER_1_PWM_NON_INVERTING_OC1A_MASK;

	}
	else
	{
		TIMER1B_COMPARE_REGISTER=SERVO_COMPARE_VALUE_RELATIVE_TO_ZERO_POSTION;
		TIMER1A_CONTROL_REGISTER|=TIMER_1_PWM_NON_INVERTING_OC1B_MASK;
	}

	TIMER1A_CONTROL_REGISTER|=TIMER_1_FAST_PWM_MASK;
	TIMER1B_CONTROL_REGISTER|=TIMER_1_PWM_F_CPU_64_MASK;

	return TRUE;

}

