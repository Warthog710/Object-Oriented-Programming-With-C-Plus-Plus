//Program name: Pig Game
//Program Description: This program pit the user in a game of dice against the computer.
//My name: Quinn Roemer W1582947
//CISP 400 T/Th FLC 9-10:20am
//August 26th 2017

#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <string>
#include <ctype.h>
#include <algorithm>

using namespace std;

int randomNumber(); //This function is used to create a random number between 0 and 6.
int pTurn(int pScore); //This function is where all the code for the players turn is located.
int cTurn(int cScore, int pScore); //This function is where all the code for the computers turn is located.
string sUp(string answer); //This function uppercases all letters contained in a string.

int main() //Main body of code to execute.
{
	int tScore = 0, pScore = 0, cScore = 0; //Intilizing the needed variables.
	string answer; //Creating a string that the user will use to answer certain questions.

	srand((unsigned)time(0)); //Creating a seed for the rand function.


	cout << "Welcome to the Pig game! In this game you will play against the computer\nin a game of luck. The first to reach a score of 100 will win. Good luck!" << endl; //This statement welcomes the user to the program and informs them what it does.

	cout << "\nAre you ready to play? Enter yes to begin or help for instructions." << endl; //This statement asks the user if they are ready to play the game.
	cin >> answer; //Reading the inputted answer.
	answer = sUp(answer); //Sending the answer to the sUp function to be uppercased.

	while ((answer != "YES") && (answer != "HELP")) { // Bonus Input Validation, throughout this program the users response will be checked to see if it works. If not, they will be asked to enter a different response.
		cout << "\nPlease enter a valid input\n"; //Informing the user they entered a bad input.
		cout << "\nAre you ready to play? Enter yes to begin or help for instructions." << endl; //Asking the user to input a different response.
		cin >> answer; //Reading the inputted answer.
		answer = sUp(answer); //Sending the answer to the sUP function to be uppercased.
	}
	if (answer == "HELP") { // Bonus If the user enters help they will be given instruction to play the game. 
		cout << "\nTo play the game you must roll a dice on your turn. You can roll the dice as\nmany times as you like but if you roll a 1 you lose all of the points you\nhave accumalated. If you enter the word 'hold' the points you have accumalated\nduring your turn will be added to your current score. The object of the game\nis to beat the computer to 100 points. Good Luck!\n" << endl; //This line of code prints instruction to the game.
		cout << "\nAre you ready to play? If so, enter yes." << endl; //Asking the user to enter a response.
		cin >> answer; //Reading the inputted answer.
		answer = sUp(answer);
		while (answer != "YES") {  //Input validation loop.
			cout << "\nPlease enter a valid input\n"; //Informing the user they entered a bad input.
			cout << "\nAre you ready to play? If so, enter yes." << endl; //Asking the user to input a different response.
			cin >> answer; //Reading the inputted answer.
			answer = sUp(answer); //Sending the answer to the sUp function to be uppercased.
		}

	}

	while (answer == "YES") { //This loop will iterate as long as the string answer is YES.
		while (1) { //This loop will keep iterating until broken out of.
			cout << "\nType roll to roll the dice. Type hold to end your turn." << endl; //Asking the user what they want to do for their turn.
			cin >> answer; //Reading the inputted answer.
			answer = sUp(answer); //Sending the answer to the sUp function to be uppercased.

			while ((answer != "ROLL") && (answer != "HOLD")) { //Input validation loop.
				cout << "\nPlease enter a valid input\n"; //Informing the user they entered a bad input.
				cout << "\nType roll to roll the dice. Type hold to end your turn." << endl; //Asking the user to input a different response.
				cin >> answer; //Reading the inputted answer.
				answer = sUp(answer); //Sending the answer to the sUp function to be uppercased.
			}

			if (answer == "ROLL") { //If the user answers "roll" the player function will be executed.
				tScore = pTurn(pScore); //Sending the current score to the player function.
				if (tScore != 0) { //If the player function returns 0 the player score will not be updated. Otherwise, it will be.
					pScore = tScore; //Setting the player score equal to the temporary score.
				}
				if (pScore >= 100) { //If the player score is over or equal to 100 points the player will be informed that they won the game.
					cout << "\nCongratulations! You won the game!" << endl; //Informing the player that they won the game.
					break; //Breaking out of the while loop.
				}
				cout << "\nYou have a total of " << pScore << " points. It is now the computers turn.\n" << endl; //Informing the player of their total score and telling them that it is now the computers turn.
				tScore = 0; //Resetting the temporary score variable.
			}
			tScore = cTurn(cScore, pScore); //After the players turn is over or if they skipped their turn the computer turn function will be executted.
			if (tScore != 0) { //If the computer function returns 0 the computer score will not be updated. Otherwise, it will be.
				cScore = tScore; //Setting the computers score equal to the temporary score.
			}
			if (cScore >= 100) { //If the computers score is over or equal to 100 points the player will be informed that the computer has won.
				cout << "\nThe computer won the game with a total of " << cScore << " points. Better luck next time." << endl; //Informing the player of the computers victory.
				break; //Breaking out of the while loop.
			}
			cout << "\nThe computer has a total of " << cScore << " points. It is now your turn.\n" << endl; //Informing the player of the computers current score.
			tScore = 0;

		}
		cout << "\nWould you like to play again? Enter yes to play again or no to quit." << endl; // Bonus After the computer or player wins the game they are given the option to play again.
		cin >> answer; //Reading the inputted answer.
		answer = sUp(answer); //Sending the answer to the sUp function to be uppercased.
		while ((answer != "YES") && (answer != "NO")) { //Input validation loop.
			cout << "\nPlease enter a valid input\n"; //Informing the user they entered a bad input.
			cout << "\nAre you ready to play? Enter yes to begin or no to quit." << endl; //Asking the user to input a different response.
			cin >> answer; //Reading the inputted answer.
			answer = sUp(answer); //Sending the answer to the sUp function to be uppercased.
		}
		if (answer == "YES") { //If the answer is YES some key variables will be reset to 0 so the game can be played again.
			tScore = 0; //Resetting the variable to 0.
			pScore = 0; //Resetting the variable to 0.
			cScore = 0; //Resetting the variable to 0.
		}
		else {//If anything else is entered the program will say goodbye and quit.
			cout << "Goodbye" << endl; //Printing goodbye to the terminal.
			return 0;
		}
	}
} //End of main.

