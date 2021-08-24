#include<iostream>
#include<vector>
#include<thread>
#include<WinSock2.h>
#include<WS2tcpip.h>

enum SOCKET_STATE
{
	DONE = 100,
	E_WSA = 101,
	E_BIND = 102,
	E_LISTEN = 103,
	E_SEND = 104,
	E_RECV = 105,
	E_CONNECT = 106,
	E_ACCEPT = 107,
};

struct Address
{
	char ip[16];
	int  port;
};

class TCPSocket
{
private:
	int totalAccept;

	int wsaResult;
	WSADATA wsaData;

	SOCKET listenSock;
	SOCKADDR_IN sockAddr;
	std::vector<SOCKET> clientSock;
	std::vector<SOCKADDR_IN> clientInfo;

public:
	TCPSocket(int port);
	TCPSocket(const char* ip, const int port);
	TCPSocket(Address address);

	~TCPSocket();

	int Bind();
	int Listen();
	int Accept();
	int Connect();

	int Recv(char* buff, int size);
	int Recv(char* buff, int size, int id);

	int Ping();
	int Ping(int id);

	int Send(char* buff, int size);
	int Send(char* buff, int size, int id);

	int GetLastError() const;
	int GetTotalAccept() const;

	void Close();

	const char* GetClientIP(int id) const;
	const char* GetClientIP(char* buff, int id);
	
	void MultiAccept();
	void CreateMultiAccept();
};

class UDPSocket
{
private:
	int wsaResult;
	WSADATA wsaData;

	SOCKET mainSock;
	SOCKADDR_IN sockAddr;

public:
	UDPSocket();
	UDPSocket(const char* ip, int port);
	UDPSocket(Address address);

	~UDPSocket();

	int Bind(Address addr);
	int Bind(const char* ip, int port);

	int RecvFrom(char* buff, int size);
	int RecvFrom(char* buff, int size, Address address);
	int RecvFrom(char* buff, int size, const char* ip, int port);
	
	int SendTo(char* buff, int size);
	int SendTo(char* buff, int size, Address address);
	int SendTo(char* buff, int size, const char* ip, int port);

	int Ping(Address address);
	int Ping(const char* ip, int port);

	int GetLastError() const;

	void Close();

	void SetTarget(Address address);
	void SetTarget(const char* ip, int port);
};