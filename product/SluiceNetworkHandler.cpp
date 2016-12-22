#include <memory.h>     // for memset()
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
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

}

bool SluiceNetworkHandler::ExchangeMessage(const std::string& input, std::string& output)
{
	return false;
}
