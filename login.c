#include<stdio.h>
#include<stdlib.h>
#include<math.h>


int usernameCheck(char uniqueids[][7], char username[], int num){
    for(int i=0;i<num;i++){
        int count=0;
        for(int j=0;j<7;j++){
            if(username[j] == uniqueids[i][j]){
                count++;
            }
        }
        if(count == 7){
            return 1;
        }
    }
    return 0;
}


int main(){
    FILE *logindb;
    char ch;

    char username[7];
    char pw[100];
    char uniqueids[100][7];
    printf("Enter Username: ");
    gets(username);
    printf("Enter PW: ");
    gets(pw);

    /* storing login username in array */
    logindb= fopen("logindb.txt","r");
    int i=0;
    int num = 0;
    while(1){
        ch = fgetc(logindb);
        if(ch == EOF){
            break;
        }
        uniqueids[num][i++] = ch;
        if(ch == '\n'){
            ++num;
            i=0;
        }
    }

    /* checking if username is in db */
    if(usernameCheck(uniqueids, username, num)){
        printf("FOUND");
    }
    else{
        printf("NOT FOUND");
    }


    fclose(logindb);
}
