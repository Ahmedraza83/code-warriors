#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll_no;          // Student Roll Number
    char name[50];        // Student Name
    int age;              // Student Age
    char uin[20];         // Unique Identification Number
};

void addStudent() {
    FILE *file = fopen("students.txt", "a");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    struct Student student;

    // Input student details
    printf("Enter Roll Number: ");
    scanf("%d", &student.roll_no);
    getchar();

    printf("Enter Name: ");
    fgets(student.name, 50, stdin);
    student.name[strcspn(student.name, "\n")] = '\0';

    printf("Enter Age: ");
    scanf("%d", &student.age);

    printf("Enter UIN (Student ID): ");
    getchar();
    fgets(student.uin, 20, stdin);
    student.uin[strcspn(student.uin, "\n")] = '\0';

    // Write to file
    fprintf(file, "%d %s %d %s\n", student.roll_no, student.name, student.age, student.uin);
    fclose(file);

    printf("Student added successfully.\n");
}

void displayAllStudents() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("No records found.\n");
        return;
    }

    struct Student student;

    printf("\nList of Students:\n");
    printf("Roll Number | Name | Age | UIN (Student ID)\n");
    printf("--------------------------------------------------\n");

    // Read and display student details
    while (fscanf(file, "%d %s %d %s", &student.roll_no, student.name, &student.age, student.uin) != EOF) {
        printf("%d | %s | %d | %s\n", student.roll_no, student.name, student.age, student.uin);
    }

    fclose(file);
}

void searchStudent() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("No records found.\n");
        return;
    }

    int roll_no, found = 0;
    struct Student student;

    printf("Enter Roll Number to search: ");
    scanf("%d", &roll_no);

    // Search for the student
    while (fscanf(file, "%d %s %d %s", &student.roll_no, student.name, &student.age, student.uin) != EOF) {
        if (student.roll_no == roll_no) {
            printf("Student found:\n");
            printf("Roll Number: %d\n", student.roll_no);
            printf("Name: %s\n", student.name);
            printf("Age: %d\n", student.age);
            printf("UIN (Student ID): %s\n", student.uin);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with Roll Number %d not found.\n", roll_no);
    }

    fclose(file);
}

void updateStudent() {
    FILE *file = fopen("students.txt", "r+");
    if (file == NULL) {
        printf("No records found.\n");
        return;
    }

    int roll_no, found = 0;
    struct Student student;

    printf("Enter Roll Number to update: ");
    scanf("%d", &roll_no);

    // Search for the student and update details
    while (fscanf(file, "%d %s %d %s", &student.roll_no, student.name, &student.age, student.uin) != EOF) {
        if (student.roll_no == roll_no) {
            found = 1;

            printf("Enter new details for Roll Number %d\n", student.roll_no);
            getchar();

            printf("Enter new Name: ");
            fgets(student.name, 50, stdin);
            student.name[strcspn(student.name, "\n")] = '\0';

            printf("Enter new Age: ");
            scanf("%d", &student.age);

            printf("Enter new UIN (Student ID): ");
            getchar();
            fgets(student.uin, 20, stdin);
            student.uin[strcspn(student.uin, "\n")] = '\0';

            // Update file
            fseek(file, -(sizeof(student) + 1), SEEK_CUR);
            fprintf(file, "%d %s %d %s\n", student.roll_no, student.name, student.age, student.uin);

            printf("Student updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Student with Roll Number %d not found.\n", roll_no);
    }

    fclose(file);
}

int main() {
    int choice;

    do {
        printf("\nStudent Management System\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search for a Student\n");
        printf("4. Update Student Details\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, try again.\n");
        }
    } while (choice != 5);

    return 0;
}
