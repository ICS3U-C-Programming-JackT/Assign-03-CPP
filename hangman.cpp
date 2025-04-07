// Copyright (c) 2025 Jack Turcotte All rights reserved.
//
// Created by: Jack Turcotte
// Date: April 5, 2025
// Hangman program in C++

#include <string.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

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

void displayHangman(int lives) {
    for (int i = 0; i < 3; i++) {
        std::cout << hangman[lives][i] << std::endl;
    }
}

const char* chooseWord() {
    int index = std::rand() % MAX_WORDS;
    return wordList[index];
}

void setupArrays(
    const char* word, char currentWord[], char guessedWord[], int length) {
    for (int i = 0; i < length; i++) {
        currentWord[i] = word[i];
        guessedWord[i] = '_';
    }
}

bool checkValid(
    const char guessedWord[], const char currentWord[], int length) {
    for (int i = 0; i < length; i++) {
        if (guessedWord[i] != currentWord[i]) {
            return false;
        }
    }
    return true;
}

void mainGame() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::cout << START_MSG << std::endl;

    const char* chosenWord = chooseWord();
    if (OVERRIDE_WORD) {
        chosenWord = "hangman";
    }

    int wordLength = sizeof(chosenWord)-1;
    char currentWord[MAX_WORD_LENGTH];
    char guessedWord[MAX_WORD_LENGTH];
    char guessedChars[26];
    int guessedCount = 0;

    setupArrays(chosenWord, currentWord, guessedWord, wordLength);

    int currentLives = STARTING_LIVES;
    bool gameOngoing = true;

    while (gameOngoing) {
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

        std::cout << "Guess a single letter a-z: ";
        std::string userGuess;
        std::cin >> userGuess;

        if (userGuess.length() == 1 && std::isalpha(userGuess[0])) {
            char newLetter = std::tolower(userGuess[0]);

            bool letterGuessed = false;
            for (int i = 0; i < guessedCount; i++) {
                if (guessedChars[i] == newLetter) {
                    letterGuessed = true;
                    break;
                }
            }

            if (letterGuessed) {
                std::cout << "You already guessed this letter!\n";
            } else {
                guessedChars[guessedCount++] = newLetter;
                bool guessValid = false;

                for (int i = 0; i < wordLength; i++) {
                    if (currentWord[i] == newLetter) {
                        guessedWord[i] = newLetter;
                        guessValid = true;
                    }
                }

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

        if (checkValid(guessedWord, currentWord, wordLength)) {
            std::cout << "\nYou guessed the word! The word was: "
                      << chosenWord << std::endl;
            break;
        }

        if (currentLives == 0) {
            displayHangman(currentLives);
            std::cout << "You lost all your lives!\n";
            std::cout << "The word was: " << chosenWord << std::endl;
            break;
        }
    }

    std::cout << "\nRestart? (yes/no): ";
    std::string restart;
    std::cin >> restart;
    if (restart == "yes") {
        mainGame();
    }
}

int main() {
    mainGame();
    return 0;
}
