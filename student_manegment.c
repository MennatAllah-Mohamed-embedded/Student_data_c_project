#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int id;
    char name[50];
    int age;
    float gpa;
    struct student* next;
};

struct student* head = NULL;

// Function prototypes
void addStudent(const struct student *const ptr);
void displayStudents(void);
void searchStudentByID(int id);
void updateStudent(int id);
float calculateAverageGPA(void);
void searchHighestGPA(void);
void deleteStudent(int id);
void menu(void);

int main(void) {
    menu();
    return 0;
}

void menu() {
    int choice, id;
    struct student temp;

    do {
        printf("\nStudent Management System\n");
        printf("1. Add a Student\n");
        printf("2. Display All Students\n");
        printf("3. Search for a Student by ID\n");
        printf("4. Update Student Information\n");
        printf("5. Delete a Student\n");
        printf("6. Calculate Average GPA\n");
        printf("7. Find Student with Highest GPA\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        fflush(stdout);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Student ID: ");
                fflush(stdout);
                scanf("%d", &temp.id);

                printf("Enter Student Name: ");
                fflush(stdout);
                scanf(" %[^\n]", temp.name); // Accepts spaces in name

                printf("Enter Student Age: ");
                fflush(stdout);
                scanf("%d", &temp.age);

                printf("Enter Student GPA: ");
                fflush(stdout);
                scanf("%f", &temp.gpa);

                addStudent(&temp);
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                printf("Enter Student ID to search: ");
                fflush(stdout);
                scanf("%d", &id);
                searchStudentByID(id);
                break;

            case 4:
                printf("Enter Student ID to update: ");
                fflush(stdout);
                scanf("%d", &id);
                updateStudent(id);
                break;

            case 5:
                printf("Enter Student ID to delete: ");
                fflush(stdout);
                scanf("%d", &id);
                deleteStudent(id);
                break;

            case 6:
                printf("Average GPA: %.2f\n", calculateAverageGPA());
                break;

            case 7:
                searchHighestGPA();
                break;

            case 8:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 8);
}

void addStudent(const struct student *const ptr) {
    struct student* current = head;
    while (current != NULL) {
        if (current->id == ptr->id) {
            printf("Error: Student ID already exists!\n");
            return;
        }
        current = current->next;
    }

    struct student* newStudent = (struct student*)malloc(sizeof(struct student));
    if (!newStudent) {
        printf("Memory allocation failed!\n");
        return;
    }

    *newStudent = *ptr;
    newStudent->next = NULL;

    if (head == NULL) {
        head = newStudent;
    } else {
        current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newStudent;
    }
    printf("Student added successfully!\n");
}

void displayStudents(void) {
    struct student* current = head;
    if (current == NULL) {
        printf("No students present.\n");
        return;
    }

    printf("\nList of Students:\n");
    while (current != NULL) {
        printf("ID: %d, Name: %s, Age: %d, GPA: %.2f\n",
               current->id, current->name, current->age, current->gpa);
        current = current->next;
    }
}

void searchStudentByID(int id) {
    struct student* current = head;
    while (current != NULL) {
        if (current->id == id) {
            printf("Student found: ID: %d, Name: %s, Age: %d, GPA: %.2f\n",
                   current->id, current->name, current->age, current->gpa);
            return;
        }
        current = current->next;
    }
    printf("Student not found.\n");
}

void updateStudent(int id) {
    struct student* current = head;
    while (current != NULL) {
        if (current->id == id) {
            printf("Updating details for Student ID: %d\n", id);

            printf("Enter new Name: ");
            fflush(stdout);
            scanf(" %[^\n]", current->name);

            printf("Enter new Age: ");
            fflush(stdout);
            scanf("%d", &current->age);

            printf("Enter new GPA: ");
            fflush(stdout);
            scanf("%f", &current->gpa);

            printf("Student information updated successfully!\n");
            return;
        }
        current = current->next;
    }
    printf("Student not found.\n");
}

float calculateAverageGPA(void) {
    struct student* current = head;
    float totalGPA = 0.0;
    int count = 0;

    while (current != NULL) {
        totalGPA += current->gpa;
        count++;
        current = current->next;
    }

    return (count == 0) ? 0.0 : totalGPA / count;
}

void searchHighestGPA(void) {
    struct student* current = head;
    if (current == NULL) {
        printf("No students present.\n");
        return;
    }

    struct student* highest = current;
    while (current != NULL) {
        if (current->gpa > highest->gpa) {
            highest = current;
        }
        current = current->next;
    }
    printf("Student with Highest GPA: ID: %d, Name: %s, Age: %d, GPA: %.2f\n",
           highest->id, highest->name, highest->age, highest->gpa);
}

void deleteStudent(int id) {
    struct student* current = head;
    struct student* previous = NULL;

    while (current != NULL) {
        if (current->id == id) {
            if (previous == NULL) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            printf("Student with ID %d deleted successfully!\n", id);
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Student not found.\n");
}
