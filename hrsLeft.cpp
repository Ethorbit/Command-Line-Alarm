#include "hrsLeft.h"

hrsLeft::hrsLeft(int targetHr, std::string Meridiem1, int curHr, std::string Meridiem2) {
	while (true) {
		if (curHr > 12) {
			curHr = 1;
			Meridiem2 = ("PM") ? "AM" : "PM";
		}

		if (curHr == targetHr && Meridiem1 == Meridiem2) {
			break;
		}

		hoursLeft += 1;
		curHr += 1;
	}
}