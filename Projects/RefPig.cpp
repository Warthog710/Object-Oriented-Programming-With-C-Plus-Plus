//Program name: RefPig
//Program Description: This program simualtes a game of pig vs the computer or another player.
//My name: Quinn Roemer W1582947
//CISP 400 T/Th FLC 9-10:20am
//November 30th 2017

#include <iostream>
#include <time.h>
#include <fstream>
#include <string>

using namespace std;

//Abstract base class for Computer and Human classes.
// Constraint 1 - Using object oriented programming techniques.
// Constraint 2 - Create an abstract class called Player.
class Player 
{
protected:
	//This variable holds the score of the player.
	int score = 0;
public:

	//Virtual roll method.
	virtual int roll() = 0;

	//Getter method for score.
	int getScore()
	{
		return score;
	}

	//Setter method for score.
	void setScore(int iTemp)
	{
		//Setting score to send variable.
		score = iTemp;
	}
};
//End Player class.

//Dice class - holds the logic for rolling a dice.
// Constraint 3 - Create a class called dice and use composition with the other classes.
class Dice
{
public:
	//This variable holds the rolled number.
	int roll;
	//This variable holds the value that will be modded to rand().
	int mod;

	//Class constructor.
	Dice(int sides)
	{
		//Setting mod to recieved variable +1.
		mod = sides + 1;
	}

	//Defaut Constructor.
	Dice()
	{
		//Setting mod to 6.
		mod = 6;
	}

	//Copy method.
	void copy(const Dice &temp)
	{
		//This method accepts a Dice object and sets the mod equal to it.
		this->mod = temp.mod;
	}

	//This method returns a dice roll within a certain range.
	int diceRoll()
	{
		//This loop iterates until broken out of.
		while (true)
		{
			//Setting roll = to the return of rand() % mod.
			roll = rand() % mod;

			//If roll = 0 this code will execute.
			if (roll == 0)
			{
				//Continueing to the next iteration.
				continue;
			}

			//Else, the loop will be broken out of.
			else
			{
				//Breaking out of while loop.
				break;
			}
		}
		//Returning the value of roll.
		return roll;
	}

	//Setter method for mod variable.
	void setMod(int iTemp)
	{
		//Setting mod to the recieved variable.
		mod = iTemp;
	}
};
//End of Dice class.

//Class Computer - inherited from Class Player
// Constraint 2 - It will have 2 child classes: Computer and Human.
class Computer : public Player
{
public:
	//Creating Dice object titled sides.
	Dice sides;

	//Class constructor.
	Computer(const Dice &temp)
	{
		//Setting sides to the value of Dice temp.
		sides.copy(temp);
	}

	//Roll method - Overiding Player's roll method.
	int roll()
	{
		//Returning the dice roll.
		return sides.diceRoll();
	}

	//Overloaded << operator.
	// Constraint 4 - Use operator overloading where appropriate.
	friend ostream &operator<<(ostream &out, Computer temp);
};
//End of Computer class.

//Human Class - Inherited from Player Class.
// Constraint 2 - It will have 2 child classes: Computer and Human.
class Human : public Player
{
public:
	//Creating Dice object titled sides.
	Dice sides;	

	//Class constructor.
	Human(const Dice &temp)
	{
		//Setting sides to the value of temp.
		sides.copy(temp);
	}

	//Roll method - Overiding Player's roll method.
	int roll()
	{
		//Returning the dice roll.
		return sides.diceRoll();
	}

	//Overloaded << operator.
	friend ostream &operator<<(ostream &out, Human temp);
};
//End of Human class.

//Overloaded << operator for Computer class.
ostream &operator<<(ostream& out, Computer temp)
{
	//Displaying the total score saved in the object.
	out << "Total points: " << temp.getScore();
	//Returning out.
	return out;
}

//Overloaded << operator for Human class.
// Constraint 4 - Use operator overloading where appropriate.
ostream &operator<<(ostream& out, Human temp)
{
	//Displaying the total score saved in the object.
	out << "Total points: " << temp.getScore();
	//Returning out.
	return out;
}

