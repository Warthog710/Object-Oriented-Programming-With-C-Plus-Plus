//Program name: Battleship
//Program Description: This program is the game of battleship. It allows a single player to play against the computer or another player.
//My name: Quinn Roemer W1582947
//CISP 400 T/Th FLC 9-10:20am
//September 25th 2017

#include <iostream>
#define NDEBUG //Used to disable or enable asserts. Comment out to enable.
#include <assert.h>
#include <ctime>
#include <limits>
#include <string>

using namespace std;

class ship { //A ship class that will be used to create the ship objects.
	int health; //A private variable in ship class. This variable will hold the health of each object.
public:
	ship(int); //Constructor method declaration.
	void shealth();	//Ship method declaration.
	int gethealth(); //Ship method declaration
};

ship::ship(int chealth) { // Bonus class constructor, used a programmer defined constructor.
	assert(chealth >= 0); //Assert, this will protect the variable chealth from going negative.
	health = chealth; //Set the private variable health equal to chealth.
}

void ship::shealth() { //Ship method, this method is used to decrement the health variable.
	health--; //Decrementing health.
	assert(health >= 0); //Assert, this will protect the variable health from going negative.
} // Bonus assert, used an extra assert in one of my methods.

int ship::gethealth() {	//Ship method, this method is used to return the value of health.
	return health; //Returning health.
}
//Function prototypes.
void playGame(int(&pGrid)[10][10], int(&cGrid)[10][10], int); //This function contains the code for playing battleship.
void placeShip(int(&pGrid)[10][10], int, int, int, string);	 //This function contains the code for setting up the ships.
void displayGrid(int(&pGrid)[10][10]); //This function contains the code to display a passed two dimensional array.
void randomSetup(int(&pGrid)[10][10]); //This function contains the code to randomly set up the game board.
void fillZero(int(&pGrid)[10][10]);	 //This function contains the code to fill a two dimensional array with zeros.
int randomNumber(int); //This function creates a random number within a passed range.
int callMenu();	//This function displays the menu of the program.
int cTurn(int(&pGrid)[10][10]); //This function contains the AI code so that the computer can play the game.
int player2(int(&pGrid)[10][10], int(&cTurnGrid)[10][10], int, int&, int&, int);
//The above function contains the code for the 2nd players turn.

