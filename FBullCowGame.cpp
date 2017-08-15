#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() {
	Reset();
}


void FBullCowGame::Reset(){
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "hank";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries () const {
	TMap<int32, int32> WordLengthToMaxtries{ {3,3},{ 4,5 },{ 5,6 },{ 6,7 },{ 7,9 },{ 8,11 },{ 9,15 } };
	//return MyMaxTries;
	return WordLengthToMaxtries[ MyHiddenWord.length() ] ;
}


EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (!IsIsogram(Guess)) {
		return EWordStatus::Not_Isogram;
	} else if ( !IsLowercase(Guess)){
		return EWordStatus::Not_Lowercase;
	} else  if (Guess.length() != GetHiddenWordLength() ) {
		return EWordStatus::Wrong_Length;
	}
	return EWordStatus::OK;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length();
	for (int32 i = 0; i < WordLength; i++) {
		for (int32 j = 0; j < WordLength; j++) {
			if (Guess[j] == MyHiddenWord[i]) {
				if (i == j) {
					BullCowCount.Bulls++;
				} else {
					BullCowCount.Cows++;
				};
			}	else {
			}
		}
	}
	if (BullCowCount.Bulls == WordLength ) {
		bGameIsWon = true;
	} else {
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const{
	if (Word.length() <= 1) {
		return true;
	}

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false;
		} else {
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const {
	for (auto Letter:Word) {
		if (!islower(Letter) ) {
			return false;
		}
	}
	return true;
}
