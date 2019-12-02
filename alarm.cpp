#include "alarm.h"
#include <Windows.h>
#include <chrono>
#include <thread>

// Wait 2 seconds after the sound's duration:
void soundWait(int milliseconds) {
	auto endTime = std::chrono::system_clock::now() + std::chrono::milliseconds(milliseconds) + std::chrono::seconds(2);
	while (std::chrono::system_clock::now() < endTime) {
	}
}

alarm::alarm(std::string Time, std::wstring SndPath):volume(600) {
	std::cout << "Alarm for " << Time << " complete!" << std::endl;
	
	// Assemble the commands to pass to mciSendString:
	wchar_t openCommand[400];
	wchar_t playCommand[400];
	wchar_t closeCommand[400];
	if (SndPath.at(0) == '"') {
		wsprintfW(openCommand, L"open %s alias alarm", SndPath.c_str());
	} else {
		wsprintfW(openCommand, L"open \"%s\" alias alarm", SndPath.c_str());
	}
	
	wsprintfW(playCommand, L"play alarm", SndPath.c_str());
	wsprintfW(closeCommand, L"close alarm", SndPath.c_str());

	// Handle any errors with playing sounds:
	auto handleErrors = [](MCIERROR Err) {
		wchar_t MciErrTxt[200];
		mciGetErrorString(Err, MciErrTxt, 200);

		if (Err != 0) {
			std::wcout << "ERROR WHILE PLAYING SOUND: " << MciErrTxt << std::endl;
		}
	};

	int vol = volume;
	auto increaseVolume = [&vol]() {
		DWORD newVol = MAKELONG(vol, vol); // Merge values for balanced left & right audio levels (I.E 0x10001000)
		if (vol * 4 < 65535) { // If it's lower than max allowed volume
			vol *= 2;
			newVol = MAKELONG(vol, vol);
			waveOutSetVolume(NULL, newVol);
		}
		else {
			waveOutSetVolume(NULL, 0xFFFFFFFF);
		}
	};

	// Increase volume every 10 seconds:
	auto TenSecVolume = [increaseVolume, vol]() {
		while (true) {
			auto endTime = std::chrono::system_clock::now() + std::chrono::seconds(10);

			while (std::chrono::system_clock::now() < endTime) {
			}

			increaseVolume();
			endTime = std::chrono::system_clock::now() + std::chrono::seconds(10);
		}
	};

	increaseVolume();
	
	// Try to play the sound:
	MCIERROR MciErr = NULL;
	MciErr = mciSendString(openCommand, NULL, 0, NULL);
	MciErr = mciSendString(playCommand, NULL, 0, NULL);
	handleErrors(MciErr);

	// Set initial volume to be quiet:
	DWORD newVol = MAKELONG(1000, 1000); 
	waveOutSetVolume(NULL, newVol);

	// Save length of audio file:
	wchar_t lengthstr[1000];
	mciSendString(L"status alarm length", lengthstr, 1000, NULL);
	int length = _wtoi(lengthstr);

	// A length of 0 would cause everything to happen too fast and crash the program!
	if (length < 1) {
		std::cout << "ERROR: The sound file's duration must be longer than 0 seconds!" << std::endl;
		return;
	}

	std::thread* t1 = nullptr;
	// If sound length is more than 10 seconds then just increase volume every 10 seconds:
	if (length > 10000) {
		t1 = new std::thread(TenSecVolume); // Use a new thread so that the next while loop can occur instantly
	}

	int Repeats = 0;
	auto playAlarm = 
	[
		&Repeats, 
		closeCommand,
		openCommand,
		playCommand,
		length, 
		&MciErr, 
		handleErrors, 
		increaseVolume
	]() {
		while (true) {
			soundWait(length); // Wait for the sound to be done before repeating
			Repeats += 1;
			MciErr = mciSendString(closeCommand, NULL, 0, NULL);
			MciErr = mciSendString(openCommand, NULL, 0, NULL);
			MciErr = mciSendString(playCommand, NULL, 0, NULL);
			handleErrors(MciErr);

			if (length < 10000) {
				increaseVolume();
			}

			if (Repeats == 1) {
				std::cout << "Sound has repeated " << Repeats << " time" << std::endl;
			}
			else {
				std::cout << "Sound has repeated " << Repeats << " times" << std::endl;
			}
		}
	};

	// Thread #1 may already be in use, so use this one on a while loop:
	std::thread t2(playAlarm);

	// Wait for both threads to complete their tasks:
	if (t1 != nullptr) { 
		t1->join();
		delete(t1);
	}
	
	t2.join();
} 