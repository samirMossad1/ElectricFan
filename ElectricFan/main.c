
#include "includes/gpio.h"
#include "includes/dc_motor.h"
#include "includes/servo.h"
#include "includes/configStructs.h"



int main(void)
{


	/*INITIALIZATIONS*/

	SERVO_init(&fanServoMotor_t);
	DCMOTOR_init(&fanDCMotor_t);


	GPIO_pinInit(&PushButtonStop_t);
	GPIO_pinInit(&PushButtonSlow_t);
	GPIO_pinInit(&PushButtonFast_t);

	GPIO_pinPullUpInit(&PushButtonStop_t);
	GPIO_pinPullUpInit(&PushButtonSlow_t);
	GPIO_pinPullUpInit(&PushButtonFast_t);

	GPIO_interruptInit(&interrupt0_t);
	GPIO_interruptInit(&interrupt1_t);
	GPIO_interruptInit(&interrupt2_t);

	GPIO_interruptEnable(INTERRUPT_0);
	GPIO_interruptEnable(INTERRUPT_1);
	GPIO_interruptEnable(INTERRUPT_2);


	/*INITIAL CONDITIONS*/
	DCMOTOR_stop(&fanDCMotor_t);

	/*Enable Global Interrupt*/
	enable_globalInterrupt();


	while(1)
	{

		SERVO_rotate(&fanServoMotor_t,90);
		_delay_ms(6000);
		SERVO_rotate(&fanServoMotor_t,-90);
		_delay_ms(6000);

	}


	return 0;
}




