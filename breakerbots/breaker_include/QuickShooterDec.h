/*
 * QuickShooter.h
 *
 *  Created on: Feb 19, 2016
 *      Author: DS_2016
 */

#ifndef SRC_QUICKSHOOTERDEC_H_
#define SRC_QUICKSHOOTERDEC_H_

AnalogInput proxSensor;
Servo servoIndexer;
Servo servoKicker;

CANTalon spinLeft;
CANTalon spinRight;

PrintStream ps;

Indexer shooter;


proxSensor(3),
servoIndexer(0),
servoKicker(1),

spinLeft(SRXMotors::spinnerLeft),
spinRight(SRXMotors::spinnerRight),

ps(),

shooter(xbox,proxSensor,
		servoIndexer,servoKicker,
		spinLeft,spinRight, ps
		),


#endif /* SRC_QUICKSHOOTERDEC_H_ */
