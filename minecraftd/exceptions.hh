/*
 * minecraftd/exceptions.hh
 * 
 * Minecraftd Exceptions - What can possibly go wrong?
 * 
 * Author: E. Mark Anderson <kd0bpv@gmail.com>
 * 
 * This file defines and implements the various exceptions that may be thrown
 * throughout minecraftd, excluding exceptions thrown by libraries.
 * 
 * Copyright (C) 2014-2015 E. Mark Anderson
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */ 

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
	
	virtual const char* what() const noexcept
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
public:
	DaemonizeException(std::string file, int line)
	: Exception(file, line, "Daemonization Failure")
	{
	}
};

#endif
