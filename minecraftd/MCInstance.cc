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

#include "MCInstance.hh"

MCInstance::MCInstance()
{
	/* Initialize fields */
	failCount = 0;
	state = State::STOPPED;
}

void MCInstance::resetFailState() noexcept
{
	failCount = 0;
	state = State::STOPPED;
}

bool MCInstance::stop(bool force)
{
	if (state == State::STOPPING || state == State::STOPPED ||
		!runner.joinable())
		return false;

	if (force == true) {
		/* Kill the process and declare failure. */



		FailEvent.fire(this);
	} else {
		/* Close the process cleanly */

	}

	runner.join();
	return true;
}

bool MCInstance::start()
{
	if (runner.joinable() || state == State::STARTING ||
		state == State::RUNNING)
		return false;

	runner = new std::thread (&MCInstance::run(), this);
	return true;
}

void MCInstance::run()
{

}

void MCInstance::sendRaw(std::string raw)
{

}

void MCInstance::say(std::string msg)
{
	sendRaw("say " + msg);
}
