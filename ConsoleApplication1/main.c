#include "Header.h"

int menu() {
    printf(" ------------------------ \n|  Amount of books: %d  | \n ------------------------ \n", amount);

    for (int i = 0; i < 40; i++) { printf("---"); }
    printf("\n\n");
    printf("\t\t\t\tPlease enter number to\n\n\t1. Print Book\n\t2. Add Book\n\t3. Delete Book\n\t4. Edit Book\n\t5. Short Table\n\t6. Borrow Book\n\t7. Return Book\n\n\t8. Push to Data.txt\n\t9. Load backup from backup.txt\n\t10. Sort MODE\n\n\t0. Exit\n\n>>>");
    int anw = 0;
    scanf_s("%d", &anw);
    return anw;
}

int main() {
    printf("Enter file name to use and save data from it. \n(1. Data.txt)\n>>>");
    scanf_s("%s", filename, 99);
    if (strcmp(filename, "1") == 0) {strncpy(filename, "Data.txt", sizeof(filename));}
    if (strcmp(filename, "Data.txt") != 0){printf("Invalid filename.");return;}
    int choice = -1;
    Init(&amount, filename); // ³ν³ηΰλ³ησΊ amount
    readDatabase(filename, &books, amount); // ³ν³φΰλ³ησΊ αΰησ
    while (choice != 0) {
        choice = menu();
        switch (choice) {
        case 0:
            system("cls"); return 0;
            break;
        case 1:
            PrintBook(books, amount); system("cls");
            break;
        case 2:
            AddBook(&books, &amount); system("cls"); printf("Successfully.\n");
            break;
        case 3:
            Delete(&books, &amount); system("cls"); printf("Successfully.\n");
            break;
        case 4:
            EditBook(&books, &amount); system("cls"); printf("Successfully.\n");
            break;
        case 5:
            PrintShortTable(books, amount); system("cls");
            break;
        case 6:
            BorrowBook(books, amount); system("cls"); printf("Successfully.\n");
            break;
        case 7:
            ReturnBook(books, amount); system("cls"); printf("Successfully.\n");
            break;
        case 8: // push new data to base
            ReWrite(filename, books, amount); system("cls"); printf("Successfully.\n");
            break;
        case 9: // Load backup
            readDatabase("backup.txt", &books, BACK); ReWrite(filename, books, BACK); amount = BACK; system("cls"); printf("Successfully.\n");
            break;
        case 10: //Sort
            SortMode();
            break;
        default:
            system("cls"); printf("Invalid choice.\n");
            break;
        }
    }
    return 0;
}
void SortMode() {
    system("cls");
    printf(" ------------------------ \n|  Amount of books: %d  | \n ------------------------ \n", amount);
    for (int i = 0; i < 40; i++) { printf("---"); }
    printf("\n");
    printf("\t\t\t\tPlease enter number to\n\n\t1. Sort By Author Name\n\t2. Sort By Author Surname\n\t3. Sort By Title\n\t4. Sort By ID\n\t0. Exit\n\n>>>");
    int anw = 0;
    scanf_s("%d", &anw);
    switch (anw) {
    case 0:
        system("cls"); return;
        break;
    case 1:
        SortByName(books, amount); PrintShortTable(books, amount); system("cls");
        break;
    case 2:
        SortBySurname(books, amount); PrintShortTable(books, amount); system("cls");
        break;
    case 3:
        SortByTitle(books, amount); PrintShortTable(books, amount); system("cls");
        break;
    case 4:
        SortById(books, amount); PrintShortTable(books, amount); system("cls");
        break;
    default:
        system("cls"); printf("Invalid choice.\n");
        break;
    }
}