int randomNumber() { //This function creates a random number between 1 and 6.

	int rnum; //Creating a variable to hold the generated number.

	rnum = rand() % 7; //Generating the random number within a certain range.

	while (rnum == 0){ //A while loop that will iterate as long as the generated number is 0.
		rnum = rand() % 7; //Generating the random number within a certain range.
	}
	return rnum; //Returning the generated number.
}

int pTurn(int score) { //This function contains all of the code for the players turn.

	int roll; //Creating a variable to hold the number from the randomNumber function.
	string answer = "ROLL"; //Creating a string and setting it to ROLL

	while (answer == "ROLL") { //While the string answer = ROLL this loop will iterate.
	roll = randomNumber(); //Caling the function randomNumber to simulate the roll of a six-sided dice.

		if (roll == 1) { //If the roll is one the player will be informed they lost there turn and this function will return 0.
			cout << "\nYou rolled a 1. You lose your turn." << endl; //Informing the user they lost their turn.
			return 0; //Returning 0 to main.
		}
		else { //If the roll is not one the player will be informed of what they rolled and it will be added to their score this turn.
			score = score + roll; //Adding the roll to the current score.
			cout << "\nYou rolled " << roll << " your total score is " << score << ".\n"; //Informing the player of their roll and current score.
		}

		cout << "\nType roll to roll again, or hold to end your turn." << endl; //Asking the player if they want to roll again or if they want to hold.
		cin >> answer; //Reading the answer.
		answer = sUp(answer); //Sending the answer to the sUp function to be uppercased.

		while ((answer != "ROLL") && (answer != "HOLD")) { //Input validation loop.
			cout << "\nPlease enter a valid input\n"; //Informing the user they entered a bad input.
			cout << "\nType roll to roll again, or hold to end your turn." << endl; //Asking the user to input a different response.
			cin >> answer; //Reading the answer.
			answer = sUp(answer); //Seding the answer to the sUp function to be uppercased.
		}
		if (answer == "HOLD") //If the user answers hold their current score will be sent back to main.
			return score; //Returning their score.
	}
	return score; //Returning their score.
}

int cTurn(int score, int pScore) { //This function contains all of the code for the computers turn.
	int turn = randomNumber(); //Setting the variable turn to a random number generated by the function randomNumber. 
	int mod, count, roll = 0; //Intilizing several needed variables.
	mod = (pScore - score) / 10; // Bonus Smarter AI, this ai will determine how many points it is behind the player and take a greater risk depending on how many points behind the player it is. Also, as soon as the computer reaches 100 it ends its turn instead of continuing.
	if (mod <= 0) //If the modifier for the ai's number of turns is less than or equal to 0 it will be set to 0. This is to prevent negative numbers.
		mod = 0; //Setting mod to 0.
	turn = mod + turn; //Adding the random turn count with the modifier to get the number of turns the computer will attempt.
	for (count = 0; count <= turn; count++) { //A for loop that will iterate a certain number of times depending on the value of turn.
		roll = randomNumber(); //Calling the function randomNumber and storing the generated number in roll.
		if (roll == 1) //If the roll equals 1 the function will return 0.
			return 0; //Returning 0.
		score = score + roll; //Adding the value of roll to the current score for the computer.
		if (score >= 100) //If at any time the computer score is at or above 100 the function will return the score.
			return score; //Returning the score.
	}
	return score; //Once the for loop is done iterating the score will be returned.
}

string sUp(string answer) { //This function takes a string and uppercases every letter of it.
	transform(answer.begin(), answer.end(), answer.begin(), ::toupper); //Transforming the letters to uppercase.
	return answer; //Returning the uppercased string.
}