#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <limits>
using namespace std;

string logged_user = "guest";
ofstream accountLog, customerRecord;
ifstream read_accountLog, read_customerRecord;

int rate_ordinary = 2000, rate_luxury = 6000, rate_royal = 10000;

void regist() {
	string username, password, confirmPass, temp1;

	while(true) {
		system("cls");
		cout << "Register Menu" << "\n\n";
		cout << "NOTE: A username and password should NOT have SPACES to avoid errors." << "\n\n";

		cout << "Enter Username (max 15 characters): ";
		cin >> username;
		if(username.size()>15) {
			cout << '\n';
			cout << "Username exceeded 15 characters." << "\n\n";
			cout << "Press ENTER to try again...";
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cin.get();
			continue;
		} else if(username == "admin") {
			cout << "You cannot create an admin account." << "\n\n";
			cout << "Press ENTER to try again...";
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
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
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cin.get();
			continue;
		}
		read_accountLog.close();

		cout << "Enter Password (max 15 characters): ";
		cin >> password;
		if(password.size()>15) {
			cout << '\n';
			cout << "Password exceeded 15 characters." << "\n\n";
			cout << "Press ENTER to try again...";
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cin.get();
			continue;
		}
        if(password == username) {
            cout << '\n';
            cout << "For security reasons. You cannot use the same username as your password." << "\n\n";
            cout << "Press ENTER to try again...";
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cin.get();
            continue;
        }

		cout << "Confirm Password: ";
		cin >> confirmPass;

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
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cin.get();
			return;
		} else {
			cout << "Password does not match. Please try again." << "\n\n";
			cout << "Press ENTER to try again...";
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cin.get();
		}
	}
}

void login() {
	system("cls");

	string username, password, temp1, temp2;
	char confirm;

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

		cout << "Enter Password: ";
		cin >> password;

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
			read_accountLog.close();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cin.get();
			return;
		} else {
			cout << "Invalid username or password. Please try again." << "\n\n";
			cout << "Enter Y to try again, N to go back to Main Menu...";
			cin >> confirm;
			if(confirm == 'Y' || confirm == 'y') {
				continue;
			} else {
				read_accountLog.close();
				return;
			}
		}
	}
}

bool checkRoomAvail(int roomNum) {
	string fname, lname, username, tp, month;
	int temp1, nightNum;
	int day, hr, mn;
	long long phone;

	read_customerRecord.open("record.txt");

	read_customerRecord.clear();
	read_customerRecord.seekg(0);
	while(!read_customerRecord.eof()) {
		read_customerRecord >> username >> temp1 >> fname >> lname >> phone >> nightNum >> month >> day >> hr >> mn >> tp;
		if(roomNum == temp1) {
			break;
		}
	}
	read_customerRecord.close();

	if(roomNum == temp1) {
		return true;
	} else {
		return false;
	}
}

