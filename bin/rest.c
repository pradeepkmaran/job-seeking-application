#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

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
            printf("%f ", dec);
        }
    }
    return res+dec;
}

int main(){
    printf("%.2f", string_to_float("413.59"));
}