#pragma once

class Logger
{
public:
	enum class MessageSeverity : unsigned short {
		RAD_NONE,
		RAD_INFO,
		RAD_TRACE,
		RAD_ERROR,
		RAD_WARNING,
		RAD_FATAL_ERROR,
	};

	Logger(const Logger&) = delete;
	Logger(Logger&&) = delete;
	Logger& operator=(const Logger&) = delete;
	Logger& operator=(Logger&&) = delete;
	Logger() = delete;
	
	static void Log(const MessageSeverity, const std::string&, const std::string&, const int);

private:	
	static MessageSeverity type;
	static std::string msg;
};

#define LOG_INFO(msg, fileName, line) { Logger::Log(Logger::MessageSeverity::RAD_INFO, msg, fileName, line); }
#define LOG_TRACE(msg, fileName, line) { Logger::Log(Logger::MessageSeverity::RAD_TRACE, msg, fileName, line); }
#define LOG_ERROR(msg, fileName, line) { Logger::Log(Logger::MessageSeverity::RAD_ERROR, msg, fileName, line); }
#define LOG_WARNING(msg, fileName, line) { Logger::Log(Logger::MessageSeverity::RAD_WARNING, msg, fileName, line); }
#define LOG_FATAL_ERROR(msg, fileName, line) { Logger::Log(Logger::MessageSeverity::RAD_FATAL_ERROR, msg, fileName, line); }