int main() //Main function to execute.
{
	srand((unsigned)time(0)); //Creating a seed for the rand function.
	int pGrid[10][10] = { 0 }; //Creating a two dimensional array intilized to 0.	
	int cGrid[10][10] = { 0 }; //Creating a two dimensional array intilized to 0.
	int choice, hold, quit = 0, isInit = 0; //Creating several int variables.

	randomSetup(cGrid); //Calling the function randomSetup and passing cGrid to it.

	cout << "Welcome to the Battleship program, in this program you will be pitched against\nthe computer or another player in a game of Battleship. Good Luck!" << endl;
	//Displaying the welcome message of the program.
	while (quit == 0) { //A loop that will iterate until quit != 0.

		choice = callMenu(); //Calling the callMenu function to display the menu.

		switch (choice) { //Switch structure that will switch the variable returned by callMenu();

		case 1:	//If the case is 1 this code will execute.
			cout << "\nHere is the grid where you will be placing your ships." << endl; //Telling the user about the grid they see.
			displayGrid(pGrid);	//Displaying the grid where they will be placing their ships.
			placeShip(pGrid, 5, 5, 5, "carrier"); //Calling the function placeShip to place the carrier.
			placeShip(pGrid, 4, 6, 4, "battleship"); //Calling the function placeShip to place the battleship.
			placeShip(pGrid, 3, 7, 3, "crusier"); //Calling the function placeShip to place the crusier.
			placeShip(pGrid, 3, 7, 2, "submarine"); //Calling the function placeShip to place the submarine.
			placeShip(pGrid, 2, 8, 1, "destroyer"); //Calling the function placeShip to place the destroyer.
			isInit = 1; //Setting is init to 0, this variable will be used as a flag telling the code if the ships have been placed yet.
			break; //Breaking out of the case.

		case 2: //If the case is 2 this code will execute.
			if (isInit == 1) { //If the ships have already been placed this will restore the grid to all zeros.
				fillZero(pGrid); //Filling pGrid with zeros.
			}
			randomSetup(pGrid); //Calling randomSetup, this will randomly setup the player's grid.
			cout << "\nHere is your randomly generated ship placement." << endl; //Telling the user their ships have been placed.
			displayGrid(pGrid); //Displaying the randomly setup grid.
			cout << "\nTo continue enter 1." << endl; //Prompting the user to enter 1 to continue.
			cin >> hold; //Reading the answer.
			while (hold != 1) { //While hold != 1 this code will execute.
				cin.clear(); //Clearing a failed state of cin.
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignoring the inputted answer.
				cout << "\nTo continue enter 1." << endl; //Prompting the user to enter 1 to continue.
				cin >> hold; //Reading the answer.
			}
			isInit = 1; //Setting isInit to 1, this will tell the program that the ships have been placed.
			break; //Breaking out of the case.

		case 3: //If the case is 3 this code will execute.
			//The following cout's are used to tell the user the legend of the grid. In other words, this code is used
			//to tell the user what the different numbers on the grid represents.
			cout << "\nWhen you play this game you will see a 10x10 grid." << endl;
			cout << "\nA 0 while placing your ships means that no ship has been placed there." << endl;
			cout << "A 1 while placing your ships means that your destroyer occupies that space." << endl;
			cout << "A 2 while placing your ships means that your submarine occupies that space." << endl;
			cout << "A 3 while placing your ships means that your cruiser occupies that space." << endl;
			cout << "A 4 while placing your ships means that your battleship occupies that space." << endl;
			cout << "A 5 while placing your ships means that your carrier occupies that space." << endl;
			cout << "\nWhile playing the game a 0 means that you have not tried to hit that location." << endl;
			cout << "While playing the game a 1 means you have hit the enemies destroyer at the corresponding location." << endl;
			cout << "While playing the game a 2 means you have hit the enemies submarine at the corresponding location." << endl;
			cout << "While playing the game a 3 means you have hit the enemies cruiser at the corresponding location." << endl;
			cout << "While playing the game a 4 means you have hit the enemies battleship at the corresponding location." << endl;
			cout << "While playing the game a 5 means you have hit the enemies carrier at the corresponding location." << endl;
			cout << "While playing the game a 9 means you have hit the corresponding location but hit no ships." << endl;

			cout << "\nTo continue enter 1." << endl; //Prompting the user to enter 1 to continue.
			cin >> hold; //Reading the inputted answer.
			while (hold != 1) { //This code will execute while hold != 1.
				cin.clear(); //Clearing a failed state of cin.
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignoring the inputted answer.
				cout << "\nTo continue enter 1." << endl; //Prompting the user to enter 1 to continue.
				cin >> hold; //Reading the inputted answer.
			}
			break; //Breaking out of the case.

		case 4: //If the case is 4 this code will execute.
			//The following cout statements explain the rules of the game to the user, in other words the user is 
			//informed how to play the game. Also, the health of each ship is displayed.
			cout << "\nThe goal of battleship is to find and destroy the enemies ships." << endl;
			cout << "Each player has a total of 5 ships. Each ship has a certain number of times it can get hit." << endl;
			cout << "The carrier, health = 5." << endl;
			cout << "The battleship, health = 4." << endl;
			cout << "The cruiser, health = 3." << endl;
			cout << "The submarine, health = 3." << endl;
			cout << "The destroyer, health = 2." << endl;
			cout << "\nYou win when all of your enemies ships are destroyed." << endl;

			cout << "\nTo continue enter 1." << endl; //Prompting the user to enter 1 to continue.
			cin >> hold; //Reading the inputted answer.
			while (hold != 1) { //While hold != 1 this code will execute.
				cin.clear(); //Clearing a failed cin state.
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignoring the inputted answer.
				cout << "\nTo continue enter 1." << endl; //Prompting the user to enter 1 to continue.
				cin >> hold; //Reading the inputted answer.
			}
			break; //Breaking out of the case.

		case 5: //If the case is 5 this code will execute.
			if (isInit == 0) { //If the player grid has not been intilized they will be sent back to the menu.
				cout << "\nPlease place your ships before playing." << endl; //Informing the user of the problem.
				cout << "\nTo continue enter 1." << endl; //Prompting the user to enter 1 to continue.
				cin >> hold; //Reading the inputted answer.
				while (hold != 1) { //While hold != 1 this code will execute.
					cin.clear(); //Clearing a failed cin state.
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignoring the inputted answer.
					cout << "\nTo continue enter 1." << endl; //Prompting the user to enter 1 to continue.
					cin >> hold; //Reading the inputted answer.
				}
				break; //Breaking out of the case.
			}
			playGame(pGrid, cGrid, 1); //Calling the playGame function, this will place the user into the game.
			fillZero(pGrid); //Calling the fillZero function for pGrid after the game is finished.
			fillZero(cGrid); //Calling the fillZero function for cGrid after the game is finished.
			randomSetup(cGrid); //Calling randomSetup and passing cGrid to it.
			isInit = 0; //Setting is isInit to 0.
			break; //Breaking out of the case.

		case 6: //If the case is 6 the following code will execute.
			if (isInit == 0) { //If the player grid has not been intilized the user will be sent back to the menu.
				cout << "\nPlease place your ships before playing." << endl; //Informing the user of the problem.
				cout << "\nTo continue enter 1." << endl; //Prompting the user to enter 1 to continue.
				cin >> hold; //Reading the inputted answer.
				while (hold != 1) { //While hold != 1 this code will execute.
					cin.clear(); //Clearing a failed cin state.
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignoring the inputted answer.
					cout << "\nTo continue enter 1." << endl; //Prompting the user to enter 1 to continue.
					cin >> hold; //Reading the inputted answer.
				}
				break; //Breaking out of the case.
			}
			cout << "\nPlayer 2" << endl; //Displaying the menu for player 2.
			cout << "=================" << endl;
			cout << "1: Randomly place your ships." << endl;
			cout << "2: Place your ships manually." << endl;
			cin >> choice; //Reading the inputted answer.
			while ((choice > 2) || (choice < 1)) { //While choice is not between 1 and 2 this code will execute.
				cin.clear(); //Clearing a failed cin state.
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignoring the inputted answer.
				cout << "\nAn input of 1-2 is accepted. " << choice << " is not a valid input." << endl; //Telling the user there input was invalid.
				cout << "\nPlease try again." << endl; //Prompting the user to try again.
				cin >> choice; //Reading the inputted answer.
			}
			if (choice == 1) { //If choice is 1 this code will execute.
				cout << "\nHere is the randomly generated set up for player 2" << endl; //Telling the user about what they are seeing.
				displayGrid(cGrid); //Displaying the randomly generated grid.
				cout << "\nTo continue enter 1." << endl; //Prompting the user to enter 1 to continue.
				cin >> hold; //Reading the inputted answer.
				while (hold != 1) { //While hold != 1 this code will execute.
					cin.clear(); //Clearing a failed cin state.
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignoring the inputted answer.
					cout << "\nTo continue enter 1." << endl; //Prompting the user to enter 1 to continue.
					cin >> hold; //Reading the inputted answer.
				}
			}
			if (choice == 2) { //If choice is 2 this code will execute.
				fillZero(cGrid); //Filling cGrid with zeros.
				cout << "\nHere is the grid where you will be placing your ships." << endl; //Telling the user about what they are seeing.
				displayGrid(cGrid); //Displaying the grid where the user will be placing their ships.
				placeShip(cGrid, 5, 5, 5, "carrier"); //Calling the placeShip function for the carrier.
				placeShip(cGrid, 4, 6, 4, "battleship"); //Calling the placeShip function for the battleship.
				placeShip(cGrid, 3, 7, 3, "crusier"); //Calling the placeShip function for the crusier.
				placeShip(cGrid, 3, 7, 2, "submarine"); //Calling the placeShip function for the submarine.
				placeShip(cGrid, 2, 8, 1, "destroyer"); //Calling the placeShip function for the destroyer.
			}
			playGame(pGrid, cGrid, 2); //Calling the play game function, Note: passing a 2. This means that code will execute for a second player as well.
			fillZero(pGrid); //Calling the fillZero function for pGrid.
			fillZero(cGrid); //Calling the fillZero function for cGrid.
			randomSetup(cGrid); //Calling the randomSetup function fo cGrid.
			isInit = 0; //Setting isInit to 0.
			break; //Breaking out of the case.

		case 7: //If the case is 7 this code will execute.
			cout << "\nThis cheat will display the computers setup. Do you want to continue?" << endl; //Informing the user they about to access the cheat.
			cout << "\nTo continue enter 1. Enter 0 to return to menu." << endl; //Prompting the user to enter 1 to continue or 0 to exit the cheat.
			cin >> hold; //Reading the inputted answer.
			while ((hold != 1) && (hold != 0)) { //While hold != 1 or 0 this code will execute.
				cin.clear(); //Clearing a failed cin state.
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignoring the inputted answer.
				cout << "\nTo continue enter 1. Enter 0 to return to menu." << endl; //Prompting the user to enter 1 to continue or 0 to exit the cheat.
				cin >> hold; //Reading the inputted answer.
			}
			if (hold == 0) //This code will execute if hold equals 0.
				break; //Breaking out of the case.

			displayGrid(cGrid); //Displaying the computers grid.

			cout << "\nTo continue enter 1." << endl; //Prompting the user to enter 1 to continue.
			cin >> hold; //Reading the inputted answer.
			while (hold != 1) { //While hold != 1 this code will execute.
				cin.clear(); //Clearing a failed cin state.
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignoring the inputted answer.
				cout << "\nTo continue enter 1." << endl; //Prompting the user to enter 1 to continue.
				cin >> hold; //Reading the inputted answer.
			}
			break; //Breaking out of the case.

		case 8: //If the case is 8 this code will execute.
			quit = 1; //Setting quit to zero. This will exit the above while loop.
			break; //Breaking out of the case.
		}
	}
	cout << "\nGoodbye!" << endl; //Wishing the user a gracious goodbye.
} //End of main.

