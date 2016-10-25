#include "WPILIB.h"
#include "breakerbots.h"


PrintStream::PrintStream():
	printIndex(0)
{}
//Other Functions
void PrintStream::clearStream(){
	printIndex = 0;
}
void PrintStream::resetStream(){
	for (int i=0;i<10;i++){
		SmartDashboard::PutString( /*Utilities::concat("MyVars/Info: ",printIndex)*/Utilities::concat("DB/String ",i) , "");
	}
}

//Print Functions
void PrintStream::print(const char* string){
	SmartDashboard::PutString( /*Utilities::concat("MyVars/Info: ",printIndex)*/Utilities::concat("DB/String ",printIndex) , string );
	printIndex++;
}
void PrintStream::print(const char* string,bool boolean){
	SmartDashboard::PutString( /*Utilities::concat("MyVars/",string)*/Utilities::concat("DB/String ",printIndex) , Utilities::toString( (boolean ? "TRUE":"FALSE") )  );
	printIndex++;
}

//Implemented in header file due to template
//	template <typename T>
//	void print(char* string, T value){
//		SmartDashboard::PutString(  concat("DB/String ",printIndex) , concat(string,value)  );
//		printIndex++;
//	}
