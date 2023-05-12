#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
//used to compare the 2nd and 2rd preference of the voter
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    //information of the candidates
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
//main thing that stores candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;


// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    //input ./runoff candidates
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }


    // Populate array of candidates
    //excludes the declaration ./runoff
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        //doesnt allow more then 9 candidates
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    //inputs the info of the cndidate array into the datatype
    for (int i = 0; i < candidate_count; i++)
    {
        //goes through all the inputed candidate
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }
    //prompts user for the num of votes
    voter_count = get_int("Number of voters: ");
    //forbids user for going passed the max voters
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        //compares the votes to the candidates
        if (strcmp(candidates[i].name, name) == 0)
        {
            //assigns the prffered candidate by rank
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    //loops through the rows
    for (int i = 0; i < voter_count; i++)
    {
        // loops through the columns
        for (int j = 0; j < candidate_count; j++)
        {
            //if candidate is eliminated
            //it will gro through the second preffered of the voter
            if (candidates[preferences[i][j]].eliminated == false)
            {
                //adds +1 to the candidate if not eliminated
                candidates[preferences[i][j]].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    //loops htorugh all the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        //checks if the candidae has more than half of the votes
        if (candidates[i].votes > voter_count / 2)
        {
            //if yes if will print the candidate
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    //defines the num of voters
    int min = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        //combs through the candidates to check who has the least amount of votes
        //also doubvle checks if the candidate is eliminated or not
        if (candidates[i].votes < min && candidates[i].eliminated == false)
        {
            //stores the lest voted candidate
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int eliminate = 0;
    int counter = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        //counts the num of candidates
        if (!candidates[i].eliminated)
        {
            eliminate++;
        }
        //counts the votes of those remaining candidates
        //if 2nd has the same num of votes as 1st
        if (candidates[i].votes == min)
        {
            counter++;
        }
    }
    //will return true if evry candidate in the election has the same num of votes
    //checks same num of votes
    if (eliminate == counter)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        //compares the least voted candidate(min) through all the cadidates votes
        if (candidates[i].votes == min)
        {
            //elimintes the candidate
            candidates[i].eliminated = true;
        }

    }
    return;
}