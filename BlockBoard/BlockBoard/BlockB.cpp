#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

HHOOK _hook;
KBDLLHOOKSTRUCT kbdStruct;

char RandomizedKey;
char lastKeyPressed;
int RandomNum;
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
            if (UnicodeCharacter[0] != RandomizedKey)
            {
                return -1;
            }
           
            if (lastKeyPressed == RandomizedKey) {
                PostQuitMessage(0);
            }
        }
    }
    return CallNextHookEx(_hook, nCode, wParam, lParam);
}

int main() {
    
    const string Alphabet[26] = {
        "Alfa", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot", "Golf", "Hotel", "India", "Juliett",
        "Kilo", "Lima", "Mike", "November", "Oscar", "Papa", "Quebec", "Romeo", "Sierra", "Tango",
        "Uniform", "Victor", "Whiskey", "X-ray", "Yankee", "Zulu"
    };

    const char KeyCharArray[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
    };

    const int NumArray[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 }; 
    int RandomNum; 
    srand(time(0)); 
    int IntRand = rand() % 10; 
    RandomNum = NumArray[IntRand]; 
    
    srand(time(0));
    int CharRand = rand() % 26;
    RandomizedKey = KeyCharArray[CharRand];  
    cout << "Your Key: " << RandomizedKey <<endl << 
        "With next number:" << RandomNum << endl
        << "Key word: " << Alphabet[CharRand] << endl
        << RandomizedKey << RandomNum;

    
    _hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0);
    MSG msg;
    while (GetMessage(&msg, 0, 0, 0)) {
        PeekMessage(&msg, 0, 0, 0, 0x0001);
    }

    return 0;
}