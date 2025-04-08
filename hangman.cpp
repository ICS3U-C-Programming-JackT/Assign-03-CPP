// Copyright (c) 2025 Jack Turcotte All rights reserved.
//
// Created by: Jack Turcotte
// Date: April 5, 2025
// Hangman program in C++

#include <string.h>

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

const int STARTING_LIVES = 5;
const char START_MSG[] = "Welcome to Jack's hangman game!";
const bool OVERRIDE_WORD = true;
const int MAX_WORD_LENGTH = 20;
const int MAX_WORDS = 5;

const char* wordList[MAX_WORDS] = {
    "hangman", "apple", "banana", "orange", "guitar"};

const char* hangman[6][3] = {
    {" O ", "/|/", "/ /"},
    {" O ", "/|/", "/  "},
    {" O ", "/|/", "   "},
    {" O ", "/| ", "   "},
    {" O ", " | ", "   "},
    {" O ", "   ", "   "}};

// Function to display hangman icon
void displayHangman(int lives) {
    for (int i = 0; i < 3; i++) {
        std::cout << hangman[lives][i] << std::endl;
    }
}

// Function to chose word randomly from list
const char* chooseWord() {
    int index = std::rand() % MAX_WORDS;
    return wordList[index];
}

// Function to set arrays to their respective strings as a list
void setupArrays(
    const char* word, char currentWord[], char guessedWord[], int length) {
    for (int i = 0; i < length; i++) {
        currentWord[i] = word[i];
        guessedWord[i] = '_';
    }
}

// Function to check if guessed word is the real word
bool checkValid(
    const char guessedWord[], const char currentWord[], int length) {
    for (int i = 0; i < length; i++) {
        if (guessedWord[i] != currentWord[i]) {
            return false;
        }
    }
    return true;
}

// Function to handle the real game, containing other functions
void mainGame() {
    // Make sure all random numbers are random, show start msg
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::cout << START_MSG << std::endl;

    // Setting the word to hangman if the word must be overrided
    const char* chosenWord = chooseWord();
    if (OVERRIDE_WORD) {
        chosenWord = "hangman";
    }

    // Create variables for word length, the current and guessed words and characters are guessed count

    int wordLength = strlen(chosenWord);
    char currentWord[MAX_WORD_LENGTH];
    char guessedWord[MAX_WORD_LENGTH];
    char guessedChars[26];
    int guessedCount = 0;

    // Setup the "arrays" after they've been set to empty
    setupArrays(chosenWord, currentWord, guessedWord, wordLength);

    // Set current lives to the default starting lives
    int currentLives = STARTING_LIVES;
    bool gameOngoing = true;

    // Loop for the game while it's ongoing
    while (gameOngoing) {

        // Print out guessed letters, the guessed word and hangman icon
        std::cout << "\nGuessed letters: ";
        for (int i = 0; i < guessedCount; i++) {
            std::cout << guessedChars[i] << ' ';
        }

        std::cout << "\nWord: ";
        for (int i = 0; i < wordLength; i++) {
            std::cout << guessedWord[i] << ' ';
        }

        std::cout << "\nHangman:\n";
        displayHangman(currentLives);

        // Get user input for the guessed letter
        std::cout << "Guess a single letter a-z: ";
        std::string userGuess;
        std::cin >> userGuess;

        // If the user guess is valid (1 letter a-z)
        if (userGuess.length() == 1 && std::isalpha(userGuess[0])) {
            char newLetter = std::tolower(userGuess[0]);

            // Checking if the user has already guessed this letter
            bool letterGuessed = false;
            for (int i = 0; i < guessedCount; i++) {
                if (guessedChars[i] == newLetter) {
                    letterGuessed = true;
                    break;
                }
            }

            // Checking if the letter has been guessed
            if (letterGuessed) {
                std::cout << "You already guessed this letter!\n";
            } else {
                guessedChars[guessedCount++] = newLetter;
                bool guessValid = false;

                //Check if the guessed letter is in the word, update guessed word "array"
                for (int i = 0; i < wordLength; i++) {
                    if (currentWord[i] == newLetter) {
                        guessedWord[i] = newLetter;
                        guessValid = true;
                    }
                }

                // Print respective outputs, take away lives if wrong!
                if (guessValid) {
                    std::cout << "Nice! The word contains the character '"
                              << newLetter << "'\n";
                } else {
                    std::cout << "Aw, that letter isn't in the word!\n";
                    currentLives--;
                }
            }
        } else {
            std::cout << "Invalid input! You entered '" << userGuess << "'\n";
        }
        // Check if the user guessed word is complete, if so then win
        if (checkValid(guessedWord, currentWord, wordLength)) {
            std::cout << "\nYou guessed the word! The word was: "
                      << chosenWord << std::endl;
            break;
        }

        // If the user has no more lives
        if (currentLives == 0) {
            displayHangman(currentLives);
            std::cout << "You lost all your lives!\n";
            std::cout << "The word was: " << chosenWord << std::endl;
            break;
        }
    }

    // Prompt restart
    std::cout << "\nRestart? (yes/no): ";
    std::string restart;
    std::cin >> restart;
    if (restart == "yes") {
        mainGame();
    }
}

// Fires main game function
int main() {
    mainGame();
    return 0;
}
