/* INCLUDE FILES */
//Version 4.0
/*	Revisions:	 -Addition of initPCA9685() function
*				 -Addition of decelerate() function
*				 -Addition of accelerate() function
*				 -Changed the code structure motorTurnL and
*				  motorTurnR to make them more efficient
*
*/
#include "motor.h"
#include <util/delay.h>


//NOTE: This function can only make the car go forward or backwards
void drive(uint8_t direction, uint16_t speed) {

	/*Essentially sets the motor speed, then the direction.
	*	Notice how motor1 is set, then motor4, motor3, motor2, this is done
	* to help keep the car moving in a straight line.
	*/
	motorSpeed(MOTOR1, speed);
	motorRun(MOTOR1, direction);

	motorSpeed(MOTOR4, speed);
	motorRun(MOTOR4, direction);

	motorSpeed(MOTOR3, speed);
	motorRun(MOTOR3, direction);

	motorSpeed(MOTOR2, speed);
	motorRun(MOTOR2, direction);
}


/*NOTE: This only needs to be used once, or else it will cause the car to
* 			come to a complete stop and accelerate again.
*/
void accelerate(uint8_t direction) {
	uint16_t speed = 0;

	//Utilizes the drive function to slowly increase the speed
	while (speed != 2000) {
		drive(direction,speed);
		speed = speed + 100;
		_delay_ms(TIME1);
	}
}

void decelerate(uint8_t direction) {
	volatile uint16_t speed = 2000;

	//Utilizes the drive function to slowly increase the speed
	while (speed >= 100) {
		drive(direction, speed);
		speed = speed - 160;
		_delay_ms(TIME1);
	}
	drive(STOP, 0);
}

//NOTE: This is only for 1 motor!
void motorRun(uint8_t motor, uint8_t direction){
	uint8_t A1, A2;

	//Sets the motor address
	switch(motor) {
		case 1:
			A1 = A11;
			A2 = A21;
			break;
		case 2:
			A1 = A12;
			A2 = A22;
			break;
		case 3:
			A1 = A13;
			A2 = A23;
			break;
		case 4:
			A1 = A14;
			A2 = A24;
			break;
	}
	//sets the direction of the motors
	switch(direction) {

		case BACKWARD:
			AIN1(ON, A1);
			AIN2(OFF, A2);
			break;
		case FORWARD:
			AIN1(OFF, A1);
			AIN2(ON, A2);
			break;
		case STOP:
			AIN1(ON, A1);
			AIN2(ON, A2);
			break;
	}
}


//NOTE: This is only for 1 motor! Also, max speed is 4064
void motorSpeed(uint8_t motor, uint16_t speed) {

	//Sets the speed of the motor
	switch(motor){
		case 1:
			i2cStart();
			i2cSend(PCA9685_ADDR << 1);
			i2cSend(PWMA1);

			i2cSend(0);
			i2cSend(0);

			i2cSend((uint8_t)speed);
			i2cSend((uint8_t)(speed >> 8));

			i2cStop();
			break;
		case 2:
			i2cStart();
			i2cSend(PCA9685_ADDR << 1);
			i2cSend(PWMA2);

			i2cSend(0);
			i2cSend(0);

			i2cSend((uint8_t)speed);
			i2cSend((uint8_t)(speed >> 8));

			i2cStop();
			break;
		case 3:
			i2cStart();
			i2cSend(PCA9685_ADDR << 1);
			i2cSend(PWMA3);

			i2cSend(0);
			i2cSend(0);

			i2cSend((uint8_t)speed);
			i2cSend((uint8_t)(speed >> 8));

			i2cStop();
			break;
		case 4:
			i2cStart();
			i2cSend(PCA9685_ADDR << 1);
			i2cSend(PWMA4);

			i2cSend(0);
			i2cSend(0);

			i2cSend((uint8_t)speed);
			i2cSend((uint8_t)(speed >> 8));

			i2cStop();
			break;
	}
}