void displayGrid(int(&pGrid)[10][10]) { //This function is used to display a passed two dimensional array.
	cout << endl; //Creating a newline.
	cout << "\n    0   1   2   3   4   5   6   7   8   9" << endl; //Outputting a number system that will help the user figure out the correct cordinates.
	cout << "    -------------------------------------\n" << endl;
	for (int count2 = 0; count2 < 10; count2++) { //A for loop that will iterate 10 times.
		cout << count2 << "|  "; //Printing the side number system to help the user.
		for (int count = 0; count < 10; count++) { //A for loop that is nested beneath another for loop, this loop will iterate 10 times.
			cout << pGrid[count][count2] << "   "; //Displaying a certain element of the array with 3 spaces after it.
		}
		cout << endl << endl; //Creating two newlines.
	}
} //End of displayGrid.

void randomSetup(int(&pGrid)[10][10]) { // Bonus random setup, this code includes the option to randomly setup the game board.
	//Place carrier
	int pos1, pos2, orentation, goAgain, flag = 0; //Intilizng the needed variables.
	pos1 = randomNumber(5); //Calling the randomNumber function with a range of 5
	pos2 = randomNumber(5); //Calling the randomNumber function with a range of 5
	orentation = randomNumber(1); //Calling the random number function with a range of 1.
	if (orentation == 0) { //If orentation = 0 this code will execute.
		for(int count = 0; count < 5; count++) { //A for loop that will iterate 5 times.
			pGrid[pos1 + count][pos2] = 5; //Replacing the randomly chosen elements to be 5.
		}
	}
	if (orentation == 1) { //If orentation = 0 this code will execute.
		for (int count = 0; count < 5; count++) { //A for loop that will iterate 5 times.
			pGrid[pos1][pos2 + count] = 5; //Replacing the randomly chosen elements to be 5.
		}
	}
	//Place Battleship
	pos1 = randomNumber(6); //Calling the randomNumber function with a range of 6.
	pos2 = randomNumber(6); //Calling the randomNumber function with a range of 6.
	orentation = randomNumber(1); //Calling the randomNumber function with a range of 1.
	if (orentation == 0) { //If orentation = 0 this code will execute.
		while (flag == 0) { //Bonus error detection, this program will make sure that player placed and computer placed ships are never on top of each other.
			for (goAgain = 0; goAgain < 4; goAgain++) { //A for loop that will iterate 4 times.
				if (pGrid[pos1 + goAgain][pos2] != 0) { //If the element is ever != 0 this code will execute.
					pos1 = randomNumber(6); //Calling the randomNumber function with a range of 6.
					pos2 = randomNumber(6); //Calling the randomNumber function with a range of 6.
					goAgain = 0; //Setting goAgain = 0.
					break; //Breaking out of the above loop.
				}
			}
			if (goAgain == 4) { //If goAgain = 4 this code will execute.
				flag = 1; //Setting flag to 4.
			}
		}
		for (int count = 0; count < 4; count++) { //A for loop that will iterate 4 times.
			pGrid[pos1 + count][pos2] = 4; //Replacing the randomly chosen elements to be 4.
		}
		flag = 0; //Setting flag = 0.
	} 
	if (orentation == 1) { //If orentation = 1 this code will execute.
		while (flag == 0) { //This loop is used to scan the proposed array elements to replace and make sure they are all 0.
			for (goAgain = 0; goAgain < 4; goAgain++) { //A for loop that will iterate 4 times.
				if (pGrid[pos1][pos2 + goAgain] != 0) { //If the element is ever != 0 this code will execute.
					pos1 = randomNumber(6); //Calling the randomNumber function with a range of 6.
					pos2 = randomNumber(6); //Calling the randomNumber function with a range of 6.
					goAgain = 0; //Setting goAgain = 0.
					break; //Breaking out of the above loop.
				}
			}
			if (goAgain == 4) { //If goAgain = 4 this code will execute.
				flag = 1; //Setting flag = 1.
			}
		}
		for (int count = 0; count < 4; count++) { //A for loop that will iterate 4 times.
			pGrid[pos1][pos2 + count] = 4; //Replacing the randomly chosen elements to be 4.
		}
		flag = 0; //Setting flag = 0.
	}
	//Place Crusier
	pos1 = randomNumber(7); //Calling the randomNumber function with a range of 7.
	pos2 = randomNumber(7); //Calling the randomNumber function with a range of 7.
	orentation = randomNumber(1); //Calling the randomNumber function with a range of 7.
	if (orentation == 0) { //If orentation = 0 this code will execute.
		while (flag == 0) { //This loop us used to scan the proposed array elements to replace and make sure they are all 0.
			for (goAgain = 0; goAgain < 3; goAgain++) { //A for loop that will iterate 3 times.
				if (pGrid[pos1 + goAgain][pos2] != 0) { //If the element is ever != 0 this code will execute.
					pos1 = randomNumber(7); //Calling the randomNumber function with a range of 7.
					pos2 = randomNumber(7); //Calling the randomNumber function with a range of 7.
					goAgain = 0; //Setting goAgain = 0.
					break; //Breaking out of the above loop.
				}
			}
			if (goAgain == 3) { //If goAgain = 3 this code will execute.
				flag = 1; //Setting flag = 1.
			}
		}
		for (int count = 0; count < 3; count++) { //A for loop that will iterate 3 times.
			pGrid[pos1 + count][pos2] = 3; //Replacing the randomly chosen elements to be 3.
		}
		flag = 0; //Setting flag = 0.
	}
	if (orentation == 1) { //If orentation = 1 this code will execute.
		while (flag == 0) { //This loop is used to scan the proposed array elements to replace and make sure they are all 0.
			for (goAgain = 0; goAgain < 3; goAgain++) { //A for loop that will iterate 3 times.
				if (pGrid[pos1][pos2 + goAgain] != 0) { //If the element is ever != this code will execute.
					pos1 = randomNumber(7); //Calling the randomNumber function with a range of 7.
					pos2 = randomNumber(7); //Calling the randomNumber function with a range of 7.
					goAgain = 0; //Setting goAgain = 0.
					break; //Breaking out of the above loop.
				}
			}
			if (goAgain == 3) { //If goAgain = 3 this code will execute.
				flag = 1; //Setting flag = 1.
			}
		}
		for (int count = 0; count < 3; count++) { //A for loop that will iterate 3 times.
			pGrid[pos1][pos2 + count] = 3; //Replacing the randomly chosen elements to be 3.
		}
		flag = 0; //Setting flag = 0.
	}
	//Place Submarine
	pos1 = randomNumber(7); //Calling the randomNumber function with a range of 7.
	pos2 = randomNumber(7); //Calling the randomNumber function with a range of 7.
	orentation = randomNumber(1); //Calling the randomNumber function with a range of 1.
	if (orentation == 0) { //If orentation = 0 this code will execute.
		while (flag == 0) { //This loop is used to scan the proposed array elements to replace and make sure they are all 0.
			for (goAgain = 0; goAgain < 3; goAgain++) { //A for loop that will iterate 3 times.
				if (pGrid[pos1 + goAgain][pos2] != 0) { //If the element is ever != 0 this code will execute.
					pos1 = randomNumber(7); //Calling the randomNumber function with a range of 7.
					pos2 = randomNumber(7); //Calling the randomNumber function with a range of 7.
					goAgain = 0; //Setting goAgain = 0.
					break; //Breaking out of the above loop.
				}
			}
			if (goAgain == 3) { //If goAgain = 3 this code will execute.
				flag = 1; //Setting flag = 1.
			}
		}
		for (int count = 0; count < 3; count++) { //A for loop that will iterate 3 times.
			pGrid[pos1 + count][pos2] = 2; //Replacing the randomly chosen elements to be 2.
		}
		flag = 0; //Setting flag = 0.
	}
	if (orentation == 1) { //If orentaion = 1 this code will execute.
		while (flag == 0) { //This loop is used to scan the proposed array elements to replace and make sure they are all 0.
			for (goAgain = 0; goAgain < 3; goAgain++) { //A for loop that will iterate 3 times.
				if (pGrid[pos1][pos2 + goAgain] != 0) { //If the element is ever != 0 this code will execute.
					pos1 = randomNumber(7); //Calling the randomNumber function with a range of 7.
					pos2 = randomNumber(7); //Calling the randomNumber function with a range of 7.
					goAgain = 0; //Setting goAgain = 0.
					break; //Breaking out of the above loop.
				}
			}
			if (goAgain == 3) { //If goAgain = 3 this code will execute.
				flag = 1; //Setting flag = 1.
			}
		}
		for (int count = 0; count < 3; count++) { //A for loop that will iterate 3 times.
			pGrid[pos1][pos2 + count] = 2; //Replacing the randomly chosen elements to be 2.
		}
		flag = 0; //Setting flag = 0.
	}
	//Place Destroyer
	pos1 = randomNumber(8); //Calling the randomNumber function with a range of 8.
	pos2 = randomNumber(8); //Calling the randomNumber function with a range of 8.
	orentation = randomNumber(1); //Calling the randomNumber function with a range of 1.
	if (orentation == 0) { //If orentation = 0 this code will execute.
		while (flag == 0) { //This loop is used to scan the proposed array elements to replace and make sure they are all 0.
			for (goAgain = 0; goAgain < 2; goAgain++) { //A for loop that will iterate 2 times.
				if (pGrid[pos1 + goAgain][pos2] != 0) { //If the element is ever != 0 this code will execute.
					pos1 = randomNumber(8); //Calling the randomNumber function with a range of 8.
					pos2 = randomNumber(8); //Calling the randomNumber function with a range of 8.
					goAgain = 0; //Setting goAgain = 0.
					break; //Breaking out of the above loop.
				}
			}
			if (goAgain == 2) { //If goAgain = 2 this code will execute.
				flag = 1; //Setting flag = 1.
			}
		}
		for (int count = 0; count < 2; count++) { //A for loop that will iterate 2 times.
			pGrid[pos1 + count][pos2] = 1; //Replacing the randomly chosen elements to be 1.
		}
		flag = 0; //Setting the flag = 0.
	}
	if (orentation == 1) { //If orentation = 0 this code will execute.
		while (flag == 0) { //This loop is used to scan the proposed array elements to replace and make sure they are all 0.
			for (goAgain = 0; goAgain < 2; goAgain++) { //A for loop that will iterate 2 times.
				if (pGrid[pos1][pos2 + goAgain] != 0) { //If the element is ever != 0 this code will execute.
					pos1 = randomNumber(8); //Calling the randomNumber function with a range of 8.
					pos2 = randomNumber(8); //Calling the randomNumber function with a range of 8.
					goAgain = 0; //Setting goAgain = 0.
					break; //Breaking out of the above loop.
				}
			}
			if (goAgain == 2) { //If goAgain = 2 this code will execute.
				flag = 1; //Setting flag = 1.
			}
		}
		for (int count = 0; count < 2; count++) { //A for loop that will iterate 2 times.
			pGrid[pos1][pos2 + count] = 1; //Replacing the randomly chosen elements to be 1.
		}
		flag = 0; //Setting flag = 0.
	}
} //End of randomSetup.

