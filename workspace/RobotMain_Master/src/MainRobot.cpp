#include "WPILib.h"
#include "breakerbots.h"
#include <math.h>

#define DRIVE_ENABLED
#define SHOOTER_ENABLED


class Robot: public IterativeRobot
{
public:
	enum AutoMode {
		DISABLED, LOW_BAR,
		PORT, CHEVAL,
		MOAT, RAMP,
		DRAW, SALLY,
		ROUGH, WALL
	};

private:
	Joystick xbox; // only joystick
	PrintStream ps;
	Timer _timer;
	bool dashLoaded;

	AutoMode _autoMode;
	int _autoState;

#ifdef DRIVE_ENABLED
	DriveCalibrator driveCalibrator;
	CANTalon frontLeft , backLeft , frontRight, backRight;
	RobotDrive bruinDrive; // robot drive system
#endif

#ifdef SHOOTER_ENABLED
	AnalogInput proxSensor;
	float proxSensor_detected;//Float value of voltage at which point the above sensor is 'triggered'

	Servo servoIndexer;
	Servo servoKicker;

	CANTalon tilterTalon;
	CANTalon spinLeft;
	CANTalon spinRight;

	Indexer ballIntakeCalibrator;
#endif

public:
	Robot()
		:
		xbox(0),
		ps(),
		dashLoaded(false),
		_autoMode(AutoMode::DISABLED),
		_autoState(0)



#ifdef DRIVE_ENABLED
		,driveCalibrator(xbox),
			frontLeft(SRXMotors::frontLeft),
			backLeft(SRXMotors::backLeft),
			frontRight(SRXMotors::frontRightBruin),
			backRight(SRXMotors::backRightBruin),
		bruinDrive(frontLeft, backLeft, frontRight, backRight)
#endif

#ifdef SHOOTER_ENABLED
		,proxSensor(3),
		proxSensor_detected(1.7),
		servoIndexer(RobotPorts::indexer),
		servoKicker(RobotPorts::kicker),

		tilterTalon(SRXMotors::tilter),

		spinLeft(SRXMotors::spinnerLeft),
		spinRight(SRXMotors::spinnerRight),

		ballIntakeCalibrator(xbox,proxSensor, proxSensor_detected,
			servoIndexer,servoKicker, tilterTalon,
			spinLeft, spinRight, ps)
#endif

	{
#ifdef DRIVE_ENABLED
	bruinDrive.SetSafetyEnabled(false);
	driveCalibrator.setPrecisionEffort(0.5);
#endif

#ifdef SHOOTER_ENABLED
	tilterTalon.SetFeedbackDevice(CANTalon::QuadEncoder);
	tilterTalon.SetControlMode(CANTalon::kPosition);
	tilterTalon.SetPID(0,0,0);

	spinLeft.SetSafetyEnabled(false);
	spinRight.SetSafetyEnabled(false);

	ballIntakeCalibrator.setTimerDelay(1.5);
	ballIntakeCalibrator.setSpinIN(.4);
	//Value used in CalGames for this is -.7, but the ball keeps
	//bouncing out of the goal. So we adjusted this value to
	//make the ball come out slower with the hope that more
	//goals stay in!
	ballIntakeCalibrator.setSpinOUT(-.4);
#endif

	}
private:

	void RobotInit()
	{

	}

