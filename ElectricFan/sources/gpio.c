
#include "../includes/gpio.h"


static void (*ISR_GPIO_IntCallBackPtr[3])(void)={NULL_PTR,NULL_PTR,NULL_PTR};




/*INTERRUPT SERVICE ROUTINES*/

ISR(INT0_vect)
{
	if(ISR_GPIO_IntCallBackPtr[0] != NULL_PTR)
	{
		ISR_GPIO_IntCallBackPtr[0]();
		SET_BIT(GPIO_MASKED_INTERRUPT_FLAG_REGISTER,GPIO_INT01_OFFSET);
	}
}


ISR(INT1_vect)
{
	if(ISR_GPIO_IntCallBackPtr[1] != NULL_PTR)
	{
		ISR_GPIO_IntCallBackPtr[1]();
		SET_BIT(GPIO_MASKED_INTERRUPT_FLAG_REGISTER,GPIO_INT1_OFFSET);
	}
}


ISR(INT2_vect)
{

	if(ISR_GPIO_IntCallBackPtr[2] != NULL_PTR)
	{
		ISR_GPIO_IntCallBackPtr[2]();
		SET_BIT(GPIO_MASKED_INTERRUPT_FLAG_REGISTER,GPIO_INT2_OFFSET);
	}
}





bool   GPIO_portInit(const GPIO_portConfigStruct* ConfigStructptr)
{

	if(ConfigStructptr == NULL_PTR) return FALSE;

	switch(ConfigStructptr->PORT)
	{

	case PORT_A:
		GPIO_PORTA_DIRECTION_REGISTER=(ConfigStructptr->PORT_TYPE == _INPUT)?0X00:0XFF;
		break;

	case PORT_B:
		GPIO_PORTB_DIRECTION_REGISTER=(ConfigStructptr->PORT_TYPE == _INPUT)?0X00:0XFF;
		break;

	case PORT_C:
		GPIO_PORTC_DIRECTION_REGISTER=(ConfigStructptr->PORT_TYPE == _INPUT)?0X00:0XFF;
		break;

	case PORT_D:
		GPIO_PORTD_DIRECTION_REGISTER=(ConfigStructptr->PORT_TYPE == _INPUT)?0X00:0XFF;
		break;
	}

	return TRUE;
}


bool	GPIO_pinInit(const GPIO_pinConfigStruct* ConfigStructptr)
{


	if(ConfigStructptr == NULL_PTR) return FALSE;

	switch(ConfigStructptr->PORT)
	{

	case PORT_A:
		if(ConfigStructptr->PIN_TYPE == _INPUT)
		{
			RESET_BIT(GPIO_PORTA_DIRECTION_REGISTER,ConfigStructptr->PIN);
		}
		else
		{
			SET_BIT(GPIO_PORTA_DIRECTION_REGISTER,ConfigStructptr->PIN);
		}
		break;

	case PORT_B:
		if(ConfigStructptr->PIN_TYPE == _INPUT)
		{
			RESET_BIT(GPIO_PORTB_DIRECTION_REGISTER,ConfigStructptr->PIN);
		}
		else
		{
			SET_BIT(GPIO_PORTB_DIRECTION_REGISTER,ConfigStructptr->PIN);
		}
		break;


	case PORT_C:
		if(ConfigStructptr->PIN_TYPE == _INPUT)
		{
			RESET_BIT(GPIO_PORTC_DIRECTION_REGISTER,ConfigStructptr->PIN);
		}
		else
		{
			SET_BIT(GPIO_PORTC_DIRECTION_REGISTER,ConfigStructptr->PIN);
		}
		break;


	case PORT_D:
		if(ConfigStructptr->PIN_TYPE == _INPUT)
		{
			RESET_BIT(GPIO_PORTD_DIRECTION_REGISTER,ConfigStructptr->PIN);
		}
		else
		{
			SET_BIT(GPIO_PORTD_DIRECTION_REGISTER,ConfigStructptr->PIN);
		}
		break;


	}

	return TRUE;
}



uint8_t GPIO_readPort(const GPIO_portConfigStruct* PORT_structPtr)
{
	switch(PORT_structPtr->PORT)
	{
	case PORT_A: return GPIO_PORTA_INPUT_REGISTER;
	case PORT_B: return GPIO_PORTB_INPUT_REGISTER;
	case PORT_C: return GPIO_PORTC_INPUT_REGISTER;
	case PORT_D: return GPIO_PORTD_INPUT_REGISTER;
	default 	 : return GPIO_PORTA_INPUT_REGISTER;
	}
}


