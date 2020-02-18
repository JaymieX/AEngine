#include <Core/AEpch.h>
#include "Logger.h"

Logger::MessageSeverity Logger::type = Logger::MessageSeverity::RAD_NONE;
std::string Logger::msg;

void Logger::Log(const Logger::MessageSeverity severity, const std::string& message, const std::string& fileName, const int line)
{
	type = severity;
	std::ofstream file;
	file.open("AEngineLog.txt", std::ios::app | std::ios::out);
	if (type <= type && type > Logger::MessageSeverity::RAD_NONE) {

		msg += "[";

		switch (type)
		{
		case Logger::MessageSeverity::RAD_INFO: msg += "Info"; 
			break;
		case Logger::MessageSeverity::RAD_TRACE: msg += "Trace";
			break;
		case Logger::MessageSeverity::RAD_ERROR: msg += "Error";
			break;
		case Logger::MessageSeverity::RAD_WARNING: msg += "Warning";
			break;
		case Logger::MessageSeverity::RAD_FATAL_ERROR: msg += "Fatal Error";
			break;
		default: msg += "Info";
		}

		msg += " " + fileName + " : " + std::to_string(line) + "] " + message + '\n';
		
		file << msg;
		std::cout << msg;
	
		msg = "";
	}

	file.close();
}