long long compute_total(int nightNum, int roomNum) {
	if(roomNum>=1&&roomNum<=20) {
		return nightNum*2000;
	} else if(roomNum>=21&&roomNum<=40) {
		return nightNum*6000;
	} else if(roomNum>=41&&roomNum<=60) {
		return nightNum*10000;
	}
	return 0;
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
	int select, roomNum, nightNum;
	int day, hr, mn;
	long long phone;
	string fname, lname, tp, month, temp1;
	char confirm;

	read_customerRecord.open("record.txt");
    read_customerRecord.clear();
	read_customerRecord.seekg(0);
	while(!read_customerRecord.eof()) {
		read_customerRecord >> temp1 >> roomNum >> fname >> lname >> phone >> nightNum >> month >> day >> hr >> mn >> tp;
		if(logged_user == temp1) {
			cout << "You can only reserve one room at a time." << "\n\n";
            cout << "Press ENTER to return to Main Menu...";
            read_customerRecord.close();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cin.get();
            return;
		}
	}

	customerRecord.open("record.txt", ios::app);

	cout << "WELCOME TO THE HOTEL & RESORT" << "\n\n";

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
				customerRecord.close();
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				cin.get();
				customer_reserve();
			} else {
				cout << '\n';
				cout << "Personal Information" << "\n\n";
				cout << "Enter First Name: ";
				cin >> fname;

				cout << "Enter Last Name: ";
				cin >> lname;

				cout << "Enter Phone Number: ";
				cin >> phone;

				cout << "Enter Number of Nights: ";
				cin >> nightNum;

				cout << '\n';
				cout << "Arrival Date & Time" << "\n\n";

				cout << "Enter Month (ex. January, March): ";
				cin >> month;

				cout << "Enter Day: ";
				cin >> day;

				cout << "Enter Hour: ";
				cin >> hr;

				cout << "Enter Minute: ";
				cin >> mn;

				cout << "Time Period (am or pm): ";
				cin >> tp;

				cout << '\n';
				cout << "Total amount to be paid: PHP " << compute_total(nightNum, roomNum) << '\n';

				cout << "Confirm reservation? (Y for Yes, N to go back): ";
				cin >> confirm;
				if(confirm == 'Y' || confirm == 'y') {
					customerRecord << logged_user << ' ' << roomNum << ' ' << fname << ' ' << lname << ' ' << phone << ' ' << nightNum << ' ';
					customerRecord << month << ' ' << day << ' ' << hr << ' ' << mn << ' ' << tp << '\n';
				} else {
					customerRecord.close();
					customer_reserve();
				}

				system("cls");
				cout << "The chosen room has been booked." << "\n\n";
				cout << "THANK YOU FOR TRUSTING OUR SERVICE" << "\n\n";
				cout << "Press ENTER to return to Main Menu...";
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				customerRecord.close();
				cin.get();
				return;
			}
			break;
		case 2:
			while(true) {
				cout << "Enter Room Number (21-40): ";
				cin >> roomNum;
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
				customerRecord.close();
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				cin.get();
				customer_reserve();
			} else {
				cout << '\n';
				cout << "Personal Information" << "\n\n";
				cout << "Enter First Name: ";
				cin >> fname;

				cout << "Enter Last Name: ";
				cin >> lname;

				cout << "Enter Phone Number: ";
				cin >> phone;

				cout << "Enter Number of Nights: ";
				cin >> nightNum;

				cout << '\n';
				cout << "Arrival Date & Time" << "\n\n";

				cout << "Enter Month (ex. January, March): ";
				cin >> month;

				cout << "Enter Day: ";
				cin >> day;

				cout << "Enter Hour: ";
				cin >> hr;

				cout << "Enter Minute: ";
				cin >> mn;

				cout << "Time Period (am or pm): ";
				cin >> tp;

				cout << '\n';
				cout << "Total amount to be paid: PHP " << compute_total(nightNum, roomNum) << '\n';

				cout << "Confirm reservation? (Y for Yes, N to go back): ";
				cin >> confirm;
				if(confirm == 'Y' || confirm == 'y') {
					customerRecord << logged_user << ' ' << roomNum << ' ' << fname << ' ' << lname << ' ' << phone << ' ' << nightNum << ' ';
					customerRecord << month << ' ' << day << ' ' << hr << ' ' << mn << ' ' << tp << '\n';
				} else {
					customerRecord.close();
					customer_reserve();
				}

				system("cls");
				cout << "The chosen room has been booked." << "\n\n";
				cout << "THANK YOU FOR TRUSTING OUR SERVICE" << "\n\n";
				cout << "Press ENTER to return to Main Menu...";
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				customerRecord.close();
				cin.get();
				return;
			}
			break;
		case 3:
			while(true) {
				cout << "Enter Room Number (41-60): ";
				cin >> roomNum;
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
				customerRecord.close();
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				cin.get();
				customer_reserve();
			} else {
				cout << '\n';
				cout << "Personal Information" << "\n\n";
				cout << "Enter First Name: ";
				cin >> fname;

				cout << "Enter Last Name: ";
				cin >> lname;

				cout << "Enter Phone Number: ";
				cin >> phone;

				cout << "Enter Number of Nights: ";
				cin >> nightNum;

				cout << '\n';
				cout << "Arrival Date & Time" << "\n\n";

				cout << "Enter Month (ex. January, March): ";
				cin >> month;

				cout << "Enter Day: ";
				cin >> day;

				cout << "Enter Hour: ";
				cin >> hr;

				cout << "Enter Minute: ";
				cin >> mn;

				cout << "Time Period (am or pm): ";
				cin >> tp;

				cout << '\n';
				cout << "Total amount to be paid: PHP " << compute_total(nightNum, roomNum) << '\n';

				cout << "Confirm reservation? (Y for Yes, N to go back): ";
				cin >> confirm;
				if(confirm == 'Y' || confirm == 'y') {
					customerRecord << logged_user << ' ' << roomNum << ' ' << fname << ' ' << lname << ' ' << phone << ' ' << nightNum << ' ';
					customerRecord << month << ' ' << day << ' ' << hr << ' ' << mn << ' ' << tp << '\n';
					customerRecord.close();
				} else {
					customerRecord.close();
					customer_reserve();
				}

				system("cls");
				cout << "The chosen room has been booked." << "\n\n";
				cout << "THANK YOU FOR TRUSTING OUR SERVICE" << "\n\n";
				cout << "Press ENTER to return to Main Menu...";
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				customerRecord.close();
				cin.get();
				return;
			}
			break;
		case 4:
			customerRecord.close();
			return;
		default:
			customerRecord.close();
			customer_reserve();
	}
}

