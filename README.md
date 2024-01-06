# Library Management with C
Certainly! The provided project is a simple Library Management System implemented in C using the GTK (GIMP Toolkit) library for the graphical user interface. Here's a brief summary:

### Project Overview:

*Features:*
1. *Add a Book:* Allows the user to add a book to the library by providing the title, author, and publication year.

2. *Display All Books:* Displays a catalog of all books in the library, including their titles, authors, and publication years.

3. *Search for a Book:* Enables the user to search for a book by its title. If found, it displays detailed information about the book.

4. *Delete a Book:* Allows the user to delete a book from the library by providing its title.

5. *Display Books by Author:* Displays a list of books by a specific author.

6. *Exit:* Exits the program.

*Implementation:*
- The program uses a simple console-based user interface created with GTK.
- Books are represented as structures with fields for title, author, and year of publication.
- The program maintains an array of books (the library) and tracks the number of books in the array.
- Various functions handle adding books, displaying the catalog, searching for books, deleting books, and displaying books by a specific author.

*How to Run:*
1. Compile the program using GCC and include the necessary GTK flags:

   bash
   gcc -o script script.c `pkg-config --cflags --libs gtk+-3.0`
   

2. Run the compiled executable:

   bash
   ./script
   

3. The GTK-based graphical user interface will open, allowing you to interact with the Library Management System.

*Notes:*
- Ensure that the GTK development libraries are installed on your system before compilation.
- The project provides a basic example of a GUI application for a library management system, and you can expand it further based on your requirements.

Feel free to customize and enhance the project as needed for your specific use case!
