#pragma once
#include <iostream>

class validate
{
	public:
		validate();
		bool ValidateTime(std::string Time);
		std::string GetMeridiem(std::string Time);
		bool ValidateSound(std::wstring SndPath);

		bool ValidTime() {
			return timeIsValid;
		}

		bool ValidPath() {
			return pathIsValid;
		}

		int GetHour() {
			return savedHour;
		}

		int GetMinutes() {
			return savedMinutes;
		}
	private:
		bool timeIsValid = false;
		bool pathIsValid = false;
		int savedHour;
		int savedMinutes;
};

