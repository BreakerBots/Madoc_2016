#include "WPILib.h"

class Robot: public IterativeRobot
{
private:
	Joystick xbox;
	CANTalon spinLeft, spinRight, test;

public:
	Robot ():
		xbox(0),

		spinLeft(5),
		spinRight(6),
//		elbow(7),
//		roller(8)
		test(9)

	{
	}
private:
	void RobotInit()
	{
	}


	/**
	 * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
	 * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
	 * Dashboard, remove all of the chooser code and uncomment the GetString line to get the auto name from the text box
	 * below the Gyro
	 *
	 * You can add additional auto modes by adding additional comparisons to the if-else structure below with additional strings.
	 * If using the SendableChooser make sure to add them to the chooser code above as well.
	 */
	void AutonomousInit()
	{
	}

	void AutonomousPeriodic()
	{
	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		float inputY = xbox.GetRawAxis(5);//RightY axis

		spinLeft.Set(inputY);
		spinRight.Set(inputY);
		test.Set(inputY);

	}

	void TestPeriodic()
	{
	}
};

START_ROBOT_CLASS(Robot)
