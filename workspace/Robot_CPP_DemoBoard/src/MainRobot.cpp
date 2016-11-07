#include "WPILib.h"
#include "breakerbots.h"


class Robot: public IterativeRobot {
public:

private:
	Joystick xbox;

	CANTalon testMotor;


public:
	Robot():
		xbox(0),
		testMotor(11)//Tilter==5
	{
	}

private:

	void RobotInit(){
		//No idea when this is called
	}

	void AutonomousInit(){
		//Called once at the start of each Auto period
	}

	void AutonomousPeriodic(){
		//Called PERIODICALLY during the Auto period
	}

	void TeleopInit(){
		//Called once at the start of each operator period
		printf("TELEOP Initialized\n");
	}
	void DisabledInit(){
		printf("Disabled TELEOP\n");
	}

	void TeleopPeriodic(){
		//Called PERIODICALLY during the operator period

		float valX = xbox.GetRawAxis(XBox::rightX);
		float valY = xbox.GetRawAxis(XBox::rightY);

		printf("Joystick: [ %4f , %4f ]\n",
				valX,valY);

		if (abs(valX)>0.15){
			testMotor.Set(valX);
		} else {
			testMotor.Set(0);
		}

	}

	void TestPeriodic(){
		//Who knows (We don't use this)
	}
};

START_ROBOT_CLASS(Robot)
