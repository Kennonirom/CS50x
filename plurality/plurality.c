#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    // -1 to exlude the argument ./plurality
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    //stores the candidates into the data type
    for (int i = 0; i < candidate_count; i++)
    {
        //theres is a plus one bcs 0 = no argument
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }
    //asks the user for number of voters
    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        //asks the voters who to vote for
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    //a loop thats combs thr4ough all the candidate
    for (int i= 0; i < candidate_count ;i++)
    {
        //compares the voter's input to the stored datatype arrays
        if (strcmp (name, candidates[i].name) == 0)
        {
            //adds + 1 to the vote of that candidate
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int maxvotes = 0;
    //a loop thats combs thr4ough all the candidate
    for (int i = 0; i < candidate_count; i++)
    {
        //combs through all the array to identify who has the highest vote
        if (candidates[i].votes > maxvotes)
        {
            //assigns the now most votes to teh variable maxvotes
            maxvotes = candidates[i].votes;
        }
    }

    //a loop thats combs thr4ough all the candidate
    for (int i = 0; i < candidate_count; i++)
    {
        //a condition that finds who has the most votes among the arrays
        if (candidates[i].votes == maxvotes)
        {
            //prints that candidate
            printf("%s\n" , candidates[i].name);
        }
    }

    return;
}