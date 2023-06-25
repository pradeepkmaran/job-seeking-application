#include<stdio.h>
#include"loginnew.h"
#include"signup.h"

void main(){
    choice:
    printf("\n1 - Login\n2 - Signup\n3 - Forgot Password\n\nEnter your choice: ");
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
    case(1):
        goto Login;
        break;
    case(2):
        goto Signup;
        break;
    case(3):
        goto forgot_Password;
        break;
    default:
        printf("Invalid choice");
        goto end;
    }

    Login: 
    int login_result = login();
    if(login_result == 1){
        system("cls");
        printf("========JOBSEEKER LOGIN DONE========\n\n");
    }
    else if(login_result == 2){
        system("cls");
        printf("========COMPANY LOGIN DONE========\n\n");
    }
    else if(login_result == -1){
        printf("\nUSERNAME NOT FOUND.\nTry again.\n");
        goto choice;
    }
    else{
        printf("WRONG PASSWORD FOR 3 TIMES.\n\n");
        main();
    }
    goto end;

    Signup: 
    signup();
    system("cls");
    printf("========SIGNUP DONE========\n\n");
    goto end;

    forgot_Password:

    end:
}
