#pragma once
#include <iostream>

class hrsLeft
{
	public: 
		hrsLeft(int targetHr, std::string Meridiem1, int curHr, std::string Meridiem2);
	
		int GetHoursLeft() {
			return hoursLeft;
		}
	private:
		int hoursLeft = 0;
};

