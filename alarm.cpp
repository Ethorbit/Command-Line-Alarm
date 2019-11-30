#include "alarm.h"
#include <Windows.h>
#include <chrono>

// Wait 2 seconds after the sound's duration:
void soundWait(int milliseconds) {
	auto endTime = std::chrono::system_clock::now() + std::chrono::milliseconds(milliseconds) + std::chrono::seconds(2);
	while (std::chrono::system_clock::now() < endTime) {
	}
}

alarm::alarm(std::string Time, std::wstring SndPath) {
	SndPath = L"G:\\Desktop\\Jeff\\question29.mp3";
	std::cout << "Alarm for " << Time << " complete!" << std::endl;
	
	// Assemble the commands to pass to mciSendString:
	wchar_t openCommand[1200];
	wchar_t playCommand[1200];
	wchar_t closeCommand[1200];
	wsprintfW(openCommand, L"open \"%s\" alias alarm", SndPath.c_str());
	wsprintfW(playCommand, L"play alarm", SndPath.c_str());
	wsprintfW(closeCommand, L"close alarm", SndPath.c_str());

	// Handle any errors with playing sounds:
	auto handleErrors = [](MCIERROR Err) {
		wchar_t MciErrTxt[200];
		mciGetErrorString(Err, MciErrTxt, 200);

		if (Err != 0) {
			std::wcout << "ERROR PLAYING SOUND: " << MciErrTxt << std::endl;
		}
	};

	// Try to play the sound:
	MCIERROR MciErr = NULL;
	MciErr = mciSendString(openCommand, NULL, 0, NULL);
	MciErr = mciSendString(playCommand, NULL, 0, NULL);
	handleErrors(MciErr);
	
	// Save length of audio file:
	wchar_t length[100000];
	mciSendString(L"status alarm length", length, 100000, NULL);

	int Repeats = 0;
	while (true) {
		soundWait(_wtoi(length)); // wait for the sound to be done before repeating
		Repeats += 1;
		MciErr = mciSendString(closeCommand, NULL, 0, NULL);
		MciErr = mciSendString(openCommand, NULL, 0, NULL);
		MciErr = mciSendString(playCommand, NULL, 0, NULL);
		handleErrors(MciErr);

		if (Repeats == 1) {
			std::cout << "Sound has repeated " << Repeats << " time" << std::endl;
		} else {
			std::cout << "Sound has repeated " << Repeats << " times" << std::endl;
		}
	}
} 