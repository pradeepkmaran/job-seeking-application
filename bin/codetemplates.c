/* Single sentence without check */
printf("Enter the institution of study: ");
fgets(institution, N, stdin);
institution[strlen(institution)-1]='\0';

/* String with check */
check = 0;
do{
    if(!check){
        printf("Enter M - Male, F - Female: ");
    }
    else{
        printf("Enter valid choice: ");
    }
    fgets(gender, N, stdin);
    check = 1;
}while(gender[0]!='M' && gender[0]!='F');
gender[strlen(gender)-1]='\0';

/* Integer with check */
check=0;
do{
    if(!check){
        printf("Enter your age: ");
    }
    else{
        printf("Enter valid age: ");
    }
    scanf("%d", &age);
    check=1;
}while(age<=0);
while(getchar()!='\n');

/* integer without check */
scanf("%d", &age);
while(getchar()!='\n');

