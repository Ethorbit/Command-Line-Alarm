#pragma once
#include <iostream>
#include <regex>

class alarm
{
	public:
		alarm(std::string Time, std::wstring SndPath);
	private:
		int volume = 600;
};

