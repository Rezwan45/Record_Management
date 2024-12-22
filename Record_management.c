#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defining student record structure
typedef struct {
    int studentID;
    char name[50];
    char email[50];
    char courseID[10];
    char grade[5];
} Student;

// Function prototypes
void addRecord(FILE *file);
void displayRecords(FILE *file);
void searchRecord(FILE *file);
void updateRecord(FILE *file);
void deleteRecord(FILE **file);
void clearInputBuffer();

int main() {
    int choice;
    FILE *file;

        file = fopen("/tmp/students.dat", "rb+");

    
    if (file == NULL) {
        file = fopen("/tmp/students.dat", "wb+");
        if (file == NULL) {
            perror("Error opening file");
            return 1;
        }
    }

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add a student record\n");
        printf("2. Display all records\n");
        printf("3. Search for a record\n");
        printf("4. Update a record\n");
        printf("5. Delete a record\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer(); // Clearing buffer 
        switch (choice) {
            case 1:
                addRecord(file);
                break;
            case 2:
                displayRecords(file);
                break;
            case 3:
                searchRecord(file);
                break;
            case 4:
                updateRecord(file);
                break;
            case 5:
                deleteRecord(&file);
                break;
            case 6:
                fclose(file);
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Function for adding student record
void addRecord(FILE *file) {
    Student student;
    fseek(file, 0, SEEK_END);  // Move to the end of the file

    printf("Enter student ID: ");
    scanf("%d", &student.studentID);
    clearInputBuffer(); 

    printf("Enter name: ");
    fgets(student.name, sizeof(student.name), stdin);
    student.name[strcspn(student.name, "\n")] = 0; 

    printf("Enter email: ");
    fgets(student.email, sizeof(student.email), stdin);
    student.email[strcspn(student.email, "\n")] = 0; 

    printf("Enter course ID: ");
    fgets(student.courseID, sizeof(student.courseID), stdin);
    student.courseID[strcspn(student.courseID, "\n")] = 0; 

    printf("Enter grade: ");
    fgets(student.grade, sizeof(student.grade), stdin);
    student.grade[strcspn(student.grade, "\n")] = 0; 

    fwrite(&student, sizeof(Student), 1, file);
    printf("Record added successfully!\n");
}

// Function to display all records
void displayRecords(FILE *file) {
    Student student;
    rewind(file);  // Move to the start of the file

    printf("\nDisplaying all records:\n");
    while (fread(&student, sizeof(Student), 1, file)) {
        printf("\nStudent ID: %d\n", student.studentID);
        printf("Name: %s\n", student.name);
        printf("Email: %s\n", student.email);
        printf("Course ID: %s\n", student.courseID);
        printf("Grade: %s\n", student.grade);
    }
}

// Function to search  a record by student ID
void searchRecord(FILE *file) {
    int id, found = 0;
    Student student;
    rewind(file);  

    printf("Enter student ID to search: ");
    scanf("%d", &id);
    clearInputBuffer(); 

    while (fread(&student, sizeof(Student), 1, file)) {
        if (student.studentID == id) {
            printf("\nRecord found:\n");
            printf("Student ID: %d\n", student.studentID);
            printf("Name: %s\n", student.name);
            printf("Email: %s\n", student.email);
            printf("Course ID: %s\n", student.courseID);
            printf("Grade: %s\n", student.grade);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Record not found.\n");
    }
}

// Function to update record by student ID
void updateRecord(FILE *file) {
    int id, found = 0;
    Student student;
    long pos;

    printf("Enter student ID to update: ");
    scanf("%d", &id);
    clearInputBuffer(); // Clearing buffer after the integer input

    rewind(file);  // Move to the start of the file

    while (fread(&student, sizeof(Student), 1, file)) {
        if (student.studentID == id) {
            printf("Enter new details:\n");

            printf("Enter name: ");
            fgets(student.name, sizeof(student.name), stdin);
            student.name[strcspn(student.name, "\n")] = 0; 

            printf("Enter email: ");
            fgets(student.email, sizeof(student.email), stdin);
            student.email[strcspn(student.email, "\n")] = 0; 

            printf("Enter course ID: ");
            fgets(student.courseID, sizeof(student.courseID), stdin);
            student.courseID[strcspn(student.courseID, "\n")] = 0; 

            printf("Enter grade: ");
            fgets(student.grade, sizeof(student.grade), stdin);
            student.grade[strcspn(student.grade, "\n")] = 0; 

            pos = ftell(file) - sizeof(Student);  
            fseek(file, pos, SEEK_SET);  

            fwrite(&student, sizeof(Student), 1, file);  
            found = 1;
            printf("Record updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Record not found.\n");
    }
}

// Function to delete  record by student ID
void deleteRecord(FILE **file) {
    int id, found = 0;
    Student student;
    FILE *tempFile;

    printf("Enter student ID to delete: ");
    scanf("%d", &id);
    clearInputBuffer(); 

    rewind(*file);  // Move to the start of the file

    // Create a temporary file to hold the new records
    tempFile = fopen("/tmp/temp.dat", "wb");

    if (tempFile == NULL) {
        perror("Error opening temporary file");
        return;
    }

    while (fread(&student, sizeof(Student), 1, *file)) {
        if (student.studentID != id) {
            fwrite(&student, sizeof(Student), 1, tempFile);  // Copy records that are not deleted
        } else {
            found = 1;
        }
    }

    fclose(*file);
    fclose(tempFile);

    remove("/tmp/students.dat");  // Deleting the original file
    rename("/tmp/temp.dat", "/tmp/students.dat");  // Renaming the file

    // Reopen the updated file
    *file = fopen("/tmp/students.dat", "rb+");
    if (*file == NULL) {
        perror("Error reopening file after deletion");
    }

    if (found) {
        printf("Record deleted successfully!\n");
    } else {
        printf("Record not found.\n");
    }
}

// Function to clear the buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Clear the buffer by discarding all characters until newline
    }
}
