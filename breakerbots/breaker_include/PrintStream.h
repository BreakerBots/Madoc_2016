/*
 * PrintStream.h
 *
 *  Created on: Feb 17, 2016
 *      Author: DS_2016
 */

#ifndef SRC_PRINTSTREAM_H_
#define SRC_PRINTSTREAM_H_

#include "WPILIB.h"
#include "Utilities.h"

class PrintStream {
private:
	int printIndex;
public:
	PrintStream();
	//Other Functions
	void clearStream();
	void resetStream();

	//Print Functions
	void print(const char* string);
	void print(const char* string,bool boolean);

	template <typename T>
	void print(const char* string, T value){
		SmartDashboard::PutString( /* Utilities::concat("MyVars/",string)*/Utilities::concat("DB/String ",printIndex) , Utilities::concat(string,value)  );
		printIndex++;
	}

};

#endif /* SRC_PRINTSTREAM_H_ */
