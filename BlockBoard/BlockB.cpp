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

		ToUnicodeEx((UINT)kbdStruct.vkCode,(UINT)kbdStruct.scanCode,KeyboardSate,UnicodeCharacter,sizeof(UnicodeCharacter) / sizeof(*UnicodeCharacter) - 1,(UINT)kbdStruct.flags,GetKeyboardLayout(0));
		if (wParam == WM_KEYDOWN) {
			lastKeyPressed = (char)UnicodeCharacter[0];
			cout << lastKeyPressed << " pressed Down" << endl;
		}
	}
	return CallNextHookEx(_hook, nCode, wParam, lParam);
}
int main() {
	//Randomized
	char KeyCharArray[57] = { 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',  'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', '~', '`', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '=', '-','1','2','3','4','5','6','7','8','9','0'};
	srand(time(0));
	int CharRand = rand() % 57;
	char RandomizedKey = KeyCharArray[CharRand];
	cout << "Your key is:" << RandomizedKey;
	//Randomized
	_hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0);
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0)) {
		PeekMessage(&msg, 0, 0, 0, 0x0001);
	}
	if (lastKeyPressed == RandomizedKey)
	{
		cout << "dse";
	}


	return 0;
}