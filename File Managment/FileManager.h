#pragma once


class FileManager {
	string currentLocation = "C:\\Users\\Public\\Downloads";
	string filepath = "locations.txt";
	vector<string> locations;
public:

	// Constructors

	FileManager() {
		writeLocations();
	}

	// Acsessors

	// Setters

	void setLocation(string path) { currentLocation = path; }

	// Getters

	string getLocation() { return currentLocation; }

	// Functions

	void writeLocations() {
		ifstream infile(filepath, ios::in);

		if (!infile) throw exception("File couldnt be found\n");
		if (!infile.is_open()) throw exception("File couldnt be opened\n");

		string location;
		while (!infile.eof()) {
			infile >> location;
			if (location != "") locations.push_back(location);
		}infile.close();
	}

	void createFile(string fileName) {
		try {
			ofstream file((currentLocation + "\\" + fileName), ios::out);

			if (!file) throw exception("File couldnt be opened\n");
			if (!file.is_open()) throw exception("File couldnt be opened\n");
			file.close();
			locations.push_back(fileName);
		}
		catch (exception& ex) {
			cout << ex.what() << endl;
		}
	}

	void deleteFile(string fileName) {
		try {
			int ret = remove((currentLocation + "\\" + fileName).c_str());
			if (ret != 0) throw exception("Error: unable to delete the file\n");
			popLocation(fileName);
		}
		catch (exception& ex) {
			cout << ex.what() << endl;
		}
	}
	
	void renamel(string oldname, string name) {
		try {
			int ret = rename((currentLocation + "\\" + oldname).c_str(), (currentLocation + "\\" + name).c_str());
			if (ret != 0) throw exception("Folder couldn't be renamed!\n");
			for (int i = 0; i < locations.size(); i++) {
				if (locations[i] == oldname) {
					locations[i] = name;
					break;
				}
			}
		}
		catch (exception& ex) {
			cout << ex.what() << endl;
		}
	}

	void printAllLocation() {
		for (int i = 0; i < locations.size(); i++) {
			cout << locations[i] << endl;
		}cout << endl;	
	}

	void createFolder(string path) {
		try {
			if (_mkdir(path.c_str()) == -1) throw exception("Folder couldn't be created!\n");
			locations.push_back(path);
			path = currentLocation + "\\" + path;
		}
		catch (exception& ex) {
			cout << ex.what() << endl;
		}
	}
    
	void deleteFolder(string path) {
		try {
			if (_rmdir((currentLocation + "\\" + path).c_str()) == -1) throw exception("Folder couldn't be deleted!\n");
			popLocation(path);
		}
		catch (exception& ex) {
			cout << ex.what() << endl;
		}
	}


	void move(string name, string move) {
		try {
			string newlocation = currentLocation + "\\" + name + "\\" + move;
			string oldlocation = currentLocation + "\\" + move;
			
			int ret = rename(oldlocation.c_str(), newlocation.c_str());
			if (ret != 0) throw exception("Folder couldn't be moved!\n");

			locations.push_back(name + "\\" + move);
			for (int i = 0; i < locations.size(); i++) {
				if (locations[i] == move) {
					popLocation(move);
					break;
				}
			}
		}
		catch (exception& ex) {
			cout << ex.what() << endl;
		}
	}

	void popLocation(string name) {
		for (auto i = locations.begin(); i < locations.end(); i++) {
			if (*i == name) {
				 locations.erase(i);
				break;
			}
		}
	}

	void saveChange() {
		try {
			ofstream file(filepath, ios::out);

			if (!file) throw exception("File couldnt be opened\n");
			if (!file.is_open()) throw exception("File couldnt be opened\n");

			for (int i = 0; i < locations.size(); i++) ((i != locations.size() - 1) ? file << locations[i] << endl : file << locations[i]);
			file.close();
		}catch (exception& ex) {
			cout << ex.what() << endl;
		}
	}

	void show_folder() {
		_finddata_t file_info;
		intptr_t handle = _findfirst((currentLocation + "/*").c_str(), &file_info);
		
		if (handle == -1) {
			cerr << "Could not open folder: " << currentLocation << endl;
			return;
		}
		do {
			if (strcmp(file_info.name, ".") == 0 || strcmp(file_info.name, "..") == 0) continue;
		
			cout << "Name: " << file_info.name << endl;
			cout << "Attribute: " << file_info.attrib << endl;
			cout << "Size: "<< file_info.size << endl;
		
			if (file_info.attrib & _A_SUBDIR) cout << "Type : Subfolder";
			else cout << "Type: File";
			cout << "\n-------------------------------------------\n";
		} while (_findnext(handle, &file_info) == 0);	
		_findclose(handle);
	}
		

	// Destructor

	~FileManager() {
		saveChange();
	}

};
