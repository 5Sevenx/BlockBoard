#include <iostream>
#include <string>
#include <windows.h>
using namespace std;
HHOOK _hook;
KBDLLHOOKSTRUCT kbdStruct; 

char RandomizedKey;          
char lastKeyPressed;

LRESULT CALLBACK HookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
	
	if (nCode >= 0)
	{
		kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
		BYTE KeyboardSate[256] = {};
		wchar_t UnicodeCharacter[3] = {};

		GetKeyState(VK_SHIFT);
		GetKeyState(VK_MENU);
		GetKeyboardState(KeyboardSate);

		ToUnicodeEx((UINT)kbdStruct.vkCode, (UINT)kbdStruct.scanCode, KeyboardSate, UnicodeCharacter, sizeof(UnicodeCharacter) / sizeof(*UnicodeCharacter) - 1, (UINT)kbdStruct.flags, GetKeyboardLayout(0));
		if (wParam == WM_KEYDOWN) {
			lastKeyPressed = (char)UnicodeCharacter[0];
			cout << lastKeyPressed << " pressed Down" << endl;
		}
	}
	return CallNextHookEx(_hook, nCode, wParam, lParam);
}

int main() {
	//Its hard to forget if associated with a military abbreviation(btw,imho)
	const string NatoAlphabet[26] = {
	"Alfa", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot", "Golf", "Hotel", "India", "Juliett",
	"Kilo", "Lima", "Mike", "November", "Oscar", "Papa", "Quebec", "Romeo", "Sierra", "Tango",
	"Uniform", "Victor", "Whiskey", "X-ray", "Yankee", "Zulu"
	};

	const char KeyCharArray[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
	};
	
	//Randomized char
	srand(time(0));
	int CharRand = rand() % 26;
	char RandomizedKey = KeyCharArray[CharRand];
	cout << "Your key is:" <<  RandomizedKey << endl << "KeyWord:" << NatoAlphabet[CharRand] << endl;
	
	//Randomized char 


	_hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0);
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0)) {
		PeekMessage(&msg, 0, 0, 0, 0x0001);
	}
	


	return 0;
}