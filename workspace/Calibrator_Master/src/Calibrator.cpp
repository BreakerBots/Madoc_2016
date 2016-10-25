#include "WPILib.h"
#include "breakerbots.h"

class Robot: public IterativeRobot
{
private:
	enum Device { ARM , TILTER };
	//A joystick object to access button and axis values.
	Joystick xbox;

	Device calibratorDevice;
	float dy;     //The value of the right Y joystick axis


		//Talon to be controlled by this program.
	CANTalon armTalon;
	CANTalon tilterTalon;

	bool armDisabled;//Flag for disabled arm (in case it is not functioning)

		//Internal Values, mostly for allowing an external interface (Printing).
	float armTarget;//Value which the elbow will aim toward
	float tilterTarget; //What the talon is aiming for.
		//PID values
	float armPID [3];//P = PID[0] | I = PID[1] | D = PID[2]
	float tilterPID[3];  //Proportional - Integral - Derivative values for the talon.
		//Setpoints
		//These are printed to the screen and can be used to set specific positions.
		//			Ex: UP, LEVEL, and DOWN positions
	float armSetPoints [3];//Stored Value Setpoints for buttons A, B, and X
	float tilterSetPoints[3];//Controlled by buttons A, B, and X and allow
			//for sudden movement in the arm.
		//Names of various setpoints
	const char* armSetPointsStr [3];
	const char* tilterSetPointsStr [3];

public:
	Robot():
		xbox(0),
		calibratorDevice(Device::TILTER),

		dy(0),

		//Talon Initialization
		armTalon(SRXMotors::elbow),
		tilterTalon(SRXMotors::tilter),

		armDisabled(true),

		//Target Initialization
		armTarget(500),//Arbitrary starting setPoint {target | ~6 <= target <= ~1023}
		tilterTarget(0)

	{
		//Initialize the Feedback Device
		//--This is the analog potentiometer that is hooked up to the arm
		//      and the quadrature encoder on the back of the tilter motor.
		armTalon.SetFeedbackDevice(CANTalon::AnalogPot);
		tilterTalon.SetFeedbackDevice(CANTalon::QuadEncoder);
		//kPosition mode allows us to set the arm to a position (5-1023).
		//The arm will then automatically work to get to that point
			//The default control mode is kPercentVBus, in which we tell a talon
			//-100% to 100%, how much power to output
		armTalon.SetControlMode(CANTalon::kPosition);
		tilterTalon.SetControlMode(CANTalon::kPosition);

		//Set up the armPID values to 0
		armTalon.SetPID(0,0,0);
		tilterTalon.SetPID(0,0,0);

		//Default values for PID, controlled by the sliders 0,1,2,3
		for (int i=0;i<3;i++){
			armPID[i] = 0;
			tilterPID[i] = 0;
		}

		//Arbitrary Default Setpoints
		for (int i=0;i<3;i++){
			armSetPoints[i] = 300*i;
			tilterSetPoints[i] = 100*(i+1);//100 - 200 - 300
		}

		//Letter Names, for use in print statements
		armSetPointsStr[0] = "PREP: ";
		armSetPointsStr[1] = "INTAKE: ";
		armSetPointsStr[2] = "CLEAR: ";

		tilterSetPointsStr[0] = "INTAKE: ";
		tilterSetPointsStr[1] = "NEUTRAL: ";
		tilterSetPointsStr[2] = "UP: ";

		armTarget = armTalon.GetPosition();
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
		//DO NOTHING
	}

	void AutonomousPeriodic()
	{
		//DO NOTHING
	}

	void TeleopInit()
	{
		printf("Robot Initialized");

		if (armDisabled) printf("THE ARM IS CURRENTLY DISABLED\n"
				"SEE 'setDevice()' TO RE-ENABLE IT\n");

		for (int i=0;i<3;i++){
//			armPID[i] = SmartDashboard::GetNumber(Utilities::concat("armPID ",i),0);
//			tilterPID[i] = SmartDashboard::GetNumber(Utilities::concat("tilterPID ",i),0);

			armSetPoints[i] = SmartDashboard::GetNumber(Utilities::concat("armSet ",i),300*i);
			tilterSetPoints[i] = SmartDashboard::GetNumber(Utilities::concat("tilterSet ",i),100*i+100);
		}
		for (int i=0;i<3;i++){
			armPID[i] = 0;
			tilterPID[i] = 0;
		}

		for (int i=0;i<3;i++){
			//Clear the sliders, so that none of the PIDF values are set to an
			//obscenely large number later on.
			SmartDashboard::PutNumber(Utilities::concat("DB/Slider ",i),armPID[i]);
		}
	}

	void TeleopPeriodic()
	{
		setDevice();

		loadPID();		//Load PID values from SmartDashboard Values
		loadSetPoints();//Load SetPoints from the xbox

		axisControl();//Fine Adjustment From the Right Y Axis

		armTalon.Set(armTarget);
		tilterTalon.Set(tilterTarget);

		printStuff();

		if (xbox.GetRawButton(XBox::y)){
			printf("SAVED VALUES TO SMARTDASHBOARD");
			saveValues();
		}


	}//teleopPeriodic function

