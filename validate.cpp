#include "validate.h"
#include <string>
#include <regex>
#include <Windows.h>

validate::validate() {
}

bool validate::ValidateTime(std::string Time) {
	bool validated = true;
	if (Time == "now") { // For debugging purposes
		return validated;
	}

	std::cmatch Match;
	std::regex TimeFormat("(\\d\\d|\\d):\\d\\d\\s*([aA][mM]|[pP][mM])");
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
		savedHour = hour;
		savedMinutes = minute;

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

bool validate::ValidateSound(std::wstring SndPath) {
	// Windows will be confused if it finds quotes in the path, so remove any:
	for (int i = 0; i < SndPath.length(); i++) {
		if (SndPath.at(i) == '"') {
			SndPath.erase(i, i + 1);
		}
	}

	bool validated = true;
	DWORD FileAttrib = GetFileAttributesW(SndPath.c_str());

	if (FileAttrib == INVALID_FILE_ATTRIBUTES) {
		wchar_t buffer[1000];
		FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), LANG_NEUTRAL, buffer, sizeof(buffer) / sizeof(wchar_t), NULL);
		std::wcout << "Error with the provided sound path! - " << buffer << std::endl;
		validated = false;
	} 

	return validated;
}

std::string validate::GetMeridiem(std::string Time) {
	std::cmatch matchAM, matchPM;
	std::regex findAM("([aA][mM])");
	std::regex findPM("([pP][mM])");
	std::regex_search(Time.c_str(), matchAM, findAM);
	std::regex_search(Time.c_str(), matchPM, findPM);

	if (matchAM.size() > 0) {
		return "AM";
	} else {
		return "PM";
	}
}