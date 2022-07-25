#include <windows.h>
#include <iostream>
using namespace std;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    HWND p = FindWindowExW(hwnd, NULL, L"SHELLDLL_DefView", NULL);
    HWND* ret = (HWND*)lParam;

    if (p) {

        *ret = FindWindowExW(NULL, hwnd, L"WorkerW", NULL);

    }
    return true;
}

HWND get_wallpaper_window() {

    HWND progman = FindWindowW(L"ProgMan", NULL);
    SendMessageTimeout(progman, 0x052C, 0, 0, SMTO_NORMAL, 1000, nullptr);
    HWND wallpaper_hwnd = nullptr;
    EnumWindows(EnumWindowsProc, (LPARAM)&wallpaper_hwnd);
    return wallpaper_hwnd;

}

void setAsWallpaper(HWND self) {

    HWND wallpaperWIndow = get_wallpaper_window();
    SetParent(self, wallpaperWIndow);

}

void restoreWallpaper() {

    SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, NULL, SPIF_SENDCHANGE);

}