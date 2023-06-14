#include<stdio.h>
#include<stdlib.h>
#include<math.h>


int usernameCheck(char uniqueids[][7], int num, char pwarr[][8], char username[], char pw[])
{
    int index = -1;
    for(int i=0;i<num;i++)
    {   
        int count=0;
        for(int j=0;j<7;j++)
        {   
            if(username[j] == uniqueids[i][j])
            {
                ++count;
            }
            if(count == 7)
            {
                index = i;
                break;
            }
            
        }
        
    }
    int count=0;
    for(int j=0;j<8;j++)
    {   
        if(pw[j] == pwarr[index][j])
        {
            count++;
        }
        if(count == 8 )
        {
            return 1;
        }
    }
    return 0;

}


int main(){
    FILE *uniqueiddb, *pwdb;
    char ch;

    char username[8];
    char pw[9];
    char uniqueids[100][7];
    char pwarr[100][8];
    
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter PW: ");
    scanf("%s", pw);

    /* storing login username in array */
    uniqueiddb= fopen("uniqueiddb.txt","r");
    int i=0;
    int num = 0;
    while(1){
        ch = fgetc(uniqueiddb);
        if(ch == EOF){
            break;
        }
        uniqueids[num][i++] = ch;
        if(ch == '\n'){
            ++num;
            i=0;
        }
    }

    pwdb= fopen("pwdb.txt","r");
    i=0;
    num = 0;
    while(1){
        ch = fgetc(pwdb);
        if(ch == EOF){
            break;
        }
        if(ch == '\n'){
            ++num;
            i=0;
        }
        else{
            pwarr[num][i++] = ch;
        }
    }
    num++;


    /* checking if username is in db */
    if(usernameCheck(uniqueids, num, pwarr, username, pw)){
        printf("FOUND");
        fclose(uniqueiddb);
        fclose(pwdb);
    }
    else{
        printf("NOT FOUND");
        fclose(uniqueiddb);
        fclose(pwdb);
    }
}
