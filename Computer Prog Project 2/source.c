#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

FILE *recordptr, *tempPtr, *droppedPtr;

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

	printf("\nSave this record? (Y/N): ");
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

	recordptr=fopen("record.txt", "r");

	if(!recordptr) {
		printf("No existing student record. Go back to MAIN MENU and use the Add Student feature.\n");
		printf("\nPress ANY key to return to MAIN MENU...");
		getch();
		return;
	}

	char searchStudentNo[50], studentNo[50], fname[50], lname[50];
	float grade1=0, grade2=0, grade3=0, grade4=0, newGrade=0;
	printf("Search Student Number: ");
	scanf("%s", &searchStudentNo);
	fflush(stdin);

	while((fscanf(recordptr, "%s %s %s %f %f %f %f", &studentNo, &fname, &lname, &grade1, &grade2, &grade3, &grade4)) != EOF) {
		if(strcmp(studentNo, searchStudentNo) == 0) {
			break;
		}
	}

	if(strcmp(studentNo, searchStudentNo) != 0) {
		printf("Student does not exist.\n");
	} else {
		int pick;
		printf("\nFirst Name: %s\nLast Name: %s\n", fname, lname);
		printf("Grade 1: %.2f\nGrade 2: %.2f\nGrade 3: %.2f\nGrade 4: %.2f\n", grade1, grade2, grade3, grade4);
		printf("\nWhich grade would you like to edit? (1/2/3/4): ");
		scanf("%d", &pick);
		fflush(stdin);

		switch(pick) {
			case 1:
				tempPtr=fopen("replace.txt", "w");
				printf("\nEnter New Grade 1: ");
				scanf("%f", &newGrade);
				fflush(stdin);

				printf("\tUpdating record...\n");
				rewind(recordptr);
				while(fscanf(recordptr, "%s %s %s %f %f %f %f", &studentNo, &fname, &lname, &grade1, &grade2, &grade3, &grade4) != EOF) {
					if(strcmp(studentNo, searchStudentNo) == 0) {
						fprintf(tempPtr, "%s %s %s %.2f %.2f %.2f %.2f\n", studentNo, fname, lname, newGrade, grade2, grade3, grade4);
					} else {
						fprintf(tempPtr, "%s %s %s %.2f %.2f %.2f %.2f\n", studentNo, fname, lname, grade1, grade2, grade3, grade4);
					}
				}

				fclose(tempPtr);
				fclose(recordptr);
				remove("record.txt");
				rename("replace.txt", "record.txt");

				break;
			case 2:
				tempPtr=fopen("replace.txt", "w");
				printf("\nEnter New Grade 2: ");
				scanf("%f", &newGrade);
				fflush(stdin);

				printf("\tUpdating record...\n");
				rewind(recordptr);
				while(fscanf(recordptr, "%s %s %s %f %f %f %f", &studentNo, &fname, &lname, &grade1, &grade2, &grade3, &grade4) != EOF) {
					if(strcmp(studentNo, searchStudentNo) == 0) {
						fprintf(tempPtr, "%s %s %s %.2f %.2f %.2f %.2f\n", studentNo, fname, lname, grade1, newGrade, grade3, grade4);
					} else {
						fprintf(tempPtr, "%s %s %s %.2f %.2f %.2f %.2f\n", studentNo, fname, lname, grade1, grade2, grade3, grade4);
					}
				}

				fclose(tempPtr);
				fclose(recordptr);
				remove("record.txt");
				rename("replace.txt", "record.txt");

				break;
			case 3:
				tempPtr=fopen("replace.txt", "w");
				printf("\nEnter New Grade 3: ");
				scanf("%f", &newGrade);
				fflush(stdin);

				printf("\tUpdating record...\n");
				rewind(recordptr);
				while(fscanf(recordptr, "%s %s %s %f %f %f %f", &studentNo, &fname, &lname, &grade1, &grade2, &grade3, &grade4) != EOF) {
					if(strcmp(studentNo, searchStudentNo) == 0) {
						fprintf(tempPtr, "%s %s %s %.2f %.2f %.2f %.2f\n", studentNo, fname, lname, grade1, grade2, newGrade, grade4);
					} else {
						fprintf(tempPtr, "%s %s %s %.2f %.2f %.2f %.2f\n", studentNo, fname, lname, grade1, grade2, grade3, grade4);
					}
				}

				fclose(tempPtr);
				fclose(recordptr);
				remove("record.txt");
				rename("replace.txt", "record.txt");

				break;
			case 4:
				tempPtr=fopen("replace.txt", "w");
				printf("\nEnter New Grade 4: ");
				scanf("%f", &newGrade);
				fflush(stdin);
				
				printf("\tUpdating record...\n");
				rewind(recordptr);
				while(fscanf(recordptr, "%s %s %s %f %f %f %f", &studentNo, &fname, &lname, &grade1, &grade2, &grade3, &grade4) != EOF) {
					if(strcmp(studentNo, searchStudentNo) == 0) {
						fprintf(tempPtr, "%s %s %s %.2f %.2f %.2f %.2f\n", studentNo, fname, lname, grade1, grade2, grade3, newGrade);
					} else {
						fprintf(tempPtr, "%s %s %s %.2f %.2f %.2f %.2f\n", studentNo, fname, lname, grade1, grade2, grade3, grade4);
					}
				}

				fclose(tempPtr);
				fclose(recordptr);
				remove("record.txt");
				rename("replace.txt", "record.txt");

				break;
			default:
				printf("Invalid Grade Number.\n");
		}
	}

	fclose(recordptr);
	
	printf("\nPress ANY key to return to MAIN MENU...");
	getch();
}

