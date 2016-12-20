#include <iostream>
#include <ctime>
#include <string>
#include <ncurses.h>
#include <thread>
#include <memory.h>     // for memset()
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */

int CreateTCPClientSocket(const char * servIP, unsigned short port)
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

void x()
{
	/*send(sock, echoString, echoStringLen, 0);
	bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0);
	if (bytesRcvd > 0)
	{
		echoBuffer[bytesRcvd < RCVBUFSIZE - 1 ? bytesRcvd : RCVBUFSIZE - 1] = 0;
		printf("%s\n", echoBuffer);
	}
	else
	{

	}*/
}

int main(int argc, char *argv[])
{
	int port = argc >= 2 ? std::atol(argv[1]) : 0;
	if (argc < 2)
	{
		std::cout << "Invoking this program requires you to supply a valid port number in the command line!" << std::endl;
		std::cout << "Supplied port must be in range [5555, 5558], supplied port: " << port << std::endl;
		std::cout << "Example: " << argv[0] << " 5555" << std::endl;
		exit(EXIT_FAILURE);
	}

	int sock = CreateTCPClientSocket("127.0.0.1", port);
	if (sock == -1)
	{
		//std::cout << "Cannot establish connection to port: " << port << std::endl;
		//exit(EXIT_FAILURE);
	}

	int sluice_number = port - 5554;

	WINDOW* mainwin = initscr();

	if (mainwin  == NULL) 
	{
		std::cout << "Error initialising ncurses." << std::endl;
		exit(EXIT_FAILURE);
	}

	noecho();				// no keyboard echoing
	nodelay(mainwin, true); // disable waiting for keypress
	keypad(mainwin, TRUE);  // enable non-printable keys in getch
	cbreak();				// disable buffering for fast updates
	curs_set(0);			// disable cursor

	bool running = true;
	while (running)
	{
		/*  Delete the old response line, and print a new one  */

		deleteln();

		time_t t = time(0);   // get time now
		struct tm * now = localtime(&t);

		mvprintw(0, 1, "%d-%d-%d %d:%d:%d", 1900 + now->tm_year, 1 + now->tm_mon, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);
		mvprintw(2, 1, "A - ALARM");
		mvprintw(3, 1, "E - SCHUTTEN");
		mvprintw(4, 1, "U - VRIJGEVEN");
		mvprintw(5, 1, "O - HERSTELLEN");
		mvprintw(6, 1, "M - AFSLUITEN");
		
		mvprintw(8, 1,  "CONNECTION:    OK");
		mvprintw(9, 1,  "SLUICE NUMBER: %d", sluice_number);
		mvprintw(10, 1, "PORT:          %d", port);
		mvprintw(12, 1, "SLUICE STATUS: NONE");

		mvprintw(0, 32,		"+ PROPERTY ----------------- LastKnownValue +");
		for (int i = 1; i <= 29; ++i)
		{
			mvprintw(i, 32, "|                                           |");
		}
		mvprintw(30, 32,	"+-------------------------------------------+");

		mvprintw(1, 33,		 " WATER LEVEL                  low");
		mvprintw(2, 33,		 " DOORS");
		mvprintw(3, 33,		 "     +----LEFT                doorLocked");
		mvprintw(4, 33,		 "     |    |");
		mvprintw(5, 33,		 "     |    +----VALVES");
		mvprintw(6, 33,		 "     |    |    +----HIGH      closed");
		mvprintw(7, 33,		 "     |    |    +----MID       closed");
		mvprintw(8, 33,		 "     |    |    +----LOW       closed");
		mvprintw(9, 33,		 "     |    |");
		mvprintw(10, 33,	 "     |    +----TRAFFIC LIGHTS");
		mvprintw(11, 33,	 "     |    |    |");
		mvprintw(12, 33,	 "     |    |    +----LEFT      off");
		mvprintw(13, 33,	 "     |    |    +----RIGHT     off");
		mvprintw(14, 33,	 "     |    |");
		mvprintw(15, 33,	 "     |    +----LOCK STATE     lockWorking");
		mvprintw(16, 33,	 "     |");
		mvprintw(17, 33,	 "     +----RIGHT               doorLocked");
		mvprintw(18, 33,	 "          |");
		mvprintw(19, 33,	 "          +----VALVES");
		mvprintw(20, 33,	 "          |    +----HIGH      closed");
		mvprintw(21, 33,	 "          |    +----MID       closed");
		mvprintw(22, 33,	 "          |    +----LOW       closed");
		mvprintw(23, 33,	 "          |");
		mvprintw(24, 33,	 "          +----TRAFFIC LIGHTS");
		mvprintw(25, 33,	 "          |    |");
		mvprintw(26, 33,	 "          |    +----LEFT      off");
		mvprintw(27, 33,	 "          |    +----RIGHT     off");
		mvprintw(28, 33,	 "          |");
		mvprintw(29, 33,	 "          +----LOCK STATE     lockWorking");


		switch (getch())
		{
			// Vrijgeven
		case 'u':
		case 'U':
			break;

			// Herstellen
		case 'o':
		case 'O':
			break;

			// Schutten
		case 'e':
		case 'E':
			break;

			// Alarm
		case 'a':
		case 'A':
			break;

			// Exit
		case 'm':
		case 'M':
			running = false;
			break;
		default:
			break;
		}

		refresh();
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	/*  Clean up after ourselves  */
	delwin(mainwin);
	endwin();
	refresh();

	return EXIT_SUCCESS;
}
