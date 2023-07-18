#include<stdio.h>
#include"login.h"
#include"signup.h"
#include"jobseeker.h"
#include"company.h"

void main(){
    choice: while(0!=0);
    system("cls");
    printf("========WELCOME TO KORTHUVIDUVOM========\n\n");
    printf("\n1 - Login\n2 - Signup\n3 - Modify User Details\n\nEnter your choice: ");
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
        //goto forgot_Password;
        break;
    default:
        printf("Invalid choice");
        goto end;
    }

    Login: while(0!=0);
    int login_result = login();
    if(login_result == 1){
        system("cls");
        printf("========JOBSEEKER LOGIN DONE========\n\n");
        goto seeker_menu;
    }
    else if(login_result == 2){
        system("cls");
        printf("========COMPANY LOGIN DONE========\n\n");
        goto company_menu;
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

    Signup: signup();
    system("cls");
    printf("========SIGNUP DONE========\n\n");
    goto choice;

    seeker_menu: job_seeker_menu();
    goto end;

    company_menu: company_menu();
    goto end;

    end: while(0!=0);
}