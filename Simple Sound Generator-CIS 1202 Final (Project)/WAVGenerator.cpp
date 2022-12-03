//4 December 2022
//This program uses PCM (Pulse Code Modulation) to create a short .wav file with a pure sine wave
//This program creates a simple sine wave and writes it to a .wav file. This .wav is classified as raw data so keep that in mind when it won't play through a media player. Software like Audacity are capable of reading raw data.

#include "ByteConvert.h"
#include "Sound.h"

#include <cmath>
#include <string>
#include <iostream>
#include <fstream>

int main() {
	int channelNum;
	int pi = 3.14;
	double amplitudeInput;
	int limiter;

	//My classes
	class ByteConvert convert;
	class RIFF RIFFformat;
	class Format SoundFormat;
	class Data DataFormat;
	class Sine SineConfig;

	//for the frequency input
	double frequency = SineConfig.frequencyInput;

	//creates the .wav file
	std::ofstream wav;
	wav.open("sine.wav", std::ios::binary);//allows the file to be in binary mode

	std::cout << "\nPlease type the number of audio channels (1 or 2): ";
	std::cin >> channelNum;
	std::cout << "\nYou have selcted " << channelNum << " channels..." << std::endl;

	if (channelNum == 1) {
		channelNum = SoundFormat.numCHANNELS;
		std::cout << "You have chosen mono. . .";
	}

	else if (channelNum == 2) {
		channelNum = SoundFormat.numCHANNELS;
		std::cout << "You have chosen stereo. . .";
	}

	else {
		std::cout << "\nInvalid number. . .";
		return 0;
	}

	std::cout << "\n\nChoose Sample Rate (41000 or 48200): ";
	std::cin >> SoundFormat.sampleRATE;

	while (SoundFormat.sampleRATE != 41000 && SoundFormat.sampleRATE != 48200) {//while the sample rate is not one of these, it will ask for the sample rate
		SoundFormat.sampleRATE = 0;
		std::cout << "\n\nChoose Sample Rate (41000 or 48200): ";
		std::cin >> SoundFormat.sampleRATE;
	}

	std::cout << "\nPlease choose frequency (in Hz: 256 or above is recommended): ";
	std::cin >> SineConfig.frequencyInput;

	std::cout << "\nPlease choose limiter value (3, 4, or 8): ";
	std::cin >> limiter;

	while (limiter != 3 && limiter != 4 && limiter != 8) {
		limiter = 0;
		std::cout << "\nPlease choose limiter value (3, 4, or 8): ";
		std::cin >> limiter;
	}

	std::cout << "\nPlease type sound duration (in seconds between 2 and 10): ";
	std::cin >> SineConfig.duration;

	while (SineConfig.duration < 2 || SineConfig.duration > 10) {
		SineConfig.duration = 0;
		std::cout << "\nPlease type sound duration (in seconds between 1 and 10): ";
		std::cin >> SineConfig.duration;
	}

	if (wav.is_open()) {
		//writing configuration for the .wav file
		wav << RIFFformat.chunkID;
		wav << RIFFformat.chunkSIZE;
		wav << RIFFformat.chunkFORMAT;
		
		wav << SoundFormat.formatCHUNKID;
		convert.convertToBytes(wav, SoundFormat.formatCHUNKSIZE, 4);//4 bytes
		convert.convertToBytes(wav, SoundFormat.audioFORMAT, 2);//2 bytes
		convert.convertToBytes(wav, SoundFormat.numCHANNELS, 2);
		convert.convertToBytes(wav, SoundFormat.sampleRATE, 4);
		convert.convertToBytes(wav, SoundFormat.byteRATE, 4);
		convert.convertToBytes(wav, SoundFormat.blockALIGN, 2);
		convert.convertToBytes(wav, SoundFormat.bitsPERSAMPLE, 2);

		wav << DataFormat.dataCHUNKID;
		wav << DataFormat.dataCHUNKSIZE;

		int startAudio = wav.tellp();

		for (int i = 0; i < SoundFormat.sampleRATE * SineConfig.duration; i++) {

			//int(3276*sin(i)
			double amplitude = ((double)i / SoundFormat.sampleRATE) * SineConfig.maxAMPLITUDE;
			double value = sin((2 * pi * i * SineConfig.frequencyInput) / SoundFormat.sampleRATE);//formula of amplitude divided by the sample rate

			if (int channelNum = 1) {
				double Channel1 = (amplitude * value) / limiter;

				convert.convertToBytes(wav, Channel1, 2);
			}


			else if (int channelNum = 2) {
				double Channel1 = (amplitude * value) / limiter;
				double Channel2 = (amplitude * value) / limiter;

				convert.convertToBytes(wav, Channel1, 2);
				convert.convertToBytes(wav, Channel2, 2);
			}

		}

		int endAudio = wav.tellp();

		wav.seekp(startAudio - 4);//start position minus 4 bytes
		convert.convertToBytes(wav, endAudio - startAudio, 4);

		wav.seekp(4, std::ios::beg);//4 places after the beginning of the file to account for the actual data chunk of the file
		convert.convertToBytes(wav, endAudio - 8, 4);//subtracts 8 bytes from the 44 total to obtain 36 bytes
	}

	wav.close();

	std::cout << "\nYour File Has Been Created As Raw Data\n" << std::endl;

	system("pause");
	return 0;
}