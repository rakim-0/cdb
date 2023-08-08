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

    for (int i = 0; i < 20; i++)
    {
        
        int studentId = randval() % 100 + 1;
        int operationId = randval() % 4;

        tuple temp = {};
        temp.stdID = studentId;
        temp.opID = operationId;
        strcpy(temp.type, "random");
        if (operationId == 0)
        {
            fwrite(&temp, 1, sizeof(tuple), waitingQueue);
            fprintf(queueFile, "(random, %d, %ld)\n", operationId, time(NULL));
        }
        else if (operationId == 2) 
        {
            int hostelRoom = randval() % 100 + 101;
            temp.roomNo = hostelRoom;
            fwrite(&temp, 1, sizeof(tuple), waitingQueue);
            fprintf(queueFile, "(random, %d, %d, %d, %ld)\n", operationId, studentId, hostelRoom, time(NULL));
        }

        else
        {
            fwrite(&temp, 1, sizeof(tuple), waitingQueue);
            fprintf(queueFile, "(random, %d, %d, %ld)\n", operationId, studentId, time(NULL));
        }        
        double randomInterval = randval()%3 + 1;
        fflush(queueFile);
        fflush(waitingQueue);
        sleep(randomInterval);
    }
    fclose(queueFile);
    fclose(waitingQueue);
    return 0;
}