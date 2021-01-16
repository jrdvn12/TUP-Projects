#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

FILE *recordptr;

void addStudent() {
	system("cls");

	char name[50], studentNo[50], choice;
	float grade1, grade2, grade3, grade4;

	printf("Enter Student No: ");
	scanf("%s", &studentNo);
	fflush(stdin);

	printf("Enter Name: ");
	gets(name);
	fflush(stdin);

	printf("Enter Score 1: ");
	scanf("%f", &grade1);
	fflush(stdin);

	printf("Enter Score 2: ");
	scanf("%f", &grade2);
	fflush(stdin);

	printf("Enter Score 3: ");
	scanf("%f", &grade3);
	fflush(stdin);

	printf("Enter Score 4: ");
	scanf("%f", &grade4);
	fflush(stdin);

	printf("\nSave this record (Y/N)?: ");
	scanf("%c", &choice);
	if(choice == 'Y' || choice == 'y') {
		printf("\tSaving student record...\n");
		recordptr = fopen("record.txt", "a");
		fprintf(recordptr, "%s %s %.2f %.2f %.2f %.2f\n", studentNo, name, grade1, grade2, grade3, grade4);
		fclose(recordptr);
	} else {
		printf("\tData discarded.\n");
	}

	printf("\nPress ANY key to return to MAIN MENU...");
	getch();
}

void editStudent() {
	system("cls");
	printf("Edit Student Screen\n");
	printf("\nPress ANY key to return to MAIN MENU...");
	getch();
}

void deleteStudent() {
	system("cls");
	printf("Delete Student Screen\n");
	printf("\nPress ANY key to return to MAIN MENU...");
	getch();
}

void displayStudent() {
	system("cls");
	printf("Display Student Screen\n");
	printf("\nPress ANY key to return to MAIN MENU...");
	getch();
}

void displayAll() {
	system("cls");
	printf("Display All Screen\n");
	printf("\nPress ANY key to return to MAIN MENU...");
	getch();
}

void computeGrade() {
	system("cls");
	printf("Compute Grade Screen\n");
	printf("\nPress ANY key to return to MAIN MENU...");
	getch();
}

void generateGSR() {
	system("cls");
	printf("Generate Grade Summary Report\n");
	printf("\nPress ANY key to return to MAIN MENU...");
	getch();
}

int main(void) {
	int select;
	while(1) {
		system("cls");
		printf("MAIN MENU\n\n");
		printf("1) Add New Student\n");
		printf("2) Edit Student\n");
		printf("3) Delete Student\n");
		printf("4) Display Student\n");
		printf("5) Display All\n");
		printf("6) Compute Grade\n");
		printf("7) Generate Grade Summary Report\n");
		printf("8) Exit\n");
		printf("\nEnter choice (1/2/3/4/5/6/7/8): ");
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
