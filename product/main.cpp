#include <iostream>
#include <ctime>
#include <string>
#include <ncurses.h>
#include <thread>
#include "SluiceLogic.hpp"

int test_main(int argc, char *argv[])
{
	int port = argc >= 2 ? std::atol(argv[1]) : 0;
	if (argc < 2)
	{
		std::cout << "Invoking this program requires you to supply a valid port number in the command line!" << std::endl;
		std::cout << "Supplied port must be in range [5555, 5558], supplied port: " << port << std::endl;
		std::cout << "Example: " << argv[0] << " 5555" << std::endl;
		exit(EXIT_FAILURE);
	}

	int sluice_number = port - 5554;
	SluiceLogic sluice(sluice_number);

	std::cout << "Schutten ..." << std::endl;
	std::cout << sluice.Schutten() << std::endl;
	std::cout << "... klaar." << std::endl;
	return 0;
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

	SluiceLogic sluice(sluice_number);

	bool running = true;
	while (running)
	{
		sluice.Update();

		/*  Delete the old response line, and print a new one  */
		deleteln();

		time_t t = time(0);   // get time now
		struct tm * now = localtime(&t);

		mvprintw(0, 1, "%04d-%02d-%02d %02d:%02d:%02d", 1900 + now->tm_year, 1 + now->tm_mon, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);
		mvprintw(2, 1, "A - ALARM");
		mvprintw(3, 1, "E - SCHUTTEN");
		mvprintw(4, 1, "Y - VRIJGEVEN INVAREN");
		mvprintw(5, 1, "U - VRIJGEVEN UITVAREN");
		mvprintw(6, 1, "O - HERSTELLEN");
		mvprintw(7, 1, "M - AFSLUITEN");
		
		mvprintw(9, 1,  "CONNECTION:    OK");
		mvprintw(10, 1, "SLUICE NUMBER: %d", sluice_number);
		mvprintw(11, 1, "PORT:          %d", port);

		mvprintw(13, 1, "SLUICE STATUS: ");
		switch (sluice.GetState())
		{
		case SluiceLogicStateIdle:
			mvprintw(13, 17, "IDLE");
			break;
		case SluiceLogicStateSchutten:
			mvprintw(13, 17, "SCHUTTEN");
			break;
		case SluiceLogicStateAlarm:
			mvprintw(13, 17, "ALARM");
			break;
		}

		switch (getch())
		{
			// Vrijgeven in
		case 'y':
		case 'Y':
			sluice.VrijgevenInvaren();
			break;

			// Vrijgeven uit
		case 'u':
		case 'U':
			sluice.VrijgevenUitvaren();
			break;

			// Herstellen
		case 'o':
		case 'O':
			sluice.Herstel();
			break;

			// Schutten
		case 'e':
		case 'E':
			sluice.Schutten();
			break;

			// Alarm
		case 'a':
		case 'A':
			sluice.Alarm();
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
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	/*  Clean up after ourselves  */
	delwin(mainwin);
	endwin();
	refresh();

	return EXIT_SUCCESS;
}
