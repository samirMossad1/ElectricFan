
#ifndef DC_MOTOR_H
#define DC_MOTOR_H



#include "micro_config.h"
#include "macros.h"
#include "std_types.h"


#define MAX_DC_MOTOR_SPEED	100U

typedef enum
{
	SPEED_OC_0,
	SPEED_OC_1_A,
	SPEED_OC_1_B,
	SPEED_OC_2

}ENABLE_PIN;


typedef struct
{

	GPIO_PORT PORT_INPUT_1;
	GPIO_PORT PORT_INPUT_2;
	GPIO_PIN PIN_INPUT_1;
	GPIO_PIN PIN_INPUT_2;
	ENABLE_PIN SPEED_PIN;

}DCMOTOR_Structure;




bool DCMOTOR_init(const DCMOTOR_Structure *);
void DCMOTOR_moveClockWise(const DCMOTOR_Structure *);
void DCMOTOR_moveAntiClockWise(const DCMOTOR_Structure *);
void DCMOTOR_stop(const DCMOTOR_Structure *);
void DCMOTOR_changeSpeed(const DCMOTOR_Structure *,uint16_t);



#endif
