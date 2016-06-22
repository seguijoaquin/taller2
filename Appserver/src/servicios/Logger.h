/*
 * Logger.h
 *
 *  Created on: Mar 22, 2015
 *      Author: neo
 *  Construction:
 *  	Logger::Instance(Logger_level, path)
 *		Logger_level sets the available Logger levels
 *		path sets the path to save.
 *		Both may be empty.
 *	Usage:
 *		Logger::Instance()->Logger(LEVEL,REPORT);
 *		Logger_PATH may be empty
 *		LEVEL & REPORT MUST NOT be empty
 *
 *	LoggerLevel: There's 3 options
 *		0: Error -> Default
 *		1: Warnings
 *		2: Debug
 */

#ifndef Logger_H_
#define Logger_H_

#include <time.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
//Default Logger path
#define LOG_PATH "log.txt"
//Level Options
#define DEBUG 3
#define WARNING 2
#define ERROR 1
#define INFO 0
#define DELIMETER "\t"


class Logger
{
	protected:
		Logger(int log_level, string path);
	public:
		void log(int level, string reg);
		void KillLogger(); //Destructor;
		static Logger* Instance(int log_level = ERROR, string path = LOG_PATH);
		void banner();
	private:
		bool canLog(int level);
		static Logger* _instance;
		string _path;
		int _logLevel;
		string getPrefix(int level);
};



#endif /* Logger_H_ */
