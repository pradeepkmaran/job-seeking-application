void write_in_collection(char str[], char file[]){
    FILE* fp;
    fp = fopen(file, 'a+');
    char obj[N][N];
    int i=0;
    while(fgets(obj[i],N,fp));
    for(int i=0;i<N;i++){
        printf("%s\n", obj[i]);
    }
}