#pragma once
#include "TCPSocket.h"
#include <sstream>

class HTTP {
public:
	static std::string urlEncode(std::string url) {
		std::stringstream ans;
		std::string ignore = "#&.=/+?-_~";
		for (int i = 0; i < url.length(); i++)
			if (url[i] == '%' && i < url.length() - 2 && isalnum(url[i + 1]) && isalnum(url[i + 2]))
				ans << url[i];
			else if (isalnum(url[i]) || ignore.find(url[i]) != std::string::npos)
				ans << url[i];
			else
				ans << '%' << std::hex << std::uppercase << (int)url[i] << std::nouppercase;
		return ans.str();
	}
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
		std::string request = "GET "+urlEncode(path)+" HTTP 1/1\r\n\
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
