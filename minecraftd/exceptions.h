#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class Exception : public std::exception
{
private:
	int line;
	std::string file;
	std::string msg;
public:
	virtual const char* what() const throw()
	{
		return msg;
	}
	
	Exception (std::string file, int line)
	{
		this->msg = "General Exception at: " + file + ", " + line;
	}
}

class DaemonizeException : public Exception
{
public:
	DaemonizeException (std::string file, int line)
	{
		this->msg = "Failed to daemonize at: " + file + ", " + line;
	}
}

class LogException : public Exception
{
public:
	LogException (std::string file, int line)
	{
		this->msg = "Logging Exception at: " + file + ", " + line;
	}
}
#endif