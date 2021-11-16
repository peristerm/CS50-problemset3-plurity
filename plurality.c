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
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
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
    for (int i = 0; i < candidate_count; i++)
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }


    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int counter = 0;
    bool check = false;
    int counter2 = 0;
    int counter3 = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            //Whether a candidate got more votes than others
            if (candidates[i].votes > candidates[j].votes)
            {
                counter++;
            }

            //If 2 candidates have equal amount of votes and more than other
            if ((candidates[i].votes == candidates[j].votes) && (i != j))
            {
                for (int k = 0; k < candidate_count; k++)
                {
                    if (candidates[i].votes != candidates[k].votes)
                    {
                        if (candidates[i].votes > candidates[k].votes)
                        {
                            check = true;
                        }

                        else
                        {
                            check = false;
                            counter2++;
                        }
                    }
                    //if all candidates have equal votes
                    else if (candidates[i].votes == candidates[k].votes)
                    {
                        if (candidates[i].votes == candidates[k].votes)
                        {
                            check = true;
                        }

                        else
                        {
                            check = false;
                            counter2++;
                        }

                    }
                }
                //print winners in a tie
                if (check == true && counter2 == 0 && counter3 == 0)
                {
                    printf("%s\n", candidates[i].name);
                    counter3++;

                }
            }


        }
        //print the absolute winner
        if (counter == candidate_count - 1)
        {
            printf("%s\n", candidates[i].name);
            counter = 0;

        }
        else
        {
            counter = 0;
        }
        counter2 = 0;
        counter3 = 0;
    }



    return;
}

