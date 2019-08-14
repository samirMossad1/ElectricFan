


#include "../includes/gpio.h"
#include "../includes/servo.h"
#include "../includes/dc_motor.h"


/*Speed Macro Definitions*/

#define FAN_SLOW_SPEED 		((MAX_DC_MOTOR_SPEED)/2)
#define FAN_MEDIUM_SPEED 	((2*MAX_DC_MOTOR_SPEED)/3)
#define FAN_FAST_SPEED 		((MAX_DC_MOTOR_SPEED))


/*Externed Structures*/

extern DCMOTOR_Structure fanDCMotor_t;



uint8_t firsttime_t=0X01;



void enable_globalInterrupt(void)
{
	SREG|=(1<<7);
}

void SlowSwitchisPressed(void)
{
	DCMOTOR_changeSpeed(&fanDCMotor_t,FAN_SLOW_SPEED);

	if(firsttime_t==0x01)
	{
		DCMOTOR_moveClockWise(&fanDCMotor_t);
		firsttime_t=0x00;
	}

}



void FastSwitchisPressed(void)
{

	DCMOTOR_changeSpeed(&fanDCMotor_t,FAN_FAST_SPEED);

	if(firsttime_t==0x01)
	{
		DCMOTOR_moveClockWise(&fanDCMotor_t);
		firsttime_t=0x00;
	}

}

void StopSwitchisPressed(void)
{
	DCMOTOR_stop(&fanDCMotor_t);
	firsttime_t=0x01;
}
