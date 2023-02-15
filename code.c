#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#undef _GLIBCXX_DEBUG
#pragma GCC optimize("Ofast,inline")
#pragma GCC target("bmi,bmi2,lzcnt,popcnt")

int recursive(int beginLetter, int** matrix, time_t beginTime, int maxInput, int* maxFlow, int* maxFlowSize) {
    int count = 0;
    int* flow = (int*)calloc(maxInput+1, sizeof(int));
    flow[count++] = beginLetter;
    
    int memoryStackCount = 0;
    int* memoryStackLetter = (int*)calloc(maxInput+1, sizeof(int));
    int* memoryStackIndex = (int*) calloc(maxInput+1, sizeof(int));
    memoryStackLetter[memoryStackCount] = beginLetter;
    memoryStackIndex[memoryStackCount] = 0;
    memoryStackCount++;
    
    int i = 0;
    int letter = 0;
    int nextLetter = 0;
    
    int foundSomething = 0;
    while(memoryStackCount > 0){
        memoryStackCount--;
        letter = memoryStackLetter[memoryStackCount];
        i = memoryStackIndex[memoryStackCount];
        time_t endTime = time(NULL);
        //printf("-----------%c-----------\n",97+letter);
        if(endTime - beginTime > 28){
            printf("A %d\n", *maxFlowSize);
            return *maxFlowSize;
        }
        
        foundSomething = 0;
        for(;i < 26;){
            nextLetter = i;
            i++;
            if(matrix[letter][nextLetter] == 0){
                continue;
            }
            
            //printf("Next Letter %c Next %c : %d \n", 97+letter, 97+nextLetter, count);
            matrix[letter][nextLetter]--;
            flow[count++] = nextLetter;
            int j;
            int validLetter = 0;
            for(j = 0; j < 26; j++){
                if(matrix[nextLetter][j] > 0){
                    validLetter = 1;
                    break;
                }
            }
            
            if(!validLetter){
                //printf("NOT VALID\n");
                if(count > (*maxFlowSize)){
                    //printf("COPY\n");
                    (*maxFlowSize) = count;
                    int k;
                    for(k = 0; k < count;k++){
                        maxFlow[k] = flow[k];
                        //printf("%c ", 97+maxFlow[k]);
                    }
                    //printf("\n");
                    maxFlow[(*maxFlowSize)] = -1;
                    
                }
                matrix[letter][nextLetter]++;
                flow[count] = -1;
                count--;
            } else {
                //printf("VALID\n");
                memoryStackLetter[memoryStackCount] = letter;
                memoryStackIndex[memoryStackCount] = i;
                memoryStackCount++;
                memoryStackLetter[memoryStackCount] = nextLetter;
                memoryStackIndex[memoryStackCount] = 0;
                memoryStackCount++;
                
                foundSomething = 1;
                if(count > (*maxFlowSize)){
                    //printf("COPY\n");
                    (*maxFlowSize) = count;
                    int k;
                    for(k = 0; k < count;k++){
                        maxFlow[k] = flow[k];
                        //printf("%c ", 97+maxFlow[k]);
                    }
                    //printf("\n");
                    maxFlow[(*maxFlowSize)] = -1;
                }
                break;
            }
        }
        
        if(!foundSomething){
            if(memoryStackCount > 0) { 
                nextLetter = flow[count-1];
                //printf("REMOVING %c\n",97+flow[count-1]);
                //printf("UPDATE %c %c\n", 97+flow[count-2],97+flow[count-1]);
                matrix[flow[count-2]][flow[count-1]]++;
                flow[count] = -1;
                count--;
            }
        }
        
    }
    return -1;
    //printf("RECURSIVE %c\n", (97+beginLetter));
}

int solve(int** matrix, time_t beginTime, int maxInput, int* flow) {
    int i, j;
    int maxFlowSize = 0;
    int validLetter;
    for(i = 0; i < 26; i++){
        validLetter = 0;
        for(j = 0; j < 26; j++){
            if(matrix[i][j] > 0){
                validLetter = 1;
                //printf("B %c\n", 97+i);
                int aux;
                aux = recursive(i, matrix, beginTime, maxInput, flow, &maxFlowSize);
                if(aux != -1)
                    return aux;
                break;
            }
        }
    }
    printf("%d\n", maxFlowSize);
    for(i = 0; i < maxFlowSize; i++){
        printf("%c ", 97+flow[i]);
    }
    printf("\n");
}

int main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    time_t beginTime;
     
    beginTime = time(NULL);
    
    //fp = fopen("teste08.txt", "r");
    
    //if (fp == NULL)
    //    return 0;
    int i, j;
    int** matrix;
    int maxInput = 0;
    //Initialize Graph
    matrix = (int**) calloc(26,sizeof(int*));
    for (i = 0; i < 26; i++)
        matrix[i] = (int*)calloc(26, sizeof(int));
        
    //Initialize Graph to print output
    int** printIndexMatrix;
    printIndexMatrix = (int**) calloc(26,sizeof(int*));
    for (i = 0; i < 26; i++)
        printIndexMatrix[i] = (int*)calloc(26, sizeof(int));
    
    //Initialize Graph to print output
    int*** wordMatrixIndex;
    char ** wordList;
    wordMatrixIndex = (int***) calloc(26,sizeof(int**));
    wordList = (char**) calloc(750000, sizeof(char*));
    for (i = 0; i < 26; i++){
        wordMatrixIndex[i] = (int**)calloc(26, sizeof(int*));
        for(j = 0; j < 26; j++){
            wordMatrixIndex[i][j] = (int*)calloc(1000, sizeof(int));
        }

    }
    
    int count = 0;
    while ((read = getline(&wordList[count], &len, stdin)) != -1) {
        int firstLetter;
        int lastLetter;
        if(wordList[count][0] < 97){
        	firstLetter = wordList[count][0]-65;
        } else {
            firstLetter = wordList[count][0]-97;
        }
        lastLetter = wordList[count][read-2]-97;
        matrix[firstLetter][lastLetter]++;
        maxInput++;


        int aux = printIndexMatrix[firstLetter][lastLetter];
        wordMatrixIndex[firstLetter][lastLetter][aux] = count;
        printIndexMatrix[firstLetter][lastLetter]++;
        
        wordList[count][strcspn(wordList[count], "\n")] = 0;
        count++;
        
    }
    for(i = 0; i < count; i++){
        printf("%s\n", wordList[i]);
    }
    return 0;



    while ((read = getline(&line, &len, fp)) != -1) {
        int firstLetter;
        int lastLetter;
        if(line[0] < 97){
        	firstLetter = line[0]-65;
        } else {
            firstLetter = line[0]-97;
        }
        lastLetter = line[read-2]-97;
        matrix[firstLetter][lastLetter]++;
        maxInput++;
        
        wordList[count++] = line;
    }

        
    for(i = 0; i < count;i++){
        printf("%s",wordList[i]);
    }
    return 0;   
    int* flow = (int*)calloc(maxInput+1, sizeof(int));
    solve(matrix, beginTime, maxInput, flow);
    fclose(fp);
    if (line)
        free(line);
        return 0;
}
