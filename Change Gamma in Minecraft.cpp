/*
 * Change Gamma in Minecraft.cpp
 *
 * Created on: Aug 8, 2021
 * Last Modified: Aug 15, 2021
 * Author: CrabPulsar
 */

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

char* appdata;
size_t len;
errno_t err = _dupenv_s(&appdata, &len, "APPDATA");

string fileLocation = "\\.minecraft\\options.txt";
string path = appdata + fileLocation;
fstream inFile(path, ios::in | ios::out);


void writeToFile(int lineNumber, string text) {
	inFile.clear();
	inFile.seekp(lineNumber);
	inFile << text;
}


int main() {

	if (!inFile.is_open()) {
		cout << "Error in opening the file." << endl;
		system("pause");
		exit(1);
	}

	string line;
	string answer;
	int counter = 0;

	cout << "Would you like to change your gamma? y/n" << endl;
	cin >> answer;
	if (answer == "n") {
		cout << "No changes will be made." << endl;
		inFile.close();
		system("pause");
		exit(1);
	}

	while (getline(inFile, line)) {
		counter = line.size() + counter + 2;
		if (line.find("gamma:") == 0) {
			string str2 = line.substr(6);
			float gammaAmount = stof(str2);
			if (gammaAmount > 1) {
				cout << "Gamma is already maxed." << endl;
				cout << "Would you like to revert it back to normal? y/n" << endl;
				cin >> answer;
				if (answer == "y") {
					writeToFile(counter - 5, "1.0");
					cout << "The gamma has been reset to default (1.0)" << endl;
					break;
				}
				else {
					cout << "Closing file. No changes were made." << endl;
					break;
				}
			}
			else {
				writeToFile(counter - 5, "999");
				cout << "Gamma Successfully maxed!" << endl;
				break;
			}
		}
	}

	inFile.close();
	system("pause");
}