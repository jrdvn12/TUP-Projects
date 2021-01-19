#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

FILE *recordPtr, *tempPtr, *droppedPtr, *outputPtr;

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
		recordPtr = fopen("record.txt", "a");
		fprintf(recordPtr, "%s %s %.2f %.2f %.2f %.2f\n", studentNo, name, grade1, grade2, grade3, grade4);
		fclose(recordPtr);
	} else {
		printf("\tData discarded.\n");
	}

	printf("\nPress ANY key to return to MAIN MENU...");
	getch();
}

void editStudent() {
	system("cls");

	recordPtr=fopen("record.txt", "r");

	if(!recordPtr) {
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

	while((fscanf(recordPtr, "%s %s %s %f %f %f %f", &studentNo, &fname, &lname, &grade1, &grade2, &grade3, &grade4)) != EOF) {
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
				rewind(recordPtr);
				while(fscanf(recordPtr, "%s %s %s %f %f %f %f", &studentNo, &fname, &lname, &grade1, &grade2, &grade3, &grade4) != EOF) {
					if(strcmp(studentNo, searchStudentNo) == 0) {
						fprintf(tempPtr, "%s %s %s %.2f %.2f %.2f %.2f\n", studentNo, fname, lname, newGrade, grade2, grade3, grade4);
					} else {
						fprintf(tempPtr, "%s %s %s %.2f %.2f %.2f %.2f\n", studentNo, fname, lname, grade1, grade2, grade3, grade4);
					}
				}

				fclose(tempPtr);
				fclose(recordPtr);
				remove("record.txt");
				rename("replace.txt", "record.txt");

				break;
			case 2:
				tempPtr=fopen("replace.txt", "w");
				printf("\nEnter New Grade 2: ");
				scanf("%f", &newGrade);
				fflush(stdin);

				printf("\tUpdating record...\n");
				rewind(recordPtr);
				while(fscanf(recordPtr, "%s %s %s %f %f %f %f", &studentNo, &fname, &lname, &grade1, &grade2, &grade3, &grade4) != EOF) {
					if(strcmp(studentNo, searchStudentNo) == 0) {
						fprintf(tempPtr, "%s %s %s %.2f %.2f %.2f %.2f\n", studentNo, fname, lname, grade1, newGrade, grade3, grade4);
					} else {
						fprintf(tempPtr, "%s %s %s %.2f %.2f %.2f %.2f\n", studentNo, fname, lname, grade1, grade2, grade3, grade4);
					}
				}

				fclose(tempPtr);
				fclose(recordPtr);
				remove("record.txt");
				rename("replace.txt", "record.txt");

				break;
			case 3:
				tempPtr=fopen("replace.txt", "w");
				printf("\nEnter New Grade 3: ");
				scanf("%f", &newGrade);
				fflush(stdin);

				printf("\tUpdating record...\n");
				rewind(recordPtr);
				while(fscanf(recordPtr, "%s %s %s %f %f %f %f", &studentNo, &fname, &lname, &grade1, &grade2, &grade3, &grade4) != EOF) {
					if(strcmp(studentNo, searchStudentNo) == 0) {
						fprintf(tempPtr, "%s %s %s %.2f %.2f %.2f %.2f\n", studentNo, fname, lname, grade1, grade2, newGrade, grade4);
					} else {
						fprintf(tempPtr, "%s %s %s %.2f %.2f %.2f %.2f\n", studentNo, fname, lname, grade1, grade2, grade3, grade4);
					}
				}

				fclose(tempPtr);
				fclose(recordPtr);
				remove("record.txt");
				rename("replace.txt", "record.txt");

				break;
			case 4:
				tempPtr=fopen("replace.txt", "w");
				printf("\nEnter New Grade 4: ");
				scanf("%f", &newGrade);
				fflush(stdin);
				
				printf("\tUpdating record...\n");
				rewind(recordPtr);
				while(fscanf(recordPtr, "%s %s %s %f %f %f %f", &studentNo, &fname, &lname, &grade1, &grade2, &grade3, &grade4) != EOF) {
					if(strcmp(studentNo, searchStudentNo) == 0) {
						fprintf(tempPtr, "%s %s %s %.2f %.2f %.2f %.2f\n", studentNo, fname, lname, grade1, grade2, grade3, newGrade);
					} else {
						fprintf(tempPtr, "%s %s %s %.2f %.2f %.2f %.2f\n", studentNo, fname, lname, grade1, grade2, grade3, grade4);
					}
				}

				fclose(tempPtr);
				fclose(recordPtr);
				remove("record.txt");
				rename("replace.txt", "record.txt");

				break;
			default:
				printf("Invalid Grade Number.\n");
		}
	}

	fclose(recordPtr);
	
	printf("\nPress ANY key to return to MAIN MENU...");
	getch();
}

