#include "Header.h"

void Init(int* ptrAmount, const char* filen) {
    FILE* file = fopen(filen, "r");
    while (fscanf(file, "Amount: %d", ptrAmount) == 1) {}
    fclose(file);
}

void readDatabase(const char* filename, Book** books, int count) { // Download db
    *books = (Book*)realloc(*books, count * sizeof(Book));
    count = count - 1; // count to last_index
    char buffer[256];
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }
    fgets(buffer, sizeof(buffer), file); // пропускаємо метадані amount
    for (int i = 0; i <= count; i++)
    {
        if (i > 0)
        {
            fgets(buffer, sizeof(buffer), file);
        }
        while (fscanf(file, "id: %d %99s %99s %99s %99s %d %99s %99s",
            &((*books)[i].bookID),
            (*books)[i].author.name,
            (*books)[i].author.surname,
            (*books)[i].title,
            (*books)[i].genre,
            &(*books)[i].isHome,
            (*books)[i].borrower.name,
            (*books)[i].borrower.surname) == 8) {
        }
    }
    fclose(file);
    UnderscoresToSpaces(*books, count);
}
void ReWrite(const char* filename, Book* books, int count) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }
    SpacesToUnderscores(books, count);
    char line[25];
    sprintf(line, "Amount: %d\n", count);
    fprintf(file, line);

    for (int i = 0; i < count; i++) {
        fprintf(file, "id: %d %s %s %s %s %d %s %s\n",
            books[i].bookID,
            books[i].author.name,
            books[i].author.surname,
            books[i].title,
            books[i].genre,
            books[i].isHome,
            books[i].borrower.name,
            books[i].borrower.surname);
    }
    fclose(file);
    UnderscoresToSpaces(books, count);
}

void PrintShortTable(Book* books, int count) {
    printf("\n\n");
    for (int i = 0; i < 149; i++) { printf("-"); }
    printf("\n| %10s | | %18s | | %20s | | %40s | | %22s || %11s |\n", "Book ID", "Surname", "Name", "Title", "Genre", "isBorrowed");
    for (int i = 0; i < count; i++) {
        printf("| %10d | ", books[i].bookID);
        printf("| %18s | | %20s | | %40s | ", books[i].author.surname, books[i].author.name, books[i].title);
        printf("| %22s |", books[i].genre);
        if (books[i].isHome == 0) { printf("| Available   |\n"); }
        if (books[i].isHome == 1) { printf("| Unavailable |\n"); }
    }
    for (int i = 0; i < 149; i++) { printf("-"); }
    printf("\n");
    system("pause");
}

void UnderscoresToSpaces(Book* books, int count) {
    for (int i = 0; i <= count; i++)
    {
        for (int j = 0; books[i].author.name[j] != '\0'; j++) {
            if (books[i].author.name[j] == '_') {
                books[i].author.name[j] = ' ';
            }
        }
        for (int j = 0; books[i].author.surname[j] != '\0'; j++) {
            if (books[i].author.surname[j] == '_') {
                books[i].author.surname[j] = ' ';
            }
        }
        for (int j = 0; books[i].title[j] != '\0'; j++) {
            if (books[i].title[j] == '_') {
                books[i].title[j] = ' ';
            }
        }
        for (int j = 0; books[i].genre[j] != '\0'; j++) {
            if (books[i].genre[j] == '_') {
                books[i].genre[j] = ' ';
            }
        }
    }
}
void SpacesToUnderscores(Book* books, int count) {
    for (int i = 0; i <= count; i++)
    {
        for (int j = 0; books[i].author.name[j] != '\0'; j++) {
            if (books[i].author.name[j] == ' ') {
                books[i].author.name[j] = '_';
            }
        }
        for (int j = 0; books[i].author.surname[j] != '\0'; j++) {
            if (books[i].author.surname[j] == ' ') {
                books[i].author.surname[j] = '_';
            }
        }
        for (int j = 0; books[i].title[j] != '\0'; j++) {
            if (books[i].title[j] == ' ') {
                books[i].title[j] = '_';
            }
        }
        for (int j = 0; books[i].genre[j] != '\0'; j++) {
            if (books[i].genre[j] == ' ') {
                books[i].genre[j] = '_';
            }
        }
    }
}

