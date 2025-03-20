# Library Management System

A **C-based Library Management System** that allows librarians and members to manage books, search for books, borrow books, and return books. The system persists data using file storage.

---

## Features

1. **Book Management**:
   - Add new books with details like title, author, genre, ISBN, year, and copies.
   - List all available books in a tabular format.
   - Search for books by title.

2. **Borrow and Return Books**:
   - Members can borrow books if copies are available.
   - Members can return books to increase availability.

3. **Data Persistence**:
   - Books are saved to files (`library_data.txt`) for persistence across program runs.

4. **User-Friendly Interface**:
   - Easy-to-navigate console-based menu.

---

## How It Works

1. **Members Features**:
   - Add new books to the library.
   - List all books with details.
   - Search for books by title.
   - Borrow and return books.

2. **File Storage**:
   - Books are saved in `library_data.txt`.

---

## File Structure

- **`library_data.txt`**: Stores book details in the following format:   ID|Title|Author|Genre|ISBN|Year|Copies|Available
---

## How to Run

1. **Clone the Repository**:
 git clone https://github.com/zena-learngithub/Library_Management_System.git
 cd library-management-system
2.  **Compile the Code**:
 gcc -o library_management library_management.c
3. **Run the Program**:
   ./library_management

