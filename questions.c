/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2024, Hasan Khan , David Hanna, Rishab Sachedeva
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "questions.h"

// Sample categories
char categories[NUM_CATEGORIES][MAX_LEN] = {
    "General Knowledge",
    "Sports",
    "TV Hollywood"
};

// Sample questions and answers
question questions[NUM_QUESTIONS];

void initialize_game(void)
{
    // Initialize questions dynamically
    strcpy(questions[0].category, "General Knowledge");
    snprintf(questions[0].question, MAX_LEN, "What is the capital of France?");
    snprintf(questions[0].answer, MAX_LEN, "Paris");
    questions[0].value = 100;
    questions[0].answered = false;

    // Initialize questions for Sports
    strcpy(questions[1].category, "Sports");
    snprintf(questions[1].question, MAX_LEN, "In which sport would you perform a slam dunk?");
    snprintf(questions[1].answer, MAX_LEN, "Basketball");
    questions[1].value = 100;
    questions[1].answered = false;

    // Initialize questions for TV Hollywood
    strcpy(questions[2].category, "TV Hollywood");
    snprintf(questions[2].question, MAX_LEN, "Who played the character Jack Dawson in Titanic?");
    snprintf(questions[2].answer, MAX_LEN, "Leonardo DiCaprio");
    questions[2].value = 100;
    questions[2].answered = false;
}
void display_categories(void)
{
    printf("\nCategories:\n");
    for (int i = 0; i < NUM_CATEGORIES; i++)
    {
        printf("%s\n", categories[i]);
    }
}

// Function to display a specific question
void display_question(char *category, int value)
{
    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value)
        {
            printf("\n%s - $%d\n", category, questions[i].value);
            printf("%s\n", questions[i].question);
            return;
        }
    }
    printf("Question not found.\n");
}

// Function to validate the answer for a specific question
bool valid_answer(char *category, int value, char *answer)
{
    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value)
        {
            return (strcmp(questions[i].answer, answer) == 0);
        }
    }
    return false; // Question not found
}
// Function to check if a question has already been answered
bool already_answered(char *category, int value)
{
    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value)
        {
            return questions[i].answered;
        }
    }
    return false;
}

