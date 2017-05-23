#pragma once
#include "TCPSocket.h"

class HTTP {
public:
	static std::string get(std::string url) {
		size_t n = url.find("://");
		if (n != std::string::npos)
			url = url.substr(n + 3);
		n = url.find('/');
		std::string path, adr;
		if (n != std::string::npos) {
			path = url.substr(n);
			adr = url.substr(0, n);
		}
		else
			path = "/";
		std::string request = "GET "+path+" HTTP 1/1\r\n\
Host: "+adr+"\r\n\
Connection: close\r\n\
\r\n";
		SocketSession wsa;
		TCPSocket sock;
		sock.Connect(adr);
		sock.Send("GET "+path+" HTTP/1.1\r\n\
Host: "+adr+"\r\n\
Connection: close\r\n\
\r\n");
		return sock.Recv();
	}
};
