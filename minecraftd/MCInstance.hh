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

enum class InstanceState {
	STARTING, RUNNING,
	STOPPING, STOPPED,
	FAILED
};

class MCInstance
{
public:
	InstanceState getState();
	void doCommand(std::string);
	void say(std::string);

	void start();
	void stop();
	void restart() {stop(); start();}

protected:

private:
	std::string instanceDir;
	InstanceState state = InstanceState::STOPPED;
	int failCount = 0;
	void setState(InstanceState);
};

#endif