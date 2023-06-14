#include<stdio.h>
#include"login.h"

void main(){
    printf("1 - Login\n2 - Signup\n3 - Forgot Password\n");
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
    }

    Login: 
    int login_result = login();
    if(login_result){
        printf("MAIN LA LOGIN WORK AGUDHU DAA!!!!!");
    }
    else{
        printf("POCHHHH!!!");
    }
    Signup:

    forgot_Password:
}
