#ifndef MEMORY
#define MEMORY

#include <stdio.h>
#include <stdlib.h>
//#include "main.c"

#include "../log.c"
#include "../generate_students.c"
typedef struct Node
{
    struct Student student;    
    struct Node* next;
}node;

node* newNode(struct Student newStudent);
void addNode(node** head, struct Student std);
void removeNode(node** head, int update);
void search(node** head, int id);
void update(node** head, int id, int hostelRoomNumber);
void printList(node* head);
void freeList(node** head);
struct Student searchFile(int id, int flag);
void updateFile(int id, int newRoomNumber);

// int main()
// {
//     // node* head = malloc(sizeof(node));
//     // head->student = std;
//     // head->next = NULL;
//     node *head = NULL;
//     for (int i = 1; i <= 6; i++)
//     {
//         struct Student std = generateStudent(i);
//         addNode(&head, std);
//     }
//     printList(head);
//     search(&head, 1);
//     //search(head, 15);
//     printList(head);
// }

// Search the file and return 1 if found and 0 if not
struct Student searchFile(int id, int flag)
{
    FILE* db = fopen("disk", "r");
    if (db == NULL) 
    {
        perror("Error opening database file");
        exit(0);
    }
    struct Student temp;
    while(fread(&temp, 1, sizeof(struct Student), db) && sizeof(temp) == sizeof(struct Student))
    {
        if (temp.id == id)
        {
            if (flag == 0)
            {
                printf("%d, %s, %s, %s, %d, %s, Year %d\n", temp.id, temp.name, 
                    temp.hostel, temp.course, temp.roomNumber, temp.dob, temp.yearOfStudy);
            }
            fclose(db);
            return temp;
        }
    }
    
    printf("NOT FOUND!!\n");
    fclose(db);
    temp.id = -1;
    return temp;
}

// Update the file.
void updateFile(int id, int newRoomNumber)
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
    if (db == NULL) 
    {
        perror("Error opening database file");
        exit(0);
    }

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


void addNode(node** head, struct Student std)
{
    node* newNode = malloc(sizeof(node));
    newNode->next = NULL;
    newNode->student = std;

    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    node* temp = *head;
    int count = 1;
    while(temp->next != NULL)
    {
        count++;
        temp = temp->next;
    }

    //printf("Count: %d\n", count);

    if (count >= 5)
        removeNode(head, 1);
    temp->next = newNode;
}

void removeNode(node** head, int update)
{
    struct Student std = (*head)->student;
    *head = (*head)->next;
    if (update == 10)
    {
        updateFile(std.id, std.roomNumber);
    }  
}

void printList(node* head)
{
    while(head != NULL)
    {
        printf("%d ", head->student.id);
        head = head->next;
    }
    printf("\n");
}

void search(node** head, int id)
{
    writeOne();
    node* temp = *head;
    int f = 0;
    while (temp != NULL)
    {
        if (temp->student.id == id)
        {
            f = 1;
            break;
        } 
        temp = temp->next;
    }

    if (f == 1)
    {
        struct Student tempStd = temp->student;
        printf("%d, %s, %s, %s, %d, %s, Year %d\n", tempStd.id, tempStd.name, 
                tempStd.hostel, tempStd.course, tempStd.roomNumber, tempStd.dob, tempStd.yearOfStudy);
    }
    else
    {
        writeTwo();
        struct Student tempStd = searchFile(id, 0);
        addNode(head, tempStd);
    }
    return;
}

void update(node** head, int id, int hostelRoomNumber)
{
    node* temp = *head;
    int f = 0;
    writeOne();
    while (temp != NULL)
    {
        if (temp->student.id == id)
        {
            f = 1;
            break;
        } 
        temp = temp->next;
    }

    if (f == 1)
    {
        temp->student.roomNumber = hostelRoomNumber;
    }
    else
    {
        writeTwo();
        struct Student tempStd = searchFile(id, 1);
        tempStd.roomNumber = hostelRoomNumber;
        addNode(head, tempStd);
    }
    return;
}

void freeList(node** head)
{
    if (head != NULL)
    {
        removeNode(head, 1);
    }
}
#endif