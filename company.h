#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define N 100
struct company_req{
    int age[2];
    char gender;
    int degree_count;
    char degrees[N][N];
    int institutions_count;
    char institutions[N][N];
    float cgpa;
    int experience_companies_count;
    char experience_companies[N][N];
    int experience_years;
    int experience_post_count;
    char experience_post[N][N];
    int skills_count;
    char skills[N][N];
    int certifications_count;
    char certifications[N][N];
};

struct seeker_details{
    char name[N];
    int age;
    char gender;
    int marital_status;
    int degree_count;
    char degrees[N][N];
    char institution[N][N];
    float cgpa[N];
    int experience_count;
    char experience_companies[N][N];
    int experience_years[N];
    int total_experience_years;
    char experience_post[N][N];
    int skills_count;
    char skills[N][N];
    int certifications_count;
    char certifications[N][N];
};

int split_input(char raw[], char out[][N]){
    int j=0, c=0;
    for(int i=0;i<strlen(raw);i++){
        if(raw[i] != '|'){
            out[j][c++] = raw[i];
        }
        else if(raw[i] == '|'){
            out[j][c] = '\0';
            j++;
            c=0;
        }
    }
    return j;
}

int count_seeker_profile_lines(){
    FILE *fp = fopen("db//seekerprofile.txt", "r");
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

int string_to_int_company(char str[]){
    int res = 0;
    for(int i=0;i<strlen(str);i++){
        res*=10;
        res+=((int)str[i])-48;
    }
    return res;
}

float string_to_float(char str[]){
    float res = 0;
    float dec = 0;
    int mark=0;
    int count=0;
    for(int i=0;i<strlen(str);i++){
        if(str[i] == '.'){
            mark=1;
            continue;
        }
        if(!mark){
            res*=10;
            res+=((int)str[i])-48;
        }
        else{
            count++;
            dec += ((((int)str[i])-48)/(pow(10, count)));
        }
    }
    return res+dec;
}

void read_seeker_data(struct seeker_details seekers[], int seeker_count){
    char ch;
    FILE *fp = fopen("db//seekerprofile.txt", "r");
    
    for(int line = 0; line<count_seeker_profile_lines(); line++){
        char content[N][N]={{}};    
        int index=0;
        int x=0;
        do{
            ch = fgetc(fp);
            if(ch == ','){
                content[x][strlen(content[x])] = '\0';
                x++;
                index=0;
                continue;
            }
            if(ch == '\n'){
                break;
            }
            content[x][index++] = ch;
        }while(ch != '\n' && ch!=EOF); 
        content[x][strlen(content[x])] = '\0';

        int content_length =x+1;
        for(int per_seeker = 0;per_seeker<seeker_count;per_seeker++){
            strcpy(seekers[line].name, content[0]);
            seekers[line].age = string_to_int_company(content[1]);
            seekers[line].gender = content[2][0];
            seekers[line].marital_status = string_to_int_company(content[3]);
            seekers[line].degree_count = string_to_int_company(content[4]);
            for(int i=0;i<seekers[line].degree_count;i++){
                strcpy(seekers[line].degrees[i], content[5+(i*3)]);
                strcpy(seekers[line].institution[i], content[6+(i*3)]);
                seekers[line].cgpa[i] = string_to_float(content[7+(i*3)]);
            }
            int exppos = 4+(seekers[line].degree_count*3)+1;
            int total_experience_years= 0;
            seekers[line].experience_count = string_to_int_company(content[4+(seekers[line].degree_count*3)+1]);
            for(int i=0;i<seekers[line].experience_count;i++){
                strcpy(seekers[line].experience_companies[i], content[exppos + (i*3) + 1]);
                seekers[line].experience_years[i] = string_to_int_company(content[exppos + (i*3) + 2]);
                total_experience_years+=seekers[line].experience_years[i];
                strcpy(seekers[line].experience_post[i], content[exppos + (i*3) + 3]);
            }
            seekers[line].total_experience_years = total_experience_years;
            int skillpos =  exppos + (seekers[line].experience_count*3)+1;
            seekers[line].skills_count = string_to_int_company(content[skillpos]);
            char rawskills[N];
            strcpy(rawskills, content[skillpos+1]);
            int j=0,c=0;
            for(int i=0;rawskills[i]!='\0';i++){
                if(rawskills[i] != '|'){
                    seekers[line].skills[j][c++] = rawskills[i];
                }
                else{
                    j++;
                    c=0;
                }
            }
            seekers[line].certifications_count = string_to_int_company(content[(seekers[line].degree_count*3)+(seekers[line].experience_count*3)+8]);
            char rawcertifications[N];
            strcpy(rawcertifications, content[(seekers[line].degree_count*3)+(seekers[line].experience_count*3)+9]);
            j=0; c=0;
            for(int i=0;rawcertifications[i]!='\0';i++){
                if(rawcertifications[i] != '|'){
                    seekers[line].certifications[j][c++] = rawcertifications[i];
                }
                else{
                    j++;
                    c=0;
                }
            }
        }
    }
    fclose(fp);
}

void get_company_requirements(struct company_req req[], int credits[], int importance[10][N]){
    char choice;
    int credit_index=0;
    printf(" Enter how important the following fields are.\n 1-5 for compulsory fields.\n 0 for optional fields.\n-1 to skip fields.\n");
    printf("Age of the seeker: ");
    scanf("%d", &credits[credit_index++]);
    printf("Gender of the seeker: ");
    scanf("%d", &credits[credit_index++]);
    printf("Degrees completed: ");
    scanf("%d", &credits[credit_index++]);
    printf("Institutions of graduation: ");
    scanf("%d", &credits[credit_index++]);
    printf("CGPA of the degrees: ");
    scanf("%d", &credits[credit_index++]);
    printf("Company of experience: ");
    scanf("%d", &credits[credit_index++]);
    printf("Number of years of experience: ");
    scanf("%d", &credits[credit_index++]);
    printf("Previous job positions: ");
    scanf("%d", &credits[credit_index++]);
    printf("Skills: ");
    scanf("%d", &credits[credit_index++]);
    printf("Certifications: ");
    scanf("%d", &credits[credit_index++]);

    credit_index = 0;
    int point_index=0;
    if(credits[credit_index] != -1){
        printf("\nEnter the Range of age (21-35): ");
        scanf("%d-%d", &req[0].age[0],&req[0].age[1]);
        while(getchar()!='\n');
    }
    else{
        req[0].age[0] = 0;
        req[0].age[1] = 65;
    }
    credit_index++;
    if(credits[credit_index] != -1){
        printf("\nEnter the gender(m/f): ");
        req[0].gender = getchar();
        while(getchar()!='\n');
    }
    credit_index++;
    if(credits[credit_index] != -1){
        char rawstring[N];
        printf("Enter degrees (BE|ME|MTech|..): ");
        fgets(rawstring, N, stdin);
        rawstring[strlen(rawstring)-1]='|';
        rawstring[strlen(rawstring)]='\0';
        req[0].degree_count = split_input(rawstring, req[0].degrees);
        printf("Enter points for the degrees entered(1-10):\n");
        for(int i=0;i<req[0].degree_count;i++){
            printf("%s - ", req[0].degrees[i]);
            scanf("%d", &importance[credit_index][point_index++]);
        }
        while(getchar()!='\n');
    }
    else{
        req[0].degree_count = 0;
    }
    credit_index++;
    point_index=0;
    if(credits[credit_index] != -1){
        char rawstring[N];
        printf("Enter institutions (SSN College of Engineering|Shiv Nadar University|..): ");
        fgets(rawstring, N, stdin);
        rawstring[strlen(rawstring)-1]='|';
        rawstring[strlen(rawstring)]='\0';
        req[0].institutions_count = split_input(rawstring, req[0].institutions);
        printf("Enter points for the Institutions entered(1-10):\n");
        for(int i=0;i<req[0].institutions_count;i++){
            printf("%s - ", req[0].institutions[i]);
            scanf("%d", &importance[credit_index][point_index++]);
        }
        while(getchar()!='\n');
    }
    else{
        req[0].institutions_count = 0;
    }
    point_index=0;
    credit_index++;
    if(credits[credit_index] != -1){
        printf("Enter minimum CGPA: ");
        scanf("%.2f", &req[0].cgpa);
        while(getchar()!='\n');
    }
    else{
        req[0].cgpa = 0;
    }
    credit_index++;
    if(credits[credit_index] != -1){
        char rawstring[N];
        printf("Enter the preferred previous companies of work(Apple|Google|Microsoft|..): ");
        fgets(rawstring, N, stdin);
        rawstring[strlen(rawstring)-1]='|';
        rawstring[strlen(rawstring)]='\0';
        req[0].experience_companies_count = split_input(rawstring, req[0].experience_companies);
        printf("Enter points for the company entered(1-10):\n");
        for(int i=0;i<req[0].experience_companies_count;i++){
            printf("%s - ", req[0].experience_companies[i]);
            scanf("%d", &importance[credit_index][point_index++]);
        }
        while(getchar()!='\n');
    }
    else{
        req[0].experience_companies_count = 0;
    }
    credit_index++;
    point_index=0;
    if(credits[credit_index] != -1){
        printf("Enter minimum number of years of experience: ");
        scanf("%d", &req[0].experience_years);
        while(getchar()!='\n');
    }
    else{
        req[0].experience_years = 0;
    }
    credit_index++;
    if(credits[credit_index] != -1){
        char rawstring[N];
        printf("Enter the preferred previous job posts of work(Android Developer|Project Manager|..): ");
        fgets(rawstring, N, stdin);
        rawstring[strlen(rawstring)-1]='|';
        rawstring[strlen(rawstring)]='\0';
        req[0].experience_post_count = split_input(rawstring, req[0].experience_post);
        printf("Enter points for the post entered(1-10):\n");
        for(int i=0;i<req[0].experience_post_count;i++){
            printf("%s - ", req[0].experience_post[i]);
            scanf("%d", &importance[credit_index][point_index++]);
        }
        while(getchar()!='\n');
    }
    else{
        req[0].experience_post_count = 0;
    }
    credit_index++;
    point_index=0;
    if(credits[credit_index] != -1){
        char rawstring[N];
        printf("Enter the preferred skills(c++|Java|..): ");
        fgets(rawstring, N, stdin);
        rawstring[strlen(rawstring)-1]='|';
        rawstring[strlen(rawstring)]='\0';
        req[0].skills_count = split_input(rawstring, req[0].skills);
        printf("Enter points for the skills entered(1-10):\n");
        for(int i=0;i<req[0].skills_count;i++){
            printf("%s - ", req[0].skills[i]);
            scanf("%d", &importance[credit_index][point_index++]);
        }
        while(getchar()!='\n');
    }
    else{
        req[0].skills_count = 0;
    }
    point_index=0;
    credit_index++;
    if(credits[credit_index] != -1){
        char rawstring[N];
        printf("Enter the preferred certifications(Intro to Python|Intro to Java|..): ");
        fgets(rawstring, N, stdin);
        rawstring[strlen(rawstring)-1]='|';
        rawstring[strlen(rawstring)]='\0';
        req[0].certifications_count = split_input(rawstring, req[0].certifications);
        printf("Enter points for the certifications entered(1-10):\n");
        for(int i=0;i<req[0].certifications_count;i++){
            printf("%s - ", req[0].certifications[i]);
            scanf("%d", &importance[credit_index][point_index++]);
        }
        while(getchar()!='\n');
    }
    else{
        req[0].certifications_count = 0;
    }
    point_index=0;
    credit_index=0;
}

void remove_seeker(struct seeker_details seekers[], int seeker_count, int pos){
    for(int i=pos; i<seeker_count-1; i++){
        seekers[i] = seekers[i+1];
    }
    /* strcpy(seekers[seeker_count-1].name,'\0');
    seekers[seeker_count-1].age=0;
    seekers[seeker_count-1].gender='\0';
    seekers[seeker_count-1].marital_status=0;
    for(int i=0; i<seekers[seeker_count-1].degree_count;i++){
        strcpy(seekers[seeker_count-1].degrees[i],"\0");
        strcpy(seekers[seeker_count-1].institution[i],"\0");
        seekers[seeker_count-1].cgpa[i] = 0;
    }
    seekers[seeker_count-1].degree_count=0;
    for(int i=0; i<seekers[seeker_count-1].experience_count;i++){
        strcpy(seekers[seeker_count-1].experience_companies[i],"\0");
        strcpy(seekers[seeker_count-1].experience_post[i],"\0");
        seekers[seeker_count-1].experience_years[i] = 0;
    }
    seekers[seeker_count-1].experience_count=0;
    seekers[seeker_count-1].total_experience_years=0;
    for(int i=0; i<seekers[seeker_count-1].skills_count;i++){
        strcpy(seekers[seeker_count-1].skills[i],"\0");
    }
    seekers[seeker_count-1].skills_count=0;
    for(int i=0; i<seekers[seeker_count-1].certifications_count;i++){
        strcpy(seekers[seeker_count-1].certifications[i],"\0");
    }
    seekers[seeker_count-1].certifications_count=0; */
}

void check_company_compulsory(struct company_req req[], struct seeker_details seekers[], int credits[10], int *seeker_count){
    int i=-1;
    while(i++<(*seeker_count)-1){
        if(credits[0]>0){
            if(seekers[i].age<req[0].age[0] || seekers[i].age>req[0].age[1]){
                remove_seeker(seekers, (*seeker_count)--, i);
                continue;
            }
        }
        if(credits[1]>0){
            if(seekers[i].gender != req[0].gender){
                remove_seeker(seekers, (*seeker_count)--, i);
                continue;
            }
        }
        if(credits[2]>0){
            int flag=0;
            for(int j=0;j<req[0].degree_count;j++){
                for(int k=0;k<seekers[i].degree_count;k++){
                    if(!(stricmp(req[0].degrees[j], seekers[i].degrees[k]))){
                        flag++;
                        goto credit3;
                    }
                }
            }
            if(!flag){
                remove_seeker(seekers, (*seeker_count)--, i);
                continue;
            }          
        }
        credit3: 
        if(credits[3]>0){
            int flag=0;
            for(int j=0;j<req[0].institutions_count;j++){
                for(int k=0;k<seekers[i].degree_count;k++){
                    if(!(stricmp(req[0].institutions[j],seekers[i].institution[k]))){
                        flag++;
                        goto credit4;
                    }
                }
            }
            if(!flag){
                remove_seeker(seekers, (*seeker_count)--, i);
                continue;
            }          
        }
        credit4:
        if(credits[4]>0){
            for(int j=0;j<seekers[i].degree_count;j++){
                if(seekers[i].cgpa[j] < req[0].cgpa){
                    remove_seeker(seekers, (*seeker_count)--, i);
                    continue;
                }
            }
            
        } 
        if(credits[5]>0){
            int flag=0;
            for(int j=0;j<req[0].experience_companies_count;j++){
                for(int k=0;k<seekers[i].experience_count;k++){
                    if(!(stricmp(req[0].experience_companies[j], seekers[i].experience_companies[k]))){
                        flag++;
                        goto credit6;
                    }
                }
            }
            if(!flag){
                remove_seeker(seekers, (*seeker_count)--, i);
                continue;
            }
        }
        credit6:
        if(credits[6]>0){
            if(req[0].experience_years < seekers[i].total_experience_years){
                remove_seeker(seekers, (*seeker_count)--, i);
                continue;
            }
        }
        if(credits[7]>0){
            int flag=0;
            for(int j=0;j<req[0].experience_post_count;j++){
                for(int k=0;k<seekers[i].experience_count;k++){
                    if(!(stricmp(req[0].experience_post[j],seekers[i].experience_post[k]))){
                        flag++;
                        goto credit8;
                    }
                }
            }
            if(!flag){
                remove_seeker(seekers, (*seeker_count)--, i);
                continue;
            }  
        }
        credit8:
        if(credits[8]>0){
            int flag=0;
            for(int j=0;j<req[0].skills_count;j++){
                for(int k=0;k<seekers[i].skills_count;k++){
                    if(!(stricmp(req[0].skills[j], seekers[i].skills[k]))){
                        flag++;
                        goto credit9;
                    }
                }
            }
            if(!flag){
                remove_seeker(seekers, (*seeker_count)--, i);
                continue;
            }          
        }
        credit9:
        if(credits[9]>0){
            int flag=0;
            for(int j=0;j<req[0].certifications_count;j++){
                for(int k=0;k<seekers[i].certifications_count;k++){
                    if(!(stricmp(req[0].certifications[j], seekers[i].certifications[k]))){
                        flag++;
                        goto endloop;
                    }
                }
            }
            if(!flag){
                remove_seeker(seekers, (*seeker_count)--, i);
                continue;
            }          
        }
        endloop:
    }
}

float calculate_seeker_score(struct company_req req, struct seeker_details seeker, int credits[10], int importance[10][N]){
    float score=0;

    if(seeker.age>=req.age[0] && seeker.age<=req.age[1]){
        if(credits[0]>0){ 
            score += credits[0];
        }
        else if(credits[0]==0){ 
            score += 0.2;
        }
    }
    if(seeker.gender == req.gender){
        if(credits[1]>0){ 
            score += credits[1];
        }
        else if(credits[2]==0){ 
            score += 0.2;
        }
    }
    if(credits[3]>0){
        for(int i=0;i<seeker.degree_count;i++){
            for(int j=0;j<req.degree_count;j++){
                if(stricmp(seeker.degrees[i], req.degrees[j]) == 0){
                    score += importance[3][j]*credits[3]*0.2/seeker.degree_count;
                }
            }
        }
    }
    else if(credits[3]==0){
        for(int i=0;i<seeker.degree_count;i++){
            for(int j=0;j<req.degree_count;j++){
                if(stricmp(seeker.degrees[i], req.degrees[j]) == 0){
                    score += importance[3][j]*0.1/seeker.degree_count ;
                }
            }
        }
    }
    if(credits[4]>0){
        for(int i=0;i<seeker.degree_count;i++){
            for(int j=0;j<req.institutions_count;j++){
                if(stricmp(seeker.institution[i], req.institutions[j]) == 0){
                    score += importance[4][j]*credits[4]*0.2/seeker.degree_count;
                }
            }
        }
    }
    else if(credits[4]==0){
        for(int i=0;i<seeker.degree_count;i++){
            for(int j=0;j<req.institutions_count;j++){
                if(stricmp(seeker.institution[i], req.institutions[j]) == 0){
                    score += importance[4][j]*0.1/seeker.degree_count ;
                }
            }
        }
    }
    if(credits[5]>0){
        for(int i=0;i<seeker.degree_count;i++){
            if(seeker.cgpa[i] >= req.cgpa){
                score+= credits[5]*0.15/seeker.degree_count;
            }
        }
    }
    else if(credits[5]==0){
        for(int i=0;i<seeker.degree_count;i++){
            if(seeker.cgpa[i] >= req.cgpa){
                score += 0.2/seeker.degree_count;
            }
        }
    }
    if(credits[6]>0){
        for(int i=0;i<seeker.experience_count;i++){
            for(int j=0;j<req.experience_companies_count;j++){
                if(stricmp(seeker.experience_companies[i], req.experience_companies[j]) == 0){
                    score += importance[6][j]*credits[6]*0.2/seeker.experience_count;
                }
            }
        }
    }
    else if(credits[6]==0){
        for(int i=0;i<seeker.experience_count;i++){
            for(int j=0;j<req.experience_companies_count;j++){
                if(stricmp(seeker.experience_companies[i], req.experience_companies[j]) == 0){
                    score += importance[6][j]*0.05/seeker.experience_count ;
                }
            }
        }
    }
    if(credits[7]>0){
        if(seeker.total_experience_years >= req.experience_years){
            score+= credits[7]*0.2/seeker.experience_count;
        }
    }
    else if(credits[7]==0){
        if(seeker.total_experience_years >= req.experience_years){
            score+= 0.1/seeker.experience_count;
        }
    }
    if(credits[7]>0){
        for(int i=0;i<seeker.experience_count;i++){
            for(int j=0;j<req.experience_post_count;j++){
                if(stricmp(seeker.experience_post[i], req.experience_post[j]) == 0){
                    score += importance[7][j]*credits[7]*0.2/seeker.experience_count;
                }
            }
        }
    }
    else if(credits[7]==0){
        for(int i=0;i<seeker.experience_count;i++){
            for(int j=0;j<req.experience_post_count;j++){
                if(stricmp(seeker.experience_post[i], req.experience_post[j]) == 0){
                    score += importance[7][j]*0.05/seeker.experience_count ;
                }
            }
        }
    }
    if(credits[8]>0){
        for(int i=0;i<seeker.skills_count;i++){
            for(int j=0;j<req.skills_count;j++){
                if(stricmp(seeker.skills[i], req.skills[j]) == 0){
                    score += importance[8][j]*credits[8]*0.2/seeker.skills_count;
                }
            }
        }
    }
    else if(credits[8]==0){
        for(int i=0;i<seeker.skills_count;i++){
            for(int j=0;j<req.skills_count;j++){
                if(stricmp(seeker.skills[i], req.skills[j]) == 0){
                    score += importance[8][j]*0.1/seeker.skills_count ;
                }
            }
        }
    }
    if(credits[9]>0){
        for(int i=0;i<seeker.certifications_count;i++){
            for(int j=0;j<req.certifications_count;j++){
                if(stricmp(seeker.certifications[i], req.certifications[j]) == 0){
                    score += importance[9][j]*credits[9]*0.2/seeker.certifications_count;
                }
            }
        }
    }
    else if(credits[9]==0){
        for(int i=0;i<seeker.certifications_count;i++){
            for(int j=0;j<req.certifications_count;j++){
                if(stricmp(seeker.certifications[i], req.certifications[j]) == 0){
                    score += importance[9][j]*0.1/seeker.certifications_count ;
                }
            }
        }
    }
    return score;
}

void sort_seeker_scores(struct seeker_details seekers[], float seekers_score[], int seekers_count)
{
    float temp;
    struct seeker_details temp1;
    for(int i=0;i<seekers_count;i++){
        for(int j=0;j<seekers_count-1;j++)
        {
            if(seekers_score[j+1]>seekers_score[j])
            {
                temp=seekers_score[j+1];
                seekers_score[j+1]=seekers_score[j];
                seekers_score[j]=temp;
                temp1=seekers[j+1];
                seekers[j+1]=seekers[j];
                seekers[j]=temp1;
            }
        }
    }
}

void company_menu(){
    int seekers_count=count_seeker_profile_lines();
    struct seeker_details seekers[seekers_count];
    struct company_req req[1];
    int credits[10];
    int importance[10][N];
    read_seeker_data(seekers, seekers_count);
    get_company_requirements(req, credits, importance);
    check_company_compulsory(req, seekers, credits, &seekers_count);

    float seekers_score[seekers_count];
    for(int i=0;i<seekers_count;i++){
        seekers_score[i] = calculate_seeker_score(req[0], seekers[i], credits, importance);
    }
    sort_seeker_scores(seekers, seekers_score, seekers_count);
    printf("########################### Selected Seekers ###########################\n");
    if(seekers_count>7){
        for(int i=0;i<7;i++){
            printf("%.2f- %s %d %c %d\n",seekers_score[i], seekers[i].name, seekers[i].age, seekers[i].gender, seekers[i].marital_status);
            printf("Number of degrees: %d\n", seekers[i].degree_count);
            for(int j=0;j<seekers[i].degree_count;j++){
                printf("Degree: %s\nInstitution: %s\nCGPA: %.2\n", seekers[i].degrees[j], seekers[i].institution[j], seekers[i].cgpa[j]);
            }
            printf("Number of previous work experience: %d\n", seekers[i].experience_count);
            for(int j=0;j<seekers[i].experience_count;j++){
                printf("Company: %s\nYears of Experience: %d\nJob Role: %s\n", seekers[i].experience_companies[j], seekers[i].experience_years[j], seekers[i].experience_post[j]);
            }
            printf("Skills: ");
            for(int j=0;j<seekers[i].skills_count;j++){
                if(j!=seekers[i].skills_count-1){
                    printf("%s, ",seekers[i].skills[j]);
                    continue;
                }
                printf("%s",seekers[i].skills[j]);
            }
            printf("\nCertifications: ");
            for(int j=0;j<seekers[i].certifications_count;j++){
                if(j!=seekers[i].certifications_count-1){
                    printf("%s, ",seekers[i].certifications[j]);
                    continue;
                }
                printf("%s\n\n",seekers[i].certifications[j]);
            }
        }
    }
    else{
        for(int i=0;i<seekers_count;i++){
            printf("%.2f- %s %d %c %d\n",seekers_score[i], seekers[i].name, seekers[i].age, seekers[i].gender, seekers[i].marital_status);
            printf("Number of degrees: %d\n", seekers[i].degree_count);
            for(int j=0;j<seekers[i].degree_count;j++){
                printf("Degree: %s\nInstitution: %s\nCGPA: %.2f\n", seekers[i].degrees[j], seekers[i].institution[j], seekers[i].cgpa[j]);
            }
            printf("Number of previous work experience: %d\n", seekers[i].experience_count);
            for(int j=0;j<seekers[i].experience_count;j++){
                printf("Company: %s\nYears of Experience: %d\nJob Role: %s\n", seekers[i].experience_companies[j], seekers[i].experience_years[j], seekers[i].experience_post[j]);
            }
            printf("Skills: ");
            for(int j=0;j<seekers[i].skills_count;j++){
                if(j!=seekers[i].skills_count-1){
                    printf("%s, ",seekers[i].skills[j]);
                    continue;
                }
                printf("%s",seekers[i].skills[j]);
            }
            printf("\nCertifications: ");
            for(int j=0;j<seekers[i].certifications_count;j++){
                if(j!=seekers[i].certifications_count-1){
                    printf("%s, ",seekers[i].certifications[j]);
                    continue;
                }
                printf("%s\n\n",seekers[i].certifications[j]);
            }
        }
    }
    
    printf("#########################################################");
}
