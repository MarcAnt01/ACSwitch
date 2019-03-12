#pragma once

#include <cerrno>
#include <memory>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>

#define LIBSOCKET_STREAM 1

#define LIBSOCKET_READ 1
#define LIBSOCKET_WRITE 2

extern "C" {
extern int create_unix_stream_socket(const char *path, int flags);
extern int destroy_unix_socket(int sfd);
extern int shutdown_unix_stream_socket(int sfd, int method);
extern int create_unix_server_socket(const char *path, int socktype, int flags);
extern int accept_unix_stream_socket(int sfd, int flags);
}

using namespace std;

namespace libsocket
{
	struct socket_exception {
		int err;
		string mesg;

		socket_exception(const string& file,int line,const string& message, bool show_errno = true);
	};

	class socket {
		protected: int sfd;
		protected: bool is_nonblocking;
		protected: bool close_on_destructor;

		public: socket(void);
		public: socket(const socket &) = delete;
		public: socket(socket &&);

		public: virtual ~socket();

		public: virtual int destroy(void);

		public: int getfd(void) const;

		public: int set_sock_opt(int level, int optname, const char *optval, socklen_t optlen) const;
	};

	class unix_socket : public virtual socket {
		protected: string _path;

		public: unix_socket();

		public: string get_path(void);
	};

	class stream_client_socket : public virtual socket {
		protected: bool shut_rd;
		protected: bool shut_wr;

		public: stream_client_socket();
		public: stream_client_socket(const stream_client_socket &) = delete;
		public: stream_client_socket(stream_client_socket && other) : socket(std::move(other)), shut_rd(false), shut_wr(false) {}

		public: ssize_t snd(const void *buf, size_t len, int flags = 0);
		public: ssize_t rcv(void *buf, size_t len, int flags = 0);

		friend stream_client_socket & operator<<(stream_client_socket &sock, const char *str);
		friend stream_client_socket & operator<<(stream_client_socket &sock, const string &str);
		friend stream_client_socket & operator>>(stream_client_socket &sock, string &dest);

		public: void shutdown(int method = LIBSOCKET_WRITE);
	};

	class unix_stream_client : public unix_socket, public stream_client_socket {
		public: unix_stream_client(void);
		public: unix_stream_client(const char *path, int socket_flags = 0);
		public: unix_stream_client(const string &path, int socket_flags = 0);

		public: void connect(const char *path, int socket_flags = 0);
		public: void connect(const string &path, int socket_flags = 0);

		friend class unix_stream_server;
	};

	class unix_stream_server : public unix_socket {
		public: unix_stream_server(void);
		public: unix_stream_server(const char *path, int flags = 0);
		public: unix_stream_server(const string &path, int flags = 0);

		public: void setup(const char *path, int flags = 0);
		public: void setup(const string &path, int flags = 0);

		public: unix_stream_client * accept(int flags = 0);
		public: unique_ptr<unix_stream_client> accept2(int flags = 0);
	};
} // END NAMESPACE LIBSOCKET

using namespace libsocket;

typedef unix_stream_client socket_client;
typedef unix_stream_server socket_server;
