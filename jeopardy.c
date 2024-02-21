/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2024, Hasan Khan , David Hanna, Rishab Sachedeva
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"


// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here
// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens)
{
    const char delim[3] = " \n";
    tokens[0] = strtok(input, delim);  // First token (category)
    tokens[1] = strtok(NULL, delim);   // Second token (value)
}

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players)
{
    // Sort players based on their scores (descending order)
    for (int i = 0; i < num_players - 1; i++)
    {
        for (int j = 0; j < num_players - i - 1; j++)
        {
            if (players[j].score < players[j + 1].score)
            {
                // Swap players
                player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }

    // Display results
    printf("\nGame Results:\n");
    for (int i = 0; i < num_players; i++)
    {
        printf("%d. %s - Score: %d\n", i + 1, players[i].name, players[i].score);
    }
}

int main(int argc, char *argv[])
{
    player players[NUM_PLAYERS];
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    initialize_game();

    // Prompt for players names
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        printf("Enter name for Player %d: ", i + 1);
        fgets(players[i].name, MAX_LEN, stdin);
        // Remove newline character if present
        players[i].name[strcspn(players[i].name, "\n")] = '\0';
        players[i].score = 0;
    }

    // Game loop
    while (1)
    {
        // Display categories and question values
        display_categories();

        // Prompt for the player who will pick the category and question
        printf("Enter the name of the player who will pick the category: ");
        fgets(buffer, BUFFER_LEN, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        // Validate player name
        if (!player_exists(players, NUM_PLAYERS, buffer))
        {
            printf("Invalid player name. Try again.\n");
            continue;
        }

        // Prompt for category and dollar amount
        printf("Enter the category and dollar amount (e.g., programming 100): ");
        fgets(buffer, BUFFER_LEN, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        // Tokenize input to get category and value
        char *tokens[2];
        tokenize(buffer, tokens);
        char *category = tokens[0];
        int value = atoi(tokens[1]);

        // Validate category and value
        if (already_answered(category, value))
        {
            printf("Question already answered. Pick another.\n");
            continue;
        }

        // Display the question
        display_question(category, value);

        // Prompt for the answer
        printf("Enter your answer (start with 'what is' or 'who is'): ");
        fgets(buffer, BUFFER_LEN, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        // Validate and update score
        if (valid_answer(category, value, buffer))
        {
            printf("Correct!\n");
            // Update player's score
            update_score(players, NUM_PLAYERS, buffer, value);
        }
        else
        {
            printf("Incorrect! The correct answer is: %s\n", questions[value].answer);
        }

        // Mark the question as answered
        questions[value].answered = true;

        // Check if all questions are answered
        int allAnswered = 1;
        for (int i = 0; i < NUM_QUESTIONS; i++)
        {
            if (!questions[i].answered)
            {
                allAnswered = 0;
                break;
            }
        }

        if (allAnswered)
        {
            // Display final results and exit the game
            show_results(players, NUM_PLAYERS);
            break;
        }
    }

    return EXIT_SUCCESS;
}
