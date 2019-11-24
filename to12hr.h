#pragma once
#include <iostream>

class to12hr
{
	public:
		to12hr(int hour);

		int Get12Hour() {
			return convertedHour;
		}

		std::string GetMeridiem() {
			return meridiem;
		}
	private:
		int convertedHour;
		std::string meridiem;
};

