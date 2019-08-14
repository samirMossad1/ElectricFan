/*
 * 		Module:  Macros.
 *
 *		File Name: macros.h
 *
 *		Disc: commonly used macros
 *
 * 	    Created on: Feb 5, 2019
 *
 *      Author: Samir Mossad Ibrahim
 */

#ifndef MACROS_H_
#define MACROS_H_

/*Clear all the bits to the corresponding  1s in the number N  then OR it with the Number Num*/
#define CLEAR_N_BITS_THEN_OR(REG,N,NUM,SHIFT)  (  (REG)=( ( REG & ~(N) ) | (NUM<<SHIFT) ) )


/*Mask all other bits except with the bit of order BIT_NUM*/
#define MASK_BITS(REG,BIT_NUM) ( (REG)&(1<<BIT_NUM) )


#define MASK_BITS_THEN_SHIFT_LEFT(REG,BIT_NUM,N) ( ((REG)&(1<<BIT_NUM))>>N )


/*Check if specific bit is set in any register*/
#define BIT_IS_SET(REG,BIT_NUM) ((REG)&(1<<BIT_NUM))


/*Check if specific bit is clear in any register*/
#define BIT_IS_CLEAR(REG,BIT_NUM) (!((REG)&(1<<BIT_NUM)))


/*Set a certain bit inside a any register*/
#define SET_BIT(REG,BIT_NUM) ((REG)=(REG)|(1<<BIT_NUM))


/*Reset a certain bit inside a any register*/
#define RESET_BIT(REG,BIT_NUM) ((REG)=(REG)&(~(1<<BIT_NUM)))


/*Toggle a certain bit inside a any register*/
#define TOGGLE_BIT(REG,BIT_NUM) ((REG)=(REG)^(1<<BIT_NUM))



/*Rotate right the register with specific no of rotates*/
#define ROTATE_RIGHT(REG,BIT_NUM) ((REG>>BIT_NUM)|(REG>>((sizeof(REG)*8)-BIT_NUM)))



/*Rotate left the register with specific no of rotates*/
#define ROTATE_LEFT(REG,BIT_NUM) ((REG<<BIT_NUM)|(REG<<>((sizeof(REG)*8)-BIT_NUM)))





#endif /* MACROS_H_ */