uint8_t	GPIO_readPin(const GPIO_pinConfigStruct* GPIO_structPtr)
{
	switch(GPIO_structPtr->PORT)
	{
	case PORT_A: return( GPIO_PORTA_INPUT_REGISTER & (1<<GPIO_structPtr->PIN) );
	case PORT_B: return( GPIO_PORTB_INPUT_REGISTER & (1<<GPIO_structPtr->PIN) );
	case PORT_C: return( GPIO_PORTC_INPUT_REGISTER & (1<<GPIO_structPtr->PIN) );
	case PORT_D: return( GPIO_PORTD_INPUT_REGISTER & (1<<GPIO_structPtr->PIN) );
	default 	 : return( GPIO_PORTA_INPUT_REGISTER & (1<<GPIO_structPtr->PIN) );

	}
}



void	GPIO_writePort(const GPIO_portConfigStruct* PORT_structPtr, const GPIO_LEVEL data)
{
	uint8_t data_mapped=0x00;

	if(data==_HIGH)
	{
		data_mapped=0xFF;
	}

	switch(PORT_structPtr->PORT)
	{
	case PORT_A: GPIO_PORTA_OUTPUT_REGISTER=data_mapped;
	break;
	case PORT_B: GPIO_PORTB_OUTPUT_REGISTER=data_mapped;
	break;
	case PORT_C: GPIO_PORTC_OUTPUT_REGISTER=data_mapped;
	break;
	case PORT_D: GPIO_PORTD_OUTPUT_REGISTER=data_mapped;
	break;
	}
}


void GPIO_writePin(const GPIO_pinConfigStruct* PIN_structPtr,const GPIO_LEVEL data)
{
	switch(PIN_structPtr->PORT)
	{
	case PORT_A:

		if(data == _LOW)
		{
			RESET_BIT(GPIO_PORTA_OUTPUT_REGISTER, PIN_structPtr->PIN);
		}
		else
		{
			SET_BIT(GPIO_PORTA_OUTPUT_REGISTER,PIN_structPtr->PIN);
		}
		break;


	case PORT_B:
		if(data == _LOW)
		{
			RESET_BIT(GPIO_PORTB_OUTPUT_REGISTER,PIN_structPtr->PIN);
		}
		else
		{
			SET_BIT(GPIO_PORTB_OUTPUT_REGISTER,PIN_structPtr->PIN);
		}
		break;


	case PORT_C:
		if(data == _LOW)
		{
			RESET_BIT(GPIO_PORTC_OUTPUT_REGISTER,PIN_structPtr->PIN);
		}
		else
		{
			SET_BIT(GPIO_PORTC_OUTPUT_REGISTER,PIN_structPtr->PIN);
		}
		break;


	case PORT_D:
		if(data == _LOW)
		{
			RESET_BIT(GPIO_PORTD_OUTPUT_REGISTER,PIN_structPtr->PIN);
		}
		else
		{
			SET_BIT(GPIO_PORTD_OUTPUT_REGISTER,PIN_structPtr->PIN);
		}
		break;
	}
}

void GPIO_togglePin(const GPIO_pinConfigStruct* PIN_structPtr)
{

	switch(PIN_structPtr->PORT)
	{
	case  PORT_A :
		TOGGLE_BIT(GPIO_PORTA_OUTPUT_REGISTER,PIN_structPtr->PIN);
		break;
	case  PORT_B :
		TOGGLE_BIT(GPIO_PORTB_OUTPUT_REGISTER,PIN_structPtr->PIN);
		break;
	case  PORT_C :
		TOGGLE_BIT(GPIO_PORTC_OUTPUT_REGISTER,PIN_structPtr->PIN);
		break;
	case  PORT_D :
		TOGGLE_BIT(GPIO_PORTD_OUTPUT_REGISTER,PIN_structPtr->PIN);
		break;
	}
}


void	GPIO_togglePort(const GPIO_portConfigStruct* PORT_structPtr)
{


	switch(PORT_structPtr->PORT)
		{
		case  PORT_A :
			GPIO_PORTA_OUTPUT_REGISTER^= GPIO_TOGGLE_PORT_MASK;
			break;
		case  PORT_B :
			GPIO_PORTB_OUTPUT_REGISTER^= GPIO_TOGGLE_PORT_MASK;
			break;
		case  PORT_C :
			GPIO_PORTC_OUTPUT_REGISTER^= GPIO_TOGGLE_PORT_MASK;
			break;
		case  PORT_D :
			GPIO_PORTD_OUTPUT_REGISTER^= GPIO_TOGGLE_PORT_MASK;
			break;
		}

}

