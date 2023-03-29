#pragma once

inline void color(int col) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
}

void gotoXy(int x, int y) {
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void menu(int* set, int x, int y) {
	gotoXy(x, y);
	color(set[0]);
	cout << "Command";
	gotoXy(x, y + 1);
	color(set[1]);
	cout << "Inteface";
	color(defC);
}

void getCurrentSizeT() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	if (columns != csbi.srWindow. Right - csbi.srWindow.Left + 1) {
		columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		change = true;
	}else if (rows != csbi.srWindow.Bottom - csbi.srWindow.Top + 1) {
		rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		change = true;
	}else change = false;
}

void cmd(FileManager& file) {
	cout << "File Managment version [1.0.0]\nAll rights deserved.\n\n";

	while (true) {
		try {
			if (autosave) file.saveChange();
			string command, data;
			cout << file.getLocation() << "> ";
			cin >> command;
			getline(cin, data);
			if (command == "mkdir") {
				if (data == "") throw exception("The syntax of the command is incorrect.\n");
				file.createFolder(data.substr(1, data.size() - 1));
			}
			else if (command == "rmdir") {
				if (data == "") throw exception("The syntax of the command is incorrect.\n");
				file.deleteFolder(data.substr(1, data.size()));
			}
			else if (command == "cd/") file.setLocation("C:");
			else if (command == "show") file.printAllLocation();
			else if (command == "move") {
				if (data == "") throw exception("The syntax of the command is incorrect.\n");
				data = data.substr(1, data.size());
				int it = data.find(" ") + 1;
				string where = data.substr(0, it - 1);
				data = data.substr(it, data.size());
				file.move(where, data);
			}
			else if (command == "create") {
				if (data.size() < 5) throw exception("Please enter valid extension for file !\n");
				if (data[data.size() - 4] == '.') file.createFile(data.substr(1, data.size()));
			}
			else if (command == "delete") {
				if (data == "") throw exception("The syntax of the command is incorrect.\n");
				file.deleteFile(data.substr(1, data.size()));
			}
			else if (command == "rename") {
				if (data == "") throw exception("The syntax of the command is incorrect.\n");
				data = data.substr(1, data.size());
				int it = data.find(" ") + 1;
				string where = data.substr(0, it - 1);
				data = data.substr(it, data.size());
				file.renamel(where, data);
			}
			else if (command == "change") {
				system("cls");
				break;
			}
			else if (command == "exit") {
				exitSt = true;
				break;
			}
			else {
				struct stat sb;
				if (stat((file.getLocation() + "\\" + command).c_str(), &sb) == 0) file.setLocation(file.getLocation() + "\\" + command);
				else {
					system((command + " " + data).c_str());
					cout << endl;
				}
			}
		}
		catch (exception& ex) {
			cout << ex.what() << endl;
		}
	}
}

void interFace(FileManager& file) {
	system("cls");
	cout << "Welcome to File Manager 1.0" << endl << endl;


}

void delay(float seconds) {
	clock_t startClock = clock();
	float secondsAhead = seconds * CLOCKS_PER_SEC;
	// do nothing until the elapsed time has passed.
	while (clock() < startClock + secondsAhead);
	return;
}