void check_reserve() {
	system("cls");

	string fname, lname, temp1;
	char month[10], tp[10];
	int roomNum, nightNum;
	int day, hr, mn;
	long long phone;

	cout << "Check Reservation Menu" << "\n\n";

	read_customerRecord.open("record.txt");
	if(!read_customerRecord) {
		cout << "No existing room reservation info." << "\n\n";
		cout << "Press ENTER to return to Main Menu...";
		read_customerRecord.close();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cin.get();
		return;
	}

	read_customerRecord.clear();
	read_customerRecord.seekg(0);
	while(!read_customerRecord.eof()) {
		read_customerRecord >> temp1 >> roomNum >> fname >> lname >> phone >> nightNum >> month >> day >> hr >> mn >> tp;
		if(logged_user == temp1) {
			break;
		}
	}
	read_customerRecord.close();

	if(logged_user == temp1) {
		cout << "Username: " << temp1 << '\n';
		cout << "Room No.: " << roomNum << ' ';
		if(roomNum>=1&&roomNum<=20) {
			cout << "(Ordinary Room)" << '\n';
		} else if(roomNum>=21&&roomNum<=40) {
			cout << "(Luxury Room)" << '\n';
		} else if(roomNum>=41&&roomNum<=60) {
			cout << "(Royal Room)" << '\n';
		}
		cout << "Name: " << fname << ' ' << lname << '\n';
		cout << "Phone No.: " << phone << '\n';
		cout << "Number of night(s): " << nightNum << '\n';
		printf("Date & Time of Arrival: %s %d %02d:%02d %s\n", month, day, hr, mn, tp);
		cout << "Total amount to be paid: PHP " << compute_total(nightNum, roomNum) << "\n\n";

		cout << "Press ENTER to return to Main Menu...";
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cin.get();
		return;
	} else {
		cout << "You have not booked a room yet." << "\n\n";
		cout << "Press ENTER to return to Main Menu...";
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cin.get();
		return;
	}
}

void cancel_reserve() {
	system("cls");

	string fname, lname, temp1;
	char month[10], tp[10];
	int roomNum, nightNum;
	int day, hr, mn;
	long long phone;
	char confirm;

	cout << "Cancel Reservation Menu" << "\n\n";

	read_customerRecord.open("record.txt");
	if(!read_customerRecord) {
		cout << "No existing room reservation info." << "\n\n";
		cout << "Press ENTER to return to Main Menu...";
		read_customerRecord.close();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cin.get();
		return;
	}

	while(!read_customerRecord.eof()) {
		read_customerRecord >> temp1 >> roomNum >> fname >> lname >> phone >> nightNum >> month >> day >> hr >> mn >> tp;
		if(logged_user == temp1) {
			break;
		}
	}

	if(logged_user != temp1) {
		cout << "You have no reservation info in the system. No data deleted." << "\n\n";
		cout << "Press ENTER to return to Main Menu...";
		read_customerRecord.close();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cin.get();
		return;
	} else {
		cout << "Username: " << temp1 << '\n';
		cout << "Room No.: " << roomNum << ' ';
		if(roomNum>=1&&roomNum<=20) {
			cout << "(Ordinary Room)" << '\n';
		} else if(roomNum>=21&&roomNum<=40) {
			cout << "(Luxury Room)" << '\n';
		} else if(roomNum>=41&&roomNum<=60) {
			cout << "(Royal Room)" << '\n';
		}
		cout << "Name: " << fname << ' ' << lname << '\n';
		cout << "Phone No.: " << phone << '\n';
		cout << "Number of night(s): " << nightNum << '\n';
		printf("Date & Time of Arrival: %s %d %02d:%02d %s\n", month, day, hr, mn, tp);
		cout << "Total amount to be paid: PHP " << compute_total(nightNum, roomNum) << "\n\n";

		cout << "Are you sure you want to cancel your reservation? (Y for Yes, N for No): ";
		cin >> confirm;
		if(confirm == 'Y' || confirm == 'y') {
			ofstream temp_customerRecord;
			temp_customerRecord.open("temp.txt");

			read_customerRecord.clear();
			read_customerRecord.seekg(0);
			while(true) {
				read_customerRecord >> temp1 >> roomNum >> fname >> lname >> phone >> nightNum >> month >> day >> hr >> mn >> tp;
				if(read_customerRecord.eof()) {
					break;
				}
				if(logged_user != temp1) {
					temp_customerRecord << temp1 << ' ' << roomNum << ' ' << fname << ' ' <<  lname << ' ' << phone << ' ' << nightNum << ' ';
					temp_customerRecord << month << ' ' << day << ' ' << hr << ' ' << mn << ' ' << tp << '\n';
				}
			}
			read_customerRecord.close();
			temp_customerRecord.close();
			remove("record.txt");
			rename("temp.txt", "record.txt");

			cout << "Your reservation has been cancelled." << "\n\n";
			cout << "Press ENTER to return to Main Menu...";
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cin.get();
			return;

		} else {
			cout << "Reservation is not cancelled." << "\n\n";
			cout << "Press ENTER to return to Main Menu...";
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			read_customerRecord.close();
			cin.get();
			return;
		}
	}
}