//Function prototypes - For further description see individual functions.
void playGame(Dice &diceObj, int, int&, int&);
void playerTurn(Human &humObj, int);
void simpleAI(Computer &comObj);
void hardAI(Computer &comObj);
void toContinue();
char pigMenu();

//Main function to execute.
int main()
{
	//Creating a seed for the rand() function.
	srand(time(NULL));

	//This variable will be used to hold the user's answer to certain questions.
	char answer;

	//This variable determines when the while loop will be broken out of.
	bool keepGoing = true;

	//Several needed int variables.
	int computerWins = 0;
	int playerWins = 0;
	int numGames = 1;
	int iTemp;

	//Outputting welcome message.
	cout << "Welcome to the Ref Pig Game! This game pits you against the computer or another player" << endl;
	cout << "in a game of dice. The first person to one-hundred wins!" << endl;

	//Dice object intilized to a total of 6 sides.
	Dice sides(6);

	//Creating file pointer.
	ofstream myfile;

	//This loop will iterate while keepGoing is true.
	while (keepGoing == true)
	{
		//Setting answer to the return of the function pigMenu().
		answer = pigMenu();

		//Switching the variable answer.
		switch (answer)
		{

		//If the case is 1 this code will execute.
		case '1':
			// Constraint 6 - Have the program create a log file which details all the moves.
			//Opening a file in append mode.
			myfile.open("refPigGame.txt", ios::app);

			//Outputting Game number message to file.
			myfile << "\n==============================================" << endl;
			myfile << "=                    Game " << numGames << "\t\t     =" << endl;
			myfile << "=               Player vs SimpleAI           =" << endl;
			myfile << "==============================================" << endl;

			//Closing the file.
			myfile.close();

			//Calling the playGame function with 1 as the mode.
			playGame(sides, 1, computerWins, playerWins);

			//Incrementing numGames variable.
			numGames++;
			//Calling toContinue().
			toContinue();
			//Breaking out of case.
			break;

		//If the case is 2 this code will execute.
		case '2':
			//Opening a file in append mode.
			myfile.open("refPigGame.txt", ios::app);

			//Outputting Game Number message to file.
			myfile << "\n==============================================" << endl;
			myfile << "=                    Game " << numGames << "\t\t     =" << endl;
			myfile << "=               Player vs HardAI             =" << endl;
			myfile << "==============================================" << endl;

			//Closing the file.
			myfile.close();

			//Calling the playGame function with 2 as the mode.
			playGame(sides, 2, computerWins, playerWins);
			
			//Incrementing the numGames variable.
			numGames++;
			//Calling the toContinue() function.
			toContinue();
			//Breaking out of the case.
			break;

		//If the case is 3 this code will execute.
		// Bonus - The player is able to play against another human player.
		case '3':
			//Opening a file in append mode.
			myfile.open("refPigGame.txt", ios::app);

			//Outputting Game Number message to file.
			myfile << "\n==============================================" << endl;
			myfile << "=                    Game " << numGames << "\t\t     =" << endl;
			myfile << "=               Player vs Player             =" << endl;
			myfile << "==============================================" << endl;

			//Closing the file.
			myfile.close();

			//Calling the playGame function with 3 as the mode.
			playGame(sides, 3, computerWins, playerWins);

			//Incrementing numGames variable.
			numGames++;
			//Calling toContinue() function.
			toContinue();
			//Breaking out of the case.
			break;

		//If the case is 4 this code will execute.
		// Bonus - The user is able to set the number of sides on the dice.
		case '4':
			//Prompting the user to enter number of desired dice sides.
			cout << "\nPlease enter the desired number of dice sides." << endl;
			//Reading the inputted variable.
			cin >> iTemp;
			//Setting sides object to the inputted number.
			sides.setMod(iTemp);
			//Informing the user that the dice is set.
			cout << "\nDice set!" << endl;
			//Calling toContinue() function.
			toContinue();
			//Breaking out of the case.
			break;

		//If the case is 5 this code will execute.
		// Bonus - Can play multiple games. The code keeps track of the wins/losses of both the player and computer.
		case '5':
			//Outputting the number of games won/lost.
			cout << "\nWin/Loss Ratio" << endl;
			cout << "=======================" << endl;
			cout << "Computer: " << computerWins << endl;
			cout << "Player: " << playerWins << endl;

			//Informing the user of a program limitation.
			cout << "\nNote: In player vs player games both player 1 and player 2 increment player wins." << endl;
			//Calling the toContinue() function.
			toContinue();
			//Breaking out of the case.
			break;

		//If the case is 6 this code will execute.
		// Bonus - You can remove the existing log file through the program.
		case '6':
			//Removing the file titled "refPigGame.txt."
			remove("refPigGame.txt");

			//Informing the user that the file was successfully removed.
			cout << "\nFile successfully removed!" << endl;
			//Calling the toContinue() function.
			toContinue();
			//Breaking out of the case.
			break;

		//If the case is 7 this code will execute.
		case '7':
			//Setting keepgoing to false.
			keepGoing = false;
			//Breaking out of the case.
			break;
		}
	}

	//Saying goodbye to the user... GOODBYE!!!!!! XD.
	cout << "\nGoodbye!" << endl;
	//Quiting the program.
	return 0;
}
//End of main function.