void GPIO_pinPullUpInit(const GPIO_pinConfigStruct* GPIO_PIN)
{

	switch(GPIO_PIN->PORT)
	{
	case  PORT_A :
		SET_BIT(GPIO_PORTA_OUTPUT_REGISTER,GPIO_PIN->PIN);
		break;
	case  PORT_B :
		SET_BIT(GPIO_PORTB_OUTPUT_REGISTER,GPIO_PIN->PIN);
		break;
	case  PORT_C :
		SET_BIT(GPIO_PORTC_OUTPUT_REGISTER,GPIO_PIN->PIN);
		break;
	case  PORT_D :
		SET_BIT(GPIO_PORTD_OUTPUT_REGISTER,GPIO_PIN->PIN);
		break;
	}

}


void GPIO_portPullUpInit(const GPIO_portConfigStruct* PORT_structPtr)
{

	switch(PORT_structPtr->PORT)
	{
	case  PORT_A :
		GPIO_PORTA_OUTPUT_REGISTER=0xFF;
		break;
	case  PORT_B :
		GPIO_PORTB_OUTPUT_REGISTER=0xFF;
		break;
	case  PORT_C :
		GPIO_PORTC_OUTPUT_REGISTER=0xFF;
		break;
	case  PORT_D :
		GPIO_PORTD_OUTPUT_REGISTER=0xFF;
		break;
	}

}


bool GPIO_interruptEnable(const GPIO_INTERRUPT_NUMBER INT_NUMBER)
{
	uint8_t interrupt_number=0;

	if(INT_NUMBER== INTERRUPT_2)
	{
		interrupt_number+=GPIO_INT2_OFFSET;
	}
	else if(INT_NUMBER== INTERRUPT_1)
	{

		interrupt_number+=GPIO_INT1_OFFSET;
	}
	else
	{

		interrupt_number+=GPIO_INT0_OFFSET;
	}

	SET_BIT(GPIO_MODULE_INTERRUPT_CONTROL_REGISTER,interrupt_number);
	SET_BIT(GPIO_MASKED_INTERRUPT_FLAG_REGISTER,interrupt_number);
	return TRUE;
}

bool GPIO_interruptDisable(const GPIO_INTERRUPT_NUMBER INT_NUMBER)
{
	uint8_t interrupt_number=0;

	if(INT_NUMBER== INTERRUPT_2)
	{
		interrupt_number+=GPIO_INT2_OFFSET;
	}
	else
	{
		interrupt_number+=GPIO_INT01_OFFSET;
	}

	RESET_BIT(GPIO_MODULE_INTERRUPT_CONTROL_REGISTER,interrupt_number);
	return TRUE;
}

bool GPIO_interruptInit(const GPIO_intConfigStruct* ConfigStructPtr)
{
	uint8_t sense_controlOffset=0x00,clear_mask=GPIO_INT0_CLEAR_MASK;

	if(ConfigStructPtr == NULL_PTR) return FALSE;

	ISR_GPIO_IntCallBackPtr[ConfigStructPtr->INTERRUPT_NUMBER]=ConfigStructPtr->ISR_ptr;

	switch(ConfigStructPtr->INTERRUPT_NUMBER)
	{

	case  INTERRUPT_0 :
		sense_controlOffset=(ConfigStructPtr->INTERRUPT_EDGE_SELECT);
		break;

	case  INTERRUPT_1 :
		sense_controlOffset=(ConfigStructPtr->INTERRUPT_EDGE_SELECT) << GPIO_INT1_EDGE_SELECT_SHIFT;
		clear_mask=GPIO_INT1_CLEAR_MASK;
		break;

	case  INTERRUPT_2 :
		sense_controlOffset=(ConfigStructPtr->INTERRUPT_EDGE_SELECT) << GPIO_INT2_EDGE_SELECT_SHIFT;
		clear_mask=GPIO_INT2_CLEAR_MASK;
		break;
	}


	GPIO_INTERRUPT_SENSE_CONTROL_REGISTER=((GPIO_INTERRUPT_SENSE_CONTROL_REGISTER & ~(clear_mask) ) | sense_controlOffset ) ;


	return TRUE;
}
