#include <iostream>
#include <ctime>
#include <ncurses.h>
#include <thread>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "Invoking this program requires you to supply a port number in the command line!" << std::endl;
		std::cout << "Example: " << argv[0] << " 5555" << std::endl;
		exit(EXIT_FAILURE);
	}

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
		mvprintw(9, 1,  "SLUICE NUMBER: 1");
		mvprintw(10, 1, "PORT:          5555");
		mvprintw(11, 1, "SLUICE STATUS: NONE");

		mvprintw(0, 32,		"+--- S L U I C E     S T A T U S ---+");
		for (int i = 1; i <= 28; ++i)
		{
			mvprintw(i, 32, "|                                   |");
		}
		mvprintw(29, 32,	"+-----------------------------------+");

		mvprintw(1, 33,		 " DOORS");
		mvprintw(2, 33,		 "     |");
		mvprintw(3, 33,		 "     +----LEFT : doorLocked");
		mvprintw(4, 33,		 "     |    |");
		mvprintw(5, 33,		 "     |    +----VALVES");
		mvprintw(6, 33,		 "     |    |    |");
		mvprintw(7, 33,		 "     |    |    +----HIGH: closed");
		mvprintw(8, 33,		 "     |    |    +----MID : closed");
		mvprintw(9, 33,		 "     |    |    +----LOW : closed");
		mvprintw(10, 33,	 "     |    |");
		mvprintw(11, 33,	 "     |    +----TRAFFIC LIGHTS");
		mvprintw(12, 33,	 "     |         |");
		mvprintw(13, 33,	 "     |         +----LEFT : off");
		mvprintw(14, 33,	 "     |         +----RIGHT: off");
		mvprintw(15, 33,	 "     |");
		mvprintw(16, 33,	 "     +----RIGHT: doorLocked");
		mvprintw(17, 33,	 "          |");
		mvprintw(18, 33,	 "          +----VALVES");
		mvprintw(19, 33,	 "          |    |");
		mvprintw(20, 33,	 "          |    +----HIGH: closed");
		mvprintw(21, 33,	 "          |    +----MID : closed");
		mvprintw(23, 33,	 "          |    +----LOW : closed");
		mvprintw(24, 33,	 "          |");
		mvprintw(25, 33,	 "          +----TRAFFIC LIGHTS");
		mvprintw(26, 33,	 "               |");
		mvprintw(27, 33,	 "               +----LEFT : off");
		mvprintw(28, 33,	 "               +----RIGHT: off");


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
