#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef _GLIBCXX_DEBUG
#pragma GCC optimize("Ofast,inline")
#pragma GCC target("bmi,bmi2,lzcnt,popcnt")

int main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("test02.txt", "r");
    
    if (fp == NULL)
        return 0;

    int i, j;
    int** matrix;
    matrix = (int**) calloc(26,sizeof(int*));
    for (i = 0; i < 26; i++)
        matrix[i] = (int*)calloc(26, sizeof(int));
        
    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu:\n", read);
        printf("first: %c last: %c\n", line[0], line[read-2]);
        if(line[0] < 97){
        	matrix[line[0]-65][line[read-2]-97]++;
        } else {
        	matrix[line[0]-97][line[read-2]-97]++;
        }
    }


    for(i = 0; i < 26; i++){
    	for(j = 0; j < 26; j++){
    	    printf("%d ", matrix[i][j]);   		 
	    }
	    printf("\n");
    }
    
    fclose(fp);
    if (line)
        free(line);
        return 0;
}
