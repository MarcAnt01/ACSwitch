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

#include "commandline.h"
#include "daemon.h"
#include "module.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

static const int UID_ROOT = 0;

static bool acquireRoot() noexcept {
	if (seteuid(UID_ROOT) == 0) {
		return true;
	} else {
		cerr << "Could not acquire root access" << endl;
		return false;
	}
}

int main(int argc, const char* argv[]) noexcept {
	if (!acquireRoot()) {
		return EXIT_FAILURE;
	}
	if (argv[0] == Module::SELF_NAME_DAEMON) {
		Daemon::runServer();
	}
	return Commandline::handleArgs(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