int randomNumber(int mod) { //This function is used to create a random number. Also, this function is passed
							//an int that used to determine the desired range of the random number.
	int rnum; //Creating a variable to hold the randomly generated number.

	mod++; //Incrementing mod by 1.

	rnum = rand() % mod; //Calling rand() with a modifier to create a random number in the desired range.

	return rnum; //Returning the randomly generated number.
} //End of randomNumber.

int callMenu() { // Bonus menu driven program, this program uses a menu to execute the users desired actions.
	int choice; //Creating a variable to hold the user's choice.
	cout << "\nBattleship Menu" << endl; //The following cout statements print the menu to the screen.
	cout << "=======================" << endl;
	cout << "1: Place your ships." << endl;
	cout << "2: Randomly place your ships." << endl;
	cout << "3: See map legend." << endl;
	cout << "4: Rules." << endl;
	cout << "5: Play Game against computer." << endl;
	cout << "6: Play game against another player." << endl;
	cout << "7: Cheat!" << endl;
	cout << "8: Quit." << endl;
	cin >> choice; //Reading the inputted answer.
	while ((choice > 8) || (choice < 1)) { //While choice is greater than 8 or less than 1 this code will execute.
		cin.clear(); //Clearing a failed cin state.
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignoring the inputted answer.
		cout << "\nAn input of 1-8 is accepted. " << choice << " is not a valid input." << endl; //Telling the user the input was invalid.
		cout << "\nPlease try again." << endl; //Prompting the user to try again.
		cin >> choice; //Reading the inputted answer.
	}
	return choice; //Returning the user's choice.
} //End of callMenu.

