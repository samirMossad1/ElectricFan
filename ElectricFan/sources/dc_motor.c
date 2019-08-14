


#include "../includes/dc_motor.h"
#include "../includes/gpio.h"


#define GetCompareValue(x,y)  ( (x/100.0)*y )

static bool timer0_pwmMode_init(void);
static bool timer2_pwmMode_init(void);
static bool timer1_pwmMode_init(const TIMER_CHANNEL);



bool DCMOTOR_init(const DCMOTOR_Structure *DCMOTOR_structPtr)
{

	if(DCMOTOR_structPtr == NULL_PTR)	return FALSE;

	GPIO_pinConfigStruct input_1={DCMOTOR_structPtr->PORT_INPUT_1
			,DCMOTOR_structPtr->PIN_INPUT_1
			,_OUTPUT};

	GPIO_pinConfigStruct input_2={DCMOTOR_structPtr->PORT_INPUT_2
			,DCMOTOR_structPtr->PIN_INPUT_2
			,_OUTPUT};

	GPIO_pinConfigStruct enable;

	switch(DCMOTOR_structPtr->SPEED_PIN)
	{

	case SPEED_OC_0:    enable.PORT=PORT_B;
	enable.PIN=PIN_3;
	enable.PIN_TYPE=_OUTPUT;
	timer0_pwmMode_init();
	break;


	case SPEED_OC_1_A:  enable.PORT=PORT_D;
	enable.PIN=PIN_5;
	enable.PIN_TYPE=_OUTPUT;
	timer1_pwmMode_init(_CHANNEL_A);
	break;

	case SPEED_OC_1_B:  enable.PORT=PORT_D;
	enable.PIN=PIN_4;
	enable.PIN_TYPE=_OUTPUT;
	timer1_pwmMode_init(_CHANNEL_B);
	break;


	case SPEED_OC_2:	enable.PORT=PORT_D;
	enable.PIN=PIN_7;
	enable.PIN_TYPE=_OUTPUT;
	timer2_pwmMode_init();
	break;

	}

	GPIO_pinInit(&input_1);
	GPIO_pinInit(&input_2) ;
	GPIO_pinInit(&enable) ;

	GPIO_writePin(DCMOTOR_structPtr->PORT_INPUT_1,DCMOTOR_structPtr->PIN_INPUT_1,LOW);
	GPIO_writePin(DCMOTOR_structPtr->PORT_INPUT_2,DCMOTOR_structPtr->PIN_INPUT_2,LOW);



	return TRUE;
}


void DCMOTOR_moveClockWise(const DCMOTOR_Structure * DCMOTOR_structPtr)
{

	if(DCMOTOR_structPtr == NULL_PTR)	return;

	GPIO_writePin(DCMOTOR_structPtr->PORT_INPUT_2,DCMOTOR_structPtr->PIN_INPUT_2,LOW);
	GPIO_writePin(DCMOTOR_structPtr->PORT_INPUT_1,DCMOTOR_structPtr->PIN_INPUT_1,HIGH);

}
void DCMOTOR_moveAntiClockWise(const DCMOTOR_Structure *DCMOTOR_structPtr)
{

	if(DCMOTOR_structPtr == NULL_PTR)	return;

	GPIO_writePin(DCMOTOR_structPtr->PORT_INPUT_1,DCMOTOR_structPtr->PIN_INPUT_1,LOW);
	GPIO_writePin(DCMOTOR_structPtr->PORT_INPUT_2,DCMOTOR_structPtr->PIN_INPUT_2,HIGH);


}
void DCMOTOR_stop(const DCMOTOR_Structure *DCMOTOR_structPtr)
{

	if(DCMOTOR_structPtr == NULL_PTR)	return;

	GPIO_writePin(DCMOTOR_structPtr->PORT_INPUT_1,DCMOTOR_structPtr->PIN_INPUT_1,LOW);
	GPIO_writePin(DCMOTOR_structPtr->PORT_INPUT_2,DCMOTOR_structPtr->PIN_INPUT_2,LOW);

}

void DCMOTOR_changeSpeed(const DCMOTOR_Structure *DCMOTOR_structPtr,uint16_t speed)
{

	if(DCMOTOR_structPtr == NULL_PTR)	return;

	switch(DCMOTOR_structPtr->SPEED_PIN)
	{

	case SPEED_OC_0:   	 TIMER0_COMPARE_REGISTER=GetCompareValue(speed,TIMER0_TOP_VALUE);
	break;

	case SPEED_OC_1_A:   TIMER1A_COMPARE_REGISTER=GetCompareValue(speed,TIMER1_TOP_VALUE);
	break;

	case SPEED_OC_1_B:   TIMER1B_COMPARE_REGISTER=GetCompareValue(speed,TIMER1_TOP_VALUE);
	break;

	case SPEED_OC_2:     TIMER2_COMPARE_REGISTER=GetCompareValue(speed,TIMER2_TOP_VALUE);
	break;
	}


}



static bool timer0_pwmMode_init(void)
{

	TIMER0_CONTROL_REGISTER&=~(TIMER_0_DISABLE_MASK);

	TIMER0_COUNT_REGISTER=TIMER0_CLEAR_MASK;

	TIMER0_COMPARE_REGISTER=_100_DUTY_CYCLE;

	TIMER0_CONTROL_REGISTER=TIMER_0_PWM_NON_INVERTING_OC0_WITH_F_CPU_64_MASK;

	return TRUE;

}


static bool timer1_pwmMode_init(const TIMER_CHANNEL TIMER_CHAN)
{

	TIMER1_COUNT_REGISTER=TIMER_1_CLEAR_MASK;
	TIMER1_INPUT_CAPTURE_REGISTER=TIMER1_TOP_VALUE;

	if(TIMER_CHAN==_CHANNEL_A)
	{
		TIMER1A_COMPARE_REGISTER=TIMER1_TOP_VALUE;
		TIMER1A_CONTROL_REGISTER|=TIMER_1_PWM_NON_INVERTING_OC1A_MASK;

	}
	else
	{
		TIMER1B_COMPARE_REGISTER=TIMER1_TOP_VALUE;
		TIMER1A_CONTROL_REGISTER|=TIMER_1_PWM_NON_INVERTING_OC1B_MASK;
	}

	TIMER1A_CONTROL_REGISTER|=TIMER_1_FAST_PWM_MASK;
	TIMER1B_CONTROL_REGISTER|=TIMER_1_PWM_F_CPU_64_MASK;

	return TRUE;

}

static bool timer2_pwmMode_init(void)
{

	TIMER2_CONTROL_REGISTER&=~(TIMER_2_DISABLE_MASK);

	TIMER2_COUNT_REGISTER=TIMER2_CLEAR_MASK;

	TIMER2_COMPARE_REGISTER=_100_DUTY_CYCLE;

	TIMER2_CONTROL_REGISTER=TIMER_2_PWM_NON_INVERTING_OC0_WITH_F_CPU_64_MASK;

	return TRUE;

}
