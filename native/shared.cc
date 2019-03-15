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

#include <fstream>
#include <iostream>
#include <unistd.h>

#include "exception.h"
#include "module.h"
#include "shared.h"

using namespace std;

const int Shared::UID_ROOT = 0;

bool Shared::acquireRoot() noexcept {
	if (seteuid(UID_ROOT) == 0) {
		return true;
	} else {
		cerr << "Could not acquire root access" << endl;
		return false;
	}
}

bool Shared::isProcessAlive(const string &pid) {
	int killRet = kill(stoi(pid), 0);
	switch (errno) {
		case ESRCH:
		case 0:
			throw("Could not check for PID: " + pid);
		default: return killRet == 0;
	}
}

bool Shared::fileExists(const string &path) noexcept {
	return ifstream(path).is_open();
}

string Shared::getProperty(const string &key, const string &file) {
	ifstream propFile(file);

	if (!propFile.is_open()) {
		throw("Could not open file: " + file);
	} else {
		string line;

		while (getline(propFile, line)) {
			if (line.compare(0, key.size(), key) == 0 && line[key.size()] == '=') {
				return line.substr(key.size() + 1);
			}
		}
	}
	throw("Could not find property: " + key + ", in file: " + file);
}

void Shared::setProperty(const string &key, const string &val, const string &file) {
	const string temp = Module::STORAGE + "/.tempfile";

	{
		ifstream propFile(file);
		ofstream tempFile(temp, ios::out | ios::trunc);

		if (!propFile.is_open()) {
			throw("Could not open file: " + file);
		}
		if (!tempFile.is_open()) {
			throw("Could not open file: " + temp);
		}

		string line;

		while (getline(propFile, line)) {
			if (line.compare(0, key.size(), key) == 0 && line[key.size()] == '=') {
				tempFile << key << '=' << val << "\n";
			} else {
				tempFile << line << "\n";
			}
		}
	}
	if (rename(temp.c_str(), file.c_str()) == -1) {
		throw("Could not move file: " + temp + ", to " + file);
	}
}
