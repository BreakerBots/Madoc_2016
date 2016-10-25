#include "WPILIB.h"
#include "breakerbots.h"
#include "DriveCalibrator.h"
//-----------DRIVE CALIBRATOR CLASS----------------//

	bool DriveCalibrator::getButton(int button){
		return robots_joystick.GetRawButton(button);
	}

	DriveCalibrator::DriveCalibrator(Joystick& js)
		: robots_joystick(js),
		  _currentMode(DriveMode::control),
		  _precisionEffort(.4),
		  _turboEngagedX(0),
		  _turboEngagedY(0),
		  _absDeadband(.1),
		  _maxControlX(.4),
		  _maxControlY(.4)
	{}

	void DriveCalibrator::setMode(){
		if ( getButton(XBox::leftBumper)){
			_currentMode = DriveMode::precisionCCW;
		} else if (getButton(XBox::rightBumper)){
			_currentMode = DriveMode::precisionCW;
		} else {
			_currentMode = DriveMode::control;
		}
	}

	DriveCalibrator::DriveMode DriveCalibrator::currentMode(){
		return _currentMode;
	}

	const char* DriveCalibrator::modeToString(DriveMode input){
		const char* print("default");
		switch (input){
		case DriveMode::control:
			print = "CONTROL";
			break;
		case DriveMode::precisionCCW:
			print = "PRECISION_CCW";
			break;
		case DriveMode::precisionCW:
			print = "PRECISION_CW";
			break;
		}
		return print;
	}

	void DriveCalibrator::setPrecisionEffort(float value){
		_precisionEffort = value;
	}
	float DriveCalibrator::precisionEffort(){
		return DriveCalibrator::_precisionEffort;
	}
	void DriveCalibrator::setMaxControlX(float newX){
		_maxControlX = newX;
	}
	float DriveCalibrator::maxControlX(){
		return _maxControlX;
	}
	void DriveCalibrator::setMaxControlY(float newY){
		_maxControlY = newY;
	}
	float DriveCalibrator::maxControlY (){
		return _maxControlY;
	}
	void DriveCalibrator::setAbsDeadband(float newDeadband){
		_absDeadband = newDeadband;
	}
	float DriveCalibrator::absDeadband(){
		return _absDeadband;
	}

	float DriveCalibrator::controlScaleRawX(const float inputX){
		//This function uses a float inputX, its one argument, and
		//returns the modified value. This modification consists of
		//a safe deadband from deadLeft to deadRight and a scale of
		//raw value {1} to modified value {0.3}

		//Example Graph:
//		       |   /
//		       |  /
//	  ____   ____/  __X-axis
//		    /
//		   /   |           Notice the continuity on both sides of the deadband
//		  /    | <- Y-axis

		//This method implements the following function when maxControl = .3

//		                { = x/3 + 1/30   : x <= -.1     }
//             f(x) =  	{ = 0            : -.1 < x < .1 }
//            		    { = x/3 -1/30    : x >= .1      }                                     }
//-----------------------------------------------------------------------

		float scaledEffort = 0;																		//y

		//value for turbo_raw will come in [-1:1]
		float turbo_trigger = robots_joystick.GetRawAxis(XBox::rightTrigger);						//x

		//This is the limit that the turbo can't exceed
		float turbo_max = 1.0 - maxControlX();

		//This sets the scaled value of the trigger
		_turboEngagedX = turbo_trigger * turbo_max;

		//This adds the current value of the leftjostickand the scaled trigger value
		float effort = maxControlX() + _turboEngagedX;

		//I am solving rise/run for the two points (1, effort) and (deadband, 0)
		float slope = (effort-0)/(1-absDeadband()); 												//m

		//This solves for the changable y intercept by solving y=mx+b for the point (deadband,0.0)
		float rightB = -1*(slope * absDeadband());
		float leftB  = -1*(slope * -absDeadband());//b

		//finally,compute the scaled effort for the piecewise function
		if (-absDeadband() < inputX && inputX < absDeadband()){
			scaledEffort = 0;
		} else if (inputX <= -absDeadband() ){
			// y         =   m   *   x    + b
			scaledEffort = slope * inputX + leftB;
		} else if (inputX >= absDeadband() ){
			// y         =   m   *   x    + b
			scaledEffort = slope * inputX + rightB;
		}
		return scaledEffort;
	}

	float DriveCalibrator::controlScaleRawY(const float inputY){

		float scaledEffort = 0;																		//y

		//value for turbo_raw will come in [-1:1]
		float turbo_trigger = robots_joystick.GetRawAxis(XBox::rightTrigger);						//x

		//This is the limit that the turbo can't exceed
		float turbo_max = 1.0 - maxControlY();

		//This sets the scaled value of the trigger
		_turboEngagedY = turbo_trigger * turbo_max;

		//This adds the current value of the leftjostickand the scaled trigger value
		float effort = maxControlY() + _turboEngagedY;

		//I am solving rise/run for the two points (1, effort) and (deadband, 0)
		float slope = (effort-0)/(1-absDeadband()); 												//m

		//This solves for the changable y intercept by solving y=mx+b for the point (deadband,0.0)
		float rightB = -1*(slope * absDeadband());
		float leftB  = -1*(slope * -absDeadband());//b

		//finally,compute the scaled effort for the piecewise function
		if (-absDeadband() < inputY && inputY < absDeadband()){
			scaledEffort = 0;
		} else if (inputY <= -absDeadband() ){
			// y         =   m   *   x    + b
			scaledEffort = slope * inputY + leftB;
		} else if (inputY >= absDeadband() ){
			// y         =   m   *   x    + b
			scaledEffort = slope * inputY + rightB;
		}
		return scaledEffort;
	}

	float DriveCalibrator::X(){
		float ret_value;
		switch(_currentMode){
		case DriveMode::control:
			ret_value = controlScaleRawX(robots_joystick.GetRawAxis(XBox::leftX));
			break;
		case DriveMode::precisionCCW:
			ret_value = -_precisionEffort;
			break;
		case DriveMode::precisionCW:
			ret_value = _precisionEffort;
			break;
//		case DriveMode::sprint:
//			ret_value = robots_joystick.GetRawAxis(XBox::leftX);
//			break;
		}
		return ret_value;
	}
	float DriveCalibrator::Y(){
		float ret_value;
		switch(_currentMode){
		case DriveMode::control:
			ret_value = controlScaleRawY(robots_joystick.GetRawAxis(XBox::leftY));
			break;
		case DriveMode::precisionCCW:
			ret_value = 0;
			break;        // ^--v---THIS IS NOT TANK DRIVE, since we are driving through
							//arcadeDrive, we DO NOT want to move forward, thus the only
							//change is through the x value, and the y value is always 0
		case DriveMode::precisionCW:
			ret_value = 0;
			break;
//		case DriveMode::sprint:
//			ret_value = robots_joystick.GetRawAxis(XBox::leftY);
//			break;
		}
		return ret_value;
	}
	float DriveCalibrator::turboEngagedX(){
		return _turboEngagedX;
	}
	float DriveCalibrator::turboEngagedY(){
		return _turboEngagedY;
	}
//
//};////^^^^^^^^^^^^DRIVE CALIBRATOR CLASS^^^^^^^^^^^^^^///////////
