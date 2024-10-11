#include <iostream>
#include <string>
#include <windows.h>
using namespace std;


int main() {
	/*char ch;
	ch = _getwch();

	if (ch == 'a')
		cout << "You pressed a!" << endl;
	else
		cout << "You did not press a!" << endl;
		*/

	//Randomized
	char KeyCharArray[57] = { 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',  'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', '~', '`', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '=', '-','1','2','3','4','5','6','7','8','9','0'};
	srand(time(0));
	int CharRand = rand() % 57;
	char RandomizedKey = KeyCharArray[CharRand];
	cout << "Your key is:" << RandomizedKey;
	//Randomized
	

	return 0;
}