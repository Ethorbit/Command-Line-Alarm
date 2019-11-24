#include "to12hr.h"

to12hr::to12hr(int hour) {
	// Set hour:
	if (hour > 11) {
		convertedHour = hour - 12;
	} 
	else if (hour == 0) {
		convertedHour = hour + 12;
	} 
	else {
		convertedHour = hour;
	}

	// Set Meridiem:
	meridiem = (hour < 12) ? "AM" : "PM";
}
