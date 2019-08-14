


#include "../includes/dc_motor.h"
#include "../includes/gpio.h"


#define GetCompareValue(x,y)  ( (x/100.0)*y )

static bool timer0_pwmMode_init(void);
static bool timer2_pwmMode_init(void);
static bool timer1_pwmMode_init(const TIMER_CHANNEL);


static GPIO_pinConfigStruct input_g;


bool DCMOTOR_init(const DCMOTOR_Structure *DCMOTOR_structPtr)
{

	if(DCMOTOR_structPtr == NULL_PTR)	return FALSE;


	input_g.PORT=DCMOTOR_structPtr->PORT_INPUT_1;
	input_g.PIN=DCMOTOR_structPtr->PIN_INPUT_1;
	input_g.PIN_TYPE=_OUTPUT;

	GPIO_pinInit(&input_g);
	GPIO_writePin(&input_g,LOW);

	input_g.PORT=DCMOTOR_structPtr->PORT_INPUT_2;
	input_g.PIN=DCMOTOR_structPtr->PIN_INPUT_2;
	input_g.PIN_TYPE=_OUTPUT;

	GPIO_pinInit(&input_g);
	GPIO_writePin(&input_g,LOW);


	switch(DCMOTOR_structPtr->SPEED_PIN)
	{

	case SPEED_OC_0:    input_g.PORT=PORT_B;
	input_g.PIN=PIN_3;
	input_g.PIN_TYPE=_OUTPUT;
	timer0_pwmMode_init();
	break;


	case SPEED_OC_1_A:  input_g.PORT=PORT_D;
	input_g.PIN=PIN_5;
	input_g.PIN_TYPE=_OUTPUT;
	timer1_pwmMode_init(_CHANNEL_A);
	break;

	case SPEED_OC_1_B:  input_g.PORT=PORT_D;
	input_g.PIN=PIN_4;
	input_g.PIN_TYPE=_OUTPUT;
	timer1_pwmMode_init(_CHANNEL_B);
	break;


	case SPEED_OC_2:	input_g.PORT=PORT_D;
	input_g.PIN=PIN_7;
	input_g.PIN_TYPE=_OUTPUT;
	timer2_pwmMode_init();
	break;

	}

	GPIO_pinInit(&input_g) ;


	return TRUE;
}


void DCMOTOR_moveClockWise(const DCMOTOR_Structure * DCMOTOR_structPtr)
{

	if(DCMOTOR_structPtr == NULL_PTR)	return;

	input_g.PORT=DCMOTOR_structPtr->PORT_INPUT_1;
	input_g.PIN=DCMOTOR_structPtr->PIN_INPUT_1;
	input_g.PIN_TYPE=_OUTPUT;

	GPIO_writePin(&input_g,HIGH);

	input_g.PORT=DCMOTOR_structPtr->PORT_INPUT_2;
	input_g.PIN=DCMOTOR_structPtr->PIN_INPUT_2;
	input_g.PIN_TYPE=_OUTPUT;

	GPIO_writePin(&input_g,LOW);

}
void DCMOTOR_moveAntiClockWise(const DCMOTOR_Structure *DCMOTOR_structPtr)
{

	if(DCMOTOR_structPtr == NULL_PTR)	return;

	input_g.PORT=DCMOTOR_structPtr->PORT_INPUT_1;
	input_g.PIN=DCMOTOR_structPtr->PIN_INPUT_1;
	input_g.PIN_TYPE=_OUTPUT;

	GPIO_writePin(&input_g,LOW);

	input_g.PORT=DCMOTOR_structPtr->PORT_INPUT_2;
	input_g.PIN=DCMOTOR_structPtr->PIN_INPUT_2;
	input_g.PIN_TYPE=_OUTPUT;

	GPIO_writePin(&input_g,HIGH);


}
void DCMOTOR_stop(const DCMOTOR_Structure *DCMOTOR_structPtr)
{

	if(DCMOTOR_structPtr == NULL_PTR)	return;

	input_g.PORT=DCMOTOR_structPtr->PORT_INPUT_1;
	input_g.PIN=DCMOTOR_structPtr->PIN_INPUT_1;
	input_g.PIN_TYPE=_OUTPUT;

	GPIO_writePin(&input_g,LOW);

	input_g.PORT=DCMOTOR_structPtr->PORT_INPUT_2;
	input_g.PIN=DCMOTOR_structPtr->PIN_INPUT_2;
	input_g.PIN_TYPE=_OUTPUT;

	GPIO_writePin(&input_g,LOW);

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
