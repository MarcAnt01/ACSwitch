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

#include "database.h"
#include "shared.h"

#include "_database.h"

vector<Database::Switch> & Database::getSwitches() {
	for (int i = 0; i < switch_.size(); i++) {
		if (!Shared::fileExists(switch_[i].uevent) || !Shared::fileExists(switch_[i].trigger)) {
			switch_.erase(switch_.begin() + i--);
		}
	}
	return switch_;
}