void playGame(int(&pGrid)[10][10], int(&cGrid)[10][10], int player) { //This function contains the code used to play the game.
	ship carrier(5), battleship(4), cruiser(3), submarine(3), destroyer(2); //Creating 5 objects of the ship clase. Note: I am passing the desired health of each ship to the constructor.
	ship Ccarrier(5), Cbattleship(4), Ccruiser(3), Csubmarine(3), Cdestroyer(2); //Creating another 5 objects of the ship class for the computer/other player.
	int pTurnGrid[10][10] = { 0 }; //Creating a new two dimensional array intilized with all zeros.
	int cTurnGrid[10][10] = { 0 }; //Creating a new two dimensional array intilized with all zeros.
	int hold, pos1, pos2, hit, turn = 1; //Creating several int variables.
	int pDestroyed = 0, cDestroyed = 0; //Creating a couple int variables.

	cout << "\nHere is your playing grid. This grid will keep track of your hits and misses." << endl; //Telling the user the reason for the printed grid.
	while ((pDestroyed < 5) && (cDestroyed < 5)) { //While the number of destroyed ships is less than 5 this code will execute.
		if (player == 2) //If player = 2 this code will execute.
			cout << "\nPlayer 1" << endl; //Printing player 1 to the screen to inform the user it is player 1's turn.
		displayGrid(pTurnGrid); //Displaying the targeting grid.
		cout << "\nPlease enter your horizontal cordinates for turn #" << turn << "." << endl; //Prompting the user to enter some cordinates.
		cin >> pos1; //Reading the inputted answer.
		cout << "\nPlease enter your vertical cordinates." << endl; //Prompting the user to enter some cordinates.
		cin >> pos2; //Reading the inputted answer.
		while ((((pos1 > 9) || (pos2 > 9) || (pos1 < 0) || (pos2 < 0)))) { //This loop will execute if pos1 or pos2 are greater than 9 or smaller than 0.
			cin.clear(); //Clearing a failed cin state.
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignoring the inputted answer.
			cout << "\nOne of your posititons is greater than " << 9 << " or smaller than 0. A value of 9 or smaller is required\nfor this ship. Please try again." << endl;
			cout << "\nHorizontal position?" << endl; //Informing the user they need to enter new cordinates.
			cin >> pos1; //Reading the inputted answer.
			cout << "\nVertical position?" << endl; //Prompting the user to enter some cordinates.
			cin >> pos2; //Reading the inputted answer.
		}
		hit = cGrid[pos1][pos2]; //Setting hit equal to the int at the cordinates location.
		cGrid[pos1][pos2] = 0; //Setting the hit location to 0.

		switch (hit) { //Switch case switching the hit variable.

		case 0: //If the case is 0 this code will execute.
			cout << "\nYou missed, better luck next time." << endl; //Informing the user they missed.
			pTurnGrid[pos1][pos2] = 9; //Setting the target grid to 9 at the designated cordinates.
			break; //Breaking out of the case.

		case 1: //If the case is 1 this code will execute.
			cout << "\nYou hit the enemies destroyer. Great job!" << endl; //Informing the user they hit the enemies destroyer.
			pTurnGrid[pos1][pos2] = 1; //Setting the target grid to 1 at the designated cordinates.
			destroyer.shealth(); //Subtracting one health from the destroyer object.
			if (destroyer.gethealth() == 0) { //If the destroyer's health is ever 0 this code will execute.
				cout << "\nYou've destroyed the enemies destroyer. Excellent work!" << endl; //Informing the user they destroyed the enemies destroyer.
				pDestroyed++; //Incrementing pDestroyed, this variable keeps track of the number of ships destroyed.
			}
			break; //Breaking out of the case.

		case 2: //If the case is 2 this code will execute.
			cout << "\nYou hit the enemies submarine. Great job!" << endl; //Informing the user they hit the enemeis submarine.
			pTurnGrid[pos1][pos2] = 2; //Setting the target grid to 2 at the designated cordinates.
			submarine.shealth(); //Subtracting one health from the submarine object.
			if (submarine.gethealth() == 0) { //If the submarine's health ever reaches 0 this code will execute.
				cout << "\nYou've destroyed the enemies submarine. Excellent work!" << endl; //Informing the user they destroyed the enemeis submarines.
				pDestroyed++; //Incrementing pDestroyed.
			}
			break; //Breaking out of the case.

		case 3: //If the case is 3 this code will execute.
			cout << "\nYou hit the enemies cruiser. Great job!" << endl; //Informing the user they hit the enemies cruiser.
			pTurnGrid[pos1][pos2] = 3; //Setting the target grid to 3 at the designated cordinates.
			cruiser.shealth(); //Subtracting one health from the cruiser object.
			if (cruiser.gethealth() == 0) { //If the cruiser's ever reaches 0 this code will execute.
				cout << "\nYou've destroyed the enemies cruiser. Excellent work!" << endl; //Informing the user they destroyed the enemies crusier.
				pDestroyed++; //Incrementing pDestroyed.
			}
			break; //Breaking out of the case.

		case 4: //If the case is 4 this code will execute.
			cout << "\nYou hit the enemies battleship. Great job!" << endl; //Informing the user they hit the enemies battleship.
			pTurnGrid[pos1][pos2] = 4; //Setting the target grid to 4 at the designated cordinates.
			battleship.shealth(); //Subtracting one health from the battleship object.
			if (battleship.gethealth() == 0) { //If the battleship's health ever reaches 0 this code will execute.
				cout << "\nYou've destroyed the enemies battleship. Excellent work!" << endl; //Informing the user they destroyed the enemies battleship.
				pDestroyed++; //Incrementing pDestroyed.
			}
			break; //Breaking out of the case.

		case 5: //If the case is 5 this code will execute.
			cout << "\nYou hit the enemies carrier. Great job!" << endl; //Informing the user they hit the enemies carrier.
			pTurnGrid[pos1][pos2] = 5; //Setting the target grid to 5 at the designated cordinates.
			carrier.shealth(); //Subracting one health from the carrier object.
			if (carrier.gethealth() == 0) { //If the carrier's health ever reaches 0 this code will execute.
				cout << "\nYou've destroyed the enemies carrier. Excellent work!" << endl; //Informing the user they destroyed the enemies carrier.
				pDestroyed++; //Incrementing pDestroyed.
			}
			break; //Breaking out of the case.
		}

		cout << "\nTo continue enter 1." << endl; //Prompting the user to enter 1 to continue.
		cin >> hold; //Reading the inputted answer.
		while (hold != 1) { //While hold != 1 this code will execute.
			cin.clear(); //Clearing a fail cin state.
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignoring the inputted answer.
			cout << "\nTo continue enter 1." << endl; //Prompting the user to enter 1 to continue.
			cin >> hold; //Reading the inputted answer.
		}

		if (pDestroyed < 5) { //If pDestroyed less than 5 this code will execute.
			if (player == 1) { //If player = 1 this code will execute.
				hit = cTurn(pGrid); //Setting hit = to the return of the cTurn function.
				
				switch (hit) { //Switch case that switches the hit variable.

				case 0: //If the case is 0 this code will execute.
					cout << "\nThe computer hit nothing." << endl; //Informing they player the computer hit nothing.
					break; //Breaking out of the case.

				case 1: //If the case is 1 this code will execute.
					cout << "\nThe computer hit your destroyer!" << endl; //Informing the player their destroyer was hit.
					Cdestroyer.shealth(); //Subtracting one health from the destroyer object.
					if (Cdestroyer.gethealth() == 0) { //If the destroyer's health ever reaches 0 this code will execute.
						cout << "\nThe computer has destroyed your destroyer!" << endl; //Informing the player that their destroyer was destroyed.
						cDestroyed++; //Incrementing the cDesroyed variable, this variable keeps track of the number of computer/player2 kills.
					}
					break; //Breaking out of the case.

				case 2: //If the case is 2 this code will execute.
					cout << "\nThe computer hit your submarine!" << endl; //Informing the player that their submarine was hit.
					Csubmarine.shealth(); //Subtracting one health from the submarine object.
					if (Csubmarine.gethealth() == 0) { //If the submarines's health ever reaches 0 this code will execute.
						cout << "\nThe computer has destroyed your submarine!" << endl; //Informing the player that their submarine was destroyed.
						cDestroyed++; //Incrementing cDestroyed.
					}
					break; //Breaking out of the case.

				case 3: //If the case is 3 this code will execute.
					cout << "\nThe computer hit your cruiser!" << endl; //Informing the player that their cruiser was hit.
					Ccruiser.shealth(); //Subtracting one health from the cruiser object.
					if (Ccruiser.gethealth() == 0) { //If the cruiser's health ever reaches 0 this code will execute.
						cout << "\nThe computer has destroyed your cruiser!" << endl; //Informing the player that their cruiser was destroyed.
						cDestroyed++; //Incrementing cDestroyed.
					}
					break; //Breaking out of the case.

				case 4: //If the case is 4 this code will execute.
					cout << "\nThe computer hit your battleship!" << endl; //Informing the player that their battleship was hit.
					Cbattleship.shealth(); //Subtracting one health from the battleship object.
					if (Cbattleship.gethealth() == 0) { //If the battleship's health ever reaches 0 this code will execute.
						cout << "\nThe computer has destroyed your battleship!" << endl; //Informing the player that their battleship was destroyed.
						cDestroyed++; //Incrementing cDestroyed.
					}
					break; //Breaking out of the case.

				case 5: //If the case is 5 this code will execute.
					cout << "\nThe computer hit your carrier!" << endl; //Informing the player that their carrier was hit.
					Ccarrier.shealth(); //Subtracting one health from the carrier object.
					if (Ccarrier.gethealth() == 0) { //If the carier's health ever reaches 0 this code will execute.
						cout << "\nThe computer has destroyed your carrier!" << endl; //Informing the player that ther carrier was destroyed.
						cDestroyed++; //Incrementing cDestroyed.
					}
					break; //Breaking out of the case.
				}

				cout << "\nTo continue enter 1." << endl; //Prompting the user to enter 1 to continue.
				cin >> hold; //Reading the inputted answer.
				while (hold != 1) { //While hold != 1 this code will execute.
					cin.clear(); //Clearing a failed cin state.
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignoring the inputted answer.
					cout << "\nTo continue enter 1." << endl; //Prompting the user to enter 1 to continue.
					cin >> hold; //Reading the inputted answer.
				}
			}

			if (player == 2) { //if player = 2 this code will execute.
				hit = player2(pGrid, cTurnGrid, turn, pos1, pos2, 9); //Setting hit = to the return of the player2 function.

				switch (hit) { //Switching the hit variable.

				case 0: //If the case is 9 this code will execute.
					cout << "\nYou missed, better luck next time." << endl; //Informing the player that they missed.
					cTurnGrid[pos1][pos2] = 9; //Setting the target grid to 9 at the designated cordinates.
					break; //Breaking out of the case.

				case 1: //If the case is 1 this code will execute.
					cout << "\nYou hit the enemies destroyer. Great job!" << endl; //Informing the player they hit the enemeis destroyer.
					cTurnGrid[pos1][pos2] = 1; //Setting the target grid to 1 at the designated location.
					Cdestroyer.shealth(); //Subtracting one health from the destoyer object.
					if (Cdestroyer.gethealth() == 0) { //If the destroyer's health ever reaches 0 this code will execute.
						cout << "\nYou've destroyed the enemies destroyer. Excellent work!" << endl; //Informing the player that they destroyed the enemies destroyer.
						cDestroyed++; //Incrementing cDestroyed.
					}
					break; //Breaking out of the case.

				case 2: //If the case is 2 this code will execute.
					cout << "\nYou hit the enemies submarine. Great job!" << endl; //Informing the player they hit the enemies submarine.
					cTurnGrid[pos1][pos2] = 2; //Setting the target grid to 2 at the designated location.
					Csubmarine.shealth(); //Subtracting one health from the submarine object.
					if (Csubmarine.gethealth() == 0) { //If the submarines's health ever reaches 0 this code will execute.
						cout << "\nYou've destroyed the enemies submarine. Excellent work!" << endl; //Informing the player they destroyed the enemies submarine.
						cDestroyed++; //Incrementing cDestroyed.
					}
					break; //Breaking out of the case.

				case 3: //If the case is 3 this code will execute.
					cout << "\nYou hit the enemies cruiser. Great job!" << endl; //Informing the player they hit the enemies cruiser.
					cTurnGrid[pos1][pos2] = 3; //Setting the target grid to 3 at the designated location.
					Ccruiser.shealth(); //Subtracting one health from the cruiser object.
					if (Ccruiser.gethealth() == 0) { //If the cruiser's health ever reaches 0 this code will execute.
						cout << "\nYou've destroyed the enemies cruiser. Excellent work!" << endl; //Informing the player they destroyed the enemies cruiser.
						cDestroyed++; //Incrementing cDestroyed.
					}
					break; //Breaking out of the case.

				case 4: //If the case is 4 this code will execute.
					cout << "\nYou hit the enemies battleship. Great job!" << endl; //Informing the player they hit the enemies battleship.
					cTurnGrid[pos1][pos2] = 4; //Setting the target grid to 4 at the designated location.
					Cbattleship.shealth(); //Subtracting one health from the battleship object.
					if (Cbattleship.gethealth() == 0) { //If the batteship's health ever reaches 0 this code will execute.
						cout << "\nYou've destroyed the enemies battleship. Excellent work!" << endl; //Informing the player they destroyed the enemies battleship.
						cDestroyed++; //Incrementing cDestroyed.
					}
					break; //Breaking out of the case.

				case 5: //If the case is 5 this code will execute.
					cout << "\nYou hit the enemies carrier. Great job!" << endl; //Informing the player they hit the enemies carrier.
					cTurnGrid[pos1][pos2] = 5; //Setting the target grid to 5 at the designated location.
					Ccarrier.shealth(); //Subtracting one health from the carrier object.
					if (Ccarrier.gethealth() == 0) { //If the carriers's health ever reaches 0 this code will execute.
						cout << "\nYou've destroyed the enemies carrier. Excellent work!" << endl; //Informing the player they destroyed the enemies carrier.
						cDestroyed++; //Incrementing cDestroyed.
					}
					break; //Breaking out of the case.

				}
				cout << "\nTo continue enter 1." << endl; //Prompting the user to enter 1 to continue.
				cin >> hold; //Reading the inputted answer.
				while (hold != 1) { //While hold != 1 this code will execute.
					cin.clear(); //Clearing a failed cin state.
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignoring the inputted answer.
					cout << "\nTo continue enter 1." << endl; //Prompting the user to enter 1 to continue.
					cin >> hold; //Reading the inputted answer.
				}
			}
		}
			turn++; //Incrementing the turn variable, this variable is used to keep track of the number of turns taken.
		}

		if (player == 1) { //If player = 1 this code will execute.
			if (pDestroyed == 5) { //If pDestroyed = 5 this code will execute.
				cout << "\nYou won the game!" << endl; //Informing the player that they won the game.
			}

			if (cDestroyed == 5) { //If cDestroyed = 5 this code will execute.
				cout << "\nThe computer won the game. Better luck next time." << endl; //Informing the player they lost the game to the computer.
			}
		}
		if (player == 2) { //If player = 2 this code will execute.
			if (pDestroyed == 5) { //If pDestroyed = 5 this code will execute.
				cout << "\nPlayer 1 won the game!" << endl; //Informing the players that player 1 won the game.
			}

			if (cDestroyed == 5) { //If cDestroyed = 5 this code will execute.
				cout << "\nPlayer 2 won the game!" << endl; //Informing the player that player 2 won the games.
			}
		}

		cout << "\nTo continue enter 1." << endl; //Prompting the user to enter 1 to continue.
		cin >> hold; //Reading the inputted answer.
		while (hold != 1) { //While hold != 1 this code will execute.
			cin.clear(); //Clearing a failed cin state.
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignoring the inputted answer.
			cout << "\nTo continue enter 1." << endl; //Prompting the user to enter 1 to continue.
			cin >> hold; //Reading the inputted answer.
	}
} //End of playGame function.

