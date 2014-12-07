/*
 * minecraftd/log.h
 * 
 * minecraftd Logging Facility
 * 
 * Author: E. Mark Anderson <kd0bpv@gmail.com>
 * 
 * Interface file for log manager. 
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

#include <string>
#include <ctime>

enum class Log::State
{
	OPEN, CLOSED, FAIL
}

enum class Log::Level
{
	ALL, DEBUG, INFO, WARN, ERROR, FATAL
}

class Log
{
private:
	std::string path;
	std::fstream file;
	State state = State::CLOSED;
	Level mask = Level::ALL;
public:
	Log();
	Log(std::string, Level);
	void write (Level, std::string);
protected:
	
}
#endif