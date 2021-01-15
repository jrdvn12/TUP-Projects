#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void addStudent() {
	system("cls");
	printf("Add Student Screen\n");
	printf("Press ANY key to continue...");
	getch();
}

void editStudent() {
	system("cls");
	printf("Edit Student Screen\n");
	printf("Press ANY key to continue...");
	getch();
}

void deleteStudent() {
	system("cls");
	printf("Delete Student Screen\n");
	printf("Press ANY key to continue...");
	getch();
}

void displayStudent() {
	system("cls");
	printf("Display Student Screen\n");
	printf("Press ANY key to continue...");
	getch();
}

void displayAll() {
	system("cls");
	printf("Display All Screen\n");
	printf("Press ANY key to continue...");
	getch();
}

void computeGrade() {
	system("cls");
	printf("Compute Grade Screen\n");
	printf("Press ENTER key to continue...");
	getch();
}

void generateGSR() {
	system("cls");
	printf("Generate Grade Summary Report\n");
	printf("Press ANY key to continue...");
	getch();
}

int main(void) {
	int select;
	while(1) {
		system("cls");
		printf("MAIN MENU\n");
		printf("1) Add New Students\n");
		printf("2) Edit Student\n");
		printf("3) Delete Student\n");
		printf("4) Display Student\n");
		printf("5) Display All\n");
		printf("6) Compute Grade\n");
		printf("7) Generate Grade Summary Report\n");
		printf("8) Exit\n");
		printf("Enter choice (1/2/3/4/5/6/7/8): ");
		scanf("%d", &select);

		switch(select) {
			case 1:
				addStudent();
				break;
			case 2:
				editStudent();
				break;
			case 3:
				deleteStudent();
				break;
			case 4:
				displayStudent();
				break;
			case 5:
				displayAll();
				break;
			case 6:
				computeGrade();
				break;
			case 7:
				generateGSR();
				break;
			case 8:
				exit(0);
			default:
				system("cls");
		}
	}
}
