#pragma once
#include <iostream>

class timeLeft
{
	public: 
		timeLeft(int targetHr, int targetMins, std::string Meridiem1, int curHr, int curMins, std::string Meridiem2);
		char* timeLeftStr();

		int GetHoursLeft() {
			return hoursLeft;
		}

		int GetMinutesLeft() {
			return minsLeft;
		}
	private:
		int minsLeft = 0;
		int hoursLeft = 0;
};

