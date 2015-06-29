/*
 * Liblogging.cc
 * 
 * Logging Facility: implementation
 * 
 * Author: E. Mark Anderson <kd0bpv@gmail.com>
 * 
 * Copyright (C) 2015 E. Mark Anderson
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

#include <string>
#include <ctime>
#include <fstream>

#include "liblogging.hh"

namespace Logging
{
	Exception::Exception (std::string file, int line, std::string msg = "")
	{
		this->file = file;
		this->line = line;
		if (msg != "")
			this->msg = msg;
		else
			this->msg = "Unspecified";
	}
	
	const char* Exception::where() const noexcept
	{
		std::string where = this->file +
		" on line " + std::to_string(this->line);
		return where.c_str();
	}
	
	const char* Exception::what() const noexcept
	{
		return this->msg.c_str();
	}
	
	Log::Log()
	{
		
	}

	Log::Log(std::string path, Level mask)
	{
		this->path = path;
		this->mask = mask;
		this->file.open(path, std::fstream::out | std::fstream::trunc);
		if (!this->file.is_open())
			throw new Exception(__FILE__, __LINE__,
					    "Could not open log file");
		this->state = State::OPEN;
	}

	Log::~Log()
	{
		if (this->file.is_open()) {
			this->file.close();
			this->state = State::CLOSED;
		}
	}

	void Log::write (Level level, std::string msg)
	{
		// Throw exception if log file isn't open.
		if (this->state != State::OPEN)
			throw new Exception(__FILE__, __LINE__,
					    "Log file not open");
		// Only write to the log if level is greater than or equal to mask.
		if (level >= this->mask) {
			// Get timestamp
			std::time_t timer;
			std::time(&timer);
			std::tm *time = std::localtime(&timer);
			
			std::string timeStamp =
				"[" + std::to_string(time->tm_year) +
				"-" + std::to_string(time->tm_mon)  +
				"-" + std::to_string(time->tm_mday) +
				" " + std::to_string(time->tm_hour) +
				":" + std::to_string(time->tm_min)  +
				":" + std::to_string(time->tm_sec)  + "] ";
			
			// Get levelstamp
			std::string levelStamp;
			switch(level) {
			case Level::DEBUG:
				levelStamp = " [DEBUG] ";
				break;
			case Level::INFO:
				levelStamp = " [INFO] ";
				break;
			case Level::WARN:
				levelStamp = " [WARN] ";
				break;
			case Level::ERROR:
				levelStamp = " [ERROR] ";
				break;
			case Level::FATAL:
				levelStamp = " [FATAL] ";
				break;
			default:
				levelStamp = " [ALL] ";
				break;
			}
			// Write log message
			this->file << timeStamp << levelStamp << msg << std::endl;
		}
	}
}