	void setDevice(){
		if (armDisabled) return;

		float POV = xbox.GetPOV(0);
		if (calibratorDevice == Device::ARM){
			if (POV == 90){
				//POV stick to the right
				calibratorDevice = Device::TILTER;
				outputPID();
			}
		} else {
			if (POV == 270){
				//POV stick to the left
				calibratorDevice = Device::ARM;
				outputPID();
			}
		}
	}//setDevice function

	void outputPID(){
		//If this function is not called at the end of each device
		//transition, then the new arm/tilter PID values will be the
		//PID values of the opposite device.

		if (calibratorDevice == Device::ARM){
			for (int i=0;i<3;i++){
				SmartDashboard::PutNumber(Utilities::concat("DB/Slider ",i),armPID[i]);
			}
		} else {
			for (int i=0;i<3;i++){
				SmartDashboard::PutNumber(Utilities::concat("DB/Slider ",i),tilterPID[i]);
			}
		}
	}//outputPID function

	void loadPID (){
		if (calibratorDevice == Device::ARM){
			//Load armPID values
//			printf("Loading PID values for the ARM\n");
			for (int i=0;i<3;i++){
				armPID[i] = SmartDashboard::GetNumber(Utilities::concat("DB/Slider ",i),0/*Default*/);
			}
		} else {
			//Load tilterPID values
//			printf("Loading PID values for the TILTER\n");
			for (int i=0;i<3;i++){
				tilterPID[i] = SmartDashboard::GetNumber(Utilities::concat("DB/Slider ",i),0/*Default*/);
			}
		}
		armTalon.SetPID(armPID[0],armPID[1],armPID[2]);
		tilterTalon.SetPID(tilterPID[0],tilterPID[1],tilterPID[2]);
	}//loadPID function
	void loadSetPoints(){
		if(calibratorDevice == Device::ARM){
			//Load armSetPoints values
			setPoints(armTarget,&armSetPoints[0],xbox);
		} else {
			//Load tilterSetPoints values
			setPoints(tilterTarget,&tilterSetPoints[0],xbox);
		}
	}//loadSetPoints function
	void axisControl(){
		dy = Utilities::deadBand(xbox.GetRawAxis(XBox::rightY),0.1,10);
		dy -= Utilities::deadBand(xbox.GetRawAxis(XBox::leftY),0.1,2);

		if (calibratorDevice == Device::ARM){
			//Change Arm Target
			armTarget -= dy;
		} else {
			//Change Tilter Target
			tilterTarget -= dy;
		}

	}

	void printStuff(){
		//Slot 0
			//Whichever Device (ARM OR TILTER) is being calibrated
		SmartDashboard::PutString("DB/String 0",calibratorDevice == Device::ARM?"Calibrating: ARM":"Calibrating: TILTER");

		//Slots 1-3 are reserved for setpoints
		for (int i=0;i<3;i++){
			if (calibratorDevice == Device::ARM){
				SmartDashboard::PutString(Utilities::concat("DB/String ",i+1),Utilities::concat(armSetPointsStr[i],armSetPoints[i]));
			} else {
				SmartDashboard::PutString(Utilities::concat("DB/String ",i+1),Utilities::concat(tilterSetPointsStr[i],tilterSetPoints[i]));
			}
		}
		//Slot 4 (bottom-left) is the ouput voltage
		if (calibratorDevice == Device::ARM){
			SmartDashboard::PutString("DB/String 4",Utilities::concat("Vout: ",armTalon.GetOutputVoltage()));
		} else {
			SmartDashboard::PutString("DB/String 4",Utilities::concat("Vout: ",tilterTalon.GetOutputVoltage()));
		}

		//Slot 5 (top-right) is the current talon's actual position
		//Slot 6 is the current talon's output voltage
		if (calibratorDevice == Device::ARM){
			SmartDashboard::PutString("DB/String 5",Utilities::concat("Aim: ",armTarget));
			SmartDashboard::PutString("DB/String 6",Utilities::concat("Cur: ",armTalon.GetPosition()));
		} else {
			SmartDashboard::PutString("DB/String 5",Utilities::concat("Aim: ",tilterTarget));
			SmartDashboard::PutString("DB/String 6",Utilities::concat("Cur: ",tilterTalon.GetPosition()));
		}

	}//printStuff function
	void saveValues(){

		for (int i=0;i<3;i++){
			//PID
			SmartDashboard::PutNumber(Utilities::concat("armPID ",i),armPID[i]);
			SmartDashboard::PutNumber(Utilities::concat("tilterPID ",i),tilterPID[i]);
			//Setpoints
			SmartDashboard::PutNumber(Utilities::concat("armSet ",i),armSetPoints[i]);
			SmartDashboard::PutNumber(Utilities::concat("tilterSet ",i),tilterSetPoints[i]);
		}


	}


	void TestPeriodic()
	{
		//DO NOTHING
	}
};

START_ROBOT_CLASS(Robot)
