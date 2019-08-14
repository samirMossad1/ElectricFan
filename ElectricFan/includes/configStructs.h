

#ifndef INCLUDES_CONFIGSTRUCTS_H_
#define INCLUDES_CONFIGSTRUCTS_H_


#include "../includes/applicationfunctions.h"


	/*Configuration Structures*/


	GPIO_pinConfigStruct PushButtonSlow_t={

			PORT_D,
			PIN_2,
			_INPUT
	};

	GPIO_pinConfigStruct PushButtonFast_t={

			PORT_D,
			PIN_3,
			_INPUT
	};

	GPIO_pinConfigStruct PushButtonStop_t={

			PORT_B,
			PIN_2,
			_INPUT
	};

	DCMOTOR_Structure fanDCMotor_t={
			PORT_C,
			PORT_C,
			PIN_0,
			PIN_1,
			SPEED_OC_2
	};


	SERVO_configStruct fanServoMotor_t={
			SERVO_OC1A
	};



	GPIO_intConfigStruct interrupt0_t={
			INTERRUPT_0,
			_FALLING_EDGE,
			SlowSwitchisPressed
	};

	GPIO_intConfigStruct interrupt1_t={
			INTERRUPT_1,
			_FALLING_EDGE,
			FastSwitchisPressed
	};

	GPIO_intConfigStruct interrupt2_t={
			INTERRUPT_2,
			_FALLING_EDGE,
			StopSwitchisPressed
	};



#endif
