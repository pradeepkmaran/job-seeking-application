#include<stdio.h>
#include<stdlib.h>
#include"login.h"
#include"signup.h"

void remove_seeker_details(int removeline1, int removeline2){
    FILE *fileptr1, *fileptr2;
    char ch;
    int temp = 1;
    fileptr1 = fopen("db\\seekerprofile.txt", "r");
    fileptr2 = fopen("db\\replica.txt", "w");
    while (1)
    {
        ch = getc(fileptr1);
        if(ch == EOF){
            break;
        }
        if (ch == '\n'){
            ++temp;
        }
        if (temp != removeline1){
            if(removeline1 == 1 && temp == 2 && ch == '\n'){
                continue;
            }
            putc(ch, fileptr2);
        }
    }
    fclose(fileptr1);
    fclose(fileptr2);
    remove("db\\seekerprofile.txt");
    rename("db\\replica.txt", "db\\seekerprofile.txt");
    
    temp = 1;
    fileptr1 = fopen("db\\usernamedb.txt", "r");
    fileptr2 = fopen("db\\replica.txt", "w");
    while (1)
    {
        ch = getc(fileptr1);
        if(ch == EOF){
            break;
        }
        if (ch == '\n'){
            ++temp;
        }
        if (temp != removeline2){
            if(removeline2 == 1 && temp == 2 && ch == '\n'){
                continue;
            }
            putc(ch, fileptr2);
        }
    }
    fclose(fileptr1);
    fclose(fileptr2);
    remove("db\\usernamedb.txt");
    rename("db\\replica.txt", "db\\usernamedb.txt");

    temp = 1;
    fileptr1 = fopen("db\\pwdb.txt", "r");
    fileptr2 = fopen("db\\replica.txt", "w");
    while (1)
    {
        ch = getc(fileptr1);
        if(ch == EOF){
            break;
        }
        if (ch == '\n'){
            ++temp;
        }
        if (temp != removeline2){
            if(removeline2 == 1 && temp == 2 && ch == '\n'){
                continue;
            }
            putc(ch, fileptr2);
        }
    }
    fclose(fileptr1);
    fclose(fileptr2);
    remove("db\\pwdb.txt");
    rename("db\\replica.txt", "db\\pwdb.txt");
}

void remove_company_details(int removeline1, int removeline2){
    FILE *fileptr1, *fileptr2;
    char ch;
    int temp = 1;
    fileptr1 = fopen("db\\companyprofile.txt", "r");
    fileptr2 = fopen("db\\replica.txt", "w");
    while (1)
    {
        ch = getc(fileptr1);
        if(ch == EOF){
            break;
        }
        if (ch == '\n'){
            ++temp;
        }
        if (temp != removeline1){
            if(removeline1 == 1 && temp == 2 && ch == '\n'){
                continue;
            }
            putc(ch, fileptr2);
        }
    }
    fclose(fileptr1);
    fclose(fileptr2);
    remove("db\\companyprofile.txt");
    rename("db\\replica.txt", "db\\companyprofile.txt");
    
    temp = 1;
    fileptr1 = fopen("db\\usernamedb.txt", "r");
    fileptr2 = fopen("db\\replica.txt", "w");
    while (1)
    {
        ch = getc(fileptr1);
        if(ch == EOF){
            break;
        }
        if (ch == '\n'){
            ++temp;
        }
        if (temp != removeline2){
            if(removeline2 == 1 && temp == 2 && ch == '\n'){
                continue;
            }
            putc(ch, fileptr2);
        }
    }
    fclose(fileptr1);
    fclose(fileptr2);
    remove("db\\usernamedb.txt");
    rename("db\\replica.txt", "db\\usernamedb.txt");

    temp = 1;
    fileptr1 = fopen("db\\pwdb.txt", "r");
    fileptr2 = fopen("db\\replica.txt", "w");
    while (1)
    {
        ch = getc(fileptr1);
        if(ch == EOF){
            break;
        }
        if (ch == '\n'){
            ++temp;
        }
        if (temp != removeline2){
            if(removeline2 == 1 && temp == 2 && ch == '\n'){
                continue;
            }
            putc(ch, fileptr2);
        }
    }
    fclose(fileptr1);
    fclose(fileptr2);
    remove("db\\pwdb.txt");
    rename("db\\replica.txt", "db\\pwdb.txt");
}

void jobseeker_signup_for_modify(char username[], char pw[]){
    /* Variables for data */
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

    clearBuffer;
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

void company_signup_for_modify(char username[], char pw[]){
    char companyName[N];
    int companyAge; 
    char companyType[N];
    char jobPost[N][N];
    int package[N]; 
    int shiftTime[N];
    char jobType[N][N];
    char location[N];

    struct employer emp;
    int check=0;

    clearBuffer;
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

int modify(){
    FILE *usernamedb, *pwdb;
    char ch;

    char username[N];
    char pw[N];
    char usernames[N][N];
    char pwarr[N][N];
    
    printf("\nEnter Username: ");
    scanf("%s", username);

    /* storing usernames in 'usernames' */
    usernamedb= fopen("db\\usernamedb.txt","r");
    int i=0;
    int num = 0;
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
    int usernameline = usernameCheck(usernames, username, num);
    if(!usernameline){
        return -1;
    }
    /* Storing passwords in 'pwarr' */
    pwdb= fopen("db\\pwdb.txt","r");
    i=0;
    num = 0;
    while(1){
        ch = fgetc(pwdb);
        if(ch == EOF){
            break;
        }
        if(ch == '\n'){
            pwarr[num][i] = '\0';
            ++num;
            i=0;
        }
        else{
            pwarr[num][i++] = ch;
        }
    }
    num++;
    
    fclose(usernamedb);
    fclose(pwdb);

    /* checking if username is in db and password matches the username*/
    int count=0;
    for(int i=0;i<usernameline;i++){
        if(usernames[i][0] == usernames[usernameline-1][0]){
            count++;
        }
    }

    int wrongpwcount = 0;
    while(wrongpwcount < 3){
        printf("Enter PW: ");
        scanf("%s", pw);
        int res = pwcheck(usernames, pwarr, pw, num, usernameline-1);
        if(res){
            if(res == 1){
                remove_seeker_details(count, usernameline);
                jobseeker_signup_for_modify(username, pw);
            }
            else{
                remove_company_details(count, usernameline);
                company_signup_for_modify(username, pw);
            }
        }
        else{
            wrongpwcount++;
        }
        if(wrongpwcount == 1){
            printf("WRONG PW. 2 MORE CHANCES.\n\n");
            continue;
        }
        if(wrongpwcount == 2){
            printf("WRONG PW. 1 MORE CHANCE.\n\n");
            continue;
        }
        return 0;
    }
}

int main(){
    int res = modify();
}