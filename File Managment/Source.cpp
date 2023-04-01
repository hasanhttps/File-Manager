#include <ios>
#include <io.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <string> 
#include <conio.h>
#include <Windows.h>
#include <direct.h>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

// Global Variables

int defC = 7, col = 112, columns, rows;
bool autosave = true, exitSt = false, change = true;

// User - Defined Libraries

#include "FileManager.h"
#include "Functions.h"

int main() {
	FileManager file;
	
	// GUI

	bool choose = 0;
	int set[2] = { col, defC };
	while (true) {
		getCurrentSizeT();// Get Current Size of Terminal wit row and column
		gotoXy(0, 0);
		if (change) {
			system("cls");
			color(127);
			if (change) cout << rows << " : " << columns;
			color(defC);
			menu(set, columns / 2 - 8, rows / 2 - 1);
			gotoXy(columns / 2 - 8, rows / 2 - 1 + choose);
		}if (_kbhit()) {
			int ascii = _getch();
			set[0] = defC;
			set[1] = defC;
			if (ascii == 72 || ascii == 119 || ascii == 89 ||
				ascii == 80 || ascii == 115 || ascii == 83) choose = !choose;
			if (ascii == '\r') {
				system("color 7");
				system("cls");
				color(defC);
				if (choose == 0) {
					cmd(file);
					if (exitSt) break;
				}
				else if (choose == 1) {
					interFace(file);

				}
			}
			if (choose == 0) set[0] = col;
			else if (choose == 1) set[1] = col;
			menu(set, columns / 2 - 8, rows / 2 - 1);
			gotoXy(columns / 2 - 8, rows / 2 - 1 + choose);
		}
	}
}