void deleteStudent() {
	system("cls");

	recordptr=fopen("record.txt", "r");

	if(!recordptr) {
		printf("No existing student record. Go back to MAIN MENU and use the Add Student feature.\n");
		printf("\nPress ANY key to return to MAIN MENU...");
		getch();
		return;
	}

	char searchStudentNo[50], studentNo[50], fname[50], lname[50];
	float grade1=0, grade2=0, grade3=0, grade4=0;
	printf("Enter Student Number: ");
	scanf("%s", &searchStudentNo);
	fflush(stdin);

	while((fscanf(recordptr, "%s %s %s %f %f %f %f", &studentNo, &fname, &lname, &grade1, &grade2, &grade3, &grade4)) != EOF) {
		if(strcmp(studentNo, searchStudentNo) == 0) {
			break;
		}
	}

	if(strcmp(studentNo, searchStudentNo) != 0) {
		printf("Student does not exist.\n");
		fclose(recordptr);
	} else {
		droppedPtr=fopen("dropped.txt", "a");
		tempPtr=fopen("replace.txt", "w");
		char choice;
		printf("\nFirst Name: %s\nLast Name: %s\n", fname, lname);
		printf("Grade 1: %.2f\nGrade 2: %.2f\nGrade 3: %.2f\nGrade 4: %.2f\n", grade1, grade2, grade3, grade4);
		printf("\nAre you sure you want to delete this record? (Y/N): ");
		scanf("%c", &choice);
		fflush(stdin);

		if(choice == 'Y' || choice == 'y') {
			printf("\tDeleting this record...\n");
			rewind(recordptr);
			while(fscanf(recordptr, "%s %s %s %f %f %f %f", &studentNo, &fname, &lname, &grade1, &grade2, &grade3, &grade4) != EOF) {
				if(strcmp(studentNo, searchStudentNo) != 0) {
					fprintf(tempPtr, "%s %s %s %.2f %.2f %.2f %.2f\n", studentNo, fname, lname, grade1, grade2, grade3, grade4);
				} else {
					fprintf(droppedPtr, "%s %s %s %.2f %.2f %.2f %.2f\n", studentNo, fname, lname, grade1, grade2, grade3, grade4);
				}
			}
			fclose(recordptr);
			fclose(tempPtr);
			fclose(droppedPtr);
			remove("record.txt");
			rename("replace.txt", "record.txt");
		} else {
			printf("\tRecord not deleted.\n");
			fclose(recordptr);
			fclose(tempPtr);
			fclose(droppedPtr);
		}
	}

	printf("\nPress ANY key to return to MAIN MENU...");
	getch();
}

void displayStudent() {
	system("cls");

	recordptr=fopen("record.txt", "r");

	if(!recordptr) {
		printf("No existing student record. Go back to MAIN MENU and use the Add Student feature.\n");
		printf("\nPress ANY key to return to MAIN MENU...");
		getch();
		return;
	}

	char studentNo[50], fname[50], lname[50], searchFname[50], searchLname[50];
	float grade1=0, grade2=0, grade3=0, grade4=0;
	printf("Enter Student Name (First and Last Name): ");
	scanf("%s%s", &searchFname, &searchLname);
	fflush(stdin);

	while((fscanf(recordptr, "%s %s %s %f %f %f %f", &studentNo, &fname, &lname, &grade1, &grade2, &grade3, &grade4)) != EOF) {
		if(strcmp(fname, searchFname) == 0 && strcmp(lname, searchLname) == 0) {
			break;
		}
	}

	if(strcmp(fname, searchFname) != 0 && strcmp(lname, searchLname) != 0) {
		printf("Student does not exist.\n");
		fclose(recordptr);
	} else {
		printf("\nFirst Name: %s\nLast Name: %s\n", fname, lname);
		printf("Grade 1: %.2f\nGrade 2: %.2f\nGrade 3: %.2f\nGrade 4: %.2f\n", grade1, grade2, grade3, grade4);
		fclose(recordptr);
	}

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
