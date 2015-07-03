/*
 * minecraftd/lib/libevent.cc
 *
 * Events library: Implementation
 *
 * Author: E. Mark Anderson <kd0bpv@gmail.com>
 *
 * Defines the events library.
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

#include <functional>
#include <vector>

#include "libevent.hh"

namespace Events
{
	Handler* Event::register_handler(Handler *handler)
	{
		handlers.push_back(handler);
		return handler;
	}
	
	void Event::fire()
	{
		for (auto handler : handlers)
		{
			(*handler)(this);
		}
	}
}