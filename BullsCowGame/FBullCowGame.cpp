#pragma once
#include "FBullCowGame.h"
#include<map>
#define TMap std::map

FBullCowGame::FBullCowGame(){
	Reset();
}

int32 FBullCowGame::GetCurrentTry() const{ return MyCurrentTry; }
bool FBullCowGame::IsGameWon() const { return bWinStatus; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {4,6}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[GetHiddenWordLength()]; 
}

void FBullCowGame::Reset(){
	const FString HIDDEN_WORD = "trench";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bWinStatus = false;
	return;
}


EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const{
	if (!IsIsogram(Guess)) { //Not isogram
		return EWordStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) { //Not lowercase
		return EWordStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) {
		return EWordStatus::Wrong_Length;
	}
	else {
		return EWordStatus::OK;
	}
}

// recieves a VALID guess and increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess){	
	MyCurrentTry++;
	FBullCowCount BullCowCount;	
	int32 WordLength = MyHiddenWord.length();
	//iterate through hidden word
	for (int32 i = 0; i < WordLength; i++) {
		//iterate through guess
		for (int32 j = 0; j < WordLength; j++) {
			//compare the guess with the hidden word
			if ((Guess[j] == MyHiddenWord[i]) && (i == j)) {
				BullCowCount.Bulls++;
			}
			else if ((Guess[j] == MyHiddenWord[i]) && (i !=j )) {
				BullCowCount.Cows++;
			}
			else {
				//this code will never be executed.
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bWinStatus = true;
	}
	else {
		bWinStatus = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const{
	if (Word.length() < 1) { return true; }

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) {
		Letter = tolower(Letter); //handle mixed case
		if (LetterSeen[Letter]) {
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}
	}
	return true; // for cases like '\0'
}

bool FBullCowGame::IsLowerCase(FString Word) const{
	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}
