#include "Utilities.h"

float Utilities::limit(const float testValue, const float minValue, const float maxValue){
	//Tests value 'testValue,' and keeps it between the minValue and maxValue
	float ret_angle;

	if (testValue < minValue){
		//If testValue is less than minValue, return minValue
		ret_angle = minValue;
	} else if (testValue > maxValue){
		//If testValue is greater than maxValue, return maxValue
		ret_angle = maxValue;
	} else {
		//If testValue is between minValue and maxValue, return
		ret_angle = testValue;
	}

	return ret_angle;
}//limit function
void Utilities::drive(DriveCalibrator& dc, RobotDrive& drive){
	dc.setMode();

	float driveX = dc.X();
	float driveY = dc.Y();

	drive.ArcadeDrive( driveY, driveX, false);
}
float Utilities::deadBand(float inputValue, float absDeadBand, float max){
	float output = 0;

	float m = max/(1-absDeadBand);
	float b = -m*absDeadBand; //y = mx+b FOR (absDeadBand,0)== 0 = m*absDeadBand + b

	if (inputValue <= -absDeadBand){
		output = m*inputValue + b;
	} else if (inputValue >= absDeadBand){
		output = m*inputValue -b;
	} else {
		output = 0;
	}
	return output;
}//deadBand method

//----------------FREE FUNCTIONS----------------//

//Returns null, modifies target ref, float pointer, and joystick ref.
void setPoints(float& target,float* set,Joystick& xbox){
	for (int i=0;i<3;i++){
		//Display Setpoints in Slots 7-9 (Bottom-right 3)
		SmartDashboard::PutString(Utilities::concat("DB/String ",7+i),Utilities::concat("Set: ",set[i]));

		//If user presses A, B, or X ...
		if (xbox.GetRawButton(i+1)/*1A->2B->3X(->4Y)*/){
			if (xbox.GetRawButton(XBox::leftBumper)){
				//Save current target as setpoint A/B/X
				set[i] = target;
			} else {
				//Load setpoint A/B/X as new target
				target = set[i];
			}
		}
	}
}//setPoints method



