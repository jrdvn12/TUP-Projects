#include <stdio.h>
#include <stdlib.h>

void settings() {
	printf("Settings screen will be shown.\n");
	return;
}

void list() {
	printf("List of Students screen will be shown.\n");
	return;
}

int main(void) {
	int option;
	printf("1) Settings\n");
	printf("2) List of Students\n");
	printf("Enter an option: ");
	scanf("%d", &option);

	switch(option) {
		case 1:
			settings();
			break;
		case 2:
			list();
			break;
		default:
			printf("Invalid option.\n");
	}

	return 0;
}