	void AutonomousInit()
	{

//#ifndef DRIVE_ENABLED
//		_autoMode = AutoMode::DISABLED;
//#else
//		//Determine the Autonomous Mode, in this case the obstacle to attack
//#endif

		//Autonomous Enums
//		enum AutoMode {
//		DISABLED = 0;
//		LOW_BAR = 1;
//		PORT = 2;
//		CHEVAL = 3;
//		MOAT = 4;
//		RAMP = 5;
//		DRAW = 6;
//		SALLY = 7;
//		ROUGH = 8;
//		WALL = 9;
//			};

		if (!dashLoaded) loadDashValues();

		bool BUT [4];
		for (int i=0;i<4;i++){
			BUT [i] = SmartDashboard::GetBoolean(Utilities::concat("DB/Button ",i),false);
		}

		for (int i=0;i<4;i++){
			printf("LED %d: %s\n",i,BUT[i]?"OOOOO":"-----");
		}

		int t = 0;
		//Create a 4-bit autonomous ID
		for (int i=0;i<4;i++){
			int temp = BUT[i] ? 1 : 0;

			t += (int)(pow(2,i)*temp);
			printf("Power: %F\n",pow(2,i));
			printf("T%d: %d",i,t);

		}
		printf("Autonomous Index: %d\n",t);
		//Setup Autonomous Values
		_autoMode = getAutoMode(t);

		_autoState = 0;

		_timer.Reset();
		_timer.Start();

#ifdef SHOOTER_ENABLED
		printf("Shooter Voltage: %F\n",proxSensor.GetVoltage());
		if (proxSensor.GetVoltage() > proxSensor_detected){
			printf("Ball Detected!!!\n");
			ballIntakeCalibrator.overrideMode(Indexer::neutral);
		}
		ballIntakeCalibrator.update(Indexer::MED);
#endif

	}

