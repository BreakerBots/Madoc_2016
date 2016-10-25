/*
 * DriveCalibrator.h
 *
 *  Created on: Feb 17, 2016
 *      Author: DS_2016
 */

#ifndef SRC_DRIVECALIBRATOR_H_
#define SRC_DRIVECALIBRATOR_H_

#include "WPILIB.h"

class DriveCalibrator {
public:
	enum DriveMode {control, precisionCCW, precisionCW/*, sprint*/};

private:
	Joystick& robots_joystick;
	DriveMode _currentMode;
	float _precisionEffort;
	float _turboEngagedX;
	float _turboEngagedY;
	float _absDeadband;
	float _maxControlX;
	float _maxControlY;

	bool getButton(int button);
public:

	explicit DriveCalibrator(Joystick& js);
	~DriveCalibrator() { }

	void setMode();

	DriveMode currentMode();

	const char* modeToString(DriveMode input);
	void setPrecisionEffort(float value);
	float precisionEffort();
	void setMaxControlX(float newX);
	float maxControlX();
	void setMaxControlY(float newY);
	float maxControlY();
	void setAbsDeadband(float newDeadband);
	float absDeadband();

	float controlScaleRawX(const float inputX);
	float controlScaleRawY(const float inputY);
	float X();
	float Y();
	float turboEngagedX();
	float turboEngagedY();
//
};

#endif /* SRC_DRIVECALIBRATOR_H_ */
