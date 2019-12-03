#include <string>
#include "input.h"
#include "alarm.h"
#include "timer.h"
#include <tchar.h>

int _tmain(int argc, _TCHAR **argv) {
	// If too few arguments passed or they are not running through the command line:
	if (argc < 3) {
		input getInput;
	} 
	else {	
		std::wstring time(argv[1]);
		char* fixedTime = (char*)malloc(200); // Allocate memory since nothing is assigned to prevent warnings
		size_t maxCount = 0;
		wcstombs_s(&maxCount, fixedTime, 200, argv[1], 200);

		if (fixedTime != NULL) { // Check if it's NULL first to get rid of VS warning
			timer Timer(fixedTime, argv[2]);
		}	
	}
}