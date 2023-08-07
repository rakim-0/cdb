#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main()
{
    srand(time(NULL));
    FILE *queue_file = fopen("operation_queue.txt", "a");
    for (int i = 0; i < 20; i++)
    {
        if (queue_file == NULL) 
        {
            perror("Error opening file");
            return 1;
        }
        int student_id = rand() % 100 + 1;
        int operation_id = rand() % 4;
        
        
        
        if (operation_id == 2) 
        {
            int hostel_room = rand() % 100 + 101;
            fprintf(queue_file, "(random, %d, %d, %d, %ld)\n", student_id, operation_id, hostel_room, time(NULL));
        }

        else
        {
            fprintf(queue_file, "(random, %d, %d, %ld)\n", student_id, operation_id, time(NULL));
        }
        
        double random_interval = rand()%3 + 1;
        sleep(random_interval);
        fflush(queue_file);
    }
    fclose(queue_file);
    return 0;
}