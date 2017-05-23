#pragma once
#define WIN32_LEAN_AND_MEAN
#include <system_error>
#include <ws2tcpip.h>
#include <WinSock2.h>

#pragma comment(lib, "Ws2_32.lib")

class SocketSession {
private:
	WSADATA wsa;
public:
	SocketSession();
	~SocketSession();
};

class TCPSocket {
private:
	SOCKET sock;
public:
	TCPSocket();
	TCPSocket(SOCKET s);
	~TCPSocket();
	void Connect(std::string serverIn);
	void Send(std::string data, int flags = 0);
	void Shutdown();
	std::string Recv(SOCKET s);
	std::string Recv(TCPSocket &s);
	std::string Recv();
	TCPSocket Accept();
	void Bind(unsigned int port = 80);
	void Bind(std::string port);
};