//playGame function - this function contains the code to actually play the game.
void playGame(Dice &diceObj, int mode, int& cWin, int& pWin)
{
	//Ignoring the last input.
	cin.ignore();

	//Creating a file pointer.
	ofstream myfile;

	//If the mode is 1 this code will execute.
	if (mode == 1)
	{
		//Creating a Human object.
		Human player(diceObj);
		//Creating a Computer object.
		Computer machine(diceObj);

		//Setting whoFirst to the return of rand().
		int whoFirst = rand() % 2;

		//If whoFirst = 0 this code will execute.
		if (whoFirst == 0)
		{
			//While players score and computers score is less than 100 this code will execute.
			while (player.getScore() < 100 && machine.getScore() < 100)
			{
				//Calling playerTurn function.
				playerTurn(player, 0);

				//If the player score is over 100 break out of the loop.
				if (player.getScore() >= 100)
				{
					//Breaking out of the loop.
					break;
				}

				//Calling simpleAI function.
				simpleAI(machine);
			}

			//If the player score is over 100 this code will execute.
			if (player.getScore() >= 100)
			{
				//Informing the user that they won the game... YEAH!!!
				cout << "\nThe player won the game!" << endl;

				//Opening a file in append mode.
				myfile.open("refPigGame.txt", ios::app);

				//Printing message to file.
				myfile << "\nThe player won the game!" << endl;
				//Closing file.
				myfile.close();

				//Incrementing pWin variable.
				pWin++;
			}

			//If the computers score is over 100 this code will execute.
			if (machine.getScore() >= 100)
			{
				//Informing the user that the computer won the game... BUMMER!!!
				cout << "\nThe computer won the game!" << endl;

				//Opening a file in append mode.
				myfile.open("refPigGame.txt", ios::app);

				//Printing message to file.
				myfile << "\nThe computer won the game!" << endl;
				//Closing file.
				myfile.close();

				//Incrementing cWin variable.
				cWin++;
			}

			//Returning to caller.
			return;
		}

		//If whoFirst == 1 this code will execute.
		if (whoFirst == 1)
		{
			//While players score and computers score is less than 100 this code will execute.
			while (player.getScore() < 100 && machine.getScore() < 100)
			{
				//Calling simpleAI function.
				simpleAI(machine);

				//If the computer score is over 100 this code will execute.
				if (machine.getScore() >= 100)
				{
					//Breaking out of the loop.
					break;
				}

				//Calling playerTurn function.
				playerTurn(player, 0);
			}

			//If the player score is over 100 this code will execute.
			if (player.getScore() >= 100)
			{
				//Informing the player that they won the game... FANTASTICAL!!!
				cout << "\nThe player won the game!" << endl;

				//Opening a file in append mode.
				myfile.open("refPigGame.txt", ios::app);

				//Printing a message to the file.
				myfile << "\nThe player won the game!" << endl;
				//Closing the file.
				myfile.close();

				//Incrementing pWin variable.
				pWin++;
			}

			//If the computers score is over 100 this code will execute.
			if (machine.getScore() >= 100)
			{
				//Informing the user that the computer won... WHY????
				cout << "\nThe computer won the game!" << endl;

				//Opening a file in append mode.
				myfile.open("refPigGame.txt", ios::app);

				//Printing a message to the file.
				myfile << "\nThe computer won the game!" << endl;
				//Closing the file.
				myfile.close();

				//Incrementing the cWin variable.
				cWin++;
			}

			//Returning to the caller.
			return;
		}
	}

	//If mode = 2 this code will execute.
	if (mode == 2)
	{
		//Creating a Human object.
		Human player(diceObj);
		//Creating a Computer object.
		Computer machine(diceObj);

		//Setting whoFirst to the return of rand().
		int whoFirst = rand() % 2;

		//If whoFirst = 0 this code will execute.
		if (whoFirst == 0)
		{
			//While players score and computers score is less than 100 this code will execute.
			while (player.getScore() < 100 && machine.getScore() < 100)
			{
				//Calling playerTurn function.
				playerTurn(player, 0);

				//If the players score is over 100 this code will execute.
				if (player.getScore() >= 100)
				{
					//Breaking out of the loop.
					break;
				}

				//Calling the hardAI function.
				hardAI(machine);
			}

			//If the players score is over 100 this code will execute.
			if (player.getScore() >= 100)
			{
				//Informing the user that they won the game... UNBELIEVABLE!!!
				cout << "\nThe player won the game!" << endl;

				//Opening a file in append mode.
				myfile.open("refPigGame.txt", ios::app);

				//Printing a message to the file.
				myfile << "\nThe player won the game!" << endl;
				//Closing the file.
				myfile.close();

				//Incrementing the pWin variable.
				pWin++;
			}

			//If the computers score is over 100 this code will execute.
			if (machine.getScore() >= 100)
			{
				//Informing the user that the computer won the game... PREDICTABLE!!!
				cout << "\nThe computer won the game!" << endl;

				//Opening a file in append mode.
				myfile.open("refPigGame.txt", ios::app);

				//Pringint a message to the file.
				myfile << "\nThe computer won the game!" << endl;
				//Closing the file.
				myfile.close();

				//Incrementing the cWin variable.
				cWin++;
			}

			//Returning to the caller.
			return;
		}

		//If whoFirst = 1 this code will execute.
		if (whoFirst == 1)
		{
			//While players score and computers score is less than 100 this code will execute.
			while (player.getScore() < 100 && machine.getScore() < 100)
			{
				//Calling the hardAI function.
				hardAI(machine);

				//If the computers score is over 100 this code will execute.
				if (machine.getScore() >= 100)
				{
					//Breaking out of the loop.
					break;
				}

				//Calling the playerTurn function.
				playerTurn(player, 0);
			}

			//If the players score is over 100 this code will execute.
			if (player.getScore() >= 100)
			{
				//Informing the user that they won the game... HA, TAKE THAT COMPUTER!!!
				cout << "\nThe player won the game!" << endl;

				//Opening a file in append mode.
				myfile.open("refPigGame.txt", ios::app);

				//Printing a message to the file.
				myfile << "\nThe player won the game!" << endl;
				//Closing the file.
				myfile.close();

				//Incrememting the pwin variable.
				pWin++;
			}

			//If the computer score is over 100 this code will execute.
			if (machine.getScore() >= 100)
			{
				//Informing the user that the computer won the game... OH NO! ITS TOO SMART!!!
				cout << "\nThe computer won the game!" << endl;

				//Opening a file in append mode.
				myfile.open("refPigGame.txt", ios::app);

				//Printing a message to the file.
				myfile << "\nThe computer won the game!" << endl;
				//Closing the file.
				myfile.close();

				//Incrementing the cWin variable.
				cWin++;
			}

			//Returning to the caller.
			return;
		}
	}

	//If the mode is 3 this code will execute.
	if (mode == 3)
	{
		//Creating two Human objects.
		Human player1(diceObj);
		Human player2(diceObj);

		//Setting whoFirst to the return of rand().
		int whoFirst = rand() % 2;

		//If whoFirst = 0 this code will execute.
		if (whoFirst == 0)
		{
			//While players score and computers score is less than 100 this code will execute.
			while (player1.getScore() < 100 && player2.getScore() < 100)
			{
				//Printing a message.
				cout << "\n=================================" << endl;
				cout << "=            Player 1           =" << endl;
				cout << "=================================" << endl;

				//Calling the playerTurn function.
				playerTurn(player1, 1);

				//If player 1 score is over 100 this code will execute.
				if (player1.getScore() >= 100)
				{
					//Breaking out of the loop.
					break;
				}

				//Printing a message.
				cout << "\n=================================" << endl;
				cout << "=            Player 2           =" << endl;
				cout << "=================================" << endl;

				//Calling the playerTurn function.
				playerTurn(player2, 2);
			}

			//If player1 score is over 100 this code will execute.
			if (player1.getScore() >= 100)
			{
				//Informing the user that Player 1 won the game... player 2 is sad :(
				cout << "\nPlayer 1 won the game!" << endl;

				//Opening a file in append mode.
				myfile.open("refPigGame.txt", ios::app);

				//Printing a message to the file.
				myfile << "\nPlayer 1 won the game!" << endl;
				//Closing the file.
				myfile.close();

				//Incrementing the pWin variable.
				pWin++;
			}

			//If player2 score is over 100 this code will execute.
			if (player2.getScore() >= 100)
			{
				//Informing the user that Player 2 won the game... player 1 is sad :(
				cout << "\nPlayer 2 won the game!" << endl;

				//Opening a file in append mode.
				myfile.open("refPigGame.txt", ios::app);

				//Printing a message to the file.
				myfile << "\nPlayer 2 won the game!" << endl;
				//Closing the file.
				myfile.close();

				//Incrementing the pWin variable.
				pWin++;
			}

			return;
		}

		//If whoFirst = 1 this code will execute.
		if (whoFirst == 1)
		{
			//While players score and computers score is less than 100 this code will execute.
			while (player1.getScore() < 100 && player2.getScore() < 100)
			{
				//Printing a message.
				cout << "\n=================================" << endl;
				cout << "=            Player 2           =" << endl;
				cout << "=================================" << endl;

				//Calling the playerTurn function.
				playerTurn(player2, 2);

				//If player2 score is over 100 this code will execute.
				if (player2.getScore() >= 100)
				{
					//Breaking out of the loop.
					break;
				}

				//Printing a message.
				cout << "\n=================================" << endl;
				cout << "=            Player 1           =" << endl;
				cout << "=================================" << endl;

				//Calling the playerTurn function.
				playerTurn(player1, 1);
			}

			//If player1 score is over 100 this code will execute.
			if (player1.getScore() >= 100)
			{
				//Informing the user that Player 1 won the game... WOOHOO!!!
				cout << "\nPlayer 1 won the game!" << endl;

				//Opening a file in append mode.
				myfile.open("refPigGame.txt", ios::app);

				//Printing a message to the file.
				myfile << "\nPlayer 1 won the game!" << endl;
				//Closing the file.
				myfile.close();

				//Incrementing the pWin variable.
				pWin++;
			}

			//If player2 score is over 100 this code will execute.
			if (player2.getScore() >= 100)
			{
				//Informing the user that Player 2 won the game... SIMPLY AMAZING!!!
				cout << "\nPlayer 2 won the game!" << endl;

				//Opening a file in append mode.
				myfile.open("refPigGame.txt", ios::app);

				//Printing a message to the file.
				myfile << "\nPlayer 2 won the game!" << endl;
				//Closing the file.
				myfile.close();

				//Incrementing the pWin variable.
				pWin++;
			}

			//Returning to the caller.
			return;
		}
	}
}
//End of playGame function.

