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
    }
}

LRESULT CALLBACK HookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
        BYTE KeyboardState[256] = {};
        wchar_t UnicodeCharacter[3] = {};

        GetKeyState(VK_SHIFT);
        GetKeyState(VK_MENU);
        GetKeyboardState(KeyboardState);

        ToUnicodeEx((UINT)kbdStruct.vkCode, (UINT)kbdStruct.scanCode, KeyboardState, UnicodeCharacter, sizeof(UnicodeCharacter) / sizeof(*UnicodeCharacter) - 1, (UINT)kbdStruct.flags, GetKeyboardLayout(0));

        if (wParam == WM_KEYDOWN) {
            lastKeyPressed = (char)UnicodeCharacter[0];
            cout << lastKeyPressed << " pressed Down" << endl;
            if (UnicodeCharacter[0] != RandomNum && UnicodeCharacter[0] != RandomKey)
            {
                return -1;
            }

            if (lastKeyPressed == RandomKey)
            { 
                    ExitCount++;
            }
            if (lastKeyPressed == RandomNum)
            {
                ExitCount++;
                if (ExitCount == 2)
                {
                    
                    PostQuitMessage(0);
                }
            }
        }
    }
    return CallNextHookEx(_hook, nCode, wParam, lParam);

}


int main() {
    srand(static_cast<unsigned int>(time(0)));
    thread mouseThread(BlockMouseMs);
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