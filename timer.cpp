#include "timer.h"
#include <Windows.h>
#include <string>
#include "to12hr.h"
#include "validate.h"
#include "input.h"
#include "alarm.h"

timer::timer(std::string Time, std::wstring SndPath) {
	// Validate user inputs:
	validate ValidateData;

	if (!ValidateData.ValidateTime(Time)) {
		std::cout << "The provided time is not in proper 12 hour format!" << std::endl;
		input getInput; // Basically sending the user to the beginning of the program again
	}

	if (!ValidateData.ValidateSound(SndPath)) {
		input getInput;
	}

	int inputHour;
	if (Time.find("PM") > 0) {
		inputHour = ValidateData.GetHour() + 12;
	}
	else {
		inputHour = ValidateData.GetHour();
	}

	// Get the system time:
	SYSTEMTIME SysTime;
	GetLocalTime(&SysTime);
	to12hr convertHr(SysTime.wHour);
	//std::string convertHrMin;
	//std::string FormattedTime;
	//convertHrMin = (SysTime.wMinute < 10) ? "0" + std::to_string(SysTime.wMinute) : std::to_string(SysTime.wMinute);
	//FormattedTime = std::to_string(convertHr.Get12Hour()) + ":" + convertHrMin + " " + convertHr.GetMeridiem();

	// Set the alarm:
	bool AlarmTriggered;
	while (SysTime.wHour >= inputHour && SysTime.wMinute > ValidateData.GetMinutes() && !AlarmTriggered) {
		alarm Alarm(SndPath); // The time has come, play the sound
	}
}