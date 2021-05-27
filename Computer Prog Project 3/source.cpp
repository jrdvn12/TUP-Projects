#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

string logged_user = "guest";

void regist() {
	string username, password, confirmPass;
	
	while(true) {
		system("cls");
		cout << "Register Menu" << "\n\n";
		cout << "NOTE: A username and password should NOT have SPACES to avoid errors." << "\n\n";

		cout << "Enter Username (max 15 characters): ";
		cin >> username;
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		if(username.size()>15) {
			cout << '\n';
			cout << "Username exceeded 15 characters." << "\n\n";
			cout << "Press ENTER to try again...";
			cin.get();
			continue;
		}
		
		cout << "Enter Password (max 15 characters): ";
		cin >> password;
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		if(password.size()>15) {
			cout << '\n';
			cout << "Password exceeded 15 characters." << "\n\n";
			cout << "Press ENTER to try again...";
			cin.get();
			continue;
		}

		cout << "Confirm Password: ";
		cin >> confirmPass;
		cin.ignore(numeric_limits<streamsize>::max(),'\n');

		cout << '\n';

		if(password == confirmPass) {
			system("cls");

			ofstream accountLog;
			accountLog.open("accounts.txt", ios::app);
			accountLog << username << " " << password << '\n';
			accountLog.close();

			cout << "Account Registered. You may now use it to login." << "\n\n";
			cout << "Take note of your account details below." << '\n';
			cout << "Username: " << username << '\n';
			cout << "Password: " << password << "\n\n";
			cout << "Press ENTER to return to Main Menu...";
			cin.get();
			break;
		} else {
			cout << "Password does not match. Please try again." << "\n\n";
			cout << "Press ENTER to try again...";
			cin.get();
		}
	}
}

void login() {
	system("cls");

	string username, password, temp1, temp2;

	ifstream accountLog;
	accountLog.open("accounts.txt");
	if(!accountLog) {
		cout << "No existing account in the system. Go back to Main Menu and Register." << "\n\n";
		cout << "Press Enter to return to Main Menu...";
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cin.get();
		return;
	}

	while(true) {
		system("cls");
		cout << "Login Menu" << "\n\n";
		cout << "Enter Username: ";
		cin >> username;
		cin.ignore(numeric_limits<streamsize>::max(),'\n');

		cout << "Enter Password: ";
		cin >> password;
		cin.ignore(numeric_limits<streamsize>::max(),'\n');

		cout << '\n';

		temp1 = username + ' ' + password;
		accountLog.clear();
		accountLog.seekg(0);
		while(getline(accountLog, temp2)) {
			if(temp1 == temp2) {
				break;
			}
		}

		if(temp1 == temp2) {
			logged_user = username;
			cout << "Login Success!" << "\n\n";
			cout << "Press ENTER to return to Main Menu...";
			cin.get();
			break;
		} else {
			cout << "Invalid username or password. Please try again." << "\n\n";
			cout << "Press ENTER to try again...";
			cin.get();
		}
	}
	accountLog.close();
}

int main() {
	int select;
	while(true) {
		system("cls");
		cout << "WELCOME TO THE HOTEL & RESERVATION SYSTEM" << "\n\n";
		cout << "Logged User: " << logged_user << "\n\n";
		cout << "Main Menu" << "\n";
		cout << "(1) Register" << '\n';
		cout << "(2) Login" << "\n";
		cout << "(3) Exit" << "\n\n";
		cout << "Enter: ";
		cin >> select;
		
		switch(select) {
			case 1:
				regist();
				break;
			case 2:
				login();
				break;
			case 3:
				exit(0);
			default:
				continue;
		}
	}
}
