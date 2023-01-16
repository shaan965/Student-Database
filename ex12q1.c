
#include "lab12.h"

#define STUDENTS 99

int assignCmp(const void *s1, const void *s2) {
    struct student *st1 = *(struct student **)s1;
    struct student *st2 = *(struct student **)s2;

    float result = st1->assignments - st2->assignments;
  
    if (result == 0) {
        result = strcmp(st1->lastname, st2->lastname);
        if (result == 0) {
            result = strcmp(st1->firstname, st2->firstname);
        }
    } else if (result > 0) {
        result = 1;
    } else {
        result = -1;
    }

    return result;
}

int examsCmp(const void *s1, const void *s2) {
    struct student *st1 = *(struct student **)s1;
    struct student *st2 = *(struct student **)s2;

    float result = st1->exams - st2->exams;
  
    if (result == 0) {
        result = strcmp(st1->lastname, st2->lastname);
        if (result == 0) {
            result = strcmp(st1->firstname, st2->firstname);
        }
    } else if (result > 0) {
        result = 1;
    } else {
        result = -1;
    }

    return result;
}

int gradeCmp(const void *s1, const void *s2) {
    struct student *st1 = *(struct student **)s1;
    struct student *st2 = *(struct student **)s2;

    float result = st1->grade - st2->grade;
    
    if (result == 0) {
        result = strcmp(st1->lastname, st2->lastname);
        if (result == 0) {
            result = strcmp(st1->firstname, st2->firstname);
        }
    } else if (result > 0) {
        result = 1;
    } else {
        result = -1;
    }

    return result;
}

int labsCmp(const void *s1, const void *s2) {
    struct student *st1 = *(struct student **)s1;
    struct student *st2 = *(struct student **)s2;

    float result = st1->labs - st2->labs;
  
    if (result == 0) {
        result = strcmp(st1->lastname, st2->lastname);
        if (result == 0) {
            result = strcmp(st1->firstname, st2->firstname);
        }
    } else if (result > 0) {
        result = 1;
    } else {
        result = -1;
    }

    return result;
}

int quizzesCmp(const void *s1, const void *s2) {
    struct student *st1 = *(struct student **)s1;
    struct student *st2 = *(struct student **)s2;

    float result = st1->quizzes - st2->quizzes;
  
    if (result == 0) {
        result = strcmp(st1->lastname, st2->lastname);
        if (result == 0) {
            result = strcmp(st1->firstname, st2->firstname);
        }
    } else if (result > 0) {
        result = 1;
    } else {
        result = -1;
    }

    return result;
}

int totalCmp(const void *s1, const void *s2) {
    struct student *st1 = *(struct student **)s1;
    struct student *st2 = *(struct student **)s2;

    float result = st1->total - st2->total;
  
    if (result == 0) {
        result = strcmp(st1->lastname, st2->lastname);
        if (result == 0) {
            result = strcmp(st1->firstname, st2->firstname);
        }
    } else if (result > 0) {
        result = 1;
    } else {
        result = -1;
    }

    return result;
}

int nameCmp(const void *s1, const void *s2) {
    struct student *st1 = *(struct student **)s1;
    struct student *st2 = *(struct student **)s2;

    int result = strcmp(st1->lastname, st2->lastname);
    if (result == 0) {
        result = strcmp(st1->firstname, st2->firstname);
    }

    return result;
}
	
void cleanup(struct student *students[]) {
	for (int i = 0; i < STUDENTS; i++) {
		free(students[i]->lastname);
		free(students[i]->firstname);
		free(students[i]);
	}
}

