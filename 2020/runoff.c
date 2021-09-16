#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct{
    string name;
    int votes;
    bool eliminated;
}
candidate;

candidate candidates[9];

bool vote();
void tabulate();
bool print_winner();
int find_min();
bool is_tie();
void eliminate();

int min_votes = 100;
int numofvoters;
int numofcandidates;
int preferences[9][100];

int main(int argc, string argv[]){

    if (argc < 2){
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    numofcandidates = argc - 1;
    if (9 < numofcandidates){
        printf("Maximum number of candidates is 9");
        return 1;
    }

    for (int i = 0; i < numofcandidates; i++){
        candidates[i].name = argv[i + 1];
    }

    numofvoters = get_int("Number of voters: ");

    for(int i = 0; i < numofcandidates; i++){
        candidates[i].eliminated = false;
    }



    for(int i = 0; i < numofvoters; i++){
        for(int j = 0; j < numofcandidates; j++){
            string name = get_string("Rank %i: ",j+1);
            if (!vote(i, j, name))
            {
            printf("Invalid vote.\n");
            }
        }
        printf("\n");
    }




    while (true){
        tabulate();

        bool won = print_winner();
        if(won){
            break;
        }

        int min = find_min();
        bool tie = is_tie(min);

        if (tie){
            for (int i = 0; i < numofcandidates; i++){
                if (!candidates[i].eliminated){
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        eliminate(min);

        for (int i = 0; i < numofcandidates; i++){
            candidates[i].votes = 0;
        }
    }
return 0;
}





bool vote(int voter, int rank, string name){
    bool exist = false;
    for (int i = 0; i < numofcandidates; i++){
        if (strcmp(name, candidates[i].name) == 0){
        preferences[voter][rank] = i;
        exist = true;
        break;
        }
    }
    return exist;
}

void tabulate(){
    for(int i = 0; i < numofvoters; i++){
        for (int j = 0; j < numofcandidates; j++){
            if(candidates[preferences[i][j]].eliminated == false){
            candidates[preferences[i][j]].votes++;
            break;
            }
        }
    }
    return;
}

bool print_winner(){
    for(int i = 0; i < numofcandidates; i++){
        if(candidates[i].votes > numofvoters / 2){
            printf("%s\n",candidates[i].name);
            return true;
        }
    }
    return false;
}

int find_min(){
    for(int i = 0; i < numofcandidates; i++){
        if(min_votes > candidates[i].votes && candidates[i].eliminated == false){
            min_votes = candidates[i].votes;
        }
    }
    return min_votes;
}

bool is_tie(int min){
    for (int i = 0; i < numofcandidates; i++){
        if (candidates[i].eliminated == false && candidates[i].votes != min){
            return false;
        }
    }
    return true;
}

void eliminate(int min){
    for(int i = 0; i < numofcandidates; i++){
        if(candidates[i].votes == min){
            candidates[i].eliminated = true;
        }
    }
}