//playerTurn function - This function contains the code for a human players turn.
void playerTurn(Human &humObj, int mode)
{
	//Creating a couple needed variables.
	string temp;
	int acumPoints = 0;
	int roll = 0;

	//Setting previousScore to the current score.
	int previousScore = humObj.getScore();

	//Creating a file pointer.
	ofstream myfile;

	//Opening a file in append mode.
	// Constraint 6 - Have the program create a log file which details all the moves.
	myfile.open("refPigGame.txt", ios::app);

	//If mode = 0 this code will execute.
	if (mode == 0)
	{
		//Printing message to file.
		myfile << "\nPlayer Turn" << endl;
		myfile << "=======================" << endl;

		//Printing message to console.
		cout << "\nPlayer Turn" << endl;
		cout << "=======================" << endl;
	}

	//If mode = 1 this code will execute.
	if (mode == 1)
	{
		//Printing message to the file.
		myfile << "\nPlayer 1 Turn" << endl;
		myfile << "=======================" << endl;
	}

	//If mode = 2 this code will execute.
	if (mode == 2)
	{
		//Printing message to the file.
		myfile << "\nPlayer 2 Turn" << endl;
		myfile << "=======================" << endl;
	}

	//This loop will iterate until broken out of.
	while (true)
	{
		//Asking the user to enter something to roll the dice.
		cout << "\nEnter something to roll the dice." << endl;
		cout << "(enter 0 to stop rolling)" << endl;
		//Reading the line as input.
		getline(cin, temp);

		//If temp = 0 this code will execute.
		if (temp == "0")
		{
			//Informing the user of their current score.
			cout << "\nYou ended your turn with..." << endl;
			cout << humObj << endl;

			//Printing message to file.
			myfile << "Player ended turn." << endl;
			myfile << humObj << endl;

			//Closing file.
			myfile.close();
			//Returning to caller.
			return;
		}

		//Setting roll to the return of the objects roll method.
		roll = humObj.roll();

		//If roll = 1 this code will execute.
		if (roll == 1)
		{
			//Setting the current score to the previous score.
			humObj.setScore(previousScore);
			//Informing the user they rolled a 1.
			cout << "\nYour rolled a 1." << endl;
			//Outputting current score.
			cout << "\nYou ended your turn with..." << endl;
			cout << humObj << endl;

			//Printing message to file.
			myfile << "Player has rolled a 1." << endl;
			myfile << humObj << endl;

			//Closing file.
			myfile.close();
			//Returning to caller.
			return;
		}

		//Else, this will execute.
		else
		{
			//Informing the user of the number they rolled.
			cout << "\nYou rolled a " << roll << "." << endl;
			humObj.setScore(humObj.getScore() + roll);
			acumPoints = acumPoints + roll;
			//Informing the user of total score for this turn.
			cout << "\nPoints accumulated this turn: " << acumPoints << "." << endl;

			//Printing message to file.
			myfile << "Player has rolled a " << roll << endl;
		}
	}
}
//End of playerTurn function.

