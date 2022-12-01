#pragma once

#ifndef Sound_H
#define Sound_H

#include <string>

class RIFF {
public:
	//RIFF is a way for the .wav file to be read and formatted as such
	const std::string chunkID = "RIFF";//Resource Interchange File Format (RIFF)
	const std::string chunkSIZE = "----";
	const std::string chunkFORMAT = "WAVE";//needed for the file to be recognized as .wav
};

class Format {
public:
	//format configuration
	const std::string formatCHUNKID = "fmt";//needed for the creation of the .wav file
	int formatCHUNKSIZE = 16;//16 is generally needed for PCM
	const int audioFORMAT = 1;//1 represents linear quantization compression for the audio (anything else may decrease performance efficiency)...
	int numCHANNELS;//this can be either 1 for mono or 2 for stereo (I will let the user decide this)
	int sampleRATE;//this should either be 41000 or 48200 (anything higher will result in performance issues: anything lower results in grainy audio)
	int byteRATE = sampleRATE * numCHANNELS * (formatCHUNKSIZE / 8);
	int blockALIGN = numCHANNELS * (formatCHUNKSIZE / 8);
	int bitsPERSAMPLE = formatCHUNKSIZE;//bps (bits per sample) will always be equal to the formatCHUNKSIZE (PCM uses 16 bits)
};

class Data {
public:
	//data configuration
	const std::string dataCHUNKID = "data";//data chunk is used to describe the size of the sound being created
	const std::string dataCHUNKSIZE = "----";
};

class Sine {
public:
	//setup for the sine sound
	const int maxAMPLITUDE = (pow(16, 2) / 2) - 1;//the number of bits to the second power divided by 2 (to factor both negative and positive values) while subtracting 1 to factor in zero
	int duration;//how long the sound will be (user will input the duration in seconds)
	double frequencyInput;

};

#endif;