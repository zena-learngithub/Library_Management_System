#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_USERS 50
#define FILENAME "library_data.txt"

typedef struct {
    int id;
    char title[50];
    char author[50];
    char genre[30];
    char isbn[20];
    int year;
    int copies;
    int available;
} Book;

typedef struct {
    int id;
    char name[50];
    char type[20]; // Admin or Member
} User;

Book library[MAX_BOOKS];
int totalBooks = 0;

void welcomeScreen() {
    printf("\n--------------------------------------------\n");
    printf("         Welcome to Library System!         \n");
    printf("--------------------------------------------\n");
}

void displayMenu() {
    printf("\n*************** Menu ***************\n");
    printf("1. Add Book\n");
    printf("2. List Books\n");
    printf("3. Search Book\n");
    printf("4. Borrow Book\n");
    printf("5. Return Book\n");
    printf("6. Exit\n");
    printf("************************************\n");
    printf("Enter your choice: ");
}

void saveDataToFile() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error: Unable to save data to file.\n");
        return;
    }

    for (int i = 0; i < totalBooks; i++) {
        fprintf(file, "%d|%s|%s|%s|%s|%d|%d|%d\n", library[i].id, library[i].title, library[i].author,
                library[i].genre, library[i].isbn, library[i].year, library[i].copies, library[i].available);
    }

    fclose(file);
    printf("Data saved successfully.\n");
}

void loadDataFromFile() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No existing data found. Starting with an empty library.\n");
        return;
    }

    while (fscanf(file, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%d\n", &library[totalBooks].id, library[totalBooks].title,
                  library[totalBooks].author, library[totalBooks].genre, library[totalBooks].isbn,
                  &library[totalBooks].year, &library[totalBooks].copies, &library[totalBooks].available) != EOF) {
        totalBooks++;
        if (totalBooks >= MAX_BOOKS) break;
    }

    fclose(file);
    printf("Data loaded successfully.\n");
}

int isBookIdUnique(int id) {
    for (int i = 0; i < totalBooks; i++) {
        if (library[i].id == id) {
            return 0; // Not unique
        }
    }
    return 1; // Unique
}

void addBook() {
    if (totalBooks >= MAX_BOOKS) {
        printf("\nLibrary is full. Cannot add more books.\n");
        return;
    }

    printf("\nEnter Book Details:\n");
    printf("ID: ");
    int id;
    scanf("%d", &id);
    if (!isBookIdUnique(id)) {
        printf("Error: Book ID already exists.\n");
        return;
    }

    library[totalBooks].id = id;
    printf("Title: ");
    getchar(); // Clear buffer
    fgets(library[totalBooks].title, sizeof(library[totalBooks].title), stdin);
    strtok(library[totalBooks].title, "\n"); // Remove newline character
    printf("Author: ");
    fgets(library[totalBooks].author, sizeof(library[totalBooks].author), stdin);
    strtok(library[totalBooks].author, "\n");
    printf("Genre: ");
    fgets(library[totalBooks].genre, sizeof(library[totalBooks].genre), stdin);
    strtok(library[totalBooks].genre, "\n");
    printf("ISBN: ");
    fgets(library[totalBooks].isbn, sizeof(library[totalBooks].isbn), stdin);
    strtok(library[totalBooks].isbn, "\n");
    printf("Year: ");
    scanf("%d", &library[totalBooks].year);
    printf("Copies: ");
    scanf("%d", &library[totalBooks].copies);

    library[totalBooks].available = library[totalBooks].copies;
    totalBooks++;
    printf("\nBook added successfully!\n");
    saveDataToFile(); // Save data to file
}

void listBooks() {
    printf("\n*********** Book List ***********\n");
    printf("%-5s %-30s %-20s %-10s %-10s %-6s %-6s\n", "ID", "Title", "Author", "Genre", "ISBN", "Year", "Available");
    printf("--------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < totalBooks; i++) {
        printf("%-5d %-30s %-20s %-10s %-10s %-6d %-6d\n", library[i].id, library[i].title, library[i].author,
               library[i].genre, library[i].isbn, library[i].year, library[i].available);
    }
}

void searchBook() {
    char searchTitle[50];
    int found = 0;
    printf("\nEnter book title to search: ");
    getchar();
    fgets(searchTitle, sizeof(searchTitle), stdin);
    strtok(searchTitle, "\n");

    printf("\nSearch Results:\n");
    for (int i = 0; i < totalBooks; i++) {
        if (strstr(library[i].title, searchTitle)) {
            printf("ID: %d, Title: %s, Author: %s, Genre: %s, Available: %d\n",
                   library[i].id, library[i].title, library[i].author, library[i].genre, library[i].available);
            found = 1;
        }
    }
    if (!found) {
        printf("Book not found.\n");
    }
}

void borrowBook() {
    int id;
    printf("\nEnter Book ID to borrow: ");
    scanf("%d", &id);
    for (int i = 0; i < totalBooks; i++) {
        if (library[i].id == id) {
            if (library[i].available > 0) {
                library[i].available--;
                printf("\nYou have successfully borrowed '%s'.\n", library[i].title);
                saveDataToFile(); // Save data to file
            } else {
                printf("\nSorry, no copies available.\n");
            }
            return;
        }
    }
    printf("\nBook not found.\n");
}

void returnBook() {
    int id;
    printf("\nEnter Book ID to return: ");
    scanf("%d", &id);
    for (int i = 0; i < totalBooks; i++) {
        if (library[i].id == id) {
            if (library[i].available < library[i].copies) {
                library[i].available++;
                printf("\nYou have successfully returned '%s'.\n", library[i].title);
                saveDataToFile(); // Save data to file
            } else {
                printf("\nAll copies of this book are already returned.\n");
            }
            return;
        }
    }
    printf("\nBook not found.\n");
}

int main() {
    int choice;
    welcomeScreen();
    loadDataFromFile(); // Load data from file at startup

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                listBooks();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                borrowBook();
                break;
            case 5:
                returnBook();
                break;
            case 6:
                printf("\nExiting... Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
