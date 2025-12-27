#include <stdio.h>
#define MAX 50

// Structure definition
struct Student {
    int id;
    char name[50];
    int age;
    float cgpa;
};

// Global variables
struct Student students[MAX];
int count = 0;

// Function declarations
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void saveToFile();
void loadFromFile();
int  duplicateId(int id);

int main() {
    int choice;

    loadFromFile();  //load data to start

    do {
        printf("\n===== Student Management System =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search student by ID\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                  deleteStudent();
                  break;
            case 6:
                 saveToFile();     //save data before exist
                printf(" Data saved. Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 6);

    return 0;
}
 
// ================= FILE HANDLING =================

// Load data from file
void loadFromFile() {
    FILE *fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        // File doesn't exist yet
        return;
    }

    fread(&count, sizeof(int), 1, fp);
    fread(students, sizeof(struct Student), count, fp);

    fclose(fp);
}

// Save data to file
void saveToFile() {
    FILE *fp = fopen("students.dat", "wb");

    fwrite(&count, sizeof(int), 1, fp);
    fwrite(students, sizeof(struct Student), count, fp);

    fclose(fp);
}

// ================= DUPLICATE ID CHECK =================
int duplicateId(int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            return 1; // duplicate found
        }
    }
    return 0; // no duplicate
}

// Function to add a student
void addStudent() {
    if (count >= MAX) {
        printf("Student limit reached!\n");
        return;
    }

     int id;
    printf("\nEnter Student ID: ");
    scanf("%d", &id);

    if (duplicateId(id)) {
        printf("❌ Error: Student ID already exists!\n");
        return;
    }

    students[count].id = id;

    printf("\nEnter Student ID: ");
    scanf("%d", &students[count].id);

    printf("Enter Student Name: ");
    scanf(" %[^\n]", students[count].name);  // reads full name with spaces

    printf("Enter Age: ");
    scanf("%d", &students[count].age);

    printf("Enter CGPA: ");
    scanf("%f", &students[count].cgpa);

    count++;

    printf("Student added successfully!\n");
}

// Function to display all students
void displayStudents() {
    int i;

    if (count == 0) {
        printf("No student records found.\n");
        return;
    }

    printf("\n---- Student List ----\n");

    for (i = 0; i < count; i++) {
        printf("\nStudent %d\n", i + 1);
        printf("ID: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
        printf("Age: %d\n", students[i].age);
        printf("CGPA: %.2f\n", students[i].cgpa);
    }
}
// Function to search student by ID
void searchStudent() {
    int searchId, i;
    int found = 0;

    if (count == 0) {
        printf("No student records to search.\n");
        return;
    }

    printf("\nEnter Student ID to search: ");
    scanf("%d", &searchId);

    for (i = 0; i < count; i++) {
        if (students[i].id == searchId) {
            printf("\nStudent Found!\n");
            printf("ID: %d\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("Age: %d\n", students[i].age);
            printf("CGPA: %.2f\n", students[i].cgpa);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Student with ID %d not found.\n", searchId);
    }
}
void updateStudent() {
    int updateId,i;
    int found = 0;

    if (count == 0) {
        printf("No student records to update.\n");
        return;
    }

    printf("\nEnter Student ID to update: ");
    scanf("%d", &updateId);

    for (i = 0; i < count; i++) {
        if (students[i].id == updateId) {

            printf("\nEnter new name: ");
            scanf(" %[^\n]", students[i].name);

            printf("Enter new age: ");
            scanf("%d", &students[i].age);

            printf("Enter new CGPA: ");
            scanf("%f", &students[i].cgpa);

            printf("Student details updated successfully!\n");
            found = 1;
             break;
        }
    }

    if (!found) {
        printf("Student with ID %d not found.\n", updateId);
    }
}
// DELETE student
void deleteStudent() {
    int deleteid, found = 0;

    printf("Enter ID to delete: ");
    scanf("%d", &deleteid);

    for (int i = 0; i < count; i++) {
        if (students[i].id == deleteid) {

            // Shift students left
            for (int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
            }

            count--;
            printf("Student deleted successfully!\n");
            found = 1;
            break;
        }
    }
     if (!found) {
        printf("Student with ID %d not found.\n", deleteid);
    }
}

