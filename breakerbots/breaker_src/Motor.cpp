#include "WPILIB.h"
#include "breakerbots.h"

	Motor::Motor(CANTalon& inMotor):
			motorOut(inMotor),

			_currentValue(0),
			_E(0.01),//Maximum _currentValue jump

			_target(0),
			_targetJump(.2),//Maximum Target jump, NOT TO BE CONFUSED WITH E

			_time(0),
			_timeToTarget(10),//In tics, the time it takes to transition to new Target Speed

			_maxDelta(0.5),
			_delta(0),

			_canJump(true)
		{}
	void Motor::update(float newValue){
		//If the user is making no drastic change...
		if (  fabs(newValue-_currentValue) < _E  ){
			//Set the _currentValue and refresh the robot's vars
			_currentValue = newValue;
			_canJump = true;
			motorOut.Set(_currentValue);
			return;
		}
		if (_canJump){ //If the talon is ready to jump.
			_target += Utilities::limit(newValue-_target,-_maxDelta,_maxDelta);
			_delta = (_target-_currentValue)/_timeToTarget;
			_canJump = false;
			_time = 0;
		} else { //For timeToJump ticks...
			if (_time < _timeToTarget){
				//CurrentValue changes by most _maxDelta
				_currentValue += _delta;
				_time++;
			} else {
				_canJump = true;
			}
		}

		motorOut.Set(_currentValue);
	}

	//------SETTERS AND GETTERS--------//
	void Motor::setE(float input){ _E = input; }
	float Motor::E (){ return _E; }

	void Motor::setTargetJump(float input){ _targetJump = input; }
	float Motor::targetJump (){ return _targetJump; }
	float Motor::target (){ return _target; }

	void Motor::setTimeToTarget(int input){ _timeToTarget = input; }
	int Motor::timeToTarget (){ return _timeToTarget; }

	void Motor::setMaxDelta(float input){ _maxDelta = input; }
	float Motor::maxDelta (){ return _maxDelta; }
	float Motor::delta (){ return _delta; }

	bool Motor::canJump (){ return _canJump; }

	//Note: As this class is about preventing a motor from jumping from
	//-1 to 1 immediately, it is strongly recommended NOT to use the below
	//functions. They can, however, be useful to kill the motor in an un-
	//friendly situation.
	void Motor::overrideCurrentValue(float value){
		_currentValue = value;
		_target = _currentValue;
		_canJump = true;
		_time = 0;
	}
	float Motor::rawCurrentValue(){
		return _currentValue;
	}
	//^^^^^SETTERS AND GETTERS^^^^^^^^^^//

