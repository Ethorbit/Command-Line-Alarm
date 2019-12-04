#include "timer.h"
#include <Windows.h>
#include <thread>
#include <chrono>
#include <string>
#include "to12hr.h"
#include "validate.h"
#include "input.h"
#include "alarm.h"
#include "timeLeft.h"

// Stall the program until it's time for the alarm:
void timer::idle(int hours, int minutes) {
	auto endTime = std::chrono::steady_clock::now() + std::chrono::hours(hours) + std::chrono::minutes(minutes);
	while (std::chrono::steady_clock::now() < endTime) {
		// Optimize program CPU usage by waiting 100ms every time:
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	};
}

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

	if (Time == "now") { // Debugging purposes
		alarm Alarm(Time, SndPath); 
		return;
	}

	// Convert meridiem to caps (I.e AM or PM):
	validate validation;
	std::string inputTimeMeridiem = validation.GetMeridiem(Time);

	// Get the system time:
	SYSTEMTIME SysTime;
	GetLocalTime(&SysTime);
	to12hr convertHr(SysTime.wHour);

	// Set the alarm:
	timeLeft timeleft(ValidateData.GetHour(), ValidateData.GetMinutes(), inputTimeMeridiem, convertHr.Get12Hour(), SysTime.wMinute, convertHr.GetMeridiem());
	std::cout << timeleft.timeLeftStr() << std::endl;
	idle(timeleft.GetHoursLeft(), timeleft.GetMinutesLeft()); // Wait until it's time
	alarm Alarm(Time, SndPath); // The time set has passed
}