int cTurn(int(&pGrid)[10][10]) { //This function contains the code for the computer to play the game.
	int pos1, pos2, hit; //Creating a few needed variables.
	pos1 = randomNumber(9); //Calling the randomNumber function with a range of 9.
	pos2 = randomNumber(9); //Calling the randomNumber function with a range of 9.
	hit = pGrid[pos1][pos2]; //Setting hit equal to the designated cordinates.
	while (pGrid[pos1][pos2] == 9) { // Bonus slightly smarter AI, the AI in this program is programmed to never hit the same spot twice.
		pos1 = randomNumber(9); //Calling the randomNumber function with a range of 9.
		pos2 = randomNumber(9); //Calling the randomNumber function with a range of 9.
		hit = pGrid[pos1][pos2]; //Setting hit equal to the new designated cordinates.
	}
	pGrid[pos1][pos2] = 9; //Setting the designated cordinates equal to 9.
	return hit; //Returning hit.
} //End of cTrun function.

int player2(int(&pGrid)[10][10], int(&cTurnGrid)[10][10], int turn, int& pos1, int& pos2, int max) { // Bonus second player, this program has the ability to play against another player instead of the computer.
	int hit; //Intilizing the needed variable.
	cout << "\nPlayer 2" << endl; //Printing player 2 to inform the users that it is player 2's turn.
	displayGrid(cTurnGrid); //Displaying the target grid for player 2.
	cout << "\nPlease enter your horizontal cordinates for turn #" << turn << "." << endl; //Prompting the user to enter some cordinates.
	cin >> pos1; //Reading the inputted answer.
	cout << "\nPlease enter your vertical cordinates." << endl; //Prompting the user to enter some cordinates.
	cin >> pos2; //Reading the inputted answer.
	while ((((pos1 > max) || (pos2 > max) || (pos1 < 0) || (pos2 < 0)))) { //While pos1 and pos2 are greater than max or smaller than 0 this code will execute.
		cin.clear(); //Clearing a failed cin state.
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignoring the inputted answer.
		cout << "\nOne of your posititons is greater than " << max << " or smaller than 0. A value of " << max << " or smaller is required\nfor this ship. Please try again." << endl;
		cout << "\nHorizontal position?" << endl; //Informing the user their answer was invalid and prompting them for some new cordinates.
		cin >> pos1; //Reading the inputted answer.
		cout << "\nVertical position?" << endl; //Primpting the user to enter some cordinates.
		cin >> pos2; //Reading the inputted answer.
	}
	hit = pGrid[pos1][pos2]; //Setting hit equal to the designated cordinates.
	pGrid[pos1][pos2] = 0; //Setting the hit location to 0.
	return hit; //Returning hit.
} //End of player 2 function.

