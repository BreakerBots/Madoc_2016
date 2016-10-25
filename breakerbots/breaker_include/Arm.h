/*
 * Arm.h
 *
 *  Created on: Mar 7, 2016
 *      Author: DS_2016
 */

#ifndef ARM_H
#define ARM_H

#include "WPILIB.h"

class Arm {

private:
	//These numbers are the ones we use from the range
	//0-1024 that represent the different points that are
	//needed to (1)get the arm out of the way [CLEAR],
	//(2)help deliver boulders to shooter [INTAKE], and
	//(3)prepare to maneuver the portculis and chival de
	//frize [PREP]. These values were set by running the
	//elbowCalibrator.cpp file.

	Joystick& robots_joystick;

	CANTalon armTalon;
	float _target;

	float clearValue;
	float intakeValue;
	float prepValue;

public:
	//Setpoint Functions
	void arm_clear();
	void arm_intake();
	void arm_prep();


	Arm(Joystick& js, int talonID);
	~Arm() { }

	void monitor();

	float target();

	//Set Functions
	void SetPID (float p,float i, float d);

	void setClear(float clear);
	void setIntake(float intake);
	void setPrep(float prep);


};

#endif /* SRC_ARM_H_ */
