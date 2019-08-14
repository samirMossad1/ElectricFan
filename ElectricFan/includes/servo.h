
#ifndef SERVO_H_
#define SERVO_H_


#include "micro_config.h"
#include "std_types.h"
#include "macros.h"

#define F_CPU 8000000UL

#define SERVO_TOP_VALUE_ICR1_FCPU_8MHZ_WITH_PRESCALAR_64 (uint16_t)(2499)
#define SERVO_COMPARE_VALUE_RELATIVE_TO_ZERO_POSTION	 (uint8_t)(187)
#define SERVO_COMPARE_VALUE_RELATIVE_TO_90_POSTION		 (uint8_t)(250)
#define SERVO_COMPARE_VALUE_RELATIVE_TO_NEG_90_POSTION	 (uint8_t)(125)

typedef enum
{
	SERVO_OC1A,
	SERVO_OC1B

}SERVO_PIN;


typedef struct
{
	SERVO_PIN SERVO_PIN;

}SERVO_configStruct;


bool SERVO_init(const SERVO_configStruct*);
void SERVO_rotate(const SERVO_configStruct*,suint8_t);


#endif