void Delete(Book** books, int* count) {
    int choice = -1, i, id = -1, n = 0;
    printf("\tYou can delete book \n\t1. by index\n\t2. by id\n\t3. all\n\n>>>");
    scanf_s("%d", &choice);

    // del by index
    if (choice == 1)
    {
        printf("\tEnter index to delete\n\n>>>");
        scanf_s("%d", &n);
        if (n > (*count) || n < 0)
        {
            printf("Invalid id\n");
            system("pause");
            return;
        }
        for (int j = n; j < (*count); j++) {
            (*books)[j - 1] = (*books)[j];
        }
        (*books) = (Book*)realloc(*books, (*count - 1) * sizeof(struct Book));
        (*count)--;
        return;
    }
    // del by id
    if (choice == 2) {
        printf("\tEnter id\n\n>>>");
        scanf_s("%d", &i);
        for (int j = 0; j < *count; j++)
        {
            if ((*books)[j].bookID == i)
            {
                id = j;
            }
        }
        if (id == -1)
        {
            printf("Invalid id\n");
            system("pause");
            return;
        }
        for (int j = id + 1; j < (*count); j++) {
            (*books)[j - 1] = (*books)[j];
        }
        (*books) = (Book*)realloc(*books, (*count - 1) * sizeof(struct Book));
        (*count)--;
        return;
    }
    if (choice == 3) { *books = NULL; *count = 0; return; } // del all
    printf("Invalid choice\n");
    system("pause");
    return;
}

void EditBook(Book** books, int* count) {
    int index = 0, id = -1, choice = 0;
    printf("\tChoose book for edit\n\t1. by index\n\t2. by id\n\n>>>");
    scanf_s("%d", &choice);
    if (choice != 1 && choice != 2) { printf("Invalid choose\n"); system("pause"); return; }
    if (choice == 1)
    {
        printf("\tEnter index\n\n>>>");
        scanf_s("%d", &index);
        if (index <= 0 || index > *count) { printf("Invalid index\n"); system("pause"); return; }
        else { index--; }
    }
    if (choice == 2)
    {
        printf("\tEnter id\n\n>>>");
        scanf_s("%d", &id);
        for (int j = 0; j < *count; j++) { if ((*books)[j].bookID == id) { id = j; } }
        if (id == -1) { printf("Invalid id\n"); system("pause"); return; }
    }
    system("cls");

    for (int i = 0; i < 40; i++) { printf("---"); }
    printf("\n");

    int option = 0;
    printf("\tChoose information for edit:\n\t1. Author Name\n\t2. Author Surname\n\t3. Title\n\t4. Genre\n\n>>>");
    scanf_s("%d", &option);
    if (option < 0 && option > 5) { printf("Invalid choice.\n"); system("pause"); return; }

    if (choice == 1)
    {
        switch (option) {
        case 1:
            printf("Enter book Author Name: ");
            scanf_s("%s", (*books)[index].author.name, FIELD);
            break;
        case 2:
            printf("Enter book Author Surname: ");
            scanf_s("%s", (*books)[index].author.surname, FIELD);
            break;
        case 3:
            printf("Enter title of a book: ");
            scanf_s("%s", (*books)[index].title, FIELD);
            break;
        case 4:
            printf("Enter book Genre: ");
            scanf_s("%s", (*books)[index].genre, FIELD);
            break;
        default:
            printf("Invalid choice.\n");
            break;
        }
    }
    if (choice == 2)
    {
        switch (option) {
        case 1:
            printf("Enter book Author Name: ");
            scanf_s("%s", (*books)[id].author.name, FIELD);
            break;
        case 2:
            printf("Enter book Author Surname: ");
            scanf_s("%s", (*books)[id].author.surname, FIELD);
            break;
        case 3:
            printf("Enter title of a book: ");
            scanf_s("%s", (*books)[id].title, FIELD);
            break;
        case 4:
            printf("Enter book Genre: ");
            scanf_s("%s", (*books)[id].genre, FIELD);
            break;
        default:
            printf("Invalid choice.\n");
            break;
        }
    }
}

