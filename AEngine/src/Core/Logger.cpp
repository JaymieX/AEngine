#include <Core/AEpch.h>
#include "Logger.h"

Logger::MessageSeverity Logger::type = Logger::MessageSeverity::NONE;
std::string Logger::msg;

void Logger::Initialize()
{
	std::ofstream out;
	out.open("AEngineLog.txt", std::ios::out);
	out.close();
}

void Logger::Log(const Logger::MessageSeverity severity, const std::string& message, const std::string& fileName, const int line)
{
	type = severity;
	std::ofstream file;
	file.open("AEngineLog.txt", std::ios::app | std::ios::out);
	if (type <= type && type > Logger::MessageSeverity::NONE) {

		msg += "[";

		switch (type)
		{
		case Logger::MessageSeverity::INFO: msg += "Info"; 
			break;
		case Logger::MessageSeverity::TRACE: msg += "Trace";
			break;
		case Logger::MessageSeverity::ERROR: msg += "Error";
			break;
		case Logger::MessageSeverity::WARNING: msg += "Warning";
			break;
		case Logger::MessageSeverity::FATAL_ERROR: msg += "Fatal Error";
			break;
		default: msg += "Info";
		}

		msg += " " + fileName + " : " + std::to_string(line) + "] " + message + '\n';
		
		file << msg;
		std::cout << msg;
	
		msg = "";
	}

	file.flush();

	file.close();
}