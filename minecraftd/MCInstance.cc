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

#include <thread>
#include <string>
/* fstream derives from iostream, giving us both. :) */
#include <fstream>

#include "lib/event/libevent.hh"
#include "MCInstance.hh"

MCInstance::MCInstance()
{
	/* Initialize fields */
	this->failCount = 0;
	this->isModded = false;
	this->state = State::STOPPED;
	
	/* Register our own event handlers */
	this->onFail.register_handler([this] (const Event * ev) {
		this->failCount++;
		if (this->failCount >= FAIL_LIMIT || ev->abort == true)
		{
			this->state = State::FAILED;
		}
	});
}

void MCInstance::resetFailState()
{
	this->failCount = 0;
	this->state = State::STOPPED;
}

void MCInstance::stop(bool force = false)
{
	if (force == true) {
		/* Kill the process and declare failure. */
		
		
		
		this->onFail.abort = true;
		this->onFail.fire();
	} else {
		
	}
}