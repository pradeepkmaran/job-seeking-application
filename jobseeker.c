#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 100

struct job_offers {
    char companyName[N];
    char jobPost[N];
    int package; 
    char companyType[N];
    char jobType[N];
    int shiftTime;
    char location[N];
} ;

int count_job_offers(){
    char ch;
    FILE *fp = fopen("db//companyprofile.txt", "r");
    
    int count_comma=0;
    int job_count=0;
    int total_job_count=0;
    do{
        ch = fgetc(fp);
        if(ch == ','){
            count_comma+=1;
        }
        if(ch == '\n'){
            total_job_count += job_count;
            count_comma = 0;
            job_count=0;
        }
        if(count_comma==4 && ch!=','){
            job_count *= 10;
            job_count += ((int)ch)-48;
        }
    }while(ch != EOF);
    fclose(fp);
    return total_job_count;
}

int count_company_profile_lines(){
    FILE *fp = fopen("db//companyprofile.txt", "r");
    int line_count= 0;
    char ch = fgetc(fp);
    do{
        if(ch == '\n'){
            line_count++;
        }
        ch=fgetc(fp);
    }while(ch!=EOF);
    fclose(fp);
    return line_count;
}

int string_to_int(char str[]){
    int res = 0;
    for(int i=0;i<strlen(str);i++){
        res*=10;
        res+=((int)str[i])-48;
    }
    return res;
}

void read_company_data(struct job_offers job_offers[], int job_offers_count){
    char ch;
    FILE *fp = fopen("db//companyprofile.txt", "r");
    
    int indexline=0;
    for(int line = 0; line<count_company_profile_lines(); line++){
        char content[N][N]={{}};    
        int index=0;
        int i=0;
        do{
            ch = fgetc(fp);
            if(ch == ','){
                content[i][strlen(content[i])] = '\0';
                i++;
                index=0;
                continue;
            }
            if(ch == '\n'){
                break;
            }
            content[i][index++] = ch;
        }while(ch != '\n' && ch!=EOF);
        content[i][strlen(content[i])] = '\0';

        int content_length = i+1;
        int jobs_per_company = (content_length - 5)/4;
        
        /*  char companyName[N];
            char jobPost[N];
            int package; 
            char companyType[N];
            char jobType[N];
            int shiftTime;
            char location[N]; */

        for(int per_job = 0;per_job<jobs_per_company;per_job++){
            strcpy(job_offers[indexline].companyName, content[0]);
            strcpy(job_offers[indexline].companyType, content[2]);
            strcpy(job_offers[indexline].location, content[3]);
            strcpy(job_offers[indexline].jobPost, content[5+4*per_job]);
            job_offers[indexline].package = string_to_int(content[6+4*per_job]);
            job_offers[indexline].shiftTime = string_to_int(content[7+4*per_job]);
            strcpy(job_offers[indexline].jobType, content[8+4*per_job]);
            indexline++;
        }
    }
    fclose(fp);
}

struct seeker_requirements_struct{
    int company_count;
    char company_name[N][N];
    char job_position[N];
    int salary_expected;
    int shift_time;
    char job_location[N];
    char company_type[N];
    char job_type[N];
};

