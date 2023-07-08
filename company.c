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
    char institutions[N][N];
    float cgpa[N];
    int experience_count;
    char experience_companies[N][N];
    int experience_years[N];
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
    char experience_post[N][N];
    int skills_count;
    char skills[N][N];
    int certifications_count;
    char certifications[N][N];
};

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

int string_to_int(char str[]){
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
            seekers[line].age = string_to_int(content[1]);
            seekers[line].gender = content[2][0];
            seekers[line].marital_status = string_to_int(content[3]);
            seekers[line].degree_count = string_to_int(content[4]);
            for(int i=0;i<seekers[line].degree_count;i++){
                strcpy(seekers[line].degrees[i], content[5+(i*3)]);
                strcpy(seekers[line].institution[i], content[6+(i*3)]);
                seekers[line].cgpa[i] = string_to_float(content[7+(i*3)]);
            }
            int exppos = 4+(seekers[line].degree_count*3)+1;
            seekers[line].experience_count = string_to_int(content[4+(seekers[line].degree_count*3)+1]);
            for(int i=0;i<seekers[line].experience_count;i++){
                strcpy(seekers[line].experience_companies[i], content[exppos + (i*3) + 1]);
                seekers[line].experience_years[i] = string_to_int(content[exppos + (i*3) + 2]);
                strcpy(seekers[line].experience_post[i], content[exppos + (i*3) + 3]);
            }
            int skillpos =  exppos + (seekers[line].experience_count*3)+1;
            seekers[line].skills_count = string_to_int(content[skillpos]);
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


            seekers[line].certifications_count = string_to_int(content[(seekers[line].degree_count*3)+(seekers[line].experience_count*3)+8]);
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

int main(){
    int seekers_count=count_seeker_profile_lines();
    struct seeker_details seekers[seekers_count];
    read_seeker_data(seekers, seekers_count);
}
