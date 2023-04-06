//Author: Will Miller
//Summary: Brute force and heuristic algorithm to solve the 3sat problem
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int teststate(int term, int state){ //Does the state of the term evaluate to true 0 = true
    if(term < 0 && state == 0)
        return 0;
    else if(term > 0 && state == 1)
        return 0;
    else
        return 1;
}

int testclause(int* clause, int one, int two, int three){ //Does the clause evaluate to true 0 = true
    if(teststate(clause[0], one) == 0)
            return 0;
    if(teststate(clause[1], two) == 0)
            return 0;
    if(teststate(clause[2], three) == 0)
            return 0;
    return 1;
}

int testsatproblem(int** clauses, int* states, int numClauses){
    int* clPtr; //What states are related to this clause
    for(int x = 0; x < numClauses; x++){
        clPtr = clauses[x];
        if(testclause(clPtr, states[abs(clPtr[0]) - 1], states[abs(clPtr[1]) - 1], states[abs(clPtr[2]) - 1]) == 1)
            return 1;
    }
    return 0;
}

int* bruteforcesolve(int** clauses, int terms, int numClauses){
    int numTerms = terms;
    int* termStates = (int*)malloc(numTerms * sizeof(int));
    int numCombinations = 1;
    for(int x = 0; x < numTerms; x++){ //Equivalent of 2^numTerms
        numCombinations *= 2;
        termStates[x] = 0; //Set all terms to zero
    }
    

    for(int combNum = 0; combNum < numCombinations; combNum++){ //combNum = binary rep
        if(testsatproblem(clauses, termStates, numClauses) == 0)
            return termStates;
        for(int x = 0; x < numTerms; x++){
            if(termStates[x] == 1){
                termStates[x] = 0; //If you try to add 1 and it carries over keep going
            }
            else{
                termStates[x] = 1; //You found a zero to drop the one. stop
                break;
            }
        }
        
    }
    return NULL;
}

int main(int argc, char* argv[]){
    char inputBuffer[20];
    int currTerms[3];
    int* results;
    int** clauses; // Each clause as they are written in the file
    int numClauses = 0;
    int currClause = 0;
    int termsSize = 0;

    if(argc > 2 || argc == 1)
        printf("Usage: ./a.out problem.dat");
    FILE* filePtr;

    filePtr = fopen(argv[1], "r");

    if (filePtr == NULL){
        printf("%s can't be opened.", argv[1]);
    }
    //Dynamic allocation
    fgets(inputBuffer, sizeof(inputBuffer), filePtr);
    sscanf(inputBuffer, "%d %d", &termsSize, &numClauses);
    clauses = (int**)malloc(numClauses * sizeof(int*));
    for(int x = 0; x < numClauses; x++)
        clauses[x] = (int*)malloc(3 * sizeof(int));

    while(fgets(inputBuffer, sizeof(inputBuffer), filePtr)){
        if(inputBuffer[0] == '$'){//This line denotes the end of the file
            break;
        }     
        sscanf(inputBuffer, "%d %d %d", &currTerms[0], &currTerms[1], &currTerms[2]);
        for(int x = 0; x < 3; x++){
            clauses[currClause][x] = currTerms[x];
        }
        currClause++;
    }

    results = bruteforcesolve(clauses, termsSize, numClauses);
    if(results == NULL){
        printf("Failed to solve.\n");
    }
    else{
        printf("Solution\n");
        for(int x = 0; x < termsSize; x++){
            printf("%d: %d\n", x + 1, results[x]);
        }
        free(results);
    }
    
    for(int x = 0; x < numClauses; x++)
        free(clauses[x]);
    free(clauses);
    fclose(filePtr);
    return 0;
}