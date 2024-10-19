#include <iostream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <thread>

using namespace std;
HHOOK _hook;
KBDLLHOOKSTRUCT kbdStruct;
HHOOK miHook;
char RandomKey;
char lastKeyPressed;
char RandomNum;
int ExitCount = 0;

int WindowX() {
    RECT desktop;
    HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    return desktop.right;
}
int WindowY() {
    RECT desktop;
    HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    return desktop.bottom;
}
void BlockMouseMs() {
    while (ExitCount < 2) {
        SetCursorPos(WindowX() / 2, WindowY() / 2); 
        this_thread::sleep_for(chrono::milliseconds(2));
    }
}


LRESULT CALLBACK HookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);

        wchar_t UnicodeCharacter[3] = {};
        BYTE KeyboardState[256] = {};
        GetKeyboardState(KeyboardState);

        if (ToUnicodeEx(kbdStruct.vkCode, kbdStruct.scanCode, KeyboardState, UnicodeCharacter, 2, 0, GetKeyboardLayout(0)) == 1) {
            lastKeyPressed = (char)UnicodeCharacter[0];
            cout << lastKeyPressed << " pressed Down" << endl;

            if (lastKeyPressed == RandomKey || lastKeyPressed == RandomNum) {
                ExitCount++;
                if (ExitCount == 2) {
                    PostQuitMessage(0);
                }
            } 
            else {
                return -1; 
            }
        }
    }
    return CallNextHookEx(_hook, nCode, wParam, lParam);
}


int main() {
    srand(static_cast<unsigned int>(time(0)));
    thread mouseThread(BlockMouseMs);
    mouseThread.detach();
    const string Alphabet[26] = {
        "Alfa", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot", "Golf", "Hotel", "India", "Juliett",
        "Kilo", "Lima", "Mike", "November", "Oscar", "Papa", "Quebec", "Romeo", "Sierra", "Tango",
        "Uniform", "Victor", "Whiskey", "X-ray", "Yankee", "Zulu"
    };

    const char KeyCharArray[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
    };

    const char NumArray[10] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

    RandomNum = NumArray[rand() % 10];
    int SameRand = rand() % 26;
    RandomKey = KeyCharArray[SameRand];
    
    cout << "Your Key: " << 
        RandomKey <<endl <<
        "With next number:" << 
        RandomNum << endl
        << "Key word: " << 
        Alphabet[SameRand] << endl
        << RandomKey << 
        RandomNum << endl;
   

    _hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0);
    MSG msg;
    while (GetMessage(&msg, 0, 0, 0)) {
        PeekMessage(&msg, 0, 0, 0, 0x0001);

    }
    mouseThread.join();
    return 0;
}