#pragma once

#include <memory>
#include <string>
#include <sys/socket.h>

#define LIBSOCKET_READ 1
#define LIBSOCKET_WRITE 2

extern "C" {
	int create_socket(const char *path, int flags);
	int destroy_socket(int fd);
	int shutdown_socket(int fd, int method);
	int create_server_socket(const char *path, int flags);
	int accept_socket(int fd, int flags);
}

using namespace std;

namespace libsocket
{
	struct socket_exception {
		int errnum;
		string what;

		socket_exception(const string &message);
	};

	class socket {
		protected:
			int fd;

		public:
			socket();
			socket(const socket &) = delete;
			socket(socket &&other);
			virtual ~socket();

			int getfd() const;

			virtual int destroy();
			int setsockopt(int level, int opt, const char *val, socklen_t len) const;
	};

	class unix_socket : public virtual socket {
		protected:
			string _path;

		public:
			unix_socket();
			string getpath();
	};

	class stream_client_socket : public virtual socket {
		protected:
			bool shut_rd;
			bool shut_wr;

		public:
			stream_client_socket();
			stream_client_socket(const stream_client_socket &) = delete;
			stream_client_socket(stream_client_socket &&other)
				: socket(move(other)), shut_rd(false), shut_wr(false) {}

			ssize_t send(const void *buf, size_t len, int flags = 0);
			ssize_t recv(void *buf, size_t len, int flags = 0);

			void shutdown(int method = LIBSOCKET_WRITE);

		friend stream_client_socket & operator<<(stream_client_socket &sock, const char *str);
		friend stream_client_socket & operator<<(stream_client_socket &sock, const string &str);
		friend stream_client_socket & operator>>(stream_client_socket &sock, string &dest);
	};

	class unix_stream_client : public unix_socket, public stream_client_socket {
		public:
			unix_stream_client();
			unix_stream_client(const char *path, int flags = 0);
			unix_stream_client(const string &path, int flags = 0);

			void connect(const char *path, int flags = 0);
			void connect(const string &path, int flags = 0);

		friend class unix_stream_server;
	};

	class unix_stream_server : public unix_socket {
		public:
			unix_stream_server();
			unix_stream_server(const char *path, int flags = 0);
			unix_stream_server(const string &path, int flags = 0);

			void setup(const char *path, int flags = 0);
			void setup(const string &path, int flags = 0);

			unix_stream_client * accept(int flags = 0);
			unique_ptr<unix_stream_client> accept2(int flags = 0);
	};
} // END NAMESPACE LIBSOCKET

using namespace libsocket;

typedef unix_stream_client socket_client;
typedef unix_stream_server socket_server;
