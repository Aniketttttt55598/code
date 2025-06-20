#include <stdio.h>                        // this contain input output function
#include <stdlib.h>                        // allow memory function like malloc and free
#include <string.h>                       // this contain the string functions(strcpy,strcmp)
typedef struct Book {                     // decare structure
    int bookID;
    char title[100];
    char author[100];
    struct Book* next;                   // point to the next pointer
    struct Book* prev;
} Book;
Book* createBook(int bookID, char title[], char author[]) {      //set the book id,title,and authorallocate memory for new book
    Book* newBook = (Book*)malloc(sizeof(Book));                //allocate memory for new book
    newBook->bookID = bookID;
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->next = NULL;                                // initialize the pointer to null
    newBook->prev = NULL;
    return newBook;                                      // return the new book
}
void addBook(Book** head, int bookID, char title[], char author[]) {  //add a new book to end of doubly linked list
    Book* newBook = createBook(bookID, title, author);
    if (*head == NULL) {                               //if the list is empty then new book becomes the first node
        *head = newBook;
    } else {                                           // it finds the last book and links the new book to it
        Book* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newBook;
        newBook->prev = temp;
    }
}
void displayBooks(Book* head) {                           //display function goes through the list and print book details
    if (head == NULL) {                                   // if it is empty show a message
        printf("No books in the library.\n");
        return;
    }
    Book* temp = head;
    while (temp != NULL) {
        printf("Book ID: %d\n", temp->bookID);
        printf("Title: %s\n", temp->title);
        printf("Author: %s\n", temp->author);
        printf("----------------------------\n");
        temp = temp->next;
    }
}
void searchBookByTitle(Book* head, char title[]) {                 //here is a search book function which search the book by its title
    if (head == NULL) {
        printf("No books in the library.\n");
        return;
    }
    Book* temp = head;
    int found = 0;
    while (temp != NULL) {                                           // if it is therre adjusts the links of previous and next node
        if (strcmp(temp->title, title) == 0) {                       //comparision used 
            printf("Book found:\n");
            printf("Book ID: %d\n", temp->bookID);
            printf("Title: %s\n", temp->title);
            printf("Author: %s\n", temp->author);
            found = 1;
            break;                                                   //used to exit from the loop
        }
        temp = temp->next;
    }
    if (!found) {
        printf("Book with title '%s' not found.\n", title);
    }
}
void deleteBook(Book** head, int bookID) {                                         // we are making delete book function here with return type void here we find book by id 
    if (*head == NULL) {                                                           // checking the head pointer have null or any book 
        printf("No books to delete.\n");                                              // if there is no book  
        return;
    }
    Book* temp = *head;                                                           //If it is delete it and adjusts the links of previous and next nodes.
    while (temp != NULL && temp->bookID != bookID) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Book with ID %d not found.\n", bookID);                              // if not found or list is empty,shows an appropriate message
        return;
    }
    if (temp == *head) {
        *head = temp->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
    } else {
        temp->prev->next = temp->next;
        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        }
    }
    free(temp);
    printf("Book with ID %d has been deleted.\n", bookID);
}
int main() {
    Book* library = NULL;       //library is the pointer to the head of book list               // variable and member declarartion
    int choice, bookID;
    char title[100], author[100];
    while (1) {                                                                   // Menu driven starts 
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book by Title\n");
        printf("4. Delete Book by ID\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();                                                                   // Clear newline from buffer
        switch (choice) {
            case 1:                                                    // used to add book
                printf("Enter Book ID: ");
                scanf("%d", &bookID);
                getchar();                                            // Clear newline
                printf("Enter Book Title: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0';                   // length of the initial segment of a string that does not contain any characters from another string.
                printf("Enter Author Name: ");
                fgets(author, sizeof(author), stdin);                         //Used for reading a line of text input, including spaces.
                author[strcspn(author, "\n")] = '\0';
                addBook(&library, bookID, title, author);
                printf("Book added successfully!\n");
                break;
            case 2:                                                    // display book
                displayBooks(library);
                break;
            case 3:                                               // search book by title
                printf("Enter Book Title to Search: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0';
                searchBookByTitle(library, title);  // ? Correct function call
                break;
            case 4:                                                            // delete book by id
                printf("Enter Book ID to Delete: ");
                scanf("%d", &bookID);
                deleteBook(&library, bookID);
                break;
            case 5:                                                                     // exit
                printf("Exiting Library Management System. Goodbye!\n");   
                exit(0);
            default:                                                          // wrong choice
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
