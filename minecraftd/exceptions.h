#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class Exception : public std::exception
{
private:
	int line;
	std::string file;
public:
	virtual const char* what() const throw()
	{
		return "General Exception at: " + file + ", " + line;
	}
	
	Exception (std::string file, int line)
	{
		this.file = file;
		this.line = line;
	}
}

class DaemonizeException : public Exception
{
public:
	virtual const char* what() const throw()
	{
		return "Failed to daemonize at: " + file + ", " + line;
	}
	
	DaemonizeException (std::string file, int line)
	{
		this.file = file;
		this.line = line;
	}
}
#endif