void deleteStudent() {
	system("cls");

	recordPtr=fopen("record.txt", "r");

	if(!recordPtr) {
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

	while((fscanf(recordPtr, "%s %s %s %f %f %f %f", &studentNo, &fname, &lname, &grade1, &grade2, &grade3, &grade4)) != EOF) {
		if(strcmp(studentNo, searchStudentNo) == 0) {
			break;
		}
	}

	if(strcmp(studentNo, searchStudentNo) != 0) {
		printf("Student does not exist.\n");
		fclose(recordPtr);
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
			rewind(recordPtr);
			while(fscanf(recordPtr, "%s %s %s %f %f %f %f", &studentNo, &fname, &lname, &grade1, &grade2, &grade3, &grade4) != EOF) {
				if(strcmp(studentNo, searchStudentNo) != 0) {
					fprintf(tempPtr, "%s %s %s %.2f %.2f %.2f %.2f\n", studentNo, fname, lname, grade1, grade2, grade3, grade4);
				} else {
					fprintf(droppedPtr, "%s %s %s %.2f %.2f %.2f %.2f\n", studentNo, fname, lname, grade1, grade2, grade3, grade4);
				}
			}
			fclose(recordPtr);
			fclose(tempPtr);
			fclose(droppedPtr);
			remove("record.txt");
			rename("replace.txt", "record.txt");
		} else {
			printf("\tRecord not deleted.\n");
			fclose(recordPtr);
			fclose(tempPtr);
			fclose(droppedPtr);
		}
	}

	printf("\nPress ANY key to return to MAIN MENU...");
	getch();
}

