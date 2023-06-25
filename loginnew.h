#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define N 100

int pwcheck(char usernames[][N], char pwarr[][N], char pw[], int num, int index );

int usernameCheck(char usernames[][N], char username[], int num)
{
    /* Username check */
    int index = -1;
    for(int i=0;i<num;i++)
    {   
        int count=0;
        if(strlen(username) == strlen(usernames[i])-1){
            for(int j=0;j<strlen(usernames[i])-1;j++)
            {   
                if(username[j] == usernames[i][j+1])
                {
                    ++count;
                }
                if(count == strlen(usernames[i])-1)
                {
                    index = i;
                    goto returnstatement;
                }
                
            }
        }      
    }
    returnstatement: return index + 1;
}

int pwcheck(char usernames[][N], char pwarr[][N], char pw[], int num, int index ){
    int count=0;
    if(strlen(pw)==strlen(pwarr[index])){
        for(int j=0;j<strlen(pwarr[index]);j++)
        {   
            if(pw[j] == pwarr[index][j])
            {
                count++;
            }
            if(count == strlen(pwarr[index]))
            {
                if(usernames[index][0] == '1'){
                    return 1;
                }
                else if(usernames[index][0] == '2'){
                    return 2;
                }
            }
        }
    }
    return 0;
}


int login(){
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
    int wrongpwcount = 0;
    while(wrongpwcount < 3){
        printf("Enter PW: ");
        scanf("%s", pw);
        int res = pwcheck(usernames, pwarr, pw, num, usernameline-1);
        if(res){
            return res;
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