void get_seeker_requirements(struct seeker_requirements_struct seeker_req[], int importance[]){
    char choice;
    int importance_index=0;
    printf(" Rate the importance of requirement on 1-5.\n 0 for optional requirements.\n-1 to skip requirements.\n");

    printf("\nEnter y to search based on company name. n to search on other parameters: ");
    choice = getchar();

    if(choice == 'y'){
        printf("\nEnter number of companies to search: ");
        scanf("%d", &seeker_req[0].company_count);
        while(getchar()!='\n');

        for(int i=0;i<seeker_req[0].company_count;i++){
            printf("Enter name of company %d: ",i+1);
            fgets(seeker_req[0].company_name[i], N, stdin);
            seeker_req[0].company_name[i][strlen(seeker_req[0].company_name[i])-1]='\0';
        }
        printf("Enter the importance of requirement: ");
        scanf("%d", &importance[importance_index++]);
        while(getchar()!='\n');
    }
    else{
        while(getchar()!='\n');
        importance_index++;
    }
    printf("\nEnter job position: ");
    fgets(seeker_req[0].job_position, N, stdin);
    seeker_req[0].job_position[strlen(seeker_req[0].job_position)-1]='\0';
    printf("Enter the importance of requirement: ");
    scanf("%d", &importance[importance_index++]);

    printf("\nEnter the salary expected: ");
    scanf("%d", &seeker_req[0].salary_expected);
    printf("Enter the importance of requirement: ");
    scanf("%d", &importance[importance_index++]);

    printf("\nEnter shift timing \n1: 1st Shift: 6:00am to 4:00pm\n2: 2nd Shift: 2:00pm to 12:00am\n3: 3rd Shift: 10pm to 8:00am\n4: rotating shift\nEnter choice: ");
    scanf("%d", &seeker_req[0].shift_time);
    printf("Enter the importance of requirement: ");
    scanf("%d", &importance[importance_index++]);
    while(getchar()!='\n');

    printf("\nEnter preferred job location: ");
    fgets(seeker_req[0].job_location, N, stdin);
    seeker_req[0].job_location[strlen(seeker_req[0].job_location)-1]='\0';
    printf("Enter the importance of requirement: ");
    scanf("%d", &importance[importance_index++]);
    while(getchar()!='\n');

    printf("\nEnter type of company: ");
    fgets(seeker_req[0].company_type, N, stdin);
    seeker_req[0].company_type[strlen(seeker_req[0].company_type)-1]='\0';
    printf("Enter the importance of requirement: ");
    scanf("%d", &importance[importance_index++]);
    while(getchar()!='\n');

    printf("\nEnter type of job(wfh/offline): ");
    fgets(seeker_req[0].job_type, N, stdin);
    seeker_req[0].job_type[strlen(seeker_req[0].job_type)-1]='\0';
    printf("Enter the importance of requirement: ");
    scanf("%d", &importance[importance_index++]);
    while(getchar()!='\n');
}

void remove_offers(struct job_offers job_offers[], int job_offers_count, int pos){
    for (int i=pos; i<job_offers_count-1; i++){
        job_offers[i] = job_offers[i+1];
    }
    strcpy(job_offers[job_offers_count-1].companyName,"");
    strcpy(job_offers[job_offers_count-1].companyType,"");
    strcpy(job_offers[job_offers_count-1].jobPost,"");
    strcpy(job_offers[job_offers_count-1].jobType,"");
    strcpy(job_offers[job_offers_count-1].location,"");
    job_offers[job_offers_count-1].shiftTime=0;
    job_offers[job_offers_count-1].package=0;
}

void check_compulsory(struct seeker_requirements_struct seeker_req[], struct job_offers job_offers[], int *job_offers_count, int importance[]){
    for(int i=0;i<7;i++){
        if(importance[i]>0){
            whilej:
            int j=0;
            while(j<*job_offers_count){
                if(i==0 && seeker_req[0].company_count!=0){ //checking if companies satisfy by its name
                    int company_match_count=0;
                    for(int company=0;company<seeker_req[0].company_count;company++){
                        if(stricmp(seeker_req[0].company_name[company], job_offers[j].companyName) == 0){
                            company_match_count++;
                        }
                    }
                    if(company_match_count==0){
                        remove_offers(job_offers, (*job_offers_count)--, j);
                        goto whilej;
                    }
                }
                else if(i==1){ //checking if companies satisfy by job_position
                    if(stricmp(seeker_req[0].job_position, job_offers[j].jobPost) != 0){
                        remove_offers(job_offers, (*job_offers_count)--, j);
                        goto whilej;
                    }
                }
                else if(i==2){ //checking if companies satisfy by salary expected
                    if(seeker_req[0].salary_expected > job_offers[j].package){
                        remove_offers(job_offers, (*job_offers_count)--, j);
                        goto whilej;
                    }
                }
                else if(i==3){ //checking if companies satisfy by shift timing
                    if(seeker_req[0].shift_time != job_offers[j].shiftTime){
                        remove_offers(job_offers, (*job_offers_count)--, j);
                        goto whilej;
                    }
                }
                else if(i==4){ //checking if companies satisfy by job location
                    if(stricmp(seeker_req[0].job_location, job_offers[j].location) != 0){
                        remove_offers(job_offers, (*job_offers_count)--, j);
                        goto whilej;
                    }
                }
                else if(i==5){ //checking if companies satisfy by type of company
                    if(stricmp(seeker_req[0].company_type, job_offers[j].companyType) != 0){
                        remove_offers(job_offers, (*job_offers_count)--, j);
                        goto whilej;
                    }
                }
                else if(i==6){ //checking if companies satisfy by type of job
                    if(stricmp(seeker_req[0].job_type, job_offers[j].jobType) != 0){
                        remove_offers(job_offers, (*job_offers_count)--, j);
                        goto whilej;
                    }
                }
                j++;
            }
        }
    }
}

