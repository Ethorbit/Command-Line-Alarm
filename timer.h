#pragma once
#include <iostream>

class Jeff;

class timer
{
	public:
		timer(std::string Time, std::wstring SndPath);
	private:
		void idle(int hours, int minutes);
};

