#include "SimpleHTTP.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	try {
		SocketSession wsa;
		TCPSocket sock;
		sock.Bind(80);
		while (1) {
			TCPSocket client = sock.Accept();
			string str = sock.Recv(client);
			string responce = "HTTP/1.1 200 OK\r\n\
Content-Type: text/plain\r\n\
\r\n\
Hi! Your request is:\r\n" + str;
			client.Send(responce);
			client.Shutdown();
		}
	}
	catch (system_error ex) {
		cout << ex.what() << endl;
	}
}
