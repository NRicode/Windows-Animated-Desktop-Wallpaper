#include "winapi.h"
#include <fstream>
#include <iostream>
#include <string.h>

bool initialize(int* fps) {

	if (!checkFileExist("source.gif")) {

		MessageBoxA(NULL, "Cannot find source.gif file to set as background", "Error", MB_OK);
		return false;

	}

	if (!checkFileExist("fps.txt")) {

		MessageBoxA(NULL, "Cannot find fps.txt file", "Error", MB_OK);
		return false;

	}

	std::string text;
	std::ifstream file("fps.txt", std::ios::in);
	file >> text;
	*fps = atoi(text.c_str());
	return true;

}