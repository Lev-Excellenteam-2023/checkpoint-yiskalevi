
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define STRING_SIZE 50
#define GRADES_SIZE 10
#define PHONE_SIZE 15
#define LEVELS 12
#define CLASS 10
#define NUM2 3


typedef struct Student {
    char first_name[STRING_SIZE];
    char last_name[STRING_SIZE];
    char phone[PHONE_SIZE];
    int grades[GRADES_SIZE];
    struct Student* next;
} Student; 

Student* school[LEVELS][CLASS];

enum menu_inputs {
    Insert = '0',
    Delete = '1',
    Edit = '2',
    Search = '3',
    Showall = '4',
    Top10 = '5',
    UnderperformedStudents = '6',
    Average = '7',
    Export = '8',
    Exit = '9'
};

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

void freeStudents() {
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

void print_details_student(Student* student){
    printf("Name: %s %s\n", student->first_name, student->last_name);
    printf("Phone: %s\n", student->phone);
    printf("Grades: ");
    for (int i = 0; i < GRADES_SIZE; i++) {
        printf("%d ", student->grades[i]);
    }
}
void printAllStudents() {
    for (int level = 0; level < LEVELS; level++) {
        printf("Lavel %d\n",level+1);
        for (int class_num = 0; class_num < CLASS; class_num++) {
            printf("Class num %d\n",class_num+1);
             Student* current = school[level][class_num];
            while (current != NULL) {
                print_details_student(current);
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

/*
 * The function gets input from the user and ensures the input
 * doesn't exceed max_size. if yes - it will shrink it and will add \0.
 */
size_t get_input(char* dst, size_t max_size) {
    char* input = NULL;
    size_t len = 0;
    size_t len_size = 0;
    len_size = getline(&input, &len, stdin);
    if (len_size == -1)
        return -1;
    if (len_size < max_size) {
        input[len_size - 1] = '\0';
        strncpy(dst, input, len_size);
    }
    else {
        input[max_size - 1] = '\0';
        strncpy(dst, input, max_size);
        len_size = max_size;
    }
    free(input);
    return len_size;
}

void get_input_curect(char* dst, size_t max_size){
    int val=get_input(dst,  max_size);
    while(val==-1){
        printf("There was a problem with the input, please enter again");
        get_input(dst,  max_size);
    }
}

// Function to check if a character is a digit (0-9)
int is_digit(char c) {
    return c >= '0' && c <= '9';
}

// Function to check if a string represents a valid positive integer
int is_valid_integer(char* dst,size_t max_size) {
    int val=get_input(dst, max_size);
    while(val==-1){
        printf("%c", *dst); 
        printf("There was a problem with the input, please enter again\n");
        get_input(dst,max_size);
    }
    char* dst1=dst;
    strncpy(dst1,dst,max_size);
    while (*dst1 != '\0') {
        if (!is_digit(*dst1)) {
            return -1; // If any character is not a digit, it's not a valid integer
        }
        dst1++;
    }
    
    return atoi(dst);
}

void insertNewStudent(){
    Student student;
    int level, class;
    printf("Enter first name: \n");
    get_input_curect(student.first_name,  STRING_SIZE);
    printf("Enter last name: \n");
    get_input_curect(student.last_name,  STRING_SIZE);
    printf("Enter phone number: \n");
    while(is_valid_integer(student.phone,  PHONE_SIZE)==-1){
        printf("There was a problem with the input, please enter again\n");
    }
    char dst[3];
    printf("Enter level: \n");
    level =is_valid_integer(dst,  2);
    while(level>LEVELS || level<1){
        printf("There was a problem with the input, please enter again\n");
        level =is_valid_integer(dst,  2);
    }

    printf("Enter class: \n");
    class =is_valid_integer(dst,  2);
    while(class>CLASS || class<1){
        printf("There was a problem with the input, please enter again\n");
        class =is_valid_integer(dst,  2);
    }
    printf("10 grades: \n");
    for (int i = 0; i < 10; i++) {
        int n=is_valid_integer(dst,  2);
        while(n==-1){
            printf("There was a problem with the input, please enter again\n");
            n=is_valid_integer(dst,  2);
        }
        student.grades[i]=n;
    }
    level=level-1;
    class=class-1;
    Student* newStudent=createStudent(student);
    insertStudent(school,newStudent,level,class);
    printf("Insert successful\n");
}
void deleteStudent(){
    printf("Enter first name and last name:\n");
    char first_name[STRING_SIZE];
    char last_name[STRING_SIZE];
    scanf("%s %s", first_name, last_name);
    bool is_find=true;
    for (int level = 0; level < LEVELS && is_find; level++) {
        Student* befor=NULL;
        for (int class_num = 0; class_num < CLASS && is_find; class_num++) {
            Student* current = school[level][class_num];
            while (current!= NULL) {
                if (strcmp(current->first_name, first_name) == 0 && strcmp(current->last_name, last_name) == 0) {
                    is_find=false; 
                    if(befor==NULL){
                        school[level][class_num]=current->next;
                        }
                    else{
                        befor->next=current->next;
                        }
               free(current);
            }
            befor=current;
            current = current->next;
            }
        }
    }
    if(is_find){
        printf("The student is not found\n");
    }
    printf("Delete successful\n");
}
Student* searchStudentP(char first_name[STRING_SIZE], char last_name[STRING_SIZE]){
    for (int level = 0; level < LEVELS ; level++) {
        for (int class_num = 0; class_num < CLASS ; class_num++) {
            Student* current = school[level][class_num];
            while (current != NULL) {
                if(strcmp(current->first_name, first_name) == 0 && strcmp(current->last_name, last_name) == 0){
                    return current;
                }
                current = current->next;
            }
        }
    }
    printf("No student found\n");
    return NULL;
}
void searchStudent(){
    printf("Enter first name and last name:\n");
    char first_name[STRING_SIZE];
    char last_name[STRING_SIZE];
    scanf("%s %s", first_name, last_name);
    Student* student =searchStudentP(first_name, last_name);
    if(student!=NULL){
        print_details_student(student);
    }
}

void editStudentGrade(){
    printf("Enter first name and last name:\n");
    char first_name[STRING_SIZE];
    char last_name[STRING_SIZE];
    scanf("%s %s", first_name, last_name);
    Student* student =searchStudentP(first_name, last_name);
    print_details_student(student);
    printf("Which grade would you like to change 0-9 and which grade do you want to change\n");
    int num,grade;
    scanf("%d %d", &num,&grade);
    student->grades[num]=grade;
    printf("Student details after the update:\n");
    print_details_student(student);
}



float calculateAverage(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }

    float average = (float)sum / size;
    return average;
}
void printUnderperformedStudents(){
    //Any student whose average is lower than 80
    float min_grade=80;
    printf("The students who are about to leave:\n");
    for (int level = 0; level < LEVELS ; level++) {
        for (int class_num = 0; class_num < CLASS ; class_num++) {
            Student* current = school[level][class_num];
            while (current!= NULL) {
                float average=calculateAverage(current->grades,GRADES_SIZE );
                if(average<min_grade){
                    print_details_student(current);
                    printf("Average: %f\n",average);
                }
                current=current->next;
            }
        }
    }

}
void printAverage(){
    for (int level = 0; level < LEVELS ; level++) {
        int sum_grade_level=0;
        for (int class_num = 0; class_num < CLASS ; class_num++) {
            int sum_grade_class_num=0;
            int count_student_class_num=0;
            Student* current = school[level][class_num];
            while (current!= NULL) {
                float averageS=calculateAverage(current->grades,GRADES_SIZE );
                sum_grade_class_num=sum_grade_class_num+averageS;
                count_student_class_num=count_student_class_num+1;

                current=current->next;
            }
            float averageC=sum_grade_class_num/count_student_class_num;
            sum_grade_level=sum_grade_level+averageC;
            printf("the average of class %d: %f\n",class_num,averageC);

        }
        float averageL=sum_grade_level/CLASS;
        printf("the average of level %d: %f\n",level,averageL);
    } 
}

void swapWithMin(Student* arr[10], Student* newElement, int size, int subject) {
    for (int i = 0; i < size; i++) {
        if(arr[i]==NULL){
            arr[i]=newElement;
            return;
        }
    }
    int minIndex = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i]->grades[subject] < arr[minIndex]->grades[subject]) {
            minIndex = i;
        }
    }

    if (arr[minIndex]->grades[subject] < newElement->grades[subject]) {
        arr[minIndex] = newElement;
    }
}

void printTopNStudentsPerCourse() {
    printf("Choose a subject (0-9) in which you want the top 10 students:\n");
    int num;
    scanf("%d", &num);
    int size = 10;

    for (int level = 0; level < LEVELS; level++) {
        Student* top_grade[size];
        for (int i = 0; i < size; i++) {
            top_grade[i] = NULL;
        }

        for (int class_num = 0; class_num < CLASS; class_num++) {
            Student* current = school[level][class_num];
            while (current != NULL) {
                swapWithMin(top_grade, current, size, num);
                current = current->next;
            }
        }

        printf("Top 10 students in Level %d for subject %d:\n", level, num);
        for (int i = 0; i < size; i++) {
            if (top_grade[i] != NULL) {
                print_details_student(top_grade[i]);
                printf("\n");
            }
        }
        printf("\n");
    }
}

void writeStudentToFile(FILE* file, Student* student) {
    if (file == NULL || student == NULL) {
        printf("Error: Invalid file or student.\n");
        return;
    }

    fprintf(file, "%s %s %s ", student->first_name, student->last_name, student->phone);

    for (int i = 0; i < GRADES_SIZE; i++) {
        fprintf(file, "%d ", student->grades[i]);
    }

    fprintf(file, "\n");
}

void writeAllStudentsToFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int level = 0; level < LEVELS; level++) {
        for (int class_num = 0; class_num < CLASS; class_num++) {
            Student* current = school[level][class_num];
            while (current != NULL) {
                writeStudentToFile(file, current);
                current = current->next;
            }
        }
    }

    fclose(file);
}
void exportDatabase(){
    printf(" What is the name of the file you want to write to:\n");
    char file_name[STRING_SIZE];
    scanf("%s", file_name);
    writeAllStudentsToFile(file_name);
}
void handleClosing(){
    freeStudents(school);
}
void menu() {
    char input;
    // school.name = "schoolName";
    do {
        printf("\n|School Manager<::>Home|\n");
        printf("--------------------------------------------------------------------------------\n");
        //printf("Welcome to ( %s ) School!\nYou have inserted ( %zu ) students.\n\n", school.name, school.numOfStudents);
        printf("\t[0] |--> Insert\n");
        printf("\t[1] |--> Delete\n");
        printf("\t[2] |--> Edit\n");
        printf("\t[3] |--> Search\n");
        printf("\t[4] |--> Show All\n");
        printf("\t[5] |--> Top 10 students per course\n");
        printf("\t[6] |--> Underperformed students\n");
        printf("\t[7] |--> Average per course\n");
        printf("\t[8] |--> Export\n");
        printf("\t[9] |--> Exit\n");
        printf("\n\tPlease Enter Your Choice (0-9): ");
        input = getc(stdin);
        fflush(stdin);
        getc(stdin);
        switch (input) {
            case Insert:
                insertNewStudent();
                break;
            case Delete:
                deleteStudent();
                break;
            case Edit:
                editStudentGrade();
                break;
            case Search:
                searchStudent();
                break;
            case Showall:
                printAllStudents();
                break;
            case Top10:
                printTopNStudentsPerCourse();
                break;
            case UnderperformedStudents:
                printUnderperformedStudents();
                break;
            case Average:
                printAverage();
                break;
            case Export:
                exportDatabase();
                break;
            case Exit:
                handleClosing();
                break;
            default:
                printf("\nThere is no item with symbol \"%c\".Please enter a number between 1-10!\nPress any key to continue...",
                       input);
                getc(stdin);
                getc(stdin);
                break;
        }
    } while (input != Exit);
}

int main() {
    
    
    
    for (int i = 0; i < LEVELS; i++) {
        for (int j = 0; j < CLASS; j++){
            school[i][j] = NULL;
        } 
    }
    //FILE* file = fopen("so.txt", "r");
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
    //printAllStudents();
    menu();

    return 0;
}