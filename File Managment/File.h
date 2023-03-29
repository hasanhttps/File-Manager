#pragma once



class File {
public:

	void createFile(string fileName) {
		try {
			ofstream file((currentLocation + "\\" + fileName), ios::out);

			if (!file) throw exception("File couldnt be opened\n");
			if (!file.is_open()) throw exception("File couldnt be opened\n");

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
};