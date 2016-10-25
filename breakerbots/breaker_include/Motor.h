/*
 * Motor.h
 *
 *  Created on: Feb 17, 2016
 *      Author: DS_2016
 */

#ifndef SRC_MOTOR_H_
#define SRC_MOTOR_H_

#include "WPILIB.h"

class Motor{
private:
	CANTalon& motorOut;

	float _currentValue;
	float _E;

	float _target;
	float _targetJump;

	int _time;
	int _timeToTarget;

	float _maxDelta;
	float _delta;

	bool _canJump;
public:
	Motor(CANTalon& inMotor);

	void update(float newValue);

	//------SETTERS AND GETTERS--------//
	void setE(float input);
	float E ();

	void setTargetJump(float input);
	float targetJump ();
	float target ();

	void setTimeToTarget(int input);
	int timeToTarget ();

	void setMaxDelta(float input);
	float maxDelta ();
	float delta ();

	bool canJump ();

	//Note: As this class is about preventing a motor from jumping from
	//-1 to 1 immediately, it is strongly recommended NOT to use the below
	//functions. They can, however, be useful to kill the motor in an un-
	//friendly situation.
	void overrideCurrentValue(float value);
	float rawCurrentValue();
	//^^^^^SETTERS AND GETTERS^^^^^^^^^^//
};

#endif /* SRC_MOTOR_H_ */
