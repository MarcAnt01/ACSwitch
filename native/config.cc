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

#include "config.h"
#include "exception.h"
#include "module.h"
#include "sanity.h"
#include "shared.h"

#include <string>
#include <vector>

using namespace std;

static const string SAVE_FILE = Module::STORAGE + "/acs.conf";

static const string AUTOMATION_KEY = "automation";
static const string THR_DISABLE_KEY = "thr_disable";
static const string THR_ENABLE_KEY = "thr_enable";

static const string UEVENT_KEY = "uevent";
static const string TRIGGER_KEY = "trigger";
static const string POS_VAL_KEY = "pos_val";
static const string NEG_VAL_KEY = "neg_val";

static const string AUTOMATION_ENABLED = "true";
static const string AUTOMATION_DISABLED = "false";
static const string THR_DISABLE_DEF = "70";
static const string THR_ENABLE_DEF = "60";

static string getConfig(const string& key) {
	return Shared::getProperty(key, SAVE_FILE);
}

static void setConfig(const string& key, const string& val) {
	Shared::setProperty(key, val, SAVE_FILE);
}

bool Config::isAutomated() {
	return getConfig(AUTOMATION_KEY) == AUTOMATION_ENABLED;
}

int Config::getThrDisable() {
	return stoi(getConfig(THR_DISABLE_KEY));
}

int Config::getThrEnable() {
	return stoi(getConfig(THR_ENABLE_KEY));
}

string Config::getUevent() {
	return getConfig(UEVENT_KEY);
}

string Config::getTrigger() {
	return getConfig(TRIGGER_KEY);
}

string Config::getPosVal() {
	return getConfig(POS_VAL_KEY);
}

string Config::getNegVal() {
	return getConfig(NEG_VAL_KEY);
}

void Config::setUevent(const string& val) {
	setConfig(UEVENT_KEY, val);
}

void Config::setTrigger(const string& val) {
	setConfig(TRIGGER_KEY, val);
}

void Config::setPosVal(const string& val) {
	setConfig(POS_VAL_KEY, val);
}

void Config::setNegVal(const string& val) {
	setConfig(NEG_VAL_KEY, val);
}

void Config::toggleAutomation(const vector<string>& args) {
	if (args[0] == "ON") {
		setConfig(AUTOMATION_KEY, AUTOMATION_ENABLED);

	} else if (args[0] == "OFF") {
		setConfig(AUTOMATION_KEY, AUTOMATION_DISABLED);

	} else {
		throw("Invalid target state: " + args[0]);
	}
}

void Config::updateThresholds(const vector<string>& args) {
	if (args.size() == 0) {
		setConfig(THR_DISABLE_KEY, THR_DISABLE_DEF);
		setConfig(THR_ENABLE_KEY, THR_ENABLE_DEF);

	} else if (args.size() == 2) {
		int thrDisable = Sanity::toLevel(args[0]);
		int thrEnable = Sanity::toLevel(args[1]);

		if (thrDisable <= thrEnable) {
			throw("Arguments are not in correct order");
		}

		setConfig(THR_DISABLE_KEY, args[0]);
		setConfig(THR_ENABLE_KEY, args[1]);

	} else {
		throw("Give either none or both arguments");
	}
}
