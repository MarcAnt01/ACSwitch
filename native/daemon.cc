/* Copyright (c) 2019 Jaymin Suthar. All rights reserved.
 *
 * This file is part of "Advanced Charging Switch (ACSwitch)".
 *
 * ACSwitch is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, only version 3 of the License.
 *
 * ACSwitch is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ACSwitch.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "battery.h"
#include "config.h"
#include "daemon.h"
#include "exception.h"
#include "ipc.h"
#include "module.h"
#include "sanity.h"
#include "setup.h"
#include "utility.h"

#include <atomic>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;
using namespace chrono;
using namespace this_thread;

static const int REQUEST_CHECK = 1;
static const int REQUEST_KILL = 2;

static const int REQUEST_AUTOMATE = 3;
static const int REQUEST_ENABLE = 4;
static const int REQUEST_DISABLE = 5;

static const int RET_VAL_POSITIVE = 1;
static const int RET_VAL_NEGATIVE = 2;

static atomic_bool IAmKilled = false;
static atomic_int switchMode = REQUEST_AUTOMATE;

static void handleRequest(int req) {
	switch (req) {
		case REQUEST_KILL:
			if (switchMode != REQUEST_AUTOMATE) {
				IPC::answerClient(RET_VAL_NEGATIVE);
				break;
			} else {
				IPC::answerClient(RET_VAL_POSITIVE);
				IAmKilled = true;
				return;
			}

		case REQUEST_CHECK:
			IPC::answerClient(RET_VAL_POSITIVE);
			break;

		case REQUEST_AUTOMATE:
			IPC::answerClient(RET_VAL_POSITIVE);
			switchMode = REQUEST_AUTOMATE;
			break;

		case REQUEST_ENABLE:
		case REQUEST_DISABLE: {
			if (switchMode != REQUEST_AUTOMATE) {
				IPC::answerClient(RET_VAL_NEGATIVE);
			} else {
				IPC::answerClient(RET_VAL_POSITIVE);
				switchMode = req;
			}
		}
	}
}

static void handleSwitch(int mode) {
	switch (mode) {
		case REQUEST_ENABLE:
			Battery::startChargingSafely();
			break;
		case REQUEST_DISABLE:
			Battery::stopChargingSafely();
			break;
		default: {
			if (!Config::isAutomated()) {
				return;
			}

			int level = Battery::getLevel();

			if (level <= Config::getThrEnable()) {
				Battery::startChargingSafely();
			}
			if (level >= Config::getThrDisable()) {
				Battery::stopChargingSafely();
			}
		}
	}
}

static void clientHandler() noexcept {
	signal(SIGPIPE, SIG_IGN);

	while (!IAmKilled) {
		try {
			handleRequest(IPC::receiveClient());

		} catch (const exception& e) {
			cerr << e.what() << endl;
			IAmKilled = true;
		}
	}
}

static void switchHandler() noexcept {
	while (!IAmKilled) {
		try {
			if (!Setup::configGood()) {
				continue;
			}
			handleSwitch(switchMode);
			sleep_for(seconds(Sanity::SLEEP_DELAY));

		} catch (const exception& e) {
			cerr << e.what() << endl;
			IAmKilled = true;
		}
	}
}

bool Daemon::isRunning() {
	return IPC::requestDaemon(REQUEST_CHECK) > 0;
}

void Daemon::requestAutomating() {
	IPC::requestDaemon(REQUEST_AUTOMATE);
}

bool Daemon::requestEnabling() {
	return IPC::requestDaemon(REQUEST_ENABLE) == RET_VAL_POSITIVE;
}

bool Daemon::requestDisabling() {
	return IPC::requestDaemon(REQUEST_DISABLE) == RET_VAL_POSITIVE;
}

void Daemon::handleArgs(const vector<string>& args) {
	if (args[0] == "launch") {
		Utility::execDaemon({ Module::SELF_NAME_DAEMON });

	} else if (args[0] == "kill") {
		if (isRunning() && IPC::requestDaemon(REQUEST_KILL) == RET_VAL_NEGATIVE) {
			throw("A method is running, can not kill daemon");
		}
	} else {
		throw("Invalid action: " + args[0]);
	}
}

[[noreturn]] void Daemon::runServer() noexcept {
	thread clientHandlerThread;
	thread switchHandlerThread;

	try {
		clientHandlerThread = thread(clientHandler);
		switchHandlerThread = thread(switchHandler);

	} catch (const exception& e) {
		cerr << e.what() << endl;
		IAmKilled = true;
	}
	try {
		clientHandlerThread.join();
		switchHandlerThread.join();
	} catch (const exception& e) {}

	exit(EXIT_FAILURE);
}
