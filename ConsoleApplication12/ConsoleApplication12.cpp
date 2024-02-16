//MARJERY DILIG
//SUFIAN MOJADDEDI
#include <iostream>
#include "windows.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct PackMan {
	int x = 1;
	int y = 1;
	int eaten = 0;
	char looks = '@';
};
int loadMap(vector<string>& map) {
	string fileName, s;
	ifstream mapFile;
	int foodCounter = 0;
	cout << "Please enter the name of the file: " << endl;
	getline(cin, fileName);
	mapFile.open(fileName, ios::in);
	if (!mapFile) {
		cout << "Open Failed." << endl;
	}
	else {
		while (getline(mapFile, s))
		{
			map.push_back(s);
			for (int i = 0; i < s.size(); i++) {
				if (tolower(s.at(i)) == 'x')
				{
					foodCounter++;
				}
			}
		}
	}
	mapFile.close();
	return foodCounter;
}
void displayMap(vector<string>& map) {
	for (string s : map) {
		cout << s << endl;
	}
}
BOOL gotoxy(const WORD x, const WORD y) {
	COORD xy;
	xy.X = x;
	xy.Y = y;
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}
bool moveTo(vector<string>& map, int newX, int newY, int& food) {
	bool move = map.at(newY).at(newX) != '#';
	food += tolower(map.at(newY).at(newX)) == 'x';
	return move;
}
int main()
{
	PackMan pac;
	vector<string> map;
	bool game_running = true;
	int total_food = loadMap(map);
	system("cls");
	do {
		gotoxy(0, 0);
		displayMap(map);
		cout << "You ate " << pac.eaten << " out of " << total_food;
		system("pause>nul");
		if (GetAsyncKeyState(VK_DOWN) && moveTo(map, pac.x, pac.y + 1, pac.eaten))
		{
			map.at(pac.y).at(pac.x) = ' ';
			pac.y++;
			map.at(pac.y).at(pac.x) = pac.looks;
		}
		if (GetAsyncKeyState(VK_UP) && moveTo(map, pac.x, pac.y - 1, pac.eaten)) {
			map.at(pac.y).at(pac.x) = ' ';
			pac.y--;
			map.at(pac.y).at(pac.x) = pac.looks;
		}
		if (GetAsyncKeyState(VK_RIGHT) && moveTo(map, pac.x + 1, pac.y, pac.eaten)) {
			map.at(pac.y).at(pac.x) = ' ';
			pac.x++;
			map.at(pac.y).at(pac.x) = pac.looks;
		}
		if (GetAsyncKeyState(VK_LEFT) && moveTo(map, pac.x - 1, pac.y, pac.eaten)) {
			map.at(pac.y).at(pac.x) = ' ';
			pac.x--;
			map.at(pac.y).at(pac.x) = pac.looks;
		}
		if (GetAsyncKeyState(VK_ESCAPE)) {
			game_running = false;
		}
	} while (game_running || pac.eaten != total_food);
	system("cls");
	cout << "GAME OVER";
	return 0;
}