int main(int argc, char *argv[]) {
	//read the name of the input file ===
	if(argc < 2){
		printf("Not enough input arguments. This program needs the name of the input file, like ./sorting input.txt  or ./grading spreadsheet.txt");
                return -1;
	}
	if(argc > 2){
                printf("Too many input arguments to the program. Only 1 argument must be passed to this program,  like ./sorting input.txt  or ./grading spreadsheet.txt");
                return -1;
        }   	
	
	 

	FILE *spreadsheet = fopen(argv[1], "r");
	if (spreadsheet == NULL) {
		printf("Could not find the file %s in the directory of the program.\n", argv[1]);
		return -1;
	}
	
	#ifndef SORT
	#ifndef GRADE
	printf("No macro defined!\n");
	return -1;
	#endif
	#endif

	// read spreadsheet
	struct student *students[STUDENTS];
	fseek(spreadsheet, 62, SEEK_CUR);
	
	for (int i = 0; i < STUDENTS; i++) {
		char *temp1 = malloc(50 * sizeof(char));
		char *temp2 = malloc(50 * sizeof(char));
		students[i] = malloc(sizeof(struct student));

		fscanf(spreadsheet, "%s %s %f %f %f %f", temp1, temp2, &(students[i]->assignments), &(students[i]->quizzes), &(students[i]->labs), &(students[i]->exams));
		students[i]->lastname = temp1;
		students[i]->firstname = temp2;
		students[i]->total = (students[i]->assignments/21.0 * 8.0) + (students[i]->quizzes/14.0 * 20.0) + (students[i]->labs /30.0 * 33.0) + (students[i]->exams /30.0 * 39.0);
		students[i]->grade = '-';
	}
	
	fclose(spreadsheet);

	#ifdef SORT
	char smethod[20];
	printf("Sort all students by: ");
	fgets(smethod, 19, stdin);

    if (strcmp("Name\n", smethod) == 0) {
        qsort(students, STUDENTS, sizeof(struct student *), nameCmp);
    } else if (strcmp("Assignments\n", smethod) == 0) {
        qsort(students, STUDENTS, sizeof(struct student *), assignCmp);
    } else if(strcmp("Quizzes\n", smethod) == 0) {
        qsort(students, STUDENTS, sizeof(struct student *), quizzesCmp);
    } else if (strcmp("Labs\n", smethod) == 0) {
        qsort(students, STUDENTS, sizeof(struct student *), labsCmp);
    } else if (strcmp("Exams\n", smethod) == 0) {
        qsort(students, STUDENTS, sizeof(struct student *), examsCmp);
    } else if (strcmp("Total\n", smethod) == 0) {
        qsort(students, STUDENTS, sizeof(struct student *), totalCmp);
    } else if (strcmp("Grade\n", smethod) == 0) {
        qsort(students, STUDENTS, sizeof(struct student *), gradeCmp);
    } else {
        printf("Invalid input!\n");
		cleanup(students);
		return -2;
    }
    

       // printing sorted students
        printf("Name                     Assignments    Quizzes   Labs      Exams \n");
        for (int i = 0; i < STUDENTS; i++) {
                struct student *s = students[i];
                strcat(s->lastname, " ");
                strcat(s->lastname, s->firstname);
                printf("%-25s%5.2f          %5.2f     %5.2f     %5.2f\n ", s->lastname, s->assignments, s->quizzes, s->labs, s->exams);
                free(s->lastname);
                free(s->firstname);
                free(s);
        }





	#endif

	#ifdef GRADE
	float cutoffs[4];
	printf("Enter four cutoffs for grade assignment: ");
	if (scanf("%f %f %f %f", cutoffs, cutoffs+1, cutoffs+2, cutoffs+3) != 4) {
		printf("Wrong number of cutoffs!\n");
		cleanup(students);
		return -2;
	}
	if (cutoffs[0] > cutoffs[1] || cutoffs[1] > cutoffs[2] || cutoffs[2] > cutoffs[3]) {
		printf("Cutoffs must be in ascending order!\n");
		cleanup(students);
		return -2;
	}
	if (cutoffs[0] < 50 || cutoffs[3] > 90) {
		printf("Cutoffs outside of acceptable range!\n");
		cleanup(students);
		return -2;
	}
	
	float total = 0.0;
	for (int i = 0; i < STUDENTS; i++) {
        switch ((students[i]->total < cutoffs[3]) + (students[i]->total < cutoffs[2]) + (students[i]->total < cutoffs[1]) + (students[i]->total < cutoffs[0])) {
			case 0:
				students[i]->grade = 'A';
				total += 4.0;
				break;
			case 1:
				students[i]->grade = 'B';
				total += 3.0;
				break;
			case 2:
				students[i]->grade = 'C';
				total += 2.0;
				break;
			case 3:
				students[i]->grade = 'D';
				total += 1.0;
				break;
			case 4:
				students[i]->grade = 'F';
				break;
		}
	}

    total /= (float)STUDENTS;
	printf("\n\nThe class average grade point is: %.2f\n\n", total);
	
	qsort(students, STUDENTS, sizeof(struct student *), gradeCmp);
	
	// printing sorted students
        FILE *fp;
   	fp = fopen("result.txt", "w");
   	//fprintf(fp, "This is testing for fprintf...\n");
   	//fputs("This is testing for fputs...\n", fp);
   	//fclose(fp);
	       

	fprintf(fp, "Name                     Assignments    Quizzes   Labs      FinalExam      Total     Grade     \n");
        for (int i = 0; i < STUDENTS; i++) {
                struct student *s = students[i];
                strcat(s->lastname, " ");
                strcat(s->lastname, s->firstname);
                fprintf(fp, "%-25s%5.2f          %5.2f     %5.2f     %5.2f          %6.2f     %c\n", s->lastname, s->assignments, s->quizzes, s->labs, s->exams, s->total, s->grade);
                free(s->lastname);
                free(s->firstname);
                free(s);
        }

	fclose(fp);



    #endif
    
	return 0;
}
