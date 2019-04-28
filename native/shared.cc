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

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

#include "exception.h"
#include "module.h"
#include "shared.h"

using namespace std;

bool Shared::fileExists(const string& path) noexcept {
	return ifstream(path).is_open();
}

string Shared::getProperty(const string& key, const string& file) {
	ifstream propFile(file);

	if (!propFile.is_open()) {
		throw("Could not open file: " + file);
	}

	for (string line; getline(propFile, line);) {
		if (line.compare(0, key.size(), key) == 0 && line[key.size()] == '=') {
			return line.substr(key.size() + 1);
		}
	}
	return "";
}

void Shared::setProperty(const string& key, const string& val, const string& file) {
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

		for (string line; getline(propFile, line);) {
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
