#include <Windows.h>
int getScreenWidth() {

	return GetSystemMetrics(SM_CXSCREEN);

}

int getScreenHeight() {

	return GetSystemMetrics(SM_CYSCREEN);

}

bool checkFileExist(LPCSTR lpFileName) {

	return (INVALID_FILE_ATTRIBUTES != GetFileAttributesA(lpFileName));

}