//Author: Will Miller
//Summary: Brute force and heuristic algorithm to solve the 3sat problem
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//#define TABU_LIFETIME 10 //How many iterations can a tabumove stay in the list
#define NEIGHBORHOOD_SIZE 5
#define ITERATIONS 10
#define REMOVAL_TRIES 3

/*-------------------- Helper Functions ---------------------*/

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

int evaluatesolution(int** clauses, int* states, int numClauses){
    int *clPtr;
    int satisfaction = 0; //How many clauses are satisfied by this solution?
    for(int x = 0; x < numClauses; x++){
        clPtr = clauses[x];
        if(testclause(clPtr, states[abs(clPtr[0]) - 1], states[abs(clPtr[1]) - 1], states[abs(clPtr[2]) - 1]) == 0)
            satisfaction++;
    }
    return satisfaction;
}

void copyarray(int* destination, int* source, int sourceSize){
    for(int x = 0; x < sourceSize; x++){
        destination[x] = source[x];
    }
}

/*-------------------- HEURISTIC IMPLEMENTATION ---------------------*/

int flip(int state){
    if(state == 0)
        return state = 1;
    else
        return state = 0;
}

int** neighborhood(int* states, int terms){
    //This block is in the case that we have too few variables to create a neighborhood of NEIGHBORHOOD_SIZE. 
    //so it should just make a neighborhood the size of the number of terms.
    int trueSize;
    int randomIndex;
    if(terms < NEIGHBORHOOD_SIZE)
        trueSize = terms;
    else
        trueSize = NEIGHBORHOOD_SIZE;

    int** neighborhood = (int**)malloc(trueSize * sizeof(int*));
    for(int x = 0; x < trueSize; x++)
        neighborhood[x] = (int*)malloc(terms * sizeof(int));

    for(int x = 0; x < trueSize; x++){
        randomIndex = rand() % terms;
        for(int y = 0; y < terms; y++){
            if(y == randomIndex)
                neighborhood[x][y] = flip(states[y]);
            else
                neighborhood[x][y] = states[y];
        }
    }

    return neighborhood;
    
}

void randomimprove(int** clauses, int* currentSolution, int terms, int numClauses){ //Assuming we use this only to improve a solution that satisfies all clauses. Edits solution given
    int size = 0;
    int* trueTerms; //What terms are true
    int index;
    int failsInRow = 0;
    int temp = 0;
    for(int x = 0; x < terms; x++){
        if(currentSolution[x] == 1)
            size++;
    }
    trueTerms = (int*)malloc(size * sizeof(int));
    index = 0;
    for(int x = 0; x < terms; x++){
        if(currentSolution[x] == 1){
            trueTerms[index] = x;
            index++;
        }
    }
    while(failsInRow <= REMOVAL_TRIES && size > 0){
        index = rand() % size;
        currentSolution[trueTerms[index]] = 0;
        if(testsatproblem(clauses, currentSolution, numClauses) == 0) {
            failsInRow = 0;
            //Trade the value that worked with the end and decrease size so we don't randomly keep hitting the same value.
            temp = trueTerms[size - 1];
            trueTerms[size - 1] = trueTerms[index];
            size--;
        }
        else {
            failsInRow++;
            currentSolution[trueTerms[index]] = 1;
        }
    }
}

int* randomsearchsolve(int** clauses, int terms, int numClauses){
    int* termStates = (int*)malloc(terms * sizeof(int));
    int trueSize;
    int** currentNeighborhood;
    int currentSatisfaction;
    int newSatisfaction;
    int attemptsRemaining = ITERATIONS;

    if(terms < NEIGHBORHOOD_SIZE)
        trueSize = terms;
    else
        trueSize = NEIGHBORHOOD_SIZE;

    for(int x = 0; x < terms; x++){ //Produce a random solution to improve
        termStates[x] = rand() % 2;
    }
    currentSatisfaction = evaluatesolution(clauses, termStates, numClauses);
    if(currentSatisfaction == numClauses)
        return termStates;
    
    while(attemptsRemaining > 0){
        currentNeighborhood = neighborhood(termStates, terms); //Get neighborhood
        for(int x = 0; x < trueSize; x++){ //Test neighborhood of solutions for a better one.
            newSatisfaction = evaluatesolution(clauses, currentNeighborhood[x], numClauses);
            if(newSatisfaction > currentSatisfaction){
                copyarray(termStates, currentNeighborhood[x], terms);
                currentSatisfaction = newSatisfaction;
            }
        }
        //Free the malloc used in the neighborhood function
        for(int x = 0; x < trueSize; x++){
            free(currentNeighborhood[x]);
        }
        free(currentNeighborhood);

        if(currentSatisfaction == numClauses){
            randomimprove(clauses, termStates, terms, numClauses);
            return termStates;
        }
        
        attemptsRemaining--;
    }

    printf("tabusearchsolve: True solution not found.\n");
    return termStates;

}
/*------------------ BRUTE-FORCE IMPLEMENTATION ------------------*/

int* bruteforcesolve(int** clauses, int terms, int numClauses){
    int numTerms = terms;
    int* termStates = (int*)malloc(numTerms * sizeof(int));
    int end = 0; //This is to check if we checked every combination and there is a roll over which means we need to stop.
    for(int x = 0; x < numTerms; x++){ //Equivalent of 2^numTerms
        termStates[x] = 0; //Set all terms to zero
    }
    

    while(end == 0){ 
        if(testsatproblem(clauses, termStates, numClauses) == 0)
            return termStates;
        for(int x = 0; x < numTerms; x++){
            if(termStates[x] == 1){
                termStates[x] = 0; //If you try to add 1 and it carries over keep going
                if(x == numTerms - 1)
                    end = 1;
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
    srand(time(NULL));
    char inputBuffer[20];
    int currTerms[3];
    int* results;
    int** clauses; // Each clause as they are written in the file
    int numClauses = 0;
    int currClause = 0;
    int termsSize = 0;
    clock_t t;
    double time_taken;

    if(argc > 2 || argc == 1) {
        printf("Usage: ./a.out problem.dat");
        return 1;
    }
        

    FILE* filePtr;

    filePtr = fopen(argv[1], "r");

    if (filePtr == NULL){
        printf("%s can't be opened.", argv[1]);
        return 2;
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
    fclose(filePtr);
    t = clock();
    filePtr = fopen(argv[1], "a");
    /*results = bruteforcesolve(clauses, termsSize, numClauses);
    t = clock() - t;
    if(results == NULL){
        printf("Failed to solve.\n");
    }
    else{
        fprintf(filePtr, "\nBrute Force Solution\n");
        for(int x = 0; x < termsSize; x++){
            fprintf(filePtr, "%d: %d\n", x + 1, results[x]);
        }
        free(results);
        time_taken = ((double)t)/CLOCKS_PER_SEC;
        printf("bruteforcesolve() took %f seconds to execute \n", time_taken);
    }*/

    results = randomsearchsolve(clauses, termsSize, numClauses);
    t = clock() - t;
    fprintf(filePtr, "\nRandom Search Heuristic Solution\n");
    for(int x = 0; x < termsSize; x++){
        fprintf(filePtr, "%d: %d\n", x + 1, results[x]);
    }
    free(results);
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("randomsearchsolve() took %f seconds to execute \n", time_taken);

    for(int x = 0; x < numClauses; x++)
        free(clauses[x]);
    free(clauses);
    fclose(filePtr);
    return 0;
}