//Sets the H-Bridge, to set the state (direction) of the motor
void AIN1(uint16_t state, uint8_t motor){
	i2cStart();
	i2cSend(PCA9685_ADDR << 1);
	i2cSend(motor);

	i2cSend((uint8_t)state);
	i2cSend((uint8_t)(state >> 8));

	i2cSend(0);
	i2cSend(0);

	i2cStop();
}

//Sets the H-Bridge, to set the state (direction) of the motor
void AIN2(uint16_t state, uint8_t motor) {
	i2cStart();
	i2cSend(PCA9685_ADDR << 1);
	i2cSend(motor);

	i2cSend((uint8_t)state);
	i2cSend((uint8_t)(state >> 8));

	i2cSend(0);
	i2cSend(0);

	i2cStop();
}

//Initializes the PCA9685 chip
void initPCA9685() {
	i2cStart();
	i2cSend(PCA9685_ADDR << 1);
	i2cSend(MODE1);
	i2cSend(BITMASK);
	i2cStop();
	_delay_us(500);

}

//NOTE: May not work on all surfaces, changes in TIME3 may be necessary
void turnAround(void) {
	uint16_t speed = 0;

	motorRun(MOTOR1, BACKWARD);
	motorRun(MOTOR2, BACKWARD);
	motorRun(MOTOR3, FORWARD);
	motorRun(MOTOR4, FORWARD);

	//Starts turning, but slowly then quickly
	while (speed != 3750) {
		motorSpeed(MOTOR1, speed);
		motorSpeed(MOTOR2, speed);
		motorSpeed(MOTOR3, speed);
		motorSpeed(MOTOR4, speed);

		speed = speed + 10;
		_delay_us(TIME2);
	}

	_delay_ms(TIME3);

	//continues turning but starts slowing down
	while (speed != 0) {
		motorSpeed(MOTOR1, speed);
		motorSpeed(MOTOR2, speed);
		motorSpeed(MOTOR3, speed);
		motorSpeed(MOTOR4, speed);

		speed = speed - 10;
		_delay_us(TIME2);
	}
	drive(STOP, speed);
}


void motorTurnL(uint8_t turns) {
	uint16_t speed = TURNSPEED;

	//initializes motor directions
	motorRun(MOTOR1, BACKWARD);
	motorRun(MOTOR2, BACKWARD);
	motorRun(MOTOR3, FORWARD);
	motorRun(MOTOR4, FORWARD);

	//initializes motor speeds and starts them
	motorSpeed(MOTOR1, speed);
	motorSpeed(MOTOR2, speed);
	motorSpeed(MOTOR3, speed);
	motorSpeed(MOTOR4, speed);

	//Waits for a TIME2 * turns
	for(uint8_t i = 0; i < turns; i++) {
		_delay_ms(TIME2);
	}
	speed = 0;

	//Stops motors
	motorSpeed(MOTOR1, speed);
	motorSpeed(MOTOR2, speed);
	motorSpeed(MOTOR3, speed);
	motorSpeed(MOTOR4, speed);

}

void motorTurnR(uint8_t turns) {
	uint16_t speed = TURNSPEED;

	//initializes motor directions
	motorRun(MOTOR1, FORWARD);
	motorRun(MOTOR2, FORWARD);
	motorRun(MOTOR3, BACKWARD);
	motorRun(MOTOR4, BACKWARD);

	//initializes motor speeds and starts them
	motorSpeed(MOTOR1, speed);
	motorSpeed(MOTOR2, speed);
	motorSpeed(MOTOR3, speed);
	motorSpeed(MOTOR4, speed);

	//Waits for a TIME2 * turns
	for(uint8_t i = 0; i < turns; i++) {
		_delay_ms(TIME2);
	}
	speed = 0;
	//Stops motors
	motorSpeed(MOTOR1, speed);
	motorSpeed(MOTOR2, speed);
	motorSpeed(MOTOR3, speed);
	motorSpeed(MOTOR4, speed);

}
