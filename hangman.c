#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void print_board(const char *line, int wrong_guess)
{
    int i;
    int part_2 = 5;
    puts(" _____"); // this is my hangman post
    puts(" |    |");
    if (wrong_guess == 1)
    {
        puts(" |    O"); // this gives us only the head of the hangman if only one letter is wrong
    }
    else if (wrong_guess == 0)
    {
        puts(" |");
    }
    if (wrong_guess >= 2) // here we will sort all of the ways that the hangman can look like based on the amount of incorecct guesses
    {
        if (wrong_guess == 2)
        {
            puts(" |    O");
            puts(" |    |");
        }
        if (wrong_guess == 3)
        {
            puts(" |    O");
            puts(" |   /|");
        }
        if (wrong_guess == 4)
        {
            puts(" |    O");
            puts(" |   /|\\");
        }
        if (wrong_guess == 5)
        {
            puts(" |    O");
            puts(" |   /|\\");
            puts(" |   /");
        }
        if (wrong_guess == 6)
        {
            puts(" |    O");
            puts(" |   /|\\");
            puts(" |   / \\");
        }
    }
    for (i = 1; i < part_2; i++)
    {
        puts(" |");
    }
    printf("\n");
    for (i = 0; i < 6; i++)
    {
        printf("%c ", line[i]);
    }
}

int main()
{
    int i, wrong_guess = 0;
    bool correct = false;
    char word[7], guess;                                 // added space for null terminator
    char line[7] = {'_', '_', '_', '_', '_', '_', '\0'}; // added null terminator
    word[6] = '\0';                                      // ensure null terminator for word

    FILE *file = fopen("guess.txt", "r");
    char file_name[] = "guess.txt";

    if (file == NULL)
    {
        printf("Couldn't open file.");
        return 1;
    }

    printf("Welcome to hangman! In order to start the game, player 1 needs to open 'guess.txt' and type in a 6 letter word. Good luck!");
    fscanf(file, "%s", word);
    fclose(file);

    // printf("Please input a 6 letter word in order to start the game: \n");
    // for (i = 0; i < 6; i++)
    // {
    //     scanf(" %c", &word[i]); // to keep it simple (for now) we will suppose that the input is correct
    // }
    getchar();

    while (wrong_guess < 6)
    {
        correct = false;
        printf("\n");
        printf("Enter your guess: \n");
        scanf(" %c", &guess);

        bool found = false;
        for (i = 0; i < 6; i++)
        {
            if (guess == word[i] && line[i] == '_')
            {
                line[i] = guess;
                found = true;
            }
        }

        if (!found)
        {
            wrong_guess++;
        }

        // check if all letters have been guessed
        bool word_guessed = true;
        for (i = 0; i < 6; i++)
        {
            if (line[i] == '_')
            {
                word_guessed = false;
                break;
            }
        }

        if (word_guessed)
        {
            print_board(line, wrong_guess);
            puts("\nCongratulations! You have guessed the word! :)");
            break;
            return 0;
        }

        print_board(line, wrong_guess);
    }

    if (wrong_guess == 6)
    {
        printf("\nSorry, you lost :( The word was: %s\n", word);
    }

    return 0;
}