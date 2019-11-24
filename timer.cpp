#include "timer.h"
#include <Windows.h>
#include "to12hr.h"
#include <string>

timer::timer(std::string Time, std::string SndPath) {
	// Add classes with code to validate the time & sound path

	SYSTEMTIME SysTime;
	GetLocalTime(&SysTime);
	std::string convertHrMin;
	to12hr convertHr(SysTime.wHour);
	std::string FormattedTime;
	convertHrMin = (SysTime.wMinute < 10) ? "0" + std::to_string(SysTime.wMinute) : std::to_string(SysTime.wMinute);
	FormattedTime = std::to_string(convertHr.Get12Hour()) + ":" + convertHrMin + " " + convertHr.GetMeridiem();
	std::cout << FormattedTime << std::endl;
}