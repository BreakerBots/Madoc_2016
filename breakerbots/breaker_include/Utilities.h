/*
 * Utilities.h
 *
 *  Created on: Feb 17, 2016
 *      Author: DS_2016
 */


#ifndef SRC_UTILITIES_H_
#define SRC_UTILITIES_H_

#include "WPILIB.h"
#include <sstream>
#include <string>
#include "DriveCalibrator.h"

class Utilities {
public:
	template <typename F,typename S>
	static const char* concat(F first, S second){

		std::stringstream ss;
		ss << first << second;
		std::string temp = ss.str();
		const char* output = temp.c_str();
		return output;

	}//concat function
	template <typename T>
	static const char* toString(T var){

		std::stringstream ss;
		ss << var;
		std::string temp = ss.str();
		const char* output = temp.c_str();
		return output;

	}//toString function
	static float limit(const float testValue, const float minValue, const float maxValue);

	static void drive(DriveCalibrator& dc, RobotDrive& drive);

	static float deadBand(float inputValue,float absDeadBand,float max);

};

//-------------XBOX CLASS---------------------------//
class XBox {
public:
		enum buttons {a=1, b, x, y, leftBumper, rightBumper, back, start, leftClick, rightClick};
		enum axis {leftX, leftY, leftTrigger, rightTrigger, rightX, rightY, dirPad};
};
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//

//----------RobotPorts CLASS-----------------------//
class SRXMotors {
public:
	enum talonIDs { frontLeft=1, backLeft=2, frontRightBruin=3, backRightBruin=4,
		spinnerLeft=5, spinnerRight=6, elbow=7, roller=8,
		frontRightMadoc=9, backRightMadoc=10, tilter=11 };


};
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//

class RobotPorts{
public:
	enum pwm { indexer=0, kicker=2, tilter=4   };
};

//-------------------FREE FUNCTIONS----------------//

void setPoints(float& target,float* set,Joystick& xbox);



#endif /* SRC_UTILITIES_H_ */
