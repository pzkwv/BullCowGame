#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//using namespace std;
// to make syntax unreal friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
FBullCowGame BCGame;



int main(){

	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	
	return 0;
}

void PrintIntro() {
	const int32 WORD_LENGTH = BCGame.GetHiddenWordLength();
	std::cout << "\n\nWelcome to Bulls and Cows\n";
	std::cout << "Can you guess the " << WORD_LENGTH << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame() {
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	//std::cout << BCGame.GetMaxTries() << std::endl;
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries ) {

		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n";

		//std::cout << "Your guess: " << Guess << std::endl;
		std::cout << std::endl;
	}
	PrintGameSummary();
	return;
}

FText GetValidGuess() {
	EWordStatus Status = EWordStatus::Invalid_Status;
	FText Guess = "";
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of "<< BCGame.GetMaxTries() <<  ". Enter your guess: ";
		
		std::getline(std::cin, Guess);
		//std::cout << "Your guess: " << Guess << std::endl;

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EWordStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EWordStatus::Not_Lowercase:
			std::cout << "Please enter lower case letters.\n\n";
			break;
		case EWordStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		}
	} while (Status != EWordStatus::OK);
	return Guess;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);

	std::cout << "Is it y? " << (Response[0] == 'y');
	std::cout << std::endl;

	return Response[0] == 'y' || Response[0] == 'Y';
}

void PrintGameSummary() {
	if (BCGame.IsGameWon() ) {
		std::cout << "WELL DONE - YOU WIN!\n";
	} else {
		std::cout << "Better luck next time!\n";
	}
	return;
}
