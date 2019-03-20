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

#include <cerrno>

#include "exception.h"
#include "ipc.h"
#include "module.h"

const string IPC::SOCKET_PATH = Module::STORAGE + "/.socket"; //FIXME: Am I initialized correctly ?

socket_server IPC::server;
socket_client *IPC::client;

void IPC::initServer() {
	try {
		server.setup(SOCKET_PATH, O_NONBLOCK);

	} catch (const socket_exception &e) {
		switch (e.errnum) {
			case EADDRINUSE:
			case EINVAL:
				throw("The daemon is already running");
			default: throw(e.what);
		}
	}
}

int IPC::receiveClient() {
	if (server.getfd() == -1) {
		initServer();
	}
	int req = -1;

	while (req == -1) {
		try {
			client = server.accept();
			client->recv(&req, sizeof(req));

		} catch (const socket_exception &e) {
			switch (e.errnum) {
				case ECONNABORTED:
				case EAGAIN:
					break;
				default: throw(e.what);
			}
		}
	}
	return req;
}

void IPC::answerClient(int ret) {
	try {
		client->send(&ret, sizeof(ret));
	} catch (const socket_exception &e) {}
	delete client;
}

int IPC::requestDaemon(int req) {
	int ret = -1;

	while (ret == -1) {
		try {
			socket_client client(SOCKET_PATH, O_NONBLOCK);
			client.send(&req, sizeof(req));
			client.recv(&ret, sizeof(ret));

		} catch (const socket_exception &e) {
			switch (e.errnum) {
				case EADDRINUSE:
				case EALREADY:
				case EINPROGRESS:
				case ETIMEDOUT:
				case EISCONN:
				case ECONNREFUSED:
					break;
				default: throw(e.what);
			}
		}
	}
	return ret;
}
