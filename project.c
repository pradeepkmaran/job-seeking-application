#include <stdio.h>
#include <string.h>

#define MAX_JOB_SEEKERS 1000
#define MAX_AVAILABLE_JOBS 1000

// Define the fields of S (Job-seekers)
struct job_seeker {
    char name[50];
    int age;
    char gender[10];
    char degree[50];
    char institution[50];
    float gpa;
    char job_title[50];
    char company[50];
    int experience;
    char skills[100];
    char certifications[100];
    int salary;
    char night_shifts[10];
};

// Define the fields of A (Available jobs)
struct available_job {
    char job_title[50];
    char job_description[500];
    char responsibilities[500];
    int experience;
    char degree[50];
    char institution[50];
    float gpa;
    char certifications[100];
};

struct score{
    int job_title;
    int experience;
    int gpa;
    int degree;
    int skills;
    int institution;
    int certification;
    int total;
};

int main() {
    int num_job_seekers, num_available_jobs;
    struct job_seeker job_seekers[MAX_JOB_SEEKERS];
    struct available_job available_jobs[MAX_AVAILABLE_JOBS];
    
    // Code to populate the job_seekers and available_jobs arrays
    
    // Code to apply the constraints and calculate the recommendation percentage
    
    return 0;
}