void displayStudent() {
	system("cls");

	recordPtr=fopen("record.txt", "r");

	if(!recordPtr) {
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

	while((fscanf(recordPtr, "%s %s %s %f %f %f %f", &studentNo, &fname, &lname, &grade1, &grade2, &grade3, &grade4)) != EOF) {
		if(strcmp(fname, searchFname) == 0 && strcmp(lname, searchLname) == 0) {
			break;
		}
	}

	if(strcmp(fname, searchFname) != 0 && strcmp(lname, searchLname) != 0) {
		printf("Student does not exist.\n");
		fclose(recordPtr);
	} else {
		printf("\nFirst Name: %s\nLast Name: %s\n", fname, lname);
		printf("Grade 1: %.2f\nGrade 2: %.2f\nGrade 3: %.2f\nGrade 4: %.2f\n", grade1, grade2, grade3, grade4);
		fclose(recordPtr);
	}

	printf("\nPress ANY key to return to MAIN MENU...");
	getch();
}

void displayAll() {
	system("cls");
	
	recordPtr=fopen("record.txt", "r");

	if(!recordPtr) {
		printf("No existing student record. Go back to MAIN MENU and use the Add Student feature.\n");
		printf("\nPress ANY key to return to MAIN MENU...");
		getch();
		return;
	}

	char studentNo[50], fname[50], lname[50];
	float grade1=0, grade2=0, grade3=0, grade4=0;

	while((fscanf(recordPtr, "%s %s %s %f %f %f %f", &studentNo, &fname, &lname, &grade1, &grade2, &grade3, &grade4)) != EOF) {
		printf("\nStudent Number: %s\n", studentNo);
		printf("First Name: %s\nLast Name: %s\n", fname, lname);
		printf("Grade 1: %.2f\nGrade 2: %.2f\nGrade 3: %.2f\nGrade 4: %.2f\n", grade1, grade2, grade3, grade4);
	}

	fclose(recordPtr);

	printf("\nPress ANY key to return to MAIN MENU...");
	getch();
}

float gwa(float grade1, float grade2, float grade3, float grade4) {
	float sum=0;
	sum=grade1+grade2+grade3+grade4;
	float gwa=sum/4;
	return gwa;
}

char grade(float gwa) {
	if(gwa>90) {
		return 'A';
	} else if(gwa>=81&&gwa<91) {
		return 'B';
	} else if(gwa>=75&&gwa<81) {
		return 'C';
	} else {
		return 'F';
	}
}

int verdict(float gwa) {
	if(gwa>=75) {
		return 1;
	} else {
		return 0;
	}
}

char *verdict2(float gwa) {
	if(gwa>=75) {
		return "Passed";
	} else {
		return "Failed";
	}
}

void loading() {
	printf("Computing Grades, Please Wait ");
	for(int i=1; i<=10; i++) {
		for(int j=1; j<=100000000; j++) {}
		printf(".");
	}
	printf(" Complete!\n");
}

void computeGrade() {
	system("cls");

	char studentNo[50], fname[50], lname[50];
	float grade1=0, grade2=0, grade3=0, grade4=0;
    int pass=0, fail=0;

	recordPtr=fopen("record.txt", "r");

	if(!recordPtr) {
		printf("No existing student record. Go back to MAIN MENU and use the Add Student feature.\n");
		printf("\nPress ANY key to return to MAIN MENU...");
		getch();
		return;
	}

	loading();
	printf("\nPress ANY key to Display...");
	getch();

	system("cls");
	outputPtr=fopen("output1.txt", "w");
	printf("Name\t\t\tGWA\t\t\tGrade Letter\n");
	fprintf(outputPtr, "Name\t\t\tGWA\t\t\tGrade Letter\n");
	while((fscanf(recordPtr, "%s %s %s %f %f %f %f", &studentNo, &fname, &lname, &grade1, &grade2, &grade3, &grade4)) != EOF) {
		printf("%s %s\t\t%.2f\t\t\t     %c\n", fname, lname, gwa(grade1,grade2,grade3,grade4), grade(gwa(grade1,grade2,grade3,grade4)));
		fprintf(outputPtr, "%s %s\t\t%.2f\t\t\t     %c\n", fname, lname, gwa(grade1,grade2,grade3,grade4), grade(gwa(grade1,grade2,grade3,grade4)));
		verdict(gwa(grade1,grade2,grade3,grade4))?pass++:fail++;
	}

	printf("\nTotal Passed: %d\n", pass);
	printf("Total Failed: %d\n", fail);
	fprintf(outputPtr, "\nTotal Passed: %d\n", pass);
	fprintf(outputPtr, "Total Failed: %d", fail);
	fclose(recordPtr);
	fclose(outputPtr);

	printf("\nPress ANY key to return to MAIN MENU...");
	getch();
}

void generateGSR() {
	system("cls");

	char studentNo[50], fname[50], lname[50];
	float grade1=0, grade2=0, grade3=0, grade4=0;
    int pass=0, fail=0, drop=0, totalStudent=0;
	recordPtr=fopen("record.txt", "r");

	if(!recordPtr) {
		printf("No existing student record. Go back to MAIN MENU and use the Add Student feature.\n");
		printf("\nPress ANY key to return to MAIN MENU...");
		getch();
		return;
	}

	loading();
	printf("\nPress ANY key to Display...");
	getch();

	system("cls");
	outputPtr=fopen("output2.txt", "w");
	printf("Student Number\t\tName\t\t\tGWA\t\tRemarks\n");
	fprintf(outputPtr, "Student Number\t\tName\t\t\tGWA\t\tRemarks\n");
	while((fscanf(recordPtr, "%s %s %s %f %f %f %f", &studentNo, &fname, &lname, &grade1, &grade2, &grade3, &grade4)) != EOF) {
		printf("%s\t\t%s %s\t\t%.2f\t\t%s\n", studentNo, fname, lname, gwa(grade1,grade2,grade3,grade4), verdict2(gwa(grade1,grade2,grade3,grade4)));
		fprintf(outputPtr, "%s\t\t%s %s\t\t%.2f\t\t%s\n", studentNo, fname, lname, gwa(grade1,grade2,grade3,grade4), verdict2(gwa(grade1,grade2,grade3,grade4)));
		verdict(gwa(grade1,grade2,grade3,grade4))?pass++:fail++;
		totalStudent++;
	}

	droppedPtr=fopen("dropped.txt", "r");
	char c;
	for(c=getc(droppedPtr); c!=EOF; c=getc(droppedPtr)) {
		if(c=='\n') {
			drop++;
		}
	}

	printf("\nTotal Students: %d\n", totalStudent);
	printf("Total Passed: %d\n", pass);
	printf("Total Failed: %d\n", fail);
	printf("Total Dropped: %d\n", drop);
	fprintf(outputPtr, "\nTotal Students: %d\n", totalStudent);
	fprintf(outputPtr, "Total Passed: %d\n", pass);
	fprintf(outputPtr, "Total Failed: %d\n", fail);
	fprintf(outputPtr, "Total Dropped: %d", drop);
	fclose(recordPtr);
	fclose(outputPtr);
	fclose(droppedPtr);

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
