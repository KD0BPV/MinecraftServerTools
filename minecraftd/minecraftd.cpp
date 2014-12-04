/*
 * minecraftd/minecraftd.cpp
 * 
 * Minecraft Server Daemon
 * 
 * Author: E. Mark Anderson <kd0bpv@gmail.com>
 * 
 * Wraps server.jar so that it can be properly daemonized. Also
 * allows for multiple, independant instances and management of those
 * instances. Controls management connections
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

// Fork(), pid_t
#include <sys/types.h>
#include <unistd.h>
// Exit()
#include <stdlib.h>

using namespace std;

void daemonize ();

int main (int argc, char *argv[])
{

  return 0;
}

void daemonize ()
{
	pid_t pid = fork();
	
	if (pid >= 0)
	{
		if (pid == 0)
		{
			// We are the child
		} else if (pid >= 1)
		{
			// We are the parent
		}
	} else
	{
		// Fork failed.
	}
	
}


