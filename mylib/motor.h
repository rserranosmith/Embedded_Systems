/* INCLUDE FILES */
//Version 4.0

/*	Revisions:	 -Addition of initPCA9685() function
*				 -Addition of decelerate() function
*				 -Addition of accelerate() function
*
*
*/


#include <avr/io.h>				// All the port definitions are here
#include "i2c.h"

#define PCA9685_ADDR	0x60
#define	MODE1			0			// Mode register 1
#define BITMASK			0b00100001	//auto increment


#define	PWMA1			38	//motor 1
#define A21				42	//AIN2
#define A11				46	//AIN1

#define PWMA2			58  //motor 2
#define A12				50  //BIN1
#define A22				54	//BIN2

#define PWMA3			14	//motor 3
#define A23				18	//AIN2
#define A13				22	//AIN1

#define PWMA4			34	//motor 4
#define A24				30	//BIN2
#define A14				26  //BIN1

#define MOTOR1			1
#define MOTOR2			2
#define MOTOR3			3
#define MOTOR4			4

#define ON				4096
#define OFF				0

#define FORWARD			1
#define BACKWARD		2
#define STOP			3

#define TIME1			10	//Acceleration (ms)
#define	TIME2			100	//buffer time for turning (us)
#define	TIME3			375 //Time for actual turn (ms)


#define TURNSPEED 		2550


void AIN1(uint16_t,uint8_t);
void AIN2(uint16_t,uint8_t);
void motorSpeed(uint8_t, uint16_t);
void motorRun(uint8_t, uint8_t);

void drive(uint8_t, uint16_t);
void decelerate(uint8_t);
void accelerate(uint8_t);


void turnAround(void);
void motorTurnR(uint8_t);
void motorTurnL(uint8_t);

void initPCA9685();
