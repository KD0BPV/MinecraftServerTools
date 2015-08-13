/*
 * minecraftd/minecraftd.cc
 *
 * Minecraft Server Daemon
 *
 * Author: E. Mark Anderson <kd0bpv@gmail.com>
 *
 * minecraftd is the main daemon that monitors and controls Minecraft server
 * instances. Also handles connections from control clients such as minecraftctl
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

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

/* Fork(), pid_t, umask() */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/* Systemd journaling */
#include <systemd/sd-journal.h>

/* Our classes, defs, etc */
#include "MCInstance.hh"
#include "exceptions.hh"

#define PID_FILE "/run/minecraft/minecraftd.pid"

enum class DaemonStatus {
	PARENT,
	CHILD,
	ERROR
};

DaemonStatus daemonize(pid_t&);

int main(int argc, char *argv[])
{
	pid_t sid = 0;
	try {
		switch (daemonize(sid)) {
		case DaemonStatus::PARENT:
			return EXIT_SUCCESS;
			break;
		case DaemonStatus::CHILD:
			break;
		default:
			throw new daemonize_fail;
		}
	} catch (daemonize_fail& e)	{
		sd_journal_print(LOG_CRIT, e.what());
		return 1;
	}

	/* Daemon-wide data values (ie: vector of instances) */
	std::vector<MCInstance> instances;

	/*
	 * Initialization
	 * This is where we parse arguments, load configs, launch configured
	 * instances, attach to running instances, etc.
	 */



	/* Main Loop */
	while (true) {

	}
	return EXIT_SUCCESS;
}

DaemonStatus daemonize(pid_t &sid)
{
	DaemonStatus result = DaemonStatus::ERROR;
	pid_t pid = fork();

	if (pid >= 0) {
		if (pid == 0) {
			/* We are the child */
			result = DaemonStatus::CHILD;
			sid = setsid();
			if (sid < 0)
				throw new daemonize_fail;
			umask(0);
			if (chdir("/") < 0)
				throw new daemonize_fail;
			close(STDIN_FILENO);
			close(STDOUT_FILENO);
			close(STDERR_FILENO);



		} else if (pid >= 1) {
			/* We are the parent */
			result = DaemonStatus::PARENT;
			/* Write a pid file so Systemd knows who our child is. */
			std::fstream pid_file (PID_FILE,
					std::fstream::out | std::fstream::trunc);
			pid_file << pid;
			pid_file.close();
		}
	} else {
		throw new daemonize_fail;
	}
	return result;
}
