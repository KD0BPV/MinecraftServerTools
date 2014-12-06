/*
 * minecraftd/minecraftd.cpp
 * 
 * Minecraft Server Daemon
 * 
 * Author: E. Mark Anderson <kd0bpv@gmail.com>
 * 
 * Wraps server.jar so that it can be properly daemonized. Also
 * allows for multiple, independant instances and management of those
 * instances. Controls management connections.
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

#include <iostream>
#include <string>
#include <fstream>

// Fork(), pid_t
#include <sys/types.h>
#include <unistd.h>
// Exit()
#include <stdlib.h>

#include "MCInstance.h"
#include "exceptions.h"

#define PID_FILE /var/run/minecraftd.pid

enum class DaemonStatus
{
	PARENT,
	CHILD,
	ERROR
}

DaemonStatus daemonize ();

int main (int argc, char *argv[])
{
	pid_t sid = 0;
	try {
		switch(daemonize(sid))
		{
			case DaemonStatus::PARENT:
				return EXIT_SUCCESS;
				break;
			case DaemonStatus::CHILD:
				break;
			case DaemonStatus::ERROR:
				throw new DaemonizeException(__FILE__, __LINE__);
				break;
		}
	} catch (DaemonizeException& e)
	{
		
	} catch (exception& e)
	{
		
	}

  return EXIT_SUCCESS;
}

DaemonStatus daemonize (pid_t& sid)
{
	DaemonStatus result = DaemonStatus::ERROR;
	pid_t pid = fork();
	
	if (pid >= 0)
	{
		if (pid == 0)
		{
			// We are the child
			result = DaemonStatus::CHILD;
			sid = setsid();
			if (sid < 0) throw new DaemonizeException(__FILE__, __LINE__);
			umask(0);
			if (chdir("/") < 0) throw new DaemonizeException(__FILE__, __LINE__);
			close(STDIN_FILENO);
			close(STDIOUT_FILENO);
			close(STDERR_FILENO);
			
			// Open log file.
			
		} else if (pid >= 1)
		{
			// We are the parent
			result = DaemonStatus::PARENT;
			// Write a pid file so Systemd knows who our child is.
			std::fstream pid_file = new std::fstream(PID_FILE, std::fstream::out | std::fstream::trunc);
			pid_file.write(pid);
			pid_file.close();
		}
	} else
	{
		throw new DaemonizeException(__FILE__, __LINE__);
	}
	return result;
}