float calculate_company_score(struct seeker_requirements_struct seeker_req, struct job_offers job_offer, int importance[]){
    float score=0;

    if(stricmp(seeker_req.job_position, job_offer.jobPost) == 0){
        if(importance[1]>0){ 
            score += importance[1];
        }
        else if(importance[1]==0){ 
            score += 0.5;
        }
    }
    if(seeker_req.salary_expected <= job_offer.package){
        if(importance[2]>0){ 
            score += importance[2];
        }
        else if(importance[2]==0){ 
            score += 0.5;
        }
    }
    if(seeker_req.shift_time == job_offer.shiftTime){
        if(importance[3]>0){ 
            score += importance[3];
        }
        else if(importance[3]==0){ 
            score += 0.2;
        }
    }
    if(stricmp(seeker_req.job_location, job_offer.location) == 0){
        if(importance[4]>0){ 
            score += importance[4];
        }
        else if(importance[4]==0){ 
            score += 0.3;
        }
    }
    if(stricmp(seeker_req.company_type, job_offer.companyType) == 0){
        if(importance[5]>0){ 
            score += importance[5];
        }
        else if(importance[5]==0){ 
            score += 0.1;
        }
    }
    if(stricmp(seeker_req.job_type, job_offer.jobType) == 0){
        if(importance[6]>0){ 
            score += importance[6];
        }
        else if(importance[6]==0){ 
            score += 0.1;
        }
    }

    return score;
}
void sort_company_score(struct job_offers job_offers[], float company_scores[], int job_offers_count)
{
    float temp;
    struct job_offers temp1;
    for(int i=0;i<job_offers_count;i++){
        for(int j=0;j<job_offers_count-1;j++)
        {
            if(company_scores[j+1]>company_scores[j])
            {
                temp=company_scores[j+1];
                company_scores[j+1]=company_scores[j];
                company_scores[j]=temp;
                temp1=job_offers[j+1];
                job_offers[j+1]=job_offers[j];
                job_offers[j]=temp1;
            }
        }
    }
}
/* void job_seeker_menu(){ */
int main(){
    int job_offers_count = count_job_offers();
    int importance[7]={0,0,0,0,0,0,0};

    struct job_offers job_offers[job_offers_count];
    struct seeker_requirements_struct seeker_req[1];

    get_seeker_requirements(seeker_req, importance);
    read_company_data(job_offers, job_offers_count);
    check_compulsory(seeker_req, job_offers, &job_offers_count, importance);
    
    float company_scores[job_offers_count];
    for(int i=0;i<job_offers_count;i++){
        company_scores[i] = calculate_company_score(seeker_req[0], job_offers[i], importance);
    }

    sort_company_score(job_offers,company_scores,job_offers_count);

    if(job_offers_count>7){
        for(int i=0;i<7;i++){
            printf("%.2f %s %s %s %s %d %d %s\n",company_scores[i], job_offers[i].companyName,job_offers[i].companyType,job_offers[i].location,job_offers[i].jobPost,job_offers[i].package,job_offers[i].shiftTime,job_offers[i].jobType);
        }
    }
    else{
        for(int i=0;i<job_offers_count;i++){
            printf("%.2f %s %s %s %s %d %d %s\n",company_scores[i], job_offers[i].companyName,job_offers[i].companyType,job_offers[i].location,job_offers[i].jobPost,job_offers[i].package,job_offers[i].shiftTime,job_offers[i].jobType);
        }
    }

    
}