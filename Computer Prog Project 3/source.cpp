#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

string logged_user = "guest";
ofstream accountLog, customerRecord;
ifstream read_accountLog, read_customerRecord;

void regist() {
	string username, password, confirmPass, temp1;
	
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
		read_accountLog.open("accounts.txt");
		while(read_accountLog >> temp1) {
			if(temp1 == username) {
				break;
			}
		}
		if(temp1 == username) {
			cout << "Username is taken." << "\n\n";
			cout << "Press ENTER to try again...";
			cin.get();
			continue;
		}
		read_accountLog.close();
		
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

	read_accountLog.open("accounts.txt");
	if(!read_accountLog) {
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
		read_accountLog.clear();
		read_accountLog.seekg(0);
		while(getline(read_accountLog, temp2)) {
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
	read_accountLog.close();
}

bool checkRoomAvail(int roomNum) {
	string fname, lname, username;
	int temp1;
	long long phone;

	read_customerRecord.open("record.txt");

	read_customerRecord.clear();
	read_customerRecord.seekg(0);
	while(!read_customerRecord.eof()) {
		read_customerRecord >> username >> temp1 >> fname >> lname >> phone;
		if(roomNum == temp1) {
			break;
		}
	}
	if(roomNum == temp1) {
		return true;
	} else {
		return false;
	}
}

void customer_reserve() {
	system("cls");
	if(logged_user == "guest") {
		cout << "Please make an account first or login your existing account." << "\n\n";
		cout << "Press ENTER to return to Main Menu...";
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cin.get();
		return;
	}

	customerRecord.open("record.txt", ios::app);

	int select, roomNum;
	long long phone;
	string name;

	cout << "Choose type of room." << "\n\n";
	cout << "(1) Ordinary Room - PHP 2,000/night" << '\n';
	cout << "(2) Luxury Room - PHP 6,000/night" << '\n';
	cout << "(3) Royal Room - PHP 10,000/night" << '\n';
	cout << "(4) Return to Main Menu" << "\n\n";
	cout << "Enter choice: ";
	cin >> select;

	cout << '\n';
	switch(select) {
		case 1:
			while(true) {
				cout << "Enter Room Number (1-20): ";
				cin >> roomNum;
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				if(roomNum<1 || roomNum>20) {
					continue;
				} else {
					break;
				}
			}
			if(checkRoomAvail(roomNum)) {
				system("cls");

				cout << "Room is already taken." << "\n\n";
				cout << "Press ENTER to go back...";
				cin.get();
				customer_reserve();
			} else {
				system("cls");

				cout << "Enter Name (First and Last Name): ";
				getline(cin, name);
				
				cout << "Enter Phone Number: ";
				cin >> phone;

				customerRecord << logged_user << ' ' << roomNum << ' ' << name << ' ' << phone << '\n';
				customerRecord.close();
				
				system("cls");
				cout << "The chosen room has been booked." << "\n\n";
				cout << "THANK YOU FOR TRUSTING OUR SERVICE" << "\n\n";
				cout << "Press ENTER to return to Main Menu...";
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				cin.get();
				return;
			}
			break;
		case 2:
			while(true) {
				cout << "Enter Room Number (21-40): ";
				cin >> roomNum;
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				if(roomNum<21 || roomNum>40) {
					continue;
				} else {
					break;
				}
			}
			if(checkRoomAvail(roomNum)) {
				system("cls");

				cout << "Room is already taken." << "\n\n";
				cout << "Press ENTER to go back...";
				cin.get();
				customer_reserve();
			} else {
				system("cls");

				cout << "Enter Name (First and Last Name): ";
				getline(cin, name);
				
				cout << "Enter Phone Number: ";
				cin >> phone;

				customerRecord << logged_user << ' ' << roomNum << ' ' << name << ' ' << phone << '\n';
				customerRecord.close();
				
				system("cls");
				cout << "The chosen room has been booked." << "\n\n";
				cout << "THANK YOU FOR TRUSTING OUR SERVICE" << "\n\n";
				cout << "Press ENTER to return to Main Menu...";
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				cin.get();
				return;
			}
			break;
		case 3:
			while(true) {
				cout << "Enter Room Number (41-60): ";
				cin >> roomNum;
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				if(roomNum<41 || roomNum>60) {
					continue;
				} else {
					break;
				}
			}
			if(checkRoomAvail(roomNum)) {
				system("cls");

				cout << "Room is already taken." << "\n\n";
				cout << "Press ENTER to go back...";
				cin.get();
				customer_reserve();
			} else {
				system("cls");

				cout << "Enter Name (First and Last Name): ";
				getline(cin, name);
				
				cout << "Enter Phone Number: ";
				cin >> phone;

				customerRecord << logged_user << ' ' << roomNum << ' ' << name << ' ' << phone << '\n';
				customerRecord.close();
				
				system("cls");
				cout << "The chosen room has been booked." << "\n\n";
				cout << "THANK YOU FOR TRUSTING OUR SERVICE" << "\n\n";
				cout << "Press ENTER to return to Main Menu...";
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				cin.get();
				return;
			}
			break;
		case 4:
			return;
		default:
			customer_reserve();
	}
}

int main() {
	int select;
	while(true) {
		system("cls");
		cout << "WELCOME TO THE HOTEL & RESERVATION SYSTEM" << "\n\n";
		cout << "Logged User: " << logged_user << "\n\n";
		cout << "Main Menu" << '\n';
		cout << "(1) Register" << '\n';
		cout << "(2) Login" << '\n';
		cout << "(3) Book a Room" << '\n';
		cout << "(4) Exit" << "\n\n";
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
				customer_reserve();
				break;
			case 4:
				exit(0);
			default:
				continue;
		}
	}
}
