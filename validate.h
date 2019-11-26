#pragma once
#include <iostream>

class validate
{
	public:
		validate();
		bool ValidateTime(std::string Time);
		bool ValidateSound(std::string SndPath);

		bool ValidTime() {
			return timeIsValid;
		}

		bool ValidPath() {
			return pathIsValid;
		}
	private:
		bool timeIsValid = false;
		bool pathIsValid = false;
};

