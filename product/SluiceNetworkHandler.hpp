#pragma once
#include <string>

class SluiceNetworkHandler
{
private:
	int socket_fd;

	static int CreateTCPClientSocket(const char * servIP, unsigned short port);
public:
	SluiceNetworkHandler(int sluis_nummer);
	bool ExchangeMessage(const std::string& input, std::string& output);
};