void showRecords() {
	system("cls");

	string fname, lname, username;
	char month[10], tp[10];
	int roomNum, nightNum;
	int day, hr, mn;
	long long phone;

	if(logged_user != "admin") {
		cout << "You do not have admin privileges to access this menu." << "\n\n";
		cout << "Press ENTER to return to Main Menu...";
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cin.get();
		return;
	}

	cout << "Show Record(s) Menu" << "\n\n";

	read_customerRecord.open("record.txt");
	if(!read_customerRecord) {
		cout << "No existing room reservation(s) info." << "\n\n";
		cout << "Press ENTER to return to Main Menu...";
		read_customerRecord.close();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cin.get();
		return;
	}

	read_customerRecord.clear();
	read_customerRecord.seekg(0);
	while(true) {
		read_customerRecord >> username >> roomNum >> fname >> lname >> phone >> nightNum >> month >> day >> hr >> mn >> tp;
		if(read_customerRecord.eof()) {
			break;
		}
		cout << "Username: " << username << '\n';
		cout << "Room No.: " << roomNum << ' ';
		if(roomNum>=1&&roomNum<=20) {
			cout << "(Ordinary Room)" << '\n';
		} else if(roomNum>=21&&roomNum<=40) {
			cout << "(Luxury Room)" << '\n';
		} else if(roomNum>=41&&roomNum<=60) {
			cout << "(Royal Room)" << '\n';
		}
		cout << "Name: " << fname << ' ' << lname << '\n';
		cout << "Phone No.: " << phone << '\n';
		cout << "Number of night(s): " << nightNum << '\n';
		printf("Date & Time of Arrival: %s %d %02d:%02d %s\n", month, day, hr, mn, tp);
		cout << "Total amount to be paid: PHP " << compute_total(nightNum, roomNum) << "\n\n";
		cout << "--------------------" << "\n\n";
	}
	read_customerRecord.close();

	cout << "Press ENTER to return to Main Menu...";
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	cin.get();
	return;
}

int main() {
	time_t my_time = time(0);
	int select;
	while(true) {
		system("cls");
		cout << "WELCOME TO THE HOTEL & RESERVATION SYSTEM" << "\n\n";
		cout << "Logged User: " << logged_user << "\n\n";
		cout << "Current Date & Time: " << ctime(&my_time) << '\n';
		cout << "Main Menu" << '\n';
		cout << "(1) Register" << '\n';
		cout << "(2) Login" << '\n';
		cout << "(3) Book a Room" << '\n';
		cout << "(4) Check Reservation" << '\n';
		cout << "(5) Cancel Reservation" << '\n';
		cout << "(6) View Customer Records" << '\n';
		cout << "(7) Exit" << "\n\n";
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
				check_reserve();
				break;
			case 5:
				cancel_reserve();
				break;
			case 6:
				showRecords();
				break;
			case 7:
				exit(0);
			default:
				continue;
		}
	}
}