//SimpleAI function - this function contains the code for the easy to beat computers turn.
// Constraint 5 - Make a simple AI with a random number.
void simpleAI(Computer &comObj)
{
	//Printing message to console.
	cout << "\nComputer Turn" << endl;
	cout << "=======================" << endl;

	//Intilizing several needed variables.
	int acumPoints = 0;
	int roll = 0;

	//Setting previousScore to the current score.
	int previousScore = comObj.getScore();

	//Creating a file pointer.
	ofstream myfile;

	//Opening a file in append mode.
	// Constraint 6 - Have the program create a log file which details all the moves.
	myfile.open("refPigGame.txt", ios::app);

	//Printing message to file.
	myfile << "\nComputer Turn" << endl;
	myfile << "=======================" << endl;

	//This loop iterates until broken out of.
	while (true)
	{
		//Setting roll to the return of the objects roll method.
		roll = comObj.roll();

		//If roll = 1 this code will execute.
		if (roll == 1)
		{
			//Setting the objects score to the previous score.
			comObj.setScore(previousScore);
			//Informing the user that the computer rolled a 1.
			cout << "\nThe computer rolled a 1." << endl;
			//Printing the computers current score.
			cout << comObj << endl;

			//Printing message to file.
			myfile << "The computer rolled a 1" << endl;
			myfile << comObj << endl;

			//Closing the file.
			myfile.close();
			//Returning to the caller.
			return;
		}

		//If roll is 2 or 3 this code will execute.
		if (roll == 2 || roll == 3)
		{
			//Informing the user that the computer decided to hold.
			cout << "\nThe computer decided to hold..." << endl;
			//Pringting points earned this turn.
			cout << "\nPoints accumulated: " << acumPoints << endl;
			//Printing the computers total score.
			cout << comObj << endl;

			//Printing message to file.
			myfile << "Computer ended turn." << endl;
			myfile << comObj << endl;

			//Closing the file.
			myfile.close();
			//Returning to caller.
			return;
		}

		//Else, this code will execute.
		else
		{
			//Setting acumPoints to rill.
			acumPoints = acumPoints + roll;
			//Adding roll to score.
			comObj.setScore(comObj.getScore() + roll);

			//Printing message to file.
			myfile << "Computer rolled a " << roll << endl;
		}
	}
}
//End of simpleAI function.

