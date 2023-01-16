#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {

    char *lastname;

    char *firstname;

    float assignments; // range [0, 21]; percentage 8%

    float quizzes; // range [0, 14]; percentage 20%

    float labs; // range [0, 30]; percentage 33%

    float exams; // range [0, 30]; percentage 39%

    float total; // range [0, 100]

    char grade; // range {'F', 'D', 'C', 'B', 'A'}

};


