#include "TCPSocket.h"

SocketSession::SocketSession() {
	if (WSAStartup(WINSOCK_VERSION, &wsa) != 0)
		throw std::system_error(WSAGetLastError(), std::system_category(), "WSA startup failed");
}
SocketSession::~SocketSession() {
	if(WSACleanup() == SOCKET_ERROR);
	//	throw std::system_error(WSAGetLastError(), std::system_category(), "WSA cleanup failed");
}

TCPSocket::TCPSocket() {
	if ((sock = socket(AF_UNSPEC, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
		throw std::system_error(WSAGetLastError(), std::system_category(), "failed to open socket");
}
TCPSocket::TCPSocket(SOCKET s) {
	sock = s;
}
TCPSocket::~TCPSocket() {
	if(closesocket(sock) != 0);
	//	throw std::system_error(WSAGetLastError(), std::system_category(), "failed to close socket");
}
void TCPSocket::Connect(std::string serverIn) {
	std::string address, port;
	size_t pos;
	if ((pos = serverIn.find(':')) != std::string::npos) {
		address = serverIn.substr(0, pos - 1);
		port = serverIn.substr(pos);
	}
	else {
		address = serverIn;
		port = "80";
	}
	struct hostent *host;
	struct addrinfo *res;
	if (getaddrinfo(address.c_str(), port.c_str(), NULL, &res) != 0)
		throw std::system_error(WSAGetLastError(), std::system_category(), "failed to get host info");
	struct sockaddr_in server;
	server.sin_addr = ((struct sockaddr_in*)(res->ai_addr))->sin_addr;
	server.sin_family = AF_INET;
	server.sin_port = htons(std::atoi(port.c_str()));
	if (connect(sock, (struct sockaddr*)&server, sizeof(server)) != 0)
		throw std::system_error(WSAGetLastError(), std::system_category(), "failed to connect to server");
}
void TCPSocket::Send(std::string data, int flags) {
	if (send(sock, data.c_str(), data.length(), flags) == SOCKET_ERROR)
		throw std::system_error(WSAGetLastError(), std::system_category(), "failed to send data");
}
void TCPSocket::Shutdown() {
	if(shutdown(sock, SD_SEND) == 0)
		throw std::system_error(WSAGetLastError(), std::system_category(), "socket shutdown failed");
}
std::string TCPSocket::Recv(SOCKET s) {
	std::string res = "";
	const size_t bufSize = 512;
	int byteCount;
	char buffer[bufSize];
	do {
		byteCount = recv(s, buffer, bufSize, 0);
		if (byteCount < 0)
			throw std::system_error(WSAGetLastError(), std::system_category(), "failed to receive data");
		for (int i = 0; i < byteCount; i++) res += buffer[i];
	} while (byteCount == bufSize);
	return res;
}
std::string TCPSocket::Recv(TCPSocket &s) {
	return Recv(s.sock);
}
std::string TCPSocket::Recv() {
	return Recv(sock);
}
TCPSocket TCPSocket::Accept() {
	if (listen(sock, SOMAXCONN) == SOCKET_ERROR)
		throw std::system_error(WSAGetLastError(), std::system_category(), "listen failed");
	SOCKET ret;
	if ((ret = accept(sock, NULL, NULL)) == INVALID_SOCKET)
		throw std::system_error(WSAGetLastError(), std::system_category(), "accept failed");
	return ret;
}
void TCPSocket::Bind(unsigned int port) {
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);
	if (bind(sock, (sockaddr*)&addr, sizeof(addr)) != 0)
		throw std::system_error(WSAGetLastError(), std::system_category(), "failed to bind");
}
void TCPSocket::Bind(std::string port) {
	Bind(std::atoi(port.c_str()));
}
