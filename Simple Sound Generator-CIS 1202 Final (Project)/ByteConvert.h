#pragma once

#ifndef ByteConvert_H
#define ByteConvert_H

#include <fstream>

//This writes the values by the size of their bytes
class ByteConvert {
public:
	void convertToBytes(std::ofstream& file, int value, int byteSize) {
		file.write(reinterpret_cast<const char*> (&value), byteSize);//allows writing in binary
	}
};

#endif;