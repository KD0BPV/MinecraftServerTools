/*
 * minecraftd/MCInstance.hh
 * 
 * Server instance management - Interface
 * 
 * Author: E. Mark Anderson <kd0bpv@gmail.com>
 * 
 * This file provides the interface for the Server Instance Management 
 * system which shall be responsible for monitoring and controlling 
 * individual Server.jar instances, and handle I/O to and from said instance.
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

#ifndef MCINSTANCE_H
#define MCINSTANCE_H

#include <string>


#define FAIL_LIMIT 3


class FailEvent : public Event
{
public:
	bool abort = false;
};

class MCInstance
{
public:
	MCInstance();
	State getState() {return state;}
	int getFailCount() {return failCount;}
	void resetFailState();
	void doCommand(std::string cmd);
	void say(std::string msg);
	void run();

	void start();
	void stop(bool force = false); /* if things REALLY break, pass true to kill.
				  This will most certainly cause data loss though. */
	void restart() {stop(); start();}
	enum class State {
		STARTING, RUNNING,
		STOPPING, STOPPED,
		FAILED
	};
	
	/* Events */
	FailEvent onFail;

protected:
	std::string instanceDir;
	std::string serverJar;
	bool isModded;
	State state;
	
	/* How many times this instance failed. Used to limit automatic restarts
	 * which could cause excessive load.
	 */
	int failCount;
private:
	
};

#endif