#include <iostream>
#include <string>
#include "timer.h"

int main(int argc, std::string argv[])
{
	// If too few arguments passed or they are not running through the command line:
	if (argc < 3) {
		std::string Answer, Time, SndPath;
		timer Timer(Time, SndPath);
	
		/*
		while (Answer != "Y" && Answer != "y") {
			std::cout << "What time should this alarm go off at? (ex. 10:30 AM)" << std::endl;
			std::getline(std::cin, Time);
			std::cout << "Where is the sound file located that should play when this alarm goes off? (C:\\Users\\bob\\Desktop\\playthis.wav)" << std::endl;
			std::getline(std::cin, SndPath);
			std::cout << "So at " << Time << " play: " << SndPath << " - is this correct? (Y/N)" << std::endl;
			std::getline(std::cin, Answer);
		}

		if (Answer == "Y" || Answer == "y") {
			timer Timer(Time, SndPath);
		}*/
	} 
	else {
		
	}
}