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

#include <array>
#include <iostream>

#include "commandline.h"
#include "config.h"
#include "daemon.h"
#include "exception.h"
#include "method.h"
#include "module.h"
#include "setup.h"
#include "utility.h"

using namespace std;

static const array<Commandline::Option, 7> options = { {
	{ "--toggle",		1,	1,	true,	Config::toggleAutomation },
	{ "--update",		0,	2,	true,	Config::updateThresholds },
	{ "--method",		1,	1,	true,	Method::parseAndRun },
	{ "--configure",	0,	0,	false,	Setup::configureSwitch },
	{ "--daemon",		1,	1,	false,	Daemon::handleArgs },
	{ "--info",			0,	0,	true,	Utility::printInfo },
	{ "--help",			0,	0,	false,	Module::printHelp }
} };

static const char **argvMain;

static int optsIndex = -1;
static int argvIndex;
static int argcMain;

static bool setOptsIndexOf(const char *arg) noexcept {
	optsIndex = -1;
	for (int i = 0; i < options.size(); i++) {
		if (options[i].option == arg) {
			optsIndex = i;
		}
	}
	return optsIndex != -1;
}

#define isOption(arg) ((arg[0]) == '-' && (arg[1]) == '-')

static bool populateArgs(vector<string> &args) {
	for (int i = argvIndex + 1; i < argcMain && argvMain[i] != nullptr; i++) {
		if (args.size() < options[optsIndex].argsMax) {
			if (isOption(argvMain[i])) {
				break;
			}
			args.push_back(argvMain[i]);
			argvIndex++;
		}
	}
	return args.size() >= options[optsIndex].argsMin;
}

bool Commandline::handleArgs(int argc, const char *argv[]) noexcept {
	argcMain = argc;
	argvMain = argv;

	for (argvIndex = 1; argvIndex < argcMain; argvIndex++) {
		try {
			vector<string> args;

			if (!setOptsIndexOf(argvMain[argvIndex])) {
				throw("Unrecognized option: " + (string) argvMain[argvIndex]);
			}
			if (!populateArgs(args)) {
				throw("Option misses arguments: " + options[optsIndex].option);
			}
			if (options[optsIndex].checkSetup) {
				Setup::checkOrDie();
			}
			options[optsIndex].handler(args);

		} catch (const exception &e) {
			cerr << e.what() << endl;
			return false;
		}
	}
	return true;
}
