/* This is the console executable that makes use of the BullCow classs 
This acts as the view in the MVC pattern, and is responsible for all user interaction. 
For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class 
void PrintIntro();
void PlayGame();
FText GetValidGuess(); 
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // intantiates a new game, which we re-use across plays

// the entry point for our application 
int main() 
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);

	return 0; // Exit the aplications
}



void PrintIntro() 
{
	// introduce the game
	constexpr int32 WORD_LENGTH = 5;
	std::cout << "\n\n Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "            }   {                           " << std::endl;
	std::cout << "            (O o)   [(o O)]                 " << std::endl;
	std::cout << "    /--------( )      ( ) ---------\\      " << std::endl;
	std::cout << "   /| BULL  |            |  Cow   | \\     " << std::endl;
	std::cout << "    |------ |            |--------|			" << std::endl;
	std::cout << "    |       |            |        |         " << std::endl;
	std::cout << "    ^       ^            ^        ^         " << std::endl;
	
	std::cout << " Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'am thinking of?\n";
	std::cout << " An isogram is a word without repeating letters" << std::endl;
	std::cout << " Bull stands for (Bullsye) and Cow stands for (right letter wrong placement)/n";
	std::cout << std::endl;
	std::cout << std::endl;
	return;
}

// plays a single game to completion 
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game 
	// is NOT won and there are still tries remaining 
	while ( ! BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) 
	{
		FText Guess = GetValidGuess();
		
		// Submit valid guess to the game, and receive counts 
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	} 
	
	PrintGameSummary();
	return;
}

// Loop continually until the user gets valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {

		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << " Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << " Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << " Please enter a word without repeating letters. \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << " Please enter all lowercase letters. \n\n";
			break;

		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); //keep looping till we get no errors
	return Guess;
} 

bool AskToPlayAgain()
{
	std::cout << " Do you want to play again? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << " WELL DONE - YOU WIN! \n";
	}
	else 
	{
		std::cout << " TO BAD SO SAD - Better LUCK NEXT TIME!\n";
	}
}
