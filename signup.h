#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define N 100
#define newline printf("\n");
#define clearBuffer while(getchar()!='\n');

struct job_seeker {
    char name[N];
    int age; 
    char gender;
    int marital_status;
    char degree[N][N];
    char institution[N][N]; 
    float cgpa[N];
    char job_title[N][N];
    char company[N][N];
    int experience[N];
    char skills[N][N];
    char certifications[N][N];
};
struct employer {
    char companyName[N];
    int companyAge; 
    char companyType[N];
    char jobPost[N][N];
    int package[N]; 
    char jobType[N][N];
    int shiftTime[N];
    char location[N];
};

int usernameCheckSignup(char username[]){
    FILE* usernamedb;
    usernamedb= fopen("db\\usernamedb.txt","r");
    int i=0;
    int num = 0;
    char ch;
    char usernames[N][N];
    while(1){
        ch = fgetc(usernamedb);
        if(ch == EOF){
            break;
        }
        if(ch == '\n'){
            usernames[num][i] = '\0';
            ++num;
            i=0;
        }
        else{
            usernames[num][i++] = ch;
        }
    }
    fclose(usernamedb);
    /* Username check */
    for(int i=0;i<num;i++){   
        int count=0;
        if(strlen(username) == strlen(usernames[i])-1){
            for(int j=0;j<strlen(usernames[i])-1;j++){   
                if(username[j] == usernames[i][j+1]){
                    ++count;
                }
                if(count == strlen(usernames[i])-1){
                    return 0;
                }
            }
        }      
    }
    return 1;
}

void employerSignup(){
    char companyName[N];
    int companyAge; 
    char companyType[N];
    char jobPost[N][N];
    int package[N]; 
    int shiftTime[N];
    char jobType[N][N];
    char location[N];
    char username[N];
    char pw[N];
    char confirmpw[N];

    struct employer emp;
    int check=0;

    /* getting username */
    int usernameCheckResult = 0;
    do{
        if(!check){
            printf("Enter username: ");
        }
        else{
            printf("Username already exists. Type another: ");
        }
        fgets(username, N, stdin);
        username[strlen(username)-1]='\0';
        check = 1;
        usernameCheckResult = usernameCheckSignup(username);
    }while(!usernameCheckResult);

    /* Getting pw */
    check=0;
    do{
        if(check){
            printf("YOUR PASSWORDS DOESNT MATCH. REENTER PASSWORD.\n");
        }
        printf("Enter your password: ");
        fgets(pw, N, stdin);
        pw[strlen(pw)-1]='\0';

        printf("Confirm password: ");
        fgets(confirmpw, N, stdin);
        confirmpw[strlen(confirmpw)-1]='\0';
        check = 1;

    }while(strcmp(pw, confirmpw));

    /* Enter company name */
    printf("Enter company name: ");
    fgets(companyName, N, stdin);
    companyName[strlen(companyName)-1]='\0';

    /* Getting Age */
    check=0;
    do{
        if(!check){
            printf("Enter company age: ");
        }
        else{
            printf("Enter valid age: ");
        }
        scanf("%d", &companyAge);
        check=1;
    }while(companyAge<=0);
    clearBuffer;

    /* Getting company type */
    printf("Enter company type : ");
    fgets(companyType, N, stdin);
    companyType[strlen(companyType)-1]='\0';
    
    /* Enter company name */
    printf("Enter company location : ");
    fgets(location, N, stdin);
    location[strlen(location)-1]='\0';

    /* Getting jobpost, package for the job and shift timing */
    int jobCount;
    printf("Enter number of job posts available: ");
    scanf("%d", &jobCount);
    clearBuffer;
    newline;

    for(int i=0;i<jobCount;i++){
        printf("Enter job post %d: ", i+1);
        fgets(jobPost[i], N, stdin);
        jobPost[i][strlen(jobPost[i])-1]='\0';
        
        printf("Enter salary: ");
        scanf("%d",&package[i]);
        clearBuffer;

        printf("Enter shift timing \n1: 1st Shift: 6:00am to 4:00pm\n2: 2nd Shift: 2:00pm to 12:00am\n3: 3rd Shift: 10pm to 8:00am\n4: rotating shift\nEnter choice: ");
        scanf("%d", &shiftTime[i]);
        clearBuffer;

        printf("Enter job type (wfh/offline): ");
        fgets(jobType[i], N, stdin);
        jobType[i][strlen(jobType[i])-1]='\0';
    }

    /* Assigning Values */
    strcpy(emp.companyName, companyName);
    emp.companyAge = companyAge;
    strcpy(emp.companyType, companyType);
    for(int i=0;i<jobCount;i++){
        strcpy(emp.jobPost[i], jobPost[i]);
    }
    for(int i=0;i<jobCount;i++){
        emp.package[i] = package[i];
    }
    for(int i=0;i<jobCount;i++){
        emp.shiftTime[i] = shiftTime[i];
    }
    for(int i=0;i<jobCount;i++){
        strcpy(emp.jobType[i], jobType[i]);
    }
    strcpy(emp.location, location);

    /* Storing username and pw */
    FILE* usernamedb;
    usernamedb  = fopen("db//usernamedb.txt", "a");
    fprintf(usernamedb, "2%s\n", username);
    fclose(usernamedb);

    FILE* pwdb;
    pwdb  = fopen("db//pwdb.txt", "a");
    fprintf(pwdb, "%s\n", pw);
    fclose(pwdb);

    /* Writing in txt file */
    FILE* companyprofile;
    companyprofile = fopen("db//companyprofile.txt", "a");
    fprintf(companyprofile,"%s,%d,%s,", emp.companyName, emp.companyAge, emp.companyType);
    fprintf(companyprofile, "%s,", emp.location);
    fprintf(companyprofile, "%d,", jobCount);
    for(int i=0;i<jobCount;i++){
        if(i == jobCount-1){
            fprintf(companyprofile,"%s,%d,%d,%s", emp.jobPost[i], emp.package[i], emp.shiftTime[i], emp.jobType[i]);
            break;
        }
        fprintf(companyprofile,"%s,%d,%d,%s,", emp.jobPost[i], emp.package[i], emp.shiftTime[i], emp.jobType[i]);
    }
    fprintf(companyprofile, "\n");
    fclose(companyprofile);
}

