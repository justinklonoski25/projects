#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
  char name[50];
  int student_id;
  double quizes[5];
  double average_score;
} student;

double minScore(student* stud) {
  double minscore = 10000;
  for (int i = 0; i < 5; i++) {
    if (stud->quizes[i] < minscore) minscore = stud->quizes[i];
  }
  return minscore;
}

int main() {
  printf("Enter an input file: ");
  char filename[100] = {0};
  int iter = 0;
  while (1) { //asks for user to input the filename
    char temp;
    scanf("%c", &temp);
    if (temp == '\n')
      break;
    filename[iter] = temp;
    iter++;
  }
  FILE *read1 = fopen(filename, "r"); //reads the file
  if (read1 == NULL) {
    printf("ERROR 404");
    return 0;
  }
  long unsigned int number_of_students; // the number of students in the file
  fscanf(read1, "%ld", &number_of_students);
  student *class;
  class = (student *)malloc(sizeof(student *) * number_of_students); //allocates memory for a student struct for each student in the file
  for (long unsigned int i = 0; i < number_of_students + 1; i++) {
    char line[100];
    fgets(line, 100, read1);
    if (i == 0)
      continue; // the first line is the newline after the first int, it is
                // ignored
    sscanf(line, "%s %d %lf %lf %lf %lf %lf", class[i - 1].name,
           &class[i - 1].student_id, &class[i - 1].quizes[0],
           &class[i - 1].quizes[1], &class[i - 1].quizes[2],
           &class[i - 1].quizes[3], &class[i - 1].quizes[4]); // reads each line in the input file and sends that information to the members of the student struct
    class[i - 1].average_score =
        (class[i - 1].quizes[0] + class[i - 1].quizes[1] +
         class[i - 1].quizes[2] + class[i - 1].quizes[3] +
         class[i - 1].quizes[4] - minScore(&class[i-1])) / 4.0; // calculates the average score using the other quiz scores
  }
  printf("--------------------------------------------------\n  Course Report: "
         "Quiz Average\n--------------------------------------------------\n");
  for (long unsigned int i = 1; i < number_of_students + 1; i++) //loops through all the student structs in the array class
    printf("   %s (%d): %0.2f \n", class[i - 1].name, class[i - 1].student_id,
           class[i - 1].average_score); //prints the value of the members of each student struct in class
  printf("--------------------------------------------------\n");
  //free(class);
  return 0;
} 