void AddBook(Book** books, int* count) {
    *books = (Book*)realloc(*books, (*count + 1) * sizeof(Book));
    if (books == NULL) {
        printf("Memory allocation failed.");
        return;
    }
    int i = *count;
    int temp = *count;
    for (int j = 0; j < i; j++)
    {
        if ((*books)[j].bookID == temp + 1)
        {
            temp++;
            j = 0;
        }
    }
    (*books)[i].bookID = temp + 1;

    printf("Enter book Author Name: ");
    scanf_s("%s", (*books)[i].author.name, FIELD);
    printf("Enter book Author Surname: ");
    scanf_s("%s", (*books)[i].author.surname, FIELD);
    printf("Enter book Title: ");
    scanf_s("%s", (*books)[i].title, FIELD);
    printf("Genre: ");
    scanf_s("%s", (*books)[i].genre, FIELD);
    (*books)[i].isHome = 0;
    strcpy((*books)[i].borrower.name, "-");
    strcpy((*books)[i].borrower.surname, "-");
    (*count)++;
    system("pause");
}

void PrintBook(Book* books, int count) {
    int choice = -1;
    printf("\tYou can print book \n\t1. by index\n\t2. by id\n\t3. by name\n\t4. all\n\n>>>");
    scanf_s("%d", &choice);
    switch (choice) {
    case 1:
        PrintByIndex(books, count);
        break;
    case 2:
        PrintById(books, count);
        break;
    case 3:
        PrintByName(books, count);
        break;
    case 4:
        PrintAll(books, count);
        break;
    default:
        printf("Invalid choice.\n");
        break;
    }
}
void PrintByIndex(Book* books, int count) {
    int i = 0;
    printf("\tEnter index\n\n>>>");
    scanf_s("%d", &i);
    if (i > count || i <= 0)
    {
        printf("Invalid index\n");
        system("pause");
        return;
    }
    i--;

    printf("\n\nBook ID: %d\n", books[i].bookID);
    printf("Author full name: %s %s\n", books[i].author.name, books[i].author.surname);
    printf("Title: %s\n", books[i].title);
    printf("Genre: %s\n", books[i].genre);
    printf("Borrower Name: %s\n", books[i].borrower.name);
    printf("Borrower Surname: %s\n", books[i].borrower.surname);
    printf("Availability: %d\n", books[i].isHome);

    system("pause");
}
void PrintById(Book* books, int count) {
    int id = -1, i = 0;
    printf("\tEnter id\n\n>>>");
    scanf_s("%d", &i);

    for (int j = 0; j < count; j++)
    {
        if (books[j].bookID == i)
        {
            id = j;
        }
    }
    if (id == -1)
    {
        printf("Invalid id\n");
        system("pause");
        return;
    }
    i = id;

    printf("\n\nBook ID: %d\n", books[i].bookID);
    printf("Author full name: %s %s\n", books[i].author.name, books[i].author.surname);
    printf("Title: %s\n", books[i].title);
    printf("Genre: %s\n", books[i].genre);
    printf("Borrower Name: %s\n", books[i].borrower.name);
    printf("Borrower Surname: %s\n", books[i].borrower.surname);
    printf("Availability: %d\n", books[i].isHome);
    system("pause");
}
void PrintByName(Book* books, int count) {
    char name[FIELD] = "";
    int inx[99] = { 0 };
    inx[0] = -1;
    printf("\tEnter name\n\n>>>");
    scanf_s("%s", name, FIELD);
    int tt = 0;
    for (int j = 0; j < count; j++)
    {
        if (strncmp(books[j].author.name, name, strlen(name)) == 0)
        {
            inx[tt] = j;
            tt++;
        }
    }
    if (inx[0] == -1)
    {
        printf("No books found\n");
        system("pause");
        return;
    }
    int i = 0;
    while (i < tt)
    {
        printf("\n\nBook ID: %d\n", books[inx[i]].bookID);
        printf("Author full name: %s %s\n", books[inx[i]].author.name, books[inx[i]].author.surname);
        printf("Title: %s\n", books[inx[i]].title);
        printf("Genre: %s\n", books[inx[i]].genre);
        printf("Borrower Name: %s\n", books[inx[i]].borrower.name);
        printf("Borrower Surname: %s\n", books[inx[i]].borrower.surname);
        printf("Availability: %d\n", books[inx[i]].isHome);
        i++;
    }
    system("pause");
}
void PrintAll(Book* books, int count) {
    int i = 0;
    while (i < count)
    {
        printf("\n\nBook ID: %d\n", books[i].bookID);
        printf("Author full name: %s %s\n", books[i].author.name, books[i].author.surname);
        printf("Title: %s\n", books[i].title);
        printf("Genre: %s\n", books[i].genre);
        printf("Borrower Name: %s\n", books[i].borrower.name);
        printf("Borrower Surname: %s\n", books[i].borrower.surname);
        printf("Availability: %d\n", books[i].isHome);
        i++;
    }
    system("pause");
}
void BorrowBook(Book* books, int count) {
    printf("Please choose book to borrow: ");
    printf("\n| %9s | | %18s | | %20s | | %40s | | %22s || %11s |", "Book ID", "Surname", "Name", "Title", "Genre", "isBorrowed");
    for (int i = 0; i < count; i++)
    {
        printf("\n| id: %5d | ", books[i].bookID);
        printf("| %18s | | %20s | | %40s | ", books[i].author.surname, books[i].author.name, books[i].title);
        printf("| %22s |", books[i].genre);
        if (books[i].isHome == 0) { printf("| Available   |"); }
        if (books[i].isHome == 1) { printf("| Unavailable |"); }
    }
    int a = -1;
    printf("\nEnter id: ");
    scanf("%d", &a);
    if (a > count || a < 1){ printf("Invalid id\n"); system("pause"); return; }
    else {
        Borrowing(books, count, a);
    }
}
void Borrowing(Book *books, int count, int id) {
    int index = -1;
    for (int i = 0; i < count; i++)
    {
        if (id == books[i].bookID)
        {
            index = i;
        }
    }
    if (index == -1)
    {
        printf("\n|- Invalid id -|\n");
        system("pause");
        return;
    }
    if (books[index].isHome == 1)
    {
        printf("\n|- Book already borrowed, open the list and view the available options. -|\n");
        system("pause");
        return;
    }
    books[index].isHome = 1;
    printf("Enter Borrower Name: ");
    scanf_s("%s", books[index].borrower.name, FIELD);
    printf("Enter Borrower Surname: ");
    scanf_s("%s", books[index].borrower.surname, FIELD);
}
void ReturnBook(Book* books, int count) {
    printf("Please choose book to return: ");
    printf("\n| %9s | | %18s | | %20s | | %40s | | %22s || %11s |", "Book ID", "Surname", "Name", "Title", "Genre", "isBorrowed");
    for (int i = 0; i < count; i++)
    {
        printf("\n| id: %5d | ", books[i].bookID);
        printf("| %18s | | %20s | | %40s | ", books[i].author.surname, books[i].author.name, books[i].title);
        printf("| %22s |", books[i].genre);
        if (books[i].isHome == 0) { printf("| Available   |"); }
        if (books[i].isHome == 1) { printf("| Unavailable |"); }
    }
    int a = -1;
    printf("\nEnter id: ");
    scanf("%d", &a);
    if (a > count || a < 1) { printf("Invalid id\n"); system("pause"); return; }
    else {
        Returning(books, count, a);
    }
}
void Returning(Book* books, int count, int id) {
    int index = -1;
    for (int i = 0; i < count; i++)
    {
        if (id == books[i].bookID)
        {
            index = i;
        }
    }
    if (index == -1)
    {
        printf("\n|- Invalid id -|\n");
        system("pause");
        return;
    }
    if (books[index].isHome == 0)
    {
        printf("\n|- Book NO borrowed, open the list and view the available options. -|\n");
        system("pause");
        return;
    }
    books[index].isHome = 0;
    strcpy(books[index].borrower.name, "-");
    strcpy(books[index].borrower.surname, "-");
}

void SortById(Book* books, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (books[j].bookID > books[j + 1].bookID) {
                Book temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
}
void SortByName(Book* books, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(books[j].author.name, books[j + 1].author.name) > 0) {
                Book temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
}
void SortBySurname(Book* books, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(books[j].author.surname, books[j + 1].author.surname) > 0) {
                Book temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
}
void SortByTitle(Book* books, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(books[j].title, books[j + 1].title) > 0) {
                Book temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
}
