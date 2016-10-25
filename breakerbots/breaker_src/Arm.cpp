#include "Arm.h"
#include "Utilities.h"

void Arm::arm_clear(){
	_target = clearValue;
	armTalon.Set(_target);
}
void Arm::arm_intake(){
	_target = intakeValue;
	armTalon.Set(_target);
}
void Arm::arm_prep(){
	_target = prepValue;
	armTalon.Set(_target);
}


Arm::Arm(Joystick& js, int talonID):
	robots_joystick(js),
	armTalon(talonID),

	clearValue(821),
	intakeValue(741),
	prepValue(640)
	{
	//Initialize the Feedback Device
	//--This is the analog potentiometer that is hooked up to the arm
	armTalon.SetFeedbackDevice(CANTalon::AnalogPot);
	//kPosition mode allows us to set the arm to a position (5-1023).
	//The arm will then automatically work to get to that point
		//The default control mode is kPercentVBus, in which we tell a talon
		//-100% to 100%, how much power to output
	armTalon.SetControlMode(CANTalon::kPosition);


	//Set up the PIDF values to 0
	armTalon.SetPID(0,0,0);

	_target = armTalon.GetSetpoint();

	}

void Arm::monitor(){

	int dpad = robots_joystick.GetPOV(0);//The only dpad on the joystick

	switch (dpad){
	case 0:
		arm_clear();
		break;
	case 90:
		arm_intake();
		break;
	case 180:
		arm_prep();
		break;
	}

	_target += Utilities::deadBand(robots_joystick.GetRawAxis(XBox::rightY),.1,2);

	_target = Utilities::limit(_target,prepValue,950/*MAX*/);
	armTalon.Set(_target);

}

float Arm::target(){
	return _target;
}
//Set Functions
void Arm::SetPID(float p,float i,float d){
	armTalon.SetPID(p,i,d);
}

void Arm::setClear(float clear){
	clearValue = clear;
}
void Arm::setIntake(float intake){
	intakeValue = intake;
}
void Arm::setPrep(float prep){
	prepValue = prep;
}

