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

char degrees_list[N][N], institutions_list[N][N], exp_companies_list[N][N], exp_post_list[N][N], skills_list[N][N], certifications_list[N][N]; 
int degrees_count=0, institutions_count=0, exp_companies_count=0, exp_post_count=0, skills_count=0, certifications_count=0; 

int company_check_unique(char arr[N][N], char val[N]){
    for(int i=0;i<N;i++){
        if(stricmp(arr[i], val) == 0){
            return 0;
        }
    }
    return 1;
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
                if(company_check_unique(degrees_list, content[5+(i*3)])){
                    strcpy(degrees_list[degrees_count++], content[5+(i*3)]);
                }
                if(company_check_unique(institutions_list, content[6+(i*3)])){
                    strcpy(institutions_list[institutions_count++], content[6+(i*3)]);
                }
            }
            int exppos = 4+(seekers[line].degree_count*3)+1;
            int total_experience_years= 0;
            seekers[line].experience_count = string_to_int_company(content[4+(seekers[line].degree_count*3)+1]);
            for(int i=0;i<seekers[line].experience_count;i++){
                strcpy(seekers[line].experience_companies[i], content[exppos + (i*3) + 1]);
                seekers[line].experience_years[i] = string_to_int_company(content[exppos + (i*3) + 2]);
                total_experience_years+=seekers[line].experience_years[i];
                strcpy(seekers[line].experience_post[i], content[exppos + (i*3) + 3]);

                if(company_check_unique(exp_companies_list, content[exppos + (i*3) + 1])){
                    strcpy(exp_companies_list[exp_companies_count++], content[exppos + (i*3) + 1]);
                }
                if(company_check_unique(exp_post_list, content[exppos + (i*3) + 3])){
                    strcpy(exp_post_list[exp_post_count++], content[exppos + (i*3) + 3]);
                }
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
            for(int i=0;i<seekers[line].skills_count;i++){
                if(company_check_unique(skills_list, seekers[line].skills[i])){
                    strcpy(skills_list[skills_count++], seekers[line].skills[i]);
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
            for(int i=0;i<seekers[line].certifications_count;i++){
                if(company_check_unique(certifications_list, seekers[line].certifications[i])){
                    strcpy(certifications_list[certifications_count++], seekers[line].certifications[i]);
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
    printf("Rate the age of the seeker: ");
    scanf("%d", &credits[credit_index++]);
    printf("Rate the Gender of the seeker: ");
    scanf("%d", &credits[credit_index++]);
    printf("Rate the Degrees completed: ");
    scanf("%d", &credits[credit_index++]);
    printf("Rate the Institutions of graduation: ");
    scanf("%d", &credits[credit_index++]);
    printf("Rate the CGPA of the degrees: ");
    scanf("%d", &credits[credit_index++]);
    printf("Rate the Company of experience: ");
    scanf("%d", &credits[credit_index++]);
    printf("Rate the Number of years of experience: ");
    scanf("%d", &credits[credit_index++]);
    printf("Rate the Previous job positions: ");
    scanf("%d", &credits[credit_index++]);
    printf("Rate the Skills: ");
    scanf("%d", &credits[credit_index++]);
    printf("Rate the Certifications: ");
    scanf("%d", &credits[credit_index++]);

    credit_index = 0;
    int point_index=0;
    
    system("cls");
    if(credits[credit_index] != -1){
        printf("\nEnter the Range of age (in this format-> 21-35): ");
        scanf("%d-%d", &req[0].age[0],&req[0].age[1]);
        while(getchar()!='\n');
    }
    else{
        req[0].age[0] = 0;
        req[0].age[1] = 65;
    }
    
    system("cls");
    credit_index++;
    if(credits[credit_index] != -1){
        printf("\nEnter the gender(m/f): ");
        req[0].gender = getchar();
        while(getchar()!='\n');
    }
    
    system("cls");
    credit_index++;
    if(credits[credit_index] != -1){
        char rawstring[N];
        printf("======DEGREES======\n");
        for(int i=0;i<degrees_count;i++){
            printf("%d. %s\n",i+1, degrees_list[i]);
        }
        printf("Enter degrees (in this format-> BE|ME|MTech|..): ");
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
    
    system("cls");
    credit_index++;
    point_index=0;
    if(credits[credit_index] != -1){
        char rawstring[N];
        printf("======INSTITUTIONS======\n");
        for(int i=0;i<institutions_count;i++){
            printf("%d. %s\n",i+1, institutions_list[i]);
        }
        printf("Enter institutions (in this format-> SSN College of Engineering|Shiv Nadar University|..): ");
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

    system("cls");
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
    
    system("cls");
    credit_index++;
    if(credits[credit_index] != -1){
        char rawstring[N];
        printf("======PREVIOUS WORK COMPANIES======\n");
        for(int i=0;i<exp_companies_count;i++){
            printf("%d. %s\n",i+1, exp_companies_list[i]);
        }
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
    
    system("cls");
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
    
    system("cls");
    credit_index++;
    if(credits[credit_index] != -1){
        char rawstring[N];
        printf("======PREVIOUS WORK POSTS======\n");
        for(int i=0;i<exp_post_count;i++){
            printf("%d. %s\n",i+1, exp_post_list[i]);
        }
        printf("Enter the preferred previous job posts of work(in this format-> Android Developer|Project Manager|..): ");
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
    
    system("cls");
    credit_index++;
    point_index=0;
    if(credits[credit_index] != -1){
        char rawstring[N];
        printf("======SKILLS======\n");
        for(int i=0;i<skills_count;i++){
            printf("%d. %s\n",i+1, skills_list[i]);
        }
        printf("Enter the preferred skills(in this format-> c++|Java|..): ");
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
    
    system("cls");
    point_index=0;
    credit_index++;
    if(credits[credit_index] != -1){
        char rawstring[N];
        printf("======CERTIFICATIONS======\n");
        for(int i=0;i<certifications_count;i++){
            printf("%d. %s\n",i+1, certifications_list[i]);
        }
        printf("Enter the preferred certifications(in this format-> Intro to Python|Intro to Java|..): ");
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
    system("cls");
}

void remove_seeker(struct seeker_details seekers[], int seeker_count, int pos){
    for(int i=pos; i<seeker_count-1; i++){
        seekers[i] = seekers[i+1];
    }
}

int removed_seekers_count = 0;

void check_company_compulsory(struct company_req req[], struct seeker_details seekers[], struct seeker_details removed_seekers[], int credits[10], int *seeker_count){
    int i=-1;
    while(i++<(*seeker_count)-1){
        if(credits[0]>0){
            if(seekers[i].age<req[0].age[0] || seekers[i].age>req[0].age[1]){
                removed_seekers[removed_seekers_count++] = seekers[i];
                remove_seeker(seekers, (*seeker_count)--, i);
                continue;
            }
        }
        if(credits[1]>0){
            if(seekers[i].gender != req[0].gender){
                removed_seekers[removed_seekers_count++] = seekers[i];
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
                removed_seekers[removed_seekers_count++] = seekers[i];
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
                removed_seekers[removed_seekers_count++] = seekers[i];
                remove_seeker(seekers, (*seeker_count)--, i);
                continue;
            }          
        }
        credit4:
        if(credits[4]>0){
            for(int j=0;j<seekers[i].degree_count;j++){
                if(seekers[i].cgpa[j] < req[0].cgpa){
                    removed_seekers[removed_seekers_count++] = seekers[i];
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
                removed_seekers[removed_seekers_count++] = seekers[i];
                remove_seeker(seekers, (*seeker_count)--, i);
                continue;
            }
        }
        credit6:
        if(credits[6]>0){
            if(req[0].experience_years < seekers[i].total_experience_years){
                removed_seekers[removed_seekers_count++] = seekers[i];
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
                removed_seekers[removed_seekers_count++] = seekers[i];
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
                removed_seekers[removed_seekers_count++] = seekers[i];
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
                removed_seekers[removed_seekers_count++] = seekers[i];
                remove_seeker(seekers, (*seeker_count)--, i);
                continue;
            }          
        }
        endloop: while(0!=0);
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

struct seeker_details removed_seekers[N];
struct seeker_details seekers[N];
void company_menu(){

    int seekers_count=count_seeker_profile_lines();
    struct company_req req[1];
    int credits[10];
    int importance[10][N];

    read_seeker_data(seekers, seekers_count);
    
    get_company_requirements(req, credits, importance); 
    check_company_compulsory(req, seekers, removed_seekers, credits, &seekers_count);

    float seekers_score[seekers_count];
    for(int i=0;i<seekers_count;i++){
        seekers_score[i] = calculate_seeker_score(req[0], seekers[i], credits, importance);
    }
    sort_seeker_scores(seekers, seekers_score, seekers_count);

    float removed_seekers_score[removed_seekers_count];
    for(int i=0;i<removed_seekers_count;i++){
        removed_seekers_score[i] = calculate_seeker_score(req[0], removed_seekers[i], credits, importance);
    }
    sort_seeker_scores(removed_seekers, removed_seekers_score, removed_seekers_count);

    printf("============ YOUR REQUIREMENTS ============\n\n");

    
    printf("AGE: %d-%d\n", req[0].age[0], req[0].age[1]);
    if(req[0].degree_count > 0){
        printf("DEGREES :\n");
        for(int i=0;i<req[0].degree_count;i++){
            printf("%d)%s\n", i+1,req[0].degrees[i]);
        }
    }
    if(req[0].institutions_count > 0){
        printf("INSTITUTIONS :\n");
        for(int i=0;i<req[0].institutions_count;i++){
            printf("%d)%s\n", i+1,req[0].institutions[i]);
        }
    }
    printf("MINIMUM CGPA : %.2f\n", req[0].cgpa);
    if(req[0].experience_companies_count > 0){
        printf("PREVIOUS WORK COMPANIES :\n");
        for(int i=0;i<req[0].experience_companies_count;i++){
            printf("%d)%s\n", i+1,req[0].experience_companies[i]);
        }
    }
    printf("MINIMUM YEARS OF EXPERIENCE: %d\n", req[0].experience_years);
    if(req[0].experience_post_count > 0){
        printf("PREVIOUS WORK POSTS:\n");
        for(int i=0;i<req[0].experience_companies_count;i++){
            printf("%d)%s\n", i+1,req[0].experience_companies[i]);
        }
    }
    if(req[0].skills_count > 0){
        printf("SKILLS:\n");
        for(int i=0;i<req[0].skills_count;i++){
            printf("%d)%s\n", i+1,req[0].skills[i]);
        }
    }
    if(req[0].certifications_count > 0){
        printf("SKILLS:\n");
        for(int i=0;i<req[0].certifications_count;i++){
            printf("%d)%s\n", i+1,req[0].certifications[i]);
        }
    }
    
    printf("\n============= SELECTED SEEKERS =============\n");
    if(seekers_count>7){
        for(int i=0;i<7;i++){
            printf("%d) NAME: %s\n", i+1, seekers[i].name);
            printf("AGE: %d\n", seekers[i].age);
            switch(seekers[i].gender){
                case('m'): printf("GENDER: Male\n"); break;
                case('f'): printf("GENDER: Female\n"); break;
                default: printf("GENDER: Unavailable\n");
            }
            switch(seekers[i].marital_status){
                case(1): printf("MARITAL STATUS: Married\n"); break;
                case(0): printf("MARITAL STATUS: Unmarried\n"); break;
                default: printf("MARITAL STATUS: Unavailable\n");
            }
            for(int j=0;j<seekers[i].degree_count;j++){
                printf("DEGREE %d : %s\n", j+1, seekers[i].degrees[j] );
                printf("INSTITUTION : %s\n", seekers[i].institution[j] );
                printf("CGPA : %.2f\n", seekers[i].cgpa[j] );
            }
            for(int j=0;j<seekers[i].experience_count;j++){
                printf("COMPANY %d : %s\n", j+1, seekers[i].experience_companies[j] );
                printf("JOB POST : %s\n", seekers[i].experience_post[j] );
                printf("YEARS : %d\n", seekers[i].experience_years[j] );
            }
            printf("SKILLS:\n");
            for(int j=0;j<seekers[i].skills_count;j++){
                printf("%d.%s\n", j+1, seekers[i].skills[j]);
            }
            printf("CERITIFICATIONS:\n");
            for(int j=0;j<seekers[i].certifications_count;j++){
                printf("%d.%s\n", j+1, seekers[i].certifications[j]);
            }
            printf("\n");
        }
    }
    else{
        for(int i=0;i<seekers_count;i++){
            printf("%d) NAME: %s\n", i+1, seekers[i].name);
            printf("AGE: %d\n", seekers[i].age);
            switch(seekers[i].gender){
                case('m'): printf("GENDER: Male\n"); break;
                case('f'): printf("GENDER: Female\n"); break;
                default: printf("GENDER: Unavailable\n");
            }
            switch(seekers[i].marital_status){
                case(1): printf("MARITAL STATUS: Married\n"); break;
                case(0): printf("MARITAL STATUS: Unmarried\n"); break;
                default: printf("MARITAL STATUS: Unavailable\n");
            }
            for(int j=0;j<seekers[i].degree_count;j++){
                printf("DEGREE %d : %s\n", j+1, seekers[i].degrees[j] );
                printf("INSTITUTION : %s\n", seekers[i].institution[j] );
                printf("CGPA : %.2f\n", seekers[i].cgpa[j] );
            }
            for(int j=0;j<seekers[i].experience_count;j++){
                printf("COMPANY %d : %s\n", j+1, seekers[i].experience_companies[j] );
                printf("JOB POST : %s\n", seekers[i].experience_post[j] );
                printf("YEARS : %d\n", seekers[i].experience_years[j] );
            }
            printf("SKILLS:\n");
            for(int j=0;j<seekers[i].skills_count;j++){
                printf("%d.%s\n", j+1, seekers[i].skills[j]);
            }
            printf("CERITIFICATIONS:\n");
            for(int j=0;j<seekers[i].certifications_count;j++){
                printf("%d.%s\n", j+1, seekers[i].certifications[j]);
            }
            printf("\n");
        }
    }
    
    printf("============= OTHER RECOMMENDATIONS =============\n");
    for(int i=0;i<5;i++){
        printf("%d) NAME: %s\n", i+1, removed_seekers[i].name);
        printf("AGE: %d\n", removed_seekers[i].age);
        switch(removed_seekers[i].gender){
            case('m'): printf("GENDER: Male\n"); break;
            case('f'): printf("GENDER: Female\n"); break;
            default: printf("GENDER: Unavailable\n");
        }
        switch(removed_seekers[i].marital_status){
            case(1): printf("MARITAL STATUS: Married\n"); break;
            case(0): printf("MARITAL STATUS: Unmarried\n"); break;
            default: printf("MARITAL STATUS: Unavailable\n");
        }
        for(int j=0;j<removed_seekers[i].degree_count;j++){
            printf("DEGREE %d : %s\n", j+1, removed_seekers[i].degrees[j] );
            printf("INSTITUTION : %s\n", removed_seekers[i].institution[j] );
            printf("CGPA : %.2f\n", removed_seekers[i].cgpa[j] );
        }
        for(int j=0;j<removed_seekers[i].experience_count;j++){
            printf("COMPANY %d : %s\n", j+1, removed_seekers[i].experience_companies[j] );
            printf("JOB POST : %s\n", removed_seekers[i].experience_post[j] );
            printf("YEARS : %d\n", removed_seekers[i].experience_years[j] );
        }
        printf("SKILLS:\n");
        for(int j=0;j<removed_seekers[i].skills_count;j++){
            printf("%d.%s\n", j+1, removed_seekers[i].skills[j]);
        }
        printf("CERITIFICATIONS:\n");
        for(int j=0;j<removed_seekers[i].certifications_count;j++){
            printf("%d.%s\n", j+1, removed_seekers[i].certifications[j]);
        }
        printf("\n");
    }
}