void fillZero(int(&pGrid)[10][10]) { //This function is used to fill a passed 10x10 two dimensional array with 0's.
	for (int count = 0; count < 10; count++) { //A for loop that will iterate 10 times.
		for (int count2 = 0; count2 < 10; count2++) { //A for loop that will iterate 10 times.
			pGrid[count2][count] = 0; //Setting the designated element to 0.
		}
	}
} //End of fillZero function.

void placeShip(int(&pGrid)[10][10], int size, int max, int number, string type) { // Bonus ship placement, this program gives the user the option to place their own ships.
	int pos1, pos2, temp; //Creating a few needed int variables.
	int orentation, flag = 0, goAgain; //Creating some more needed int variables.
	cout << "\nWhere would you like your " << type << " placed? (enter the starting position)" << endl; //Asking the user where they want their ship placed.
	cout << "\nHorizontal position?" << endl; //Prompting the user to enter some cordinates.
	cin >> pos1; //Reading the inputted answer.
	cout << "\nVertical position?" << endl; //Prompting the user to enter some cordinates.
	cin >> pos2; //Reading the inputted answer.
	while ((((pos1 > max) || (pos2 > max) || (pos1 < 0) || (pos2 < 0)))) { //While pos1 and pos2 are greater than max or less than 0 this code will execute.
		cin.clear(); //Clearing a failed cin state.
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignoring the inputted answer.
		cout << "\nOne of your posititons is greater than " << max << " or smaller than 0. A value of " << max << " or smaller is required\nfor this ship. Please try again." << endl;
		cout << "\nHorizontal position?" << endl; //Informing the user that their input was invalid, also prompting the user to enter some new cordinates.
		cin >> pos1; //Reading the inputted answer.
		cout << "\nVertical position?" << endl; //Prompting the user to enter some cordinates.
		cin >> pos2; //Reading the inputted answer.
	}
	cout << "\nWould you like your " << type << " to be placed horizontal or vertical?\n(enter 0 for horizontal and 1 for vertical)" << endl;
	cin >> orentation; //Asking the user what orentation they want their ship to be placed, also prompting the user for input.
	while ((orentation != 0) && (orentation != 1)) { //While orentation is not 1 or 0 this code will execute.
		cin.clear(); //Clearing a failed cin state.
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignoring the inputted answer.
		cout << "\nInput invalid. Please try again." << endl; //Prompting the user to enter a new answer.
		cin >> orentation; //Readng the inputted answer.
	}

	if (orentation == 0) { //If orentation = 0 this code will execute.
		while (flag == 0) { //While flag = 0 this code will execute.
			for (goAgain = 0; goAgain < size; goAgain++) { //A for loop that will iterate until one smaller than goAgain.
				if (pGrid[pos1 + goAgain][pos2] != 0) { //If the element ever is != 0 this code will execute.
					cout << "\nBy placing your ship here you overlap with another ship.\nPlease enter a new position." << endl;
					cout << "\nHorizontal position?" << endl; //Informing the user that their ship cannot be placed here. And prompting them for a new answer.
					cin >> pos1; //Reading the inputted answer.
					cout << "\nVertical position?" << endl; //Prompting the user for a new answer.
					cin >> pos2; //Reading the inputted answer.
					while ((((pos1 > max) || (pos2 > max) || (pos1 < 0) || (pos2 < 0)))) { //While pos1 and pos2 are greater than max or less than 0 this code will execute.
						cin.clear(); //Clearing a failed cin state.
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignoring the inputted answer.
						cout << "\nOne of your posititons is greater than " << max << " or smaller than 0. A value of " << max << " or smaller is required\nfor this ship. Please try again." << endl;
						cout << "\nHorizontal position?" << endl; //Informing the user that their answer is invalid. Also, prompting the user to enter a new answer.
						cin >> pos1; //Reading the inputted answer.
						cout << "\nVertical position?" << endl; //Prompting the user for a new answer.
						cin >> pos2; //Reading the inputted answer.
					}
					goAgain = 0; //Setting goAgain = 0.
					break; //Breaking out of the above loop.
				}
			}
			if (goAgain == size) { //If goAgain = size this code will execute.
				flag = 1; //Setting flag = 1.
			}
		}
		for (int count = 0; count < size; count++) { //A for loop that will iterate to one smaller than the value of size.
			pGrid[pos1 + count][pos2] = number; //Setting the designated element equal to number.
		}
	}
	if (orentation == 1) { //If orentation = 1 this code will execute.
		while (flag == 0) { //While flag = 0 this code will execute.
			for (goAgain = 0; goAgain < size; goAgain++) { //This loop will iterate to one smaller than goAgain.
				if (pGrid[pos1][pos2 + goAgain] != 0) { //If the element ever is != 0 this code will execute.
					cout << "\nBy placing your ship here you overlap with another ship.\nPlease enter a new position." << endl;
					cout << "\nHorizontal position?" << endl; //Informing the user that they cannot place their ship here. Also, prompting them to input a new answer.
					cin >> pos1; //Reading the inputted answer.
					cout << "\nVertical position?" << endl; //Prompting the user for a new answer.
					cin >> pos2; //Reading the inputted answer.
					while ((((pos1 > max) || (pos2 > max) || (pos1 < 0) || (pos2 < 0)))) { //While pos1 and pos2 are greater than max and smaller than 0 this code will execute.
						cin.clear(); //Clearing a failed cin state.
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignoring the inputted answer.
						cout << "\nOne of your posititons is greater than " << max << " or smaller than 0. A value of " << max << " or smaller is required\nfor this ship. Please try again." << endl;
						cout << "\nHorizontal position?" << endl; //Informing the user that their answer was invalid. Also, prompting the user to input a new answer.
						cin >> pos1; //Reading the inputted answer.
						cout << "\nVertical position?" << endl; //Prompting the user to input a new answer.
						cin >> pos2; //Reading the inputted answer.
					}
					goAgain = 0; //Setting goAgain = 0.
					break; //Breaking out of the above loop.
				}
			}
			if (goAgain == size) { //If goAgain = size this code will execute.
				flag = 1; //Setting flag to 1.
			}
		}
		for (int count = 0; count < size; count++) { //A for loop that will iterate to one less than size.
			pGrid[pos1][pos2 + count] = number; //Setting the element equal to number.
		}
	}
	cout << "\nHere is what your current playing field looks like." << endl; //Informing the user of the reason for the printed grid.
	displayGrid(pGrid); //Calling the displayGrid function to display the current ship location(s).

	cout << "To continue enter 1" << endl; //Prompting the user to enter 1 to continue.
	cin >> temp; //Reading the inputted answer.
	while (temp != 1) { //While temp != 1 this code will execute.
		cin.clear(); //Clearing a faild cin state.
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignoring the inputted answer.
		cout << "\nTo continue enter 1" << endl; //Prompting the user to enter 1 to continue.
		cin >> temp; //Reading the inputted answer.
	}
} //End of placeShip function.