void jobseekerSignup(){   
    /* Variables for data */
    char username[N];
    char pw[N];
    char confirmpw[N];
    char name[N];
    int age; 
    char gender;
    int marital_status;
    char degree[N][N];
    char institution[N][N]; 
    float cgpa[N];
    char company[N][N];
    int experience[N];
    char job_title[N][N];
    char skills[N*N]={};
    char certifications[N*N]={};
    struct job_seeker seeker;
    int check=0;
    
    /* getting username */
    int usernameCheckResult = 0;
    do{
        if(!check){
            printf("Enter username: ");
        }
        else{
            printf("Username already exists. Type another: ");
        }
        fgets(username, N, stdin);
        username[strlen(username)-1]='\0';
        check = 1;
        usernameCheckResult = usernameCheckSignup(username);
    }while(!usernameCheckResult);

    /* Getting pw */
    check=0;
    do{
        if(check){
            printf("YOUR PASSWORDS DOESNT MATCH. REENTER PASSWORD.\n");
        }
        printf("Enter your password: ");
        fgets(pw, N, stdin);
        pw[strlen(pw)-1]='\0';

        printf("Confirm password: ");
        fgets(confirmpw, N, stdin);
        confirmpw[strlen(confirmpw)-1]='\0';
        check = 1;

    }while(strcmp(pw, confirmpw));

    /* Getting name */
    printf("Enter your name: ");
    fgets(name, N, stdin);
    name[strlen(name)-1]='\0';

    /* Getting Age */
    check=0;
    do{
        if(!check){
            printf("Enter your age: ");
        }
        else{
            printf("Enter valid age: ");
        }
        scanf("%d", &age);
        check=1;
    }while(age<=0);
    clearBuffer;

    /* Getting Gender */
    check = 0;
    do{
        if(!check){
            printf("Enter your Gender (m/f): ");
        }
        else{
            printf("Enter valid choice: ");
        }
        gender = getchar();
        clearBuffer;
        check = 1;
    }while(gender!='m' && gender!='f');

    /* Enter marital status */
    check = 0;
    char ch;
    do{
        if(!check){
            printf("Enter your marital status (y/n): ");
        }
        else{
            printf("Enter valid choice: ");
        }
        ch = getchar();
        if(ch=='y'){
            marital_status=1;
        }
        else{
            marital_status=0;
        }
        clearBuffer;
    }while(ch != 'y' && ch != 'n');
    
    /* Getting degree and institution and cgpa */
    int degreeCount;
    printf("Enter number of degrees completed: ");
    scanf("%d", &degreeCount);
    clearBuffer;
    newline;

    for(int i=0;i<degreeCount;i++){
        printf("Enter degree %d: ", i+1);
        fgets(degree[i], N, stdin);
        degree[i][strlen(degree[i])-1]='\0';
        
        printf("Enter the institution of study for degree %d: ", i+1);
        fgets(institution[i], N, stdin);
        institution[i][strlen(institution[i])-1]='\0';

        check=0;
        do{
            if(!check){
                printf("Enter your CGPA for degree %d: ", i+1);
            }
            else{
                printf("Enter valid CGPA for degree %d: ", i+1);
            }
            scanf("%f", &cgpa[i]);
            check=1;
        }while((cgpa[i]<0.0 )|| (cgpa[i]>10.0));
        clearBuffer;
        newline;
    }    

    char choice;
    printf("Do you have previous job experience? (y/n): ");
    choice = getchar();
    clearBuffer;
    int companyCount;
    if(choice == 'y'){
        printf("Enter the number of companies in which you worked for: ");
        
        scanf("%d", &companyCount);
        clearBuffer;
        newline;

        for(int i=0;i<companyCount;i++){
            printf("Enter the name of company %d: ", i+1);
            fgets(company[i], N, stdin);
            company[i][strlen(company[i])-1] = '\0';

            printf("Enter the years of experience in company %d: ", i+1);
            scanf("%d", &experience[i]);
            clearBuffer;

            printf("Enter the job position in company %d: ", i+1);
            fgets(job_title[i], N, stdin);
            job_title[i][strlen(job_title[i])-1] = '\0';
            newline;
        }
    }

    /* Getting skills */
    printf("Enter skills(comma separated): ");
    fgets(skills, N*N, stdin);
    skills[strlen(skills)-1]='\0';

    /* Getting certifications */
    printf("Enter certifications name(comma separated): ");
    fgets(certifications, N*N, stdin);
    certifications[strlen(certifications)-1]='\0';
    
    /* Assigning values to structure */
    strcpy(seeker.name, name);
    seeker.age = age;
    seeker.gender = gender;
    seeker.marital_status = marital_status;

        /* Assigning degrees */
    for(int i=0;i<N;i++){
        strcpy(seeker.degree[i], degree[i]);
    }
        /* Assigning institutions */
    for(int i=0;i<N;i++){
        strcpy(seeker.institution[i], institution[i]);
    }
        /* Assigning cgpa */
    for(int i=0;i<N;i++){
        seeker.cgpa[i] = cgpa[i];
    }  
        /* Assigning companies */
   for(int i=0;i<companyCount;i++){
        strcpy(seeker.company[i], company[i]);
    }  
        /* Assigning experience*/
   for(int i=0;i<companyCount;i++){
        seeker.experience[i] = experience[i];
    } 
        /* Assigning job_title */
   for(int i=0;i<companyCount;i++){
        strcpy(seeker.job_title[i], job_title[i]);
    }  
        /* Assigning skills */
    int indi = 0, indj = 0;
    int skillsCount=0;
    for(int i=0;i<strlen(skills);i++){
        if(skills[i] == ','){
            seeker.skills[indi][indj++] = '\0';
            indi++;
            indj=0;
        }
        else{
            seeker.skills[indi][indj++] = skills[i];
        }
    }
    seeker.skills[indi][indj] = '\0';
    skillsCount = indi+1;
        /* Assigning certifications */
    indi = 0, indj = 0;
    int certCount=0;
    for(int i=0;i<strlen(certifications);i++){
        if(certifications[i] == ','){
            seeker.certifications[indi][indj++] = '\0';
            indi++;
            indj=0;
        }
        else{
            seeker.certifications[indi][indj++] = certifications[i];
        }
    }
    seeker.certifications[indi][indj] = '\0';
    certCount=indi+1;

    /* Storing username and pw  */
    FILE* usernamedb;
    usernamedb  = fopen("db//usernamedb.txt", "a");
    fprintf(usernamedb, "1%s\n", username);
    fclose(usernamedb);

    FILE* pwdb;
    pwdb  = fopen("db//pwdb.txt", "a");
    fprintf(pwdb, "%s\n", pw);
    fclose(pwdb);

    /* Writing in txt file */
    FILE* seekerprofile;
    seekerprofile = fopen("db//seekerprofile.txt", "a");
    fprintf(seekerprofile,"%s,%d,%c,%d,%d,", seeker.name, seeker.age, seeker.gender, seeker.marital_status, degreeCount);
    for(int i=0;i<degreeCount;i++){
        fprintf(seekerprofile,"%s,%s,%.2f,", seeker.degree[i], seeker.institution[i], seeker.cgpa[i]);
    }
    fprintf(seekerprofile, "%d,",companyCount);
    for(int i=0;i<companyCount;i++){
        fprintf(seekerprofile,"%s,%d,%s,", seeker.company[i], seeker.experience[i], seeker.job_title[i]);
    }
    fprintf(seekerprofile, "%d,",skillsCount);
    for(int i=0;i<N;i++){
        if(seeker.skills[i][0]!='\0'){
            fprintf(seekerprofile, "%s|", seeker.skills[i]);
        }
    }
    fprintf(seekerprofile, ",%d,", certCount);
    for(int i=0;i<N;i++){
        if(seeker.certifications[i][0]!='\0'){
            fprintf(seekerprofile, "%s|", seeker.certifications[i]);
        }
    }
    fprintf(seekerprofile, "\n");
    fclose(seekerprofile);
}

void signup()
{
    int choice;
    printf("1 - JobSeeker.\n2 - Employer.\nEnter your choice: ");
    scanf("%d", &choice);
    clearBuffer;
    switch (choice)
    {
        case(1):
            jobseekerSignup();
            break;
        case(2):
            employerSignup();
            break;
        default:
            printf("Invalid Choice");
    }
}
