#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIELD 150
#define BACK 10 // Amount of backup

typedef struct Book {
    int bookID; // позиція в шафі, id
    struct Authors {
        char name[FIELD];
        char surname[FIELD];
    } author;
    char title[FIELD];
    char genre[FIELD];
    int isHome;
    struct Borrow {
        char name[FIELD];
        char surname[FIELD];
    } borrower;
} Book;

static Book* books = NULL;
static int amount = 0;
const char filename[99];

void ReWrite(const char* filename, Book* books, int count);
void SortMode();
void SortById(Book* books, int count);
void SortByName(Book* books, int count);
void SortBySurname(Book* books, int count);

void Init(int* ptrAmount, const char* filen);
void readDatabase(const char* filename, Book** books, int count);
void SpacesToUnderscores(Book* books, int count);
void UnderscoresToSpaces(Book* books, int count);
void PrintShortTable(Book* books, int count);

void BorrowBook(Book* books, int count);
void Borrowing(Book* books, int count, int id);

void ReturnBook(Book* books, int count);
void Returning(Book* books, int count, int id);

void SortById(Book* books, int count);
void SortByTitle(Book* books, int count);
void SortByName(Book* books, int count);
void SortBySurname(Book* books, int count);

void PrintBook(Book* books, int count);
void AddBook(Book** books, int* count);
void EditBook(Book** books, int* count);
void Delete(Book** books, int* count);

void PrintByIndex(Book* books, int count);
void PrintById(Book* books, int count);
void PrintAll(Book* books, int count);
void PrintByName(Book* books, int count);
