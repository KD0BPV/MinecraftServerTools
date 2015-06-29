#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class Exception : public std::exception
{
public:
	Exception(std::string file, int line, std::string msg = "")
	{
		this->file = file;
		this->line = line;
		if (msg != "")
			this->msg = msg;
		else
			this->msg = "Unspecified";
	}
	
	virtual const char* where() const noexcept
	{
		std::string where = this->file +
		" on line " + std::to_string(this->line);
		return where.c_str();
	}
	
	virtual const char* Exception::what() const noexcept
	{
		return this->msg.c_str();
	}
protected:
	std::string msg;
	std::string file;
	int line = 0;
private:
};

class DaemonizeException : public Exception
{
	DaemonizeException(std::string file, int line)
	: Exception(file, line, "Daemonization Failure")
	{
	}
}

#endif
