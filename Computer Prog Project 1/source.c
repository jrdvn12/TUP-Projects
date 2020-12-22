#include <stdio.h>
#include <stdlib.h>

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

int main(void) {
	char name[10];
	float grade1, grade2, grade3, grade4;
    int pass=0, fail=0;

	FILE * frecord=fopen("record.txt", "r");
	if(!frecord) {
		printf("ERROR OPENING FILE\n");
		exit(0);
	} else {
        FILE * foutput=fopen("output.txt", "w");
        printf("Name\t\tGWA\t\tGrade Letter\n");
        fprintf(foutput, "Name\t\tGWA\t\tGrade Letter\n");
		while(fscanf(frecord, "%s%f%f%f%f", &name, &grade1, &grade2, &grade3, &grade4)!=EOF) {
            printf("%s\t\t%.2f\t\t%c\n", name, gwa(grade1,grade2,grade3,grade4), grade(gwa(grade1,grade2,grade3,grade4)));
            fprintf(foutput, "%s\t\t%.2f\t\t%c\n", name, gwa(grade1,grade2,grade3,grade4), grade(gwa(grade1,grade2,grade3,grade4)));
            verdict(gwa(grade1,grade2,grade3,grade4))?pass++:fail++;
		}
        printf("\n");
        fprintf(foutput, "\n");
        printf("Total Passed: %d\n", pass);
        printf("Total Failed: %d\n", fail);
        fprintf(foutput, "Total Passed: %d\n", pass);
        fprintf(foutput, "Total Failed: %d", fail);
        fclose(frecord);
        fclose(foutput);
	}
    return 0;
}
