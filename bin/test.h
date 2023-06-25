#include<stdio.h>
#include<string.h>

void testString() {
    char str[1000];
    int n;
    char str2[1000];

    printf("Enter a string: ");
    scanf("")
    str[strlen(str) -1]='\0';
    
    printf("Enter a num: ");
    scanf("%d", &n);
    
    printf("Enter another string: ");
    fgets(str2, sizeof(str), stdin);
    str2[strlen(str2) -1]='\0';

    /* printf("%s %d %s", str, n, str2); */

    printf("%s %s", str, str2);

    
}