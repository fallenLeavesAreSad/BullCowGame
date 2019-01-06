#pragma once
#include<string>

using int32 = int;
using FString = std::string;

enum class EWordStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

//All values initialized to zero
struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};



class FBullCowGame {
public:
	FBullCowGame();
	int32 GetMaxTries() const; //Return the maximum number of tries
	int32 GetCurrentTry() const; //Gets the current attempt
	bool IsGameWon() const; //Checks the status of game (Won or lost)
	int32 GetHiddenWordLength() const;
	EWordStatus CheckGuessValidity(FString) const; //Checks if the guess is a valid one
	void Reset(); //Reset the game
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry;
	int32 MaxTries;
	FString MyHiddenWord;
	bool bWinStatus;
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};
