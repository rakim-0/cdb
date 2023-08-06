#ifndef STUDENT
#define STUDENT

#define MAX_RECORDS 100
#define MAX_NAME_LEN 50
#define MAX_HOSTEL_LEN 50
#define MAX_COURSE_LEN 20

// Define a structure to hold student information   
// Cecily and Sindhu
struct Student 
{
    int id;
    char name[MAX_NAME_LEN];
    char hostel[MAX_HOSTEL_LEN];
    char course[MAX_COURSE_LEN];
    int roomNumber;
    char dob[13];
    int yearOfStudy;
};

#endif