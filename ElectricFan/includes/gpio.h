
/*
 * 		Module: General Purpose Input/Output.
 *
 *		File Name: gpio.h
 *
 *		Disc: This module gives you full control on GPIO registers with
 *			  very stable and clear functions
 *
 * 	    Created on:  2019
 *
 *      Author: Samir Mossad Ibrahim
 */


#ifndef GPIO_H
#define GPIO_H



/*Needed Includes*/

#include "macros.h"
#include "micro_config.h"
#include "std_types.h"




/*This enum is used to declare Levels of GPIO*/
typedef enum gpio_level
{
	_LOW,_HIGH

}GPIO_LEVEL;


/*This enum is used to declare the type of GPIO*/
typedef enum gpio_type
{
	_INPUT,_OUTPUT

}GPIO_TYPE;


/*This enum is used to declare selected edge of the external interrupt of GPIO*/
typedef enum interrupt_edge
{
	_LOW_LEVEL,
	_LOGICAL_CHANGE,
	_FALLING_EDGE,
	_RISING_EDGE

}GPIO_INTERRUPT_EDGE;


/*This is structure is used to initialize any GPIO_PORT*/
typedef struct GPIO_port
{

	GPIO_PORT PORT;
	GPIO_TYPE PORT_TYPE;

}GPIO_portConfigStruct;



/*This is structure is used to initialize any GPIO_PIN*/
typedef struct GPIO_pin
{
	GPIO_PORT PORT;
	GPIO_PIN  PIN;
	GPIO_TYPE PIN_TYPE;

}GPIO_pinConfigStruct;


/*This is structure is used to initialize any GPIO External Interrupt*/
typedef struct GPIO_int
{
	GPIO_INTERRUPT_NUMBER INTERRUPT_NUMBER;
	GPIO_INTERRUPT_EDGE   INTERRUPT_EDGE_SELECT;
	void (*ISR_ptr)(void);

}GPIO_intConfigStruct;





/* ------------------------------------------------------------
 *Function-Name:GPIO_portInit
 *
 *Description: This function initializes the direction of the whole port at a time
 *
 *Inputs: reference to a GPIO_portConfigStruct
 *
 *Returns:
 *			True if succeeded
 *			False if failed
 *
 *--------------------------------------------------------------*/
bool   GPIO_portInit(const GPIO_portConfigStruct*);


/* ------------------------------------------------------------
 *Function-Name: GPIO_readPort
 *
 *Description: This function reads the data register of a whole input port at a time
 *
 *Inputs: GPIO_PORT
 *
 *Returns: the value of the data register
 *
 *--------------------------------------------------------------*/
uint8_t GPIO_readPort(const GPIO_portConfigStruct*);


/* ------------------------------------------------------------
 *Function-Name:GPIO_writePort
 *
 *Description: This function write an 8-bit value on a whole output port at a time
 *
 *Inputs: GPIO_PORT , uint8_t Data
 *
 *Returns: void
 *
 *--------------------------------------------------------------*/
void	GPIO_writePort(const GPIO_portConfigStruct*, const uint8_t);


/* ------------------------------------------------------------
 *Function-Name:GPIO_togglePort
 *
 *Description: This function toggles a whole output port at a time
 *
 *Inputs: GPIO_PORT
 *
 *Returns: void
 *
 *--------------------------------------------------------------*/
void	GPIO_togglePort(const GPIO_portConfigStruct*);



/* ------------------------------------------------------------
 *Function-Name:GPIO_togglePort
 *
 *Description: This function initializes the internal pull up resistors for a whole input
 *			   port at a time
 *
 *Inputs: GPIO_PORT
 *
 *Returns: void
 *
 *--------------------------------------------------------------*/
void GPIO_portPullUpInit(const GPIO_portConfigStruct*);

/* ------------------------------------------------------------
 *Function-Name:GPIO_pinInit
 *
 *Description: This function initializes the direction of a pin
 *
 *Inputs: reference to a GPIO_pinConfigStruct
 *
 *Returns:
 *			True if succeeded
 *			False if failed
 *
 *--------------------------------------------------------------*/
bool	GPIO_pinInit(const GPIO_pinConfigStruct*);


/* ------------------------------------------------------------
 *Function-Name:GPIO_readPin
 *
 *Description: this function reads the value of an input pin
 *
 *Inputs: GPIO_PORT , GPIO_PIN
 *
 *Returns: the value of the corresponding pin in the data register
 *
 *--------------------------------------------------------------*/
uint8_t	GPIO_readPin(const GPIO_pinConfigStruct*);


/* ------------------------------------------------------------
 *Function-Name:GPIO_writePin
 *
 *Description: this function writes a 1-bit value on an output pin
 *
 *Inputs: GPIO_PORT , GPIO_PIN and uint8_t data
 *
 *Returns:	void
 *
 *--------------------------------------------------------------*/
void GPIO_writePin(const GPIO_pinConfigStruct*,const uint8_t);


/* ------------------------------------------------------------
 *Function-Name:GPIO_togglePin
 *
 *Description: this function toggles the value of an output pin
 *
 *Inputs: GPIO_PORT , GPIO_PIN
 *
 *Returns:	void
 *
 *--------------------------------------------------------------*/
void GPIO_togglePin(const GPIO_pinConfigStruct*);


/* ------------------------------------------------------------
 *Function-Name:GPIO_pinPullupInit
 *
 *Description: this function initialize and active the internal pull up resistor for an input pin
 *
 *Inputs: GPIO_PORT , GPIO_PIN
 *
 *Returns:	void
 *
 *--------------------------------------------------------------*/
void GPIO_pinPullUpInit(const GPIO_pinConfigStruct*);


/* ------------------------------------------------------------
 *Function-Name:GPIO_interruptInit
 *
 *Description:this function initialize the required external interrupt , sets the external interrupt sense
 *			  and sets the call back pointer to the call back function which is called in the ISR
 *
 *Inputs: reference to GPIO_intConfigStruct
 *
 *Returns:
 *			True if succeeded
 *			False if failed
 *
 *--------------------------------------------------------------*/
bool GPIO_interruptInit(const GPIO_intConfigStruct*);


/* ------------------------------------------------------------
 *Function-Name:GPIO_interruptEnable
 *
 *Description:this function enables and active the required external interrupt.
 *
 *Inputs: GPIO_INTERRUPT_NUMBER
 *
 *Returns:
 *			True if succeeded
 *			False if failed
 *
 *--------------------------------------------------------------*/
bool GPIO_interruptEnable(const GPIO_INTERRUPT_NUMBER);


/* ------------------------------------------------------------
 *Function-Name:GPIO_interruptDisable
 *
 *Description:this function disables any of the pre-enabled external interrupts.
 *
 *Inputs: GPIO_INTERRUPT_NUMBER
 *
 *Returns:
 *			True if succeeded
 *			False if failed
 *
 *--------------------------------------------------------------*/
bool GPIO_interruptDisable(const GPIO_INTERRUPT_NUMBER);



#endif
