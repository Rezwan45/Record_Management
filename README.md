# Record_Management

This project is a menu-driven **Student Records Management System** implemented in C. It allows users to add, view, search, update, and delete student records stored in a binary file.

## Features

- **Add Student Records**: Store student details, including ID, name, email, course ID, and grade.
- **View All Records**: Retrieve and display all saved records.
- **Search Records**: Find a specific record using the student ID.
- **Update Records**: Modify existing records by entering the student ID.
- **Delete Records**: Remove a specific record by student ID.
- **Persistent Storage**: Uses a binary file (`students.dat`) for storing records.

## Menu Options

1. **Add a Student Record**: Input new details and save them in the database.
2. **Display All Records**: View a list of all student records.
3. **Search for a Record**: Find a specific record using the student ID.
4. **Update a Record**: Modify a record’s details by specifying the student ID.
5. **Delete a Record**: Permanently delete a record from the database.
6. **Exit**: Close the program.

## File Structure

- **student_records.c**: The main program file containing all logic and functions.
- **README.md**: Documentation file.

## Example Workflow

```text
Menu:
1. Add a student record
2. Display all records
3. Search for a record
4. Update a record
5. Delete a record
6. Exit
Enter your choice: 1
Enter student ID: 101
Enter name: Rezwanul haque
Enter email: rezwanulhaque542@gmail.com
Enter course ID: Comp101
Enter grade: A
Record added successfully!
```

## Technologies Used

- **C Programming Language**: Core implementation.
- **File Handling**: Uses binary files for persistent storage.
- **Structs**: Defines a `Student` structure for record management.

## Notes

- Data is stored in a binary file named `students.dat` in the `/tmp` directory.
- Temporary files are used for safe deletion operations.

---

Feel free to contribute or customize this program as per your requirements!
