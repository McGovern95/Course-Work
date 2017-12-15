#define MAX_RECORDS 20
#define MAX_STRING 10

//structure definition
struct student{ 
   int number; 
   char first[MAX_STRING];    
   char last[MAX_STRING];  
   int age;  
   double gpa;
};
typedef struct student Student;

