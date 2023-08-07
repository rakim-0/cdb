#ifndef SERVER
#define SERVER

#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "main_memory.c"

// Functional Prototypes
void server();
void registerStudent();

void delete(int id);
void printFile(char* filename);

void server()
{
    node *head = NULL;
    char op_id = 0; // OPERATION ID, 0->registration, 1-> search, 2-> update, 3-> delete.
    int st_id = 0;
    while(1)
    {
        //fputs("> ", stdout);
        scanf("%c", &op_id);
        //op_id = '1';
        switch(op_id)
        {
            case '0':
                registerStudent();
                break;

            case '1':
                scanf("%d", &st_id);
                search(&head, st_id);
                break;

            case '2':
                scanf("%d", &st_id);
                int newRoomNumber = 0;
                scanf("%d\n", &newRoomNumber);
                update(&head, st_id, newRoomNumber);
                break;
                
            case'3':
                scanf("%d", &st_id);
                delete(st_id);
                //printFile("disk.tmp");
                break;
            case '4':
                printFile("disk");
                break;
        }
    }
}

// Register a user and update the file accordingly
// First get the last roll no. used and then use generate_student(id) to write it to the file.
// Use printFile to see if the file is updated.
void registerStudent()
{
    FILE* db = fopen("disk", "r+");
    if (db == NULL) 
    {
        perror("Error opening database file");
        exit(0);
    }
    struct Student temp;
    int id = 0;

    while(fread(&temp, 1, sizeof(struct Student), db) && sizeof(temp) == sizeof(struct Student))
    {
        id = temp.id;
    }

    struct Student s;
    id++;
    s = generateStudent(id);
    fwrite(&s, 1, sizeof(struct Student), db);
    fclose(db);
}

// Delete a line from the file 

void delete(int id)
{
    /* 
     *
     *  Implement the logic for deleting here.
     *
     *  First search file, but instead of returning a number, get the line number.
     *  Now make a new copy of the file and copy all the lines except that one.
     *  Delete the original file and rename the current file to disk.
     *
     *  refer https://www.w3resource.com/c-programming-exercises/file-handling/c-file-handling-exercise-8.php
     *
     */
    FILE* db = fopen("disk", "r");
    FILE* dbTemp = fopen("disk.tmp", "w");

    if (db == NULL) 
    {
        perror("Error opening database file");
        exit(0);
    }
    if (dbTemp == NULL) 
    {
        perror("Error opening database file");
        exit(0);
    }

    struct Student temp;
    while(fread(&temp, 1, sizeof(struct Student), db) && sizeof(temp) == sizeof(struct Student))
    {
        if (temp.id != id)
        {
            fwrite(&temp, 1, sizeof(struct Student), dbTemp);
        }
    }

    fclose(db);
    fclose(dbTemp);
    remove("disk");
    rename("disk.tmp", "disk");
    return;
}

void printFile(char* filename)
{
    FILE* db = fopen(filename, "r");
    if (db == NULL) 
    {
        perror("Error opening database file");
        exit(0);
    }
    struct Student temp;
    while(fread(&temp, 1, sizeof(struct Student), db) && sizeof(temp) == sizeof(struct Student))
    {
        printf("%d: %s\n", temp.id, temp.name);
    }
    fclose(db);
}
#endif