#include <iostream>
#include <fstream>
#include <limits>
using namespace std;

ifstream filePtr; // reads from file
ofstream filePtr2; // creates and writes to file

void RLE() { // Run Length Encoding compression function
	system("cls");

	string fileName, fileStr, compressed;

	while(true) {
        cout << "-----------------------------------------------------------\n\n";
		cout << "Enter complete filename (with extension): ";
		getline(cin, fileName);

		filePtr.open(fileName);
		if(!filePtr) {
			cout << "\nERROR!! File does not exist.\n\n";
			cout << "Press ENTER to try again...";
			cin.get();
			continue;
		} else {
			break;
		}
	}

	while(filePtr) {
		getline(filePtr, fileStr);
	}
	filePtr.close();
    cout << "-----------------------------------------------------------\n\n";
	cout << "Text file data before compression:\n\n" << fileStr << "\n\n";
    cout << "-----------------------------------------------------------\n\n";
	filePtr2.open(fileName);
	for(int i=0; i<fileStr.length(); i++) {
		int count=1;
		while(i < fileStr.length()-1 && fileStr[i] == fileStr[i+1]) {
			count++;
			i++;
		}
		if(count<=1) {
			filePtr2 << fileStr[i];
		} else {
			filePtr2 << count << fileStr[i];
		}
	}
	filePtr2.close();

	filePtr.open(fileName);
	while(filePtr) {
		getline(filePtr, compressed);
	}
	filePtr.close();

	cout << "[File Compression Complete!]\n\n";
	cout << "Text file data after compression:\n\n" << compressed << "\n\n";
	cout << "Press ENTER to return to Main Menu...";
	cin.get();
	return;
}

bool alpha_or_space(char c) {
	return isalpha(c) || c==' ';
}

void RLD() { // Run Length Decoding decompression function
	system("cls");

	string fileName, compressed, original;

	while(true) {
        cout << "-----------------------------------------------------------\n\n";
		cout << "Enter complete filename (with extension): ";
		getline(cin, fileName);

		filePtr.open(fileName);
		if(!filePtr) {
			cout << "\nERROR!!!File does not exist.\n\n";
			cout << "Press ENTER to try again...";
			cin.get();
			continue;
		} else {
			break;
		}
	}

	while(filePtr) {
		getline(filePtr, compressed);
	}
	filePtr.close();
    cout << "-----------------------------------------------------------\n\n";
	cout << "Text file data before decompression:\n\n" << compressed << "\n\n";
    cout << "-----------------------------------------------------------\n\n";
	int i=0;
	int repeat;
	while(i<compressed.length()) {
		while(alpha_or_space(compressed[i])) {
			original.push_back(compressed[i++]);
		}

		repeat = 0;
		while(isdigit(compressed[i])) {
			repeat=10*repeat+(compressed[i++]-'0');
		}

		auto unroll=compressed[i++];
		while (repeat--) {
			original.push_back(unroll);
		}
	}

	filePtr2.open(fileName);
	filePtr2 << original;
	filePtr2.close();

	cout << "[File Decompression Complete!]\n\n";
	cout << "Text file data after decompression:\n\n" << original << "\n\n";
	cout << "Press ENTER to return to Main Menu...";
	cin.get();
}

int main() {
	int select;
	while(true) {
		system("cls");

        cout << "-----------------------------------------------------------\n\n";
		cout << "Run Length Encoding (Lossless Data Compression Algorithm)\n\n";
		cout << "-----------------------------------------------------------\n\n";
		cout << "***ENTER THE NUMBER OF THE OPERATION YOU WANT TO USE ***\n\n";

		cout << "Press 1  to Compress a file (Run Length Encoding)" << '\n';
		cout << "Press 2  to Decompress a file (Run Length Decoding)" << '\n';
		cout << "Press 3  to Exit\n\n";
		cout << "Enter number: ";
		cin >> select;
		cin.ignore(numeric_limits<streamsize>::max(),'\n');

		switch(select) {
			case 1:
				RLE();
				break;
			case 2:
				RLD();
				break;
			case 3:
				exit(0);
			default:
				continue;
		}
	}
	return 0;
}
