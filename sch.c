
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STRING_SIZE 50
#define GRADES_SIZE 10
#define PHONE_SIZE 1
#define LEVELS 12
#define CLASS 10

typedef struct Student {
    char first_name[STRING_SIZE];
    char last_name[STRING_SIZE];
    char phone[PHONE_SIZE];
    int grades[GRADES_SIZE];
    struct Student* next;
} Student; 

Student* createStudent(Student student) {
    Student* newStudent = ( Student*)malloc(sizeof( Student));
    if (newStudent != NULL) {
        strncpy(newStudent->first_name, student.first_name, STRING_SIZE);
        strncpy(newStudent->last_name, student.last_name, STRING_SIZE);
        strncpy(newStudent->phone, student.phone, PHONE_SIZE);
        for (int i = 0; i < GRADES_SIZE; i++) {
            newStudent->grades[i] = student.grades[i];
        }
        newStudent->next = NULL;
    }
    return newStudent;
}

void freeStudents( Student* school[LEVELS][CLASS]) {
    for (int level = 0; level < LEVELS; level++) {
        for (int class_num = 0; class_num < CLASS; class_num++) {
             Student* current = school[level][class_num];
            while (current != NULL) {
                 Student* temp = current;
                current = current->next;
                free(temp); // Free the memory for the current student node
            }
        }
    }
}

void printAllStudents( Student* school[LEVELS][CLASS]) {
    for (int level = 0; level < LEVELS; level++) {
        for (int class_num = 0; class_num < CLASS; class_num++) {
             Student* current = school[level][class_num];
            while (current != NULL) {
                printf("Level: %d, Class: %d\n", level, class_num);
                printf("Name: %s %s\n", current->first_name, current->last_name);
                printf("Phone: %s\n", current->phone);
                printf("Grades: ");
                for (int i = 0; i < GRADES_SIZE; i++) {
                    printf("%d ", current->grades[i]);
                }
                printf("\n\n");
                current = current->next;
            }
        }
    }
}
void insertStudent(Student* school[LEVELS][CLASS],Student* newStudent,int level,int class){
    if (school[level][class] == NULL) {
        school[level][class] = newStudent;
    } 
    else {
        Student* current = school[level][class];
        while (current->next != NULL) {
            current = current->next;
            }
            current->next = newStudent;
    }

}

int main() {
    
    Student* school[LEVELS][CLASS];
    
    for (int i = 0; i < LEVELS; i++) {
        for (int j = 0; j < CLASS; j++){
            school[i][j] = NULL;
        } 
    }

    FILE* file = fopen("students_with_class.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    
    Student student;
    int level, class;

    while (fscanf(file, "%s %s %s %d %d", student.first_name, student.last_name, student.phone, &level, &class) == 5) {
        //create student
        if (level >= 1 && level <= LEVELS && class >= 1 && class <= CLASS) {
            level=level-1;
            class=class-1;
            for (int i = 0; i < 10; i++) {
                fscanf(file, "%d", &student.grades[i]);
            }
            Student* newStudent=createStudent(student);
            insertStudent(school,newStudent,level,class);
        } 
        else {
            printf("Invalid level or class: %d, %d\n", level, class);
        }
    }

    fclose(file);
    printAllStudents(school);
    freeStudents(school);

    return 0;
}