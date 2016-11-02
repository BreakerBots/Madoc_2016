/*
 * Indexer.h
 *
 *  Created on: Feb 17, 2016
 *      Author: DS_2016
 */

#ifndef SRC_INDEXER_H_
#define SRC_INDEXER_H_

#include "WPILIB.h"
#include "PrintStream.h"
#include "Arm.h"

class Indexer {
public:
	enum IndexerMode {eject, ballOut, ballIntake, neutral, armed, fire};
	enum DebugRange {MIN, MED, MAX};


private:

	Joystick& robots_joystick;

	AnalogInput& proxSensor;
	float proxSensor_detected;

	Servo& indexer;
	Servo& kicker;

	CANTalon& tilter;
	CANTalon& spinLeft;
	CANTalon& spinRight;

	bool _usingArm;
	Arm& arm;
	CANTalon& roller;

	PrintStream& ps;

	Timer timer;
	float _timerDelay;

	IndexerMode _currentMode;

	int _indexerOPEN;
	int _indexerCLOSED;
	int _indexerPos;

	int _kickerLOAD;
	int _kickerFIRE;
	int _kickerPos;

	float _tilterUP;
	float _tilterDOWN;
	float _tilterLEVEL;

	float _tilterPos;

	float _spinIN;
	float _spinOUT;
	float _spinSF;

	float _rollerSpeed;

public:

	Indexer(Joystick& js, AnalogInput& sensor, float proxSensor_point,
			Servo& ind, Servo& kick, CANTalon& tilt,
			CANTalon& spinL, CANTalon& spinR, Arm& armTalon, CANTalon& roller,
			PrintStream& printStream
			);
	Indexer(Joystick& js, AnalogInput& sensor, float proxSensor_point,
				Servo& ind, Servo& kick, CANTalon& tilt,
				CANTalon& spinL, CANTalon& spinR, PrintStream& printStream
				);

	void setMode();

	void index();
	void kick();
	void spin();
	void tilt();
	void roll();

	void debug(DebugRange debugAmount);
	void update(DebugRange debugAmount);

	void overrideMode(IndexerMode newMode);
	IndexerMode currentMode();

	//--------SETTER AND GETTERS--------//
	////////INDEXER VALUES/////////
	void setIndexerUP(const int newUP);
	int indexerUP () const;
	void setIndexerDOWN(const int newDOWN);
	int indexerDOWN () const;
	////////KICKER VALUES//////////
	void setKickerLOAD(const int newLOAD);
	int kickerLOAD () const;
	void setKickerFIRE(const int newFIRE);
	int kickerFIRE () const;
	////////tilterER VALUES//////////
	void setTilterUP(const int newUP);
	int tilterUP () const;
	void setTilterDOWN(const int newDOWN);
	int tilterDOWN () const;
	void setTilterLEVEL(const int newLEVEL);
	int tilterLEVEL () const;
	/////////SPIN VALUES/////////
	void setSpinIN(const float newIN);
	float spinIN () const;
	void setSpinOUT(const float newOUT);
	float spinOUT () const;
	/////////TIMER DELAY//////////////
	void setTimerDelay(const float newDELAY);
	float timerDelay () const;
	//^^^^^^^^END OF SETTER/GETTERS VALUES^^^^^^//

	const char* modeToString(IndexerMode input);
};

#endif /* SRC_INDEXER_H_ */
