#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>
#include <errno.h>
#include <unistd.h>
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
        if(endTime - beginTime > 28){
            return *maxFlowSize;
        }
        
        foundSomething = 0;
        for(;i < 26;){
            nextLetter = i;
            i++;
            if(matrix[letter][nextLetter] == 0){
                continue;
            }
            
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
                if(count > (*maxFlowSize)){
                    (*maxFlowSize) = count;
                    int k;
                    for(k = 0; k < count;k++){
                        maxFlow[k] = flow[k];
                    }
                    maxFlow[(*maxFlowSize)] = -1;
                    
                }
                matrix[letter][nextLetter]++;
                flow[count] = -1;
                count--;
            } else {
                memoryStackLetter[memoryStackCount] = letter;
                memoryStackIndex[memoryStackCount] = i;
                memoryStackCount++;
                memoryStackLetter[memoryStackCount] = nextLetter;
                memoryStackIndex[memoryStackCount] = 0;
                memoryStackCount++;
                
                foundSomething = 1;
                if(count > (*maxFlowSize)){
                    (*maxFlowSize) = count;
                    int k;
                    for(k = 0; k < count;k++){
                        maxFlow[k] = flow[k];
                    }
                    maxFlow[(*maxFlowSize)] = -1;
                }
                break;
            }
        }
        
        if(!foundSomething){
            if(memoryStackCount > 0) { 
                nextLetter = flow[count-1];
                matrix[flow[count-2]][flow[count-1]]++;
                flow[count] = -1;
                count--;
            }
        }
        
    }
    return -1;
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
                int aux;
                aux = recursive(i, matrix, beginTime, maxInput, flow, &maxFlowSize);
                if(aux != -1)
                    return aux;
                break;
            }
        }
    }
    return maxFlowSize;
}

int main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    time_t beginTime;
    beginTime = time(NULL);
    
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
    //Matrix of list of word position in list
    int*** wordMatrixIndex;
    char ** wordList;
    wordMatrixIndex = (int***) calloc(26,sizeof(int**));
    wordList = (char**) calloc(200001, sizeof(char*));
    for (i = 0; i < 26; i++){
        wordMatrixIndex[i] = (int**)calloc(26, sizeof(int*));
        for(j = 0; j < 26; j++){
            wordMatrixIndex[i][j] = (int*)calloc(10000, sizeof(int));
        }

    }
    
    //Read input and print word position for each letter
    int count = 0;
    while ((read = getline(&wordList[count], &len, stdin)) != -1) {
        int firstLetter;
        int lastLetter;
        if(wordList[count][0] < 97){
            firstLetter = wordList[count][0]-65;
        } else {
            firstLetter = wordList[count][0]-97;
        }
        if(wordList[count][read-2] < 97){
            lastLetter = wordList[count][read-2]-65;
        } else {
            lastLetter = wordList[count][read-2]-97;
        }
        matrix[firstLetter][lastLetter]++;
        maxInput++;


        int aux = printIndexMatrix[firstLetter][lastLetter];
        wordMatrixIndex[firstLetter][lastLetter][aux] = count;
        printIndexMatrix[firstLetter][lastLetter]++;
        
        wordList[count][strcspn(wordList[count], "\n")] = 0;
        count++;
        
    }
    
    //Reset the index of matrix
    for (i = 0; i < 26; i++){
        for(j = 0; j < 26; j++){
            printIndexMatrix[i][j] = 0;
        }
    }
    
    int* flow = (int*)calloc(maxInput+1, sizeof(int));
    int flowSize = solve(matrix, beginTime, maxInput, flow);

    //Print output
    for(i = 1; i < flowSize;i++){
        int firstLetter = flow[i-1];
        int lastLetter = flow[i];
        int aux = printIndexMatrix[firstLetter][lastLetter]++;
        printf("%s\n", wordList[wordMatrixIndex[firstLetter][lastLetter][aux]]);
    }
        
}
