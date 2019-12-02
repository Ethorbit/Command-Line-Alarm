#include "timer.h"
#include <Windows.h>
#include <string>
#include "to12hr.h"
#include "validate.h"
#include "input.h"
#include "alarm.h"
#include <chrono>

// Stall the program until it's time for the alarm:
void timer::idle(int hours, int minutes) {
	auto endTime = std::chrono::system_clock::now() + std::chrono::hours(hours) + std::chrono::minutes(minutes);
	while (std::chrono::system_clock::now() < endTime) {};
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

	int inputHour;
	if (Time.find("PM") > 0) {
		inputHour = ValidateData.GetHour() + 12;
	} else {
		inputHour = ValidateData.GetHour();
	}

	// Get the system time:
	SYSTEMTIME SysTime;
	GetLocalTime(&SysTime);
	to12hr convertHr(SysTime.wHour);

	// Set the alarm:
	int hoursLeft = inputHour - SysTime.wHour;
	int minsLeft =  ValidateData.GetMinutes() - SysTime.wMinute;
		
	const char* hourTxt = "hours";
	const char* minTxt = "minutes";
	if (hoursLeft == 1) {
		hourTxt = "hour";
	}

	if (minsLeft == 1) {
		minTxt = "minute";
	} 

	if (minsLeft < 1) {
		minsLeft = 0;
	}

	char alarmTxt[150];
	sprintf_s(alarmTxt, 150, "Alarm set for %i %s and %i %s from now", hoursLeft, hourTxt, minsLeft, minTxt);
	std::cout << alarmTxt << std::endl;
	idle(hoursLeft, minsLeft); // Wait until it's time
	alarm Alarm(Time, SndPath); // The time set has passed
}