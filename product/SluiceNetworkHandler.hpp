#pragma once
#include <string>

class SluiceNetworkHandler
{
private:
	int socket_fd;
	static const size_t buffer_size = 64;
	char buffer[buffer_size];

	static int CreateTCPClientSocket(const char * servIP, unsigned short port);
public:
	SluiceNetworkHandler(int sluis_nummer);
	bool ExchangeMessage(const std::string& input, std::string& output);
	bool AckOk(const std::string& input);
};