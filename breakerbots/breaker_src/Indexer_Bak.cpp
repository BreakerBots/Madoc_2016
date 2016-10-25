//#include "WPILIB.h"
//#include "breakerbots.h"
////--------------INDEXER CLASS----------------------//
//	Indexer::Indexer(Joystick& js, AnalogInput& sensor,
//			float proxSensor_point,
//			Servo& ind, Servo& kick, Servo& tilt,
//			CANTalon& spinL, CANTalon& spinR, Arm& armTalon,
//			PrintStream& printStream
//			)
//		:
//		  robots_joystick(js),
//		  proxSensor(sensor),
//		  proxSensor_detected(proxSensor_point),
//
//		  indexer(ind),
//		  kicker(kick),
//		  tilter(tilt),
//
//		  spinLeft(spinL),
//		  spinRight(spinR),
//
//		  arm(armTalon),
//
//		  ps(printStream),
//
//		  timer(),
//		  _timerDelay(1),
//
//		  _currentMode(IndexerMode::ballOut),
//
//		  _indexerOPEN(65),
//		  _indexerCLOSED(12),
//		  _indexerPos(_indexerOPEN),
//
//		  _kickerLOAD(0),
//		  _kickerFIRE(90),
//		  _kickerPos(_kickerLOAD),
//
//		  _tilterUP(78),
//		  _tilterDOWN(48),
//		  _tilterLEVEL(65),
//
//		  _tilterDA(.2),
//		  _tilterAngle(_tilterLEVEL),
//
//		  _spinIN(.2),
//		  _spinOUT(-.2),
//		  _spinSF(_spinIN)
//
//
//	{
//	}
//
//	void Indexer::setMode(){
//		switch (_currentMode){
//		case IndexerMode::ballOut:
//			if (robots_joystick.GetRawButton(XBox::x)){
//				_currentMode = IndexerMode::ballIntake;
//				arm.arm_intake();
//			}
//			break;
//		case IndexerMode::ballIntake:
//			if (proxSensor.GetVoltage() > proxSensor_detected){
//				_currentMode = IndexerMode::neutral;
//			}
//			if (robots_joystick.GetRawButton(XBox::b)){
//				_currentMode = IndexerMode::ballOut;
//			}
//			break;
//		case IndexerMode::neutral:
//			if ( robots_joystick.GetRawButton(XBox::a) ){
//				_currentMode = IndexerMode::armed;
//				arm.arm_clear();
//			}
//			break;
//		case IndexerMode::armed:
//			if ( !robots_joystick.GetRawButton(XBox::a) ){
//				_currentMode = IndexerMode::fire;
//				timer.Reset();
//				timer.Start();
//			}
//			break;
//		case IndexerMode::fire:
//			if (  proxSensor.GetVoltage() < proxSensor_detected   && timer.Get() > _timerDelay  ){
//				_currentMode = IndexerMode::ballOut;
//				timer.Stop();
//			}
//			break;
//		}
//	}//setMode function
//
//	void Indexer::index(){
//		switch (_currentMode){
//		case IndexerMode::ballOut:
//			_indexerPos = _indexerOPEN;
//			break;
//		case IndexerMode::ballIntake:
//			_indexerPos = _indexerOPEN;
//			break;
//		case IndexerMode::neutral:
//			_indexerPos = _indexerCLOSED;
//			break;
//		case IndexerMode::armed:
//			_indexerPos = _indexerCLOSED;
//			break;
//		case IndexerMode::fire:
//			_indexerPos = _indexerOPEN;
//			break;
//		}//switch statement
//		indexer.SetAngle(_indexerPos);
//	}//index
//	void Indexer::kick(){
//		switch (_currentMode){
//		case IndexerMode::ballOut:
//			_kickerPos = _kickerLOAD;
//			break;
//		case IndexerMode::ballIntake:
//			_kickerPos = _kickerLOAD;
//			break;
//		case IndexerMode::neutral:
//			_kickerPos = _kickerLOAD;
//			break;
//		case IndexerMode::armed:
//			_kickerPos = _kickerLOAD;
//			break;
//		case IndexerMode::fire:
//			_kickerPos = _kickerFIRE;
//			break;
//		}//switch statement
//		kicker.SetAngle(_kickerPos);
//	}//kick
//	void Indexer::spin() {
//		switch (_currentMode){
//		case IndexerMode::ballOut:
//			_spinSF = 0;
//			break;
//		case IndexerMode::ballIntake:
//			_spinSF = _spinIN;
//			break;
//		case IndexerMode::neutral:
//			_spinSF = 0;
//			break;
//		case IndexerMode::armed:
//			_spinSF = _spinOUT;
//			break;
//		case IndexerMode::fire:
//			_spinSF = _spinOUT;
//			break;
//		}//switch statement
//		spinLeft.Set(_spinSF);
//		spinRight.Set(_spinSF);
//	}//spin
//	void Indexer::tilt(){
//		switch (_currentMode){
//		case IndexerMode::ballOut:
//			_tilterAngle = _tilterLEVEL;
//			break;
//		case IndexerMode::ballIntake:
//			_tilterAngle = _tilterDOWN;
//			break;
//		case IndexerMode::neutral:
//			_tilterAngle = _tilterLEVEL;
//			break;
//		case IndexerMode::armed:
//			_tilterAngle = _tilterLEVEL;
//			break;
//		case IndexerMode::fire:
//			_tilterAngle = _tilterLEVEL;/*Utilities::limit(robots_joystick.GetRawAxis(XBox::rightY),_tilterDOWN,_tilterLEVEL+20)*/;
//			break;
//		}//switch statement
//		tilter.SetAngle(_tilterAngle);
//	}//kick
//
//	void Indexer::debug(){
//		ps.print(modeToString(_currentMode),0);
//		ps.print("Sensor: "           , proxSensor.GetVoltage());
//		ps.print("Indexer Position: " , _indexerPos);
//		ps.print("Kicker Position: "  , _kickerPos);
//		ps.print("SpinSF: "           , _spinSF);
//		ps.print("TiltAngle: "  	  , _tilterAngle);
//	}
//	void Indexer::update(bool debugTrue) {
//		//Poll devices and modes and possibly change the _currentMode
//		setMode();
//
//		//Change state of peripherals
//		index();
//		kick();
//		spin();
//		tilt();
//
//		if (debugTrue){
//			debug();
//		}
//	}
//
//	Indexer::IndexerMode Indexer::currentMode(){
//		return _currentMode;
//	}
//	//--------SETTER AND GETTERS--------//
//	////////INDEXER VALUES/////////
//	void Indexer::setIndexerUP(const int newUP){
//		_indexerOPEN = newUP;
//	}
//	int Indexer::indexerUP () const {
//		return _indexerOPEN;
//	}
//	void Indexer::setIndexerDOWN(const int newDOWN){
//		_indexerCLOSED = newDOWN;
//	}
//	int Indexer::indexerDOWN () const {
//		return _indexerCLOSED;
//	}
//	////////KICKER VALUES//////////
//	void Indexer::setKickerLOAD(const int newLOAD){
//		_kickerLOAD = newLOAD;
//	}
//	int Indexer::kickerLOAD () const {
//		return _kickerLOAD;
//	}
//	void Indexer::setKickerFIRE(const int newFIRE){
//		_kickerFIRE = newFIRE;
//	}
//	int Indexer::kickerFIRE () const {
//		return _kickerFIRE;
//	}
//	/////////SPIN VALUES/////////
//	void Indexer::setSpinIN(const float newIN){
//		_spinIN = newIN;
//	}
//	float Indexer::spinIN () const {
//		return _spinIN;
//	}
//	void Indexer::setSpinOUT(const float newOUT){
//		_spinOUT = newOUT;
//	}
//	float Indexer::spinOUT () const {
//		return _spinOUT;
//	}
//	////////tilter VALUES//////////
//	void Indexer::setTilterUP(const int newUP){
//		_tilterUP = newUP;
//	}
//	int Indexer::tilterUP () const {
//		return _tilterUP;
//	}
//	void Indexer::setTilterDOWN(const int newDOWN){
//		_tilterDOWN = newDOWN;
//	}
//	int Indexer::tilterDOWN () const {
//		return _tilterDOWN;
//	}
//	void Indexer::setTilterLEVEL(const int newLEVEL){
//		_tilterLEVEL = newLEVEL;
//	}
//	int Indexer::tilterLEVEL () const {
//		return _tilterLEVEL;
//	}
//	/////////TIMER DELAY//////////////
//	void Indexer::setTimerDelay(const float newDELAY){
//		_timerDelay = newDELAY;
//	}
//	float Indexer::timerDelay () const {
//		return _timerDelay;
//	}
//	//^^^^^^^^END OF SETTER/GETTERS VALUES^^^^^^//
//
//	const char* Indexer::modeToString(IndexerMode input){
//		const char* print("+default");
//		switch (input){
//		case IndexerMode::ballOut:
//			print = "BALL OUT";
//			break;
//		case IndexerMode::ballIntake:
//			print = "BALL INTAKE";
//			break;
//		case IndexerMode::neutral:
//			print = "NEUTRAL";
//			break;
//		case IndexerMode::armed:
//			print = "ARMED";
//			break;
//		case IndexerMode::fire:
//			print = "FIRE";
//			break;
//		}//switch
//		return print;
//	}// modeToString
