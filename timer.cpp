#include "timer.h"
#include <Windows.h>
#include <string>
#include "to12hr.h"
#include "validate.h"
#include "input.h"

timer::timer(std::string Time, std::string SndPath) {
	validate ValidateData;

	if (!ValidateData.ValidateTime(Time)) {
		std::cout << "The provided time is not in proper 12 hour format!" << std::endl;
		input getInput; // Basically sending the user to the beginning of the program again
	}

	SYSTEMTIME SysTime;
	GetLocalTime(&SysTime);
	std::string convertHrMin;
	to12hr convertHr(SysTime.wHour);
	std::string FormattedTime;
	convertHrMin = (SysTime.wMinute < 10) ? "0" + std::to_string(SysTime.wMinute) : std::to_string(SysTime.wMinute);
	FormattedTime = std::to_string(convertHr.Get12Hour()) + ":" + convertHrMin + " " + convertHr.GetMeridiem();
	std::cout << FormattedTime << std::endl;
}