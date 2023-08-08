#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "tuple.h"

unsigned int randval()
{
    unsigned int randval;
    FILE *f;
    f = fopen("/dev/random", "r");
    fread(&randval, sizeof(randval), 1, f);
    fclose(f);
    return randval;
}

int main()
{
    srand(time(NULL));
    FILE *queueFile = fopen("operation_queue.txt", "a");
    FILE *waitingQueue = fopen("waiting_queue", "a");
    if (queueFile == NULL) 
    {
        perror("Error opening file");
        return 1;
    }
    if (waitingQueue == NULL) 
    {
        perror("Error opening file");
        return 1;
    }

    for (int i = 0; i < 50; i++)
    {
        
        int studentId = randval() % 100 + 1;
        int operationId = randval() % 4;

        tuple temp = {};
        temp.stdID = studentId;
        temp.opID = operationId;
        strcpy(temp.type, "regular");
        if (operationId == 0)
        {
            fwrite(&temp, 1, sizeof(tuple), waitingQueue);
            fprintf(queueFile, "(regular, %d, %ld)\n", operationId, time(NULL));
        }
        else if (operationId == 2) 
        {
            int hostelRoom = randval() % 100 + 101;
            temp.roomNo = hostelRoom;
            fwrite(&temp, 1, sizeof(tuple), waitingQueue);
            fprintf(queueFile, "(regular, %d, %d, %d, %ld)\n", operationId, studentId, hostelRoom, time(NULL));
        }

        else
        {
            fwrite(&temp, 1, sizeof(tuple), waitingQueue);
            fprintf(queueFile, "(regular, %d, %d, %ld)\n", operationId, studentId, time(NULL));
        }
        
        fflush(queueFile);
        fflush(waitingQueue);
        sleep(1);
    }
    fclose(queueFile);
    fclose(waitingQueue);
    return 0;
}