#include "validate.h"
#include <string>
#include <regex>
#include <Windows.h>

validate::validate() {
}

bool validate::ValidateTime(std::string Time) {
	bool validated = true;
	std::cmatch Match;
	std::regex TimeFormat("(\\d\\d|\\d):\\d\\d\\s*(PM|AM)");
	std::regex_match(Time.c_str(), Match, TimeFormat);

	// If the provided string is in 12 hour format:
	if (Match.size() > 0) {
		std::string newResult;
		int hour, minute;
		char result[3], result2[3];

		// Concatenate the integers:
		if (Time.at(1) != ':') {
			sprintf_s(result, sizeof(result), "%i%i", Time.at(0) - '0', Time.at(1) - '0');
			sprintf_s(result2, sizeof(result2), "%i%i", Time.at(3) - '0', Time.at(4) - '0');
		} else {
			sprintf_s(result, sizeof(result), "%i", Time.at(0) - '0');
			sprintf_s(result2, sizeof(result2), "%i%i", Time.at(2) - '0', Time.at(3) - '0');
		}

		// Convert the chars to integers and assign them:
		hour = std::stoi(result); 
		minute = std::stoi(result2);
		std::cout << "The time passed in: " << hour << ":" << minute << std::endl;

		// Something like 15:00 or 0:15 makes no sense in 12 hr format
		if (hour > 12 || hour < 1) {
			validated = false;
		}

		// And something like 10:99 also makes no sense
		if (minute > 59) {
			validated = false;
		}
	} else { // If the provided Time string is not int:int
		validated = false;
	}

	return validated;
}

bool validate::ValidateSound(std::string SndPath) {

}