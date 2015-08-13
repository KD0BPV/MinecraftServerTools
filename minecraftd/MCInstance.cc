/*
 * minecraftd/MCInstance.cc
 *
 * Server instance management - Implementation
 *
 * Author: E. Mark Anderson <kd0bpv@gmail.com>
 *
 * This file implements the Server Instance Management system which shall
 * be responsible for monitoring and controlling individual Server.jar
 * instances, and handle I/O to and from said instance.
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

#include <systemd/sd-journal.h>

#include "MCInstance.hh"

MCInstance::MCInstance()
{
	failCount.store(0);
	state.store(State::STOPPED);
}

void MCInstance::resetFailState() noexcept
{
	failCount.store(0);
	state.store(State::STOPPED);
}

bool MCInstance::stop(bool force)
{
	char* UUID = cfg.load().UUID;
	State s = state.load();
	if (s == State::STOPPING || s == State::STOPPED ||
		!runner.joinable())
		return false;

	if (force == true) {
		/* Kill the process and declare failure. */
		sd_journal_print(LOG_NOTICE,
			"Forcibly stopping Instace %i", *UUID);


		FailEvent.fire(this);
	} else {
		/* Close the process cleanly */
		sd_journal_print(LOG_NOTICE,
			"Stopping Instance %i", *UUID);

	}

	runner.join();
	return true;
}

bool MCInstance::start()
{
	char* UUID = cfg.load().UUID;
	sd_journal_print(LOG_NOTICE,
		"Attempting to start Instance %i", *UUID);

	State s = state.load();
	if (runner.joinable() ||
	    (s == State::STARTING ||
	     s == State::RUNNING)) {
		sd_journal_print(LOG_WARNING,
			"Instance %i appears to be already running.",
			*UUID);
		return false;
	}

	runner = std::thread (&MCInstance::run, this);
	if (runner.joinable()) {
		state.store(State::STARTING);
		sd_journal_print(LOG_INFO,
			"Instance %i is starting", *UUID);
		return true;
	} else {
		failCount.store(failCount.load()+1);
		sd_journal_print(LOG_ERR,
			"Could not start Instance %i", *UUID);
		return false;
	}
}

/* Remember, we're working in a separate thread here. Stay thread-safe! */
void MCInstance::run()
{
	state.store(State::STARTING);

	while (true) {

	}
}

void MCInstance::sendRaw(std::string raw)
{

}

void MCInstance::say(std::string msg)
{
	sendRaw("say " + msg);
}
