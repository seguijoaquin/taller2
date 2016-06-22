#include <Logger.h>

Logger* Logger::_instance = 0;

Logger* Logger::Instance(int Logger_level, string path)
{
	if (_instance == 0)
	{
		_instance = new Logger(Logger_level,path);
	}
	return _instance;
}
void Logger::KillLogger(){
	delete _instance;
	_instance = NULL;
}

Logger::Logger(int Logger_level, string path)
{
	//Assign the argument to the local atribute
	_path = path;
	_logLevel = Logger_level;
	//Check if the file exists, if not create it.
	fstream LoggerFile(path.c_str(),fstream::app);
	if (!LoggerFile)
	{
		//The file does not exist, must create it
		fstream LoggerFile(path.c_str(),fstream::out);
	}
	LoggerFile.close();
}

void Logger::log(int level, string reg)
{
	bool allowed = canLog(level);
	if (allowed)
	{
		time_t timer;
		time (&timer);
		string stringTime = ctime(&timer);
		stringTime = stringTime.substr(0,stringTime.length()-1);
		string prefix = getPrefix(level);
		//Open the stream
		ofstream LoggerFile(_path.c_str(),fstream::app);
		LoggerFile << prefix << DELIMETER;
		LoggerFile << stringTime << DELIMETER;
		LoggerFile << reg << endl;
		LoggerFile.close();
	}
}

void Logger::banner()
{
	time_t timer;
	time (&timer);
	string stringTime = ctime(&timer);
	stringTime = stringTime.substr(0,stringTime.length()-1);
	string stringLevel;
	switch	(_logLevel) {
	    case 0:	stringLevel = "INF";
				break;
		case 1:	stringLevel = "ERR";
				break;
		case 2: stringLevel = "WAR";
				break;
		case 3:	stringLevel = "DEB";
				break;
	}
	string output = string(80,'*') + "\n" + '*' + string(25,' ') + stringTime + ' ' + stringLevel + string(25,' ') + "*\n" + string(80,'*') + '\n';
	//Open the stream
	fstream LoggerFile(_path.c_str(),fstream::app);
	LoggerFile << output;
	LoggerFile.close();
}

bool Logger::canLog(int intentLevel)
{
	if (intentLevel <= _logLevel) //Ej Intento guardar un error en nivel debug
	{
		return true;
	}else{
		return false;
	}
}
string Logger::getPrefix(int level)
{
	string prefix = "";
	switch(level)
	{
	case ERROR:
		prefix = "ERROR";
		break;
	case WARNING:
		prefix = "WARNING";
		break;
	case DEBUG:
		prefix = "DEBUG";
		break;
    case INFO:
        prefix = "INFO";
		break;
	}
	return prefix;
}


