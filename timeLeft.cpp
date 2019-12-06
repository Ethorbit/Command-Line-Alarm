#include "timeLeft.h"

timeLeft::timeLeft(int targetHr, int targetMins, std::string Meridiem1, int curHr, int curMins, std::string Meridiem2) {
	std::string nextMeridiem;

	// Increment minutes/hours until the calculated time is equal to the destination time:
	while (true) {
		if (curMins > 59) {
			curHr += 1;
			curMins = 0;
		}
		
		if (curHr > 12) {
			curHr = 1;
		}

		if (curHr == 12 && curMins == 0) { 
			if (Meridiem2 == "AM") {
				Meridiem2 = "PM";
			} else if (Meridiem2 == "PM") {
				Meridiem2 = "AM";
			}
		}

		if (curHr == targetHr && curMins == targetMins && Meridiem1 == Meridiem2) {
			break;
		}

		minsLeft += 1;
		curMins += 1;
	}
	
	// Assign values to hoursLeft & minutesLeft:
	while (minsLeft - 60 > 0) {
		minsLeft -= 60;
		hoursLeft += 1;
	}
}

char* timeLeft::timeLeftStr() {
	const char* hourTxt = "hours";
	const char* minTxt = "minutes";
	
	if (hoursLeft == 1) {
		hourTxt = "hour";
	}
	
	if (minsLeft == 1) {
		minTxt = "minute";
	}
	
	char alarmTxt[150];
	sprintf_s(alarmTxt, 150, "Alarm set for %i %s and %i %s from now", hoursLeft, hourTxt, minsLeft, minTxt);
	return alarmTxt;
}

