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
	gotoXy(x, y + 2);
	color(set[2]);
	cout << "Help";
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
			else if (command == "cd..") {
				string location = file.getLocation();
				location = location.substr(0, location.rfind("\\"));
				file.setLocation(location);
			}
			else if (command == "show") file.printAllLocation();
			else if (command == "dir") file.show_folder();
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

	vector<string> options;
	options.push_back("1. Print all folders in current folder");
	options.push_back("2. Print all created subfolders or files");
	options.push_back("3. Open new folder");
	options.push_back("4. Delete selected file");
	options.push_back("5. Delete selected folder");
	options.push_back("6. Rename selected file");
	options.push_back("7. Rename selected folder");
	options.push_back("8. Move selected file");
	options.push_back("9. Move selected folder");
	options.push_back("10. Create new folder with specified name");
	options.push_back("11. Create empty file with specified name and extension");
	options.push_back("12. Organize files and subfolders");
	options.push_back("13. Open selected file in default app");
	options.push_back("14. Change working directory");
	options.push_back("15. Exit");

	int* set = new int[options.size()];
	int choose = 0;
	while(true) {
		for (int i = 0; i < options.size(); i++) set[i] = defC;
		set[choose] = col;
		for (int i = 0; i < options.size(); i++) {
			gotoXy((columns / 2) - (options[0].size() / 2), ((rows / 2) - (options.size() / 2)) + i);
			color(set[i]);
			cout << options[i] << endl;
		}
		int ascii = _getch();
		for (int j = 0; j < options.size(); j++) set[j] = defC;
		if (ascii == 72 || ascii == 119 || ascii == 89) {
			if (choose) choose--;
			else choose = options.size() - 1;
		} else if (ascii == 80 || ascii == 115 || ascii == 83) {
			if (choose < options.size() - 1) choose++;
			else choose = 0;
		} else if (ascii == '\r') {
			system("cls");
			if (choose == 0) file.show_folder();
			else if (choose == 1) file.printAllLocation();
			if (choose == 0 || choose == 1) system("pause");
			else if (choose == 2) file.createFolder("New Folder");
			else if (choose == 3) {
				file.show_folder();
				string filename;
				cout << "Please enter the file name : ";
				cin >> filename;

				file.deleteFile(filename);
			}else if (choose == 4) {
				file.show_folder();
				string folder;
				cout << "Please enter the folder name : ";
				cin >> folder;

				file.deleteFolder(folder);
			}else if (choose == 5 || choose == 6) {
				file.show_folder();
				string old, newn;
				cout << "Please enter the old name : ";
				cin >> old;
				cout << "Please enter the new name : ";
				cin >> newn;

				file.renamel(old, newn);
			}else if (choose == 7 || choose == 8) {
				file.show_folder();
				string subfolder, folder;
				cout << "Please enter the subfolder path : ";
				cin >> subfolder;
				cout << "Please enter the path : ";
				cin >> folder;

				file.renamel(subfolder, folder);
			}else if (choose == 9) {
				string folder; 
				cout << "Please enter the folder path : ";
				cin >> folder;

				file.createFolder(folder);
			}else if (choose == 10) {
				string filename, extension;

				cout << "Please enter the file name : ";
				cin >> filename;
				cout << "Please enter the file extension : ";
				cin >> extension;

				filename.append("." + extension);
				file.createFile(filename);
			}else if (choose == 11) {
				
			}else if (choose == 12) {
				system("color 7");
				color(defC);
				file.show_folder();
				string path;
				cout << "Please enter the file path : ";
				getline(cin, path);

				ShellExecuteA(0, 0, (file.getLocation() + "\\" + path).c_str(), 0, 0, SW_SHOW);
			}else if (choose == 13) {
				string directory;
				cout << "Please enter the working directory : ";
				getline(cin, directory);

				file.setLocation(directory);
			}
			else if (choose == 14) break;
			system("cls");
		}
	}system("color 7");
}

void help() {
	getCurrentSizeT();
	char* help = new char[] {
		R"(
							File Manager is originally a program to control files or folders, change system files or folders etc.
							File Manager consists of two main page : command page and inteface page. Recomandation is using command
							because of controlling all folder with easy commands. The commands is overloaded is these :

							1. mkdir foldername  ->  create Folder with specified name
							2. rmdir foldername  ->  delete Folder if exist
							3. rename file|foldername  ->  change file|folder name
							4. move old(file|foldername) new(file|foldername)  ->  move new(file|foldername) to old(file|foldername) path
							5. create filename  ->  create file with specified name and extension
							6. delete filename  ->  delete file with specified name if exist
							7. show  ->  show created files or folders with File Manager
							8. dir  ->  show all files or folder in current location
							9. cd/  ->  return to C:>
							10. cd ..  ->  return one previous folder in subfolder
							11. foldername  ->  go to folder if exist in current location
							12. change  ->  return to home
							13. exit  -> close program		
		
		)"
	};

	for (int i = 0; i < rows / 2 - 9; i++) cout << "\n";
	cout << help;
	for (int i = 0; i < columns / 2 - 10; i++) cout << " ";
	system("pause");
	system("cls");
}

void delay(float seconds) {
	clock_t startClock = clock();
	float secondsAhead = seconds * CLOCKS_PER_SEC;
	// do nothing until the elapsed time has passed.
	while (clock() < startClock + secondsAhead);
	return;
}