	void AutonomousPeriodic()
	{
		if (_autoMode == AutoMode::DISABLED) return;
		//Else

#ifdef DRIVE_ENABLED
		switch (_autoMode){
		case AutoMode::DISABLED:
			//Do Nothing
			break;
		case AutoMode::LOW_BAR:
//			printf("LOW_BAR\n");
			switch (_autoState){
			case 0:

				delay(2);
				break;
			case 1:
				bruinDrive.ArcadeDrive(-.4,0,false);

				delay(3);
				break;
			default:
				bruinDrive.ArcadeDrive(0,0,false);
				break;
			}
			break;
		case AutoMode::PORT:
//			printf("PORTCULLIS\n");
			switch (_autoState){
			case 0:

				delay(2);
				break;
			case 1:
				bruinDrive.ArcadeDrive(-.4,0,false);

				delay(3);
				break;
			case 2:
				bruinDrive.ArcadeDrive(-.4,0,false);

				delay(2);
				break;
			case 3:
				bruinDrive.ArcadeDrive(-.6,0,false);

				delay(2);
				break;
			default:
				bruinDrive.ArcadeDrive(0,0,false);
				break;
			}

			break;
		case AutoMode::CHEVAL:
//			printf("CHEVAL\n");
			switch (_autoState){
			case 0:
				delay(2);
				break;
			case 1:
				bruinDrive.ArcadeDrive(-.5,0,false);

				delay(0.7);
				break;
			case 2:
				bruinDrive.ArcadeDrive(0,0,false);
				delay(2);
				break;
			case 3:
				bruinDrive.ArcadeDrive(-.5,0,false);
				delay(2);
				break;
			default:
				bruinDrive.ArcadeDrive(0,0,false);
				break;
			}
			break;
		case AutoMode::MOAT:
//			printf("MOAT\n");
			basicBreach();
			break;
		case AutoMode::RAMP:
//			printf("RAMPARTS\n");
			switch(_autoState){
			case 0:
				delay(2);
				break;
			case 1:
				//Drive quickly over defense.
				bruinDrive.ArcadeDrive(-.5,0,false);
				delay(0.9);
				printf("STATE 0\n");
				break;
			case 2:
//				bruinDrive.ArcadeDrive(-.5,-.75,false);
				bruinDrive.TankDrive(-.5,-.8,false);
				delay(0.5);
				printf("STATE 1\n");
				break;
			case 3:
				bruinDrive.ArcadeDrive(-.75,0,false);
				delay(1);
				printf("STATE 2\n");
				break;
			default:
				bruinDrive.ArcadeDrive(0,0,false);
				break;
			}
			break;
		case AutoMode::DRAW:
//			printf("DRAWBRIDGE\n");
			approach();
			break;
		case AutoMode::SALLY:
//			printf("SALLY_PORT\n");
			approach();
			break;
		case AutoMode::ROUGH:
//			printf("ROUGH_TERRAIN\n");
			//Sprint over defenses 	-- MOAT 			-- RAMPARTS
			//						-- ROUGH_TERRAIN	-- ROCK_WALL;
			/*
			switch(_autoState){
			case 0:
				//Lower arm to stabilize robot.
	#ifdef ELBOW_ENABLED
				arm.arm_intake();
	#endif

				delay(2);
				break;
			case 1:
				//Drive quickly over defense.
				bruinDrive.ArcadeDrive(-.7,0,false);
				delay(2.5);
				break;
			default:
				bruinDrive.ArcadeDrive(0,0,false);
				break;
			}
			*/
			basicBreach();//Minimal Ramp
			break;
		case AutoMode::WALL:
//			printf("ROCK_WALL\n");
			//Sprint over defenses 	-- MOAT 			-- RAMPARTS
			//						-- ROUGH_TERRAIN	-- ROCK_WALL;
			//Old Version, Did not work, tilted robot to the side.
/*			switch(_autoState){
			case 0:
				//Lower arm to stabilize robot.
				delay(2);
				break;
			case 1:
				//Drive quickly over defense.
				bruinDrive.ArcadeDrive(-.7,0,false);
				delay(2.5);
				break;
			default:
				bruinDrive.ArcadeDrive(0,0,false);
				break;
			}
		*/
			//Same approach as rough terrain, successful
			basicBreach();
			break;
		}

#endif //DRIVE_ENABLED (Autonomous is pointless w/o drive.


	}
	void delay(float time){
		if (_timer.Get() > time){
			_autoState++;
			_timer.Reset();
			_timer.Start();
		}
	}
	void approach(){
		switch(_autoState){
		case 0:
			delay(2);
			break;
		case 1:
#ifdef DRIVE_ENABLED
			bruinDrive.ArcadeDrive(-.4,0,0);
#endif
			delay(3.5);
			break;

		default:
#ifdef DRIVE_ENABLED
			bruinDrive.ArcadeDrive(0,0,false);
#endif
			break;
		}
	}
	AutoMode getAutoMode(int autoMode){
		AutoMode newMode;
		switch (autoMode){
		case 0:
			newMode = AutoMode::DISABLED;
			break;
		case 1:
			newMode = AutoMode::LOW_BAR;
			break;
		case 2:
			newMode = AutoMode::PORT;
			break;
		case 3:
			newMode = AutoMode::CHEVAL;
			break;
		case 4:
			newMode = AutoMode::MOAT;
			break;
		case 5:
			newMode = AutoMode::RAMP;
			break;
		case 6:
			newMode = AutoMode::DRAW;
			break;
		case 7:
			newMode = AutoMode::SALLY;
			break;
		case 8:
			newMode = AutoMode::ROUGH;
			break;
		case 9:
			newMode = AutoMode::WALL;
			break;
		default:
			printf("!!!---Autonomous Mode NOT Recognized---!!!");
			newMode = AutoMode::DISABLED;
			break;
		}
		return newMode;
	}
	void ramp(float moveVal, float rotateVal, float dur, float steps){
		//Ramps bruinDrive up to a certain speed (and spin) to prevent
		//jumps that misalign our robot.

		//Every dur/steps seconds, the output values are incremented
		float step = dur/steps;
#ifdef DRIVE_ENABLED
		for (int i=steps;i>=0;i--){
			if (_timer.Get() > (i+1)*step){
				bruinDrive.ArcadeDrive((i+1)*0.2,0,false);
				break;
			}
		}
#endif

	}//ramp method
	void basicBreach(){
		//Sprint over defenses 	-- MOAT 			-- RAMPARTS
		//						-- ROUGH_TERRAIN	-- ROCK_WALL;
		switch(_autoState){
		case 0:
			//Lower arm to stabilize robot.
			delay(2);
			break;
		case 1:
#ifdef DRIVE_ENABLED
			bruinDrive.ArcadeDrive(-.3,0,false);
#endif
			delay(1);
			break;
		case 2:
			//Drive quickly over defense.
#ifdef DRIVE_ENABLED
			bruinDrive.ArcadeDrive(-.7,0,false);
#endif
			delay(2.5);
			break;
		default:
#ifdef DRIVE_ENABLED
			bruinDrive.ArcadeDrive(0,0,false);
#endif
			break;
		}
	}


