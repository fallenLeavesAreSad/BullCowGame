//Bull and Cow game, naming schemes are according to Unreal Coding Standards
//Practice Project

#include<iostream>
#include<string>
#include"FBullCowGame.h"

using int32 = int;
using FText = std::string;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGameSummary();
bool bAskToPlayAgain();

FBullCowGame BCGame; //Instantiation of the game	


//Entry point32
int main(){
	do {
		PrintIntro();
		PlayGame();
	} while(bAskToPlayAgain() == 1);
	return 0;
}

//introduce player to the game
void PrintIntro(){
	std::cout << "\n\nWelcome to Bull and Cow, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I am thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame(){
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries()) {
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls: " << BullCowCount.Bulls;
		std::cout << " Cows: " << BullCowCount.Cows << std::endl;
		std::cout << std::endl;
	}
	PrintGameSummary();
	return;
}

//get a valid guess from the player
FText GetValidGuess(){	
	FText Guess = "";
	EWordStatus Status = EWordStatus::Invalid_Status;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter a guess: ";
		getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EWordStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter isogram\n\n";
			break;
		case EWordStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EWordStatus::Not_Lowercase:
			std::cout << "Please make sure that your guess is in lower case.\n\n";
			break;
		default:
			break;
		}
	} while (Status != EWordStatus::OK);
	return Guess;
}

bool bAskToPlayAgain(){
	std::cout << "Do you want to play again with the same word? (y/n) > ";
	FText Response;
	getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "Mission Passed! Respect+++++" << std::endl;
	}
	else {
		std::cout << "                          ^ ^" << std::endl;
		std::cout << "                         (O.O)/" << std::endl;
		std::cout << "Better Luck next time    /[_]/" << std:: endl;
		std::cout << "                         _| |_" << std::endl;
	}
}