//hardAI function - this function contains the code for the hard to beat computers turn.
// Bonus - Created a more sophisticated AI. The player has the choice of AI they want to play against.
void hardAI(Computer &comObj)
{
	//Printing message to console.
	cout << "\nComputer Turn" << endl;
	cout << "=======================" << endl;

	//Intilzing several needed variables.
	int acumPoints = 0;
	int roll = 0;
	int turnNumber = 0;

	//Setting previousScore to the current score.
	int previousScore = comObj.getScore();

	//Creating a file pointer.
	ofstream myfile;

	//Opening a file in append mode.
	// Constraint 6 - Have the program create a log file which details all the moves.
	myfile.open("refPigGame.txt", ios::app);

	//Outputting message to file.
	myfile << "\nComputer Turn" << endl;
	myfile << "=======================" << endl;

	//This loop iterates until broken out of.
	while (true)
	{
		//Setting roll to the objects roll method.
		roll = comObj.roll();

		//This executs when the computer has acumalted 15 points or
		//if the computer has a total score over 100 or
		//if the computer has already successfully rolled the dice 4 times.
		if (acumPoints >= 15 || comObj.getScore() >= 100 || turnNumber >= 4)
		{
			//Informing the user that the computer decided to hold.
			cout << "\nThe computer decided to hold..." << endl;
			cout << "\nPoints accumulated: " << acumPoints << endl;
			//Printing the computers total points.
			cout << comObj << endl;

			//Printing a message to the file.
			myfile << "Computer ended turn." << endl;
			myfile << comObj << endl;

			//Closing the file.
			myfile.close();
			//Returning to the caller.
			return;
		}

		//If roll = 1 this code will execute.
		if (roll == 1)
		{
			//Set the current score to the previous score.
			comObj.setScore(previousScore);
			//Informing the user that the computer rolled 1.
			cout << "\nThe computer rolled a 1." << endl;
			cout << comObj << endl;

			//Printing a message to the file.
			myfile << "The computer rolled a 1" << endl;
			myfile << comObj << endl;

			//Closing the file.
			myfile.close();
			//Returning to the caller.
			return;
		}

		//Else, this code will execute.
		else
		{
			//Setting acumPoints to itself + roll.
			acumPoints = acumPoints + roll;
			//Adding roll to the current score.
			comObj.setScore(comObj.getScore() + roll);
			//Incrementing turnNumber.
			turnNumber++;

			//Printing message to the file.
			myfile << "Computer rolled a " << roll << endl;
		}
	}
}
//End of hardAI function.

//toContinue functon - this function simply asks the user to enter something to continue.
void toContinue()
{
	//Creating needed string variable.
	string answer;

	//Asking the user to enter something... anything... JUST DO IT!!!
	cout << "\nEnter something to continue." << endl;
	//Reading the answer.
	cin >> answer;
}
//End of toContinue.

//pigMenu function - this function outputs and reads the answer for the programs menu.
char pigMenu()
{
	//Creating a char variable to hold the user's answer.
	char answer;

	//Outputting the menu.
	cout << "\nRefactored Pig Game Menu" << endl;
	cout << "======================================" << endl;
	cout << "1. Play a game with easy AI." << endl;
	cout << "2. Play a game with hard AI." << endl;
	cout << "3. Play a game with another player." << endl;
	cout << "4. Set number of dice sides." << endl;
	cout << "5. See win/loss data." << endl;
	cout << "6. Remove log file." << endl;
	cout << "7. Quit game." << endl;

	//Reading the answer.
	cin >> answer;

	//Input validation loop.
	while ((answer < '1') || (answer > '7'))
	{
		cout << answer << " is not a valid input. Please try again." << endl;
		cin >> answer;
	}

	//Returning the answer to the caller.
	return answer;
}
//End of pigMenu function.
