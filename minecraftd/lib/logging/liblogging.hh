/*
 * liblogging.hh
 * 
 * Logging Facility: Definition/API
 * 
 * Author: E. Mark Anderson <kd0bpv@gmail.com>
 * 
 * Copyright (C) 2014 E. Mark Anderson
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

#ifndef LOG_H
#define LOG_H

namespace Logging
{
	enum class State {
		OPEN, CLOSED, FAIL
	};

	enum class Level {
		ALL, DEBUG, INFO, WARN, ERROR, FATAL
	};
	
	/* Exception definitions. */
	class Exception : public std::exception
	{
	public:
		Exception (std::string file, int line, std::string msg);
		virtual const char* where() const noexcept;
		virtual const char* what() const noexcept;
	protected:
		
	private:
		std::string msg;
		std::string file;
		int line = 0;
	};

	class Log
	{
	public:
		Log();
		Log(std::string, Level);
		~Log();
		void write (Level, std::string);
	protected:
		
	private:
		std::string path;
		std::fstream file;
		State state = State::CLOSED;
		Level mask = Level::ALL;
	};
}
#endif