	//------------------TELE OP-----------//
	void TeleopInit()
	{
		printf("Calling TeleopInit!!!\n");
#ifdef SHOOTER_ENABLED
		if (proxSensor.GetVoltage() > proxSensor_detected){
			ballIntakeCalibrator.overrideMode(Indexer::neutral);
		}
#endif
		if (!dashLoaded) loadDashValues();

		_timer.Stop();
		ps.resetStream();
	}

	void TeleopPeriodic()
	{
		ps.clearStream();

#ifdef DRIVE_ENABLED
		Utilities::drive(driveCalibrator,bruinDrive);
		ps.print(driveCalibrator.modeToString(driveCalibrator.currentMode()));

//		ps.print(Utilities::concat("RawX: ",xbox.GetRawAxis(XBox::leftX)));
//		ps.print(Utilities::concat("RawY: ",xbox.GetRawAxis(XBox::leftY)));
//
//		ps.print(Utilities::concat("NewX: ",driveCalibrator.X()));
//		ps.print(Utilities::concat("NewY: ",driveCalibrator.Y()));

//		ps.print(Utilities::concat("TurboX: ",driveCalibrator.turboEngagedX()));
//		ps.print(Utilities::concat("TurboY: ",driveCalibrator.turboEngagedY()));
#endif
#ifdef SHOOTER_ENABLED
//		ballIntakeCalibrator.setTilterDOWN(SmartDashboard::GetNumber("MyVars/TilterDown",0));
//		printf("Down: %d\n",ballIntakeCalibrator.tilterDOWN());
//		ballIntakeCalibrator.setTilterLEVEL(SmartDashboard::GetNumber("MyVars/TilterLevel",0));
//		printf("Level: %d\n",ballIntakeCalibrator.tilterLEVEL());
		ballIntakeCalibrator.update(Indexer::MED);//bool = debug

		if (proxSensor.GetVoltage()>proxSensor_detected){
			SmartDashboard::PutBoolean("DB/LED 0",true);
		} else {
			SmartDashboard::PutBoolean("DB/LED 0",false);
		}
#endif


	}

	void loadDashValues(){
		dashLoaded = true;
		//Load NetworkTable values for the tilter and arm.
#ifdef SHOOTER_ENABLED
		float tilterPID[3];
		float tilterSet[3];
#endif

		for (int i=0;i<3;i++){

#ifdef SHOOTER_ENABLED
			tilterPID[i] = SmartDashboard::GetNumber(
					Utilities::concat("tilterPID ",i),0);
			tilterSet[i] = SmartDashboard::GetNumber(
					Utilities::concat("tilterSet ",i),100*i);
#endif
		}


#ifdef SHOOTER_ENABLED
//		tilterTalon.SetPID(tilterPID[0],tilterPID[1],tilterPID[2]);
		tilterTalon.SetPID(0.55,0,0);
		ballIntakeCalibrator.setTilterDOWN(0);

		//Hayden / HAYDEN / hayden / haeden
		//  Max (B & X) value goes here -----V
		ballIntakeCalibrator.setTilterLEVEL(1300);
		ballIntakeCalibrator.setTilterUP(1300);

		//Values from SmartDashboard
//		ballIntakeCalibrator.setTilterDOWN(tilterSet[0]);
//		ballIntakeCalibrator.setTilterLEVEL(tilterSet[1]);
//		ballIntakeCalibrator.setTilterUP(tilterSet[2]);
#endif
#ifdef SHOOTER_ENABLED
		printf("Tilter--\tP: %F\tI: %F\tD: %F\n",tilterPID[0],tilterPID[1],tilterPID[2]);
		printf("Tilter--\tIntake: %F\tNeutral: %F\tUp: %F\n",tilterSet[0],tilterSet[1],tilterSet[2]);
#endif
	}

	void TestPeriodic()
	{


	}
};

START_ROBOT_CLASS(Robot)

