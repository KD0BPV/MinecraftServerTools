/**
 * @file minecraftd/MCInstance.hh
 *
 * @brief Server instance management - Interface
 *
 * @author E. Mark Anderson <kd0bpv@gmail.com>
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
#include <thread>
#include <atomic>
/* fstream derives from iostream, giving us both. :) */
#include <fstream>

#include "lib/event/libevent.hh"

#ifndef FAIL_LIMIT
#define FAIL_LIMIT 3
#endif

enum class MCInstance::State {
	STARTING, RUNNING,
	STOPPING, STOPPED,
	FAILED
};

struct MCInstance::Config
{
	/* Where am I? */
	std::string InstancePath;

	/* Who am I? */
	std::string MCVersion;
	std::string ForgeVersion = "none";
	std::string ServerJar;

	/* JVM Options */
	std::string MinHeap = "512M";
	std::string MaxHeap = "1G";
	bool x64Mode = false; // Don't assume environment is 64-bit.
	std::string MiscJVMArgs;

	/* Minecraft Options */
	bool OnlineMode = true;
	std::string MiscMCArgs;
};

/* TODO: Probably should make fields Atomic. After all, I'm working with
 * threads here...
 */
class MCInstance
{
public:
	MCInstance();
	~MCInstance();

	/* Inspection methods */
	State getState() const noexcept {return state;}
	int getFailCount() const noexcept {return failCount;}
	void resetFailState() noexcept;

	/* Management methods */
	bool start();
	/* If things REALLY break, pass true to kill.
	 This will most certainly cause data loss though. */
	bool stop(bool force = false);
	bool restart() {stop(); return start();}

	/* Input methods for server jar */
	void sendRaw(std::string raw);
	void say(std::string msg);

	/* Events */
	static Events::Event<MCInstance> FailEvent;

	/* Operator Overloads */
	MCInstance* operator<< (std::string raw); // "alias" for sendRaw()

protected:
	std::thread runner;
	void run(); // Wrapper for Server Jar. Run in thread.
	std::atomic<Config> cfg;
	std::atomic<State> state;
	/* How many times this instance failed. Used to limit automatic restarts
	 * which could cause excessive load.
	 */
	std::atomic<int> failCount;
	std::atomic<int> pid;
private:

};

class MCForgeInstance : public MCInstance
{

};

#endif
