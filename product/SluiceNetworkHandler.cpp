#include <memory.h>     // for memset()
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <stdexcept>
#include "SluiceNetworkHandler.hpp"

int SluiceNetworkHandler::CreateTCPClientSocket(const char * servIP, unsigned short port)
{
	int                 sock;
	struct sockaddr_in  ServAddr;

	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		return -1;
	}

	memset(&ServAddr, 0, sizeof(ServAddr));
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_addr.s_addr = inet_addr(servIP);
	ServAddr.sin_port = htons(port);

	if (connect(sock, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) < 0)
	{
		return -1;
	}

	return (sock);
}

SluiceNetworkHandler::SluiceNetworkHandler(int sluis_nummer)
	: socket_fd(CreateTCPClientSocket("127.0.0.1", 5554 + sluis_nummer))
{
	if (socket_fd == -1)
	{
		throw std::invalid_argument("sluis_nummer");
	}

	buffer[buffer_size - 1] = 0; // so we always have a null termination
}

bool SluiceNetworkHandler::ExchangeMessage(const std::string& input, std::string& output)
{
	if (send(socket_fd, input.c_str(), input.size(), 0) != (int)input.size())
	{
		return false;
	}

	int bytesRcvd = recv(socket_fd, buffer, buffer_size - 1, 0);
	if (bytesRcvd < 0)
	{
		return false;
	}

	buffer[bytesRcvd] = 0;
	output = buffer;

	return true;
}

bool SluiceNetworkHandler::AckOk(const std::string& input)
{
	return input == "ack;";
}
