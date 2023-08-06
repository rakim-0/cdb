#include <stdio.h>
#include "student.h"
#include <stdlib.h>

#ifndef SERVER
#define SERVER

// Functional Prototypes
void server();
int search(int id);
void update(int id);
void delete(int id);
void printFile(char* filename);

void server()
{
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
                break;

            case '1':
                scanf("%d", &st_id);
                search(st_id);
                break;

            case '2':
                scanf("%d", &st_id);
                update(st_id);
                break;
                
            case'3':
                scanf("%d", &st_id);
                delete(st_id);
                //printFile("disk.tmp");
                break;
        }
    }
}

// Search the file and return 1 if found and 0 if not
int search(int id)
{
    FILE* db = fopen("disk", "r");
    if (db == NULL) {
        perror("Error opening database file");
        exit(0);
    }
    struct Student temp;
    while(fread(&temp, 1, sizeof(struct Student), db) && sizeof(temp) == sizeof(struct Student))
    {
        if (temp.id == id)
        {
            printf("%d, %s, %s, %s, %d, %s, Year %d\n", temp.id, temp.name, 
                temp.hostel, temp.course, temp.roomNumber, temp.dob, temp.yearOfStudy);
                fclose(db);
            return 1;
        }
    }
    
    printf("NOT FOUND!!\n");
    fclose(db);
    return 0;
}

// Update the file.
void update(int id)
{
    /* 
     *
     *  Implement the logic for updating here.
     *  First search file, but instead of returning a number, get the file pointer.
     *  Use fseek to reposition the file pointer. The number of bytes will be similar.
     *  And write the new struct there.
     *
     */
    FILE* db = fopen("disk", "r+");
    if (db == NULL) {
        perror("Error opening database file");
        exit(0);
    }

    int newRoomNumber = 0;
    scanf("%d\n", &newRoomNumber);

    struct Student temp;

    while(fread(&temp, 1, sizeof(struct Student), db) && sizeof(temp) == sizeof(struct Student))
    {
        if (temp.id == id)
        {
            temp.roomNumber = newRoomNumber;
            fseek(db, -sizeof(struct Student), SEEK_CUR);
            fwrite(&temp, 1, sizeof(struct Student), db);
            fclose(db);
            return;
        }
    }

    fclose(db);
    return;
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
    FILE* db_temp = fopen("disk.tmp", "w");

    if (db == NULL) {
        perror("Error opening database file");
        exit(0);
    }
    if (db_temp == NULL) {
        perror("Error opening database file");
        exit(0);
    }

    struct Student temp;
    while(fread(&temp, 1, sizeof(struct Student), db) && sizeof(temp) == sizeof(struct Student))
    {
        if (temp.id != id)
        {
            fwrite(&temp, 1, sizeof(struct Student), db_temp);
        }
    }

    fclose(db);
    fclose(db_temp);
    remove("disk");
    rename("disk.tmp", "disk");
    return;
}

void printFile(char* filename)
{
    FILE* db = fopen(filename, "r");
    if (db == NULL) {
        perror("Error opening database file");
        exit(0);
    }
    struct Student temp;
    while(fread(&temp, 1, sizeof(struct Student), db) && sizeof(temp) == sizeof(struct Student))
    {
        printf("%d\n", temp.id);
        if (temp.id == 5)
        {
            break;
        }
    }
    fclose(db);
}
#endif