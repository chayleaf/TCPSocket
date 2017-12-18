Basic socket library. Note that you must not include any winapi-related headers before TCPSocket.h since all the dependencies need to be included in the right order.
Client example:
```cpp
SocketSession wsa;
TCPSocket sock;
sock.Connect("127.0.0.1:80");
sock.Send("GET / HTTP/1.1\r\n\
Host: 127.0.0.1\r\n\
Connection: close\r\n\
\r\n");
return sock.Recv();
```

Server example:
```cpp
SocketSession wsa;
TCPSocket sock;
sock.Bind(80);
while (1) {
	TCPSocket client = sock.Accept();
	string str = sock.Recv(client);
	client.Send("HTTP/1.1 200 OK\r\n\
Content-Type: text/plain\r\n\
\r\n\
Hi\r\n");
	client.Shutdown();
}
```

You can handle errors via std::system_error
