//Program name: Genetic Algorithm Robots.
//Program Description: This program creates random robots and allows the computer to figure out the best way to navigate
//a playing field.

//My name: Quinn Roemer W1582947
//CISP 400 T/Th FLC 9-10:20am
//December 2nd 2017

#include <iostream>
#include <string>
#include <time.h>

using namespace std;

//This class is used to create all of the robots.
class robot
{
//Private class variables.
private:
	//Several int variables. These variables are used to keep track of certain robot attributes.
	int tSurvived = 0;
	int score = 0;
	// Constraint 2 - Start your robot on a random square with 5 power.
	int energy = 5;
	int bCollected = 0;

	//This two dimensional array holds all of the robots genes.
	char geneTable[24][8];

//Public class methods.
public:

	//Constructor for class. Defined outside of class.
	robot();

	//Gene related methods. Defined outside of class.
	void setGeneTable(char fArray[24][8], char sArray[24][8]);
	void compareGenes(char sensorData[4], char action[4]);
	void getGeneTable(char tArray[24][8]);
	void printGenes();

	//Setter method for score variable.
	void setScore(int iTemp) 
	{
		score = iTemp;
	}

	//Getter function for several in class variables.
	int getBatteries() { return bCollected; }
	int getTurns() { return tSurvived; }
	int getEnergy() { return energy; }
	int getScore() { return score; }

	//Methods that increment/decrement certain in class variables.
	void incBatteries() { bCollected++; }
	void incEnergy() { energy++; }
	void incTurns() { tSurvived++; }
	void DecEnergy() { energy--; }
};

//Robot class constructor.
robot::robot()
{
	//Creating variable to hold randomly generated variables.
	int random;

	//Char arrays. These array hold the possible gene data that can be placed in a gene.
	char posAction[2] = { 'M', 'P' };
	char posDirection[4] = { 'N', 'S', 'E', 'W' };
	char posSensor[4] = { '0', '1', '2', '9' };

	//For loop. This loop iterates 24 times.
	for (int index = 0; index < 24; index++)
	{
		//Nested For loop. This loop iterates 4 times.
		for (int count = 0; count < 4; count++)
		{
			//Creating a random number with range of 0 to 3.
			random = rand() % 4;
			//Setting gene to random posSensor array element.
			geneTable[index][count] = posSensor[random];
		}

		//Nested For loop. This loop iterates 2 times.
		for (int count = 4; count < 8; count += 2)
		{
			//Creating a random number with range of 0 to 3.
			random = rand() % 4;
			//Setting gene to random posDirection array element.
			geneTable[index][count] = posDirection[random];
			//Creating a random number with range of 0 to 2.
			random = rand() % 2;
			//Setting gene to random posAction array element.
			geneTable[index][count + 1] = posAction[random];
		}
	}
}
//End of robot constructor.

//Robot class method. This method accepts two robot gene data and combines them.
void robot::setGeneTable(char fArray[24][8], char sArray[24][8])
{
	//Creating needed int variables.
	int place;
	int random;

	//Char arrays. These array hold the possible gene data that can be placed in a gene.
	//Note: This data is only used when random gene morphing occurs.
	char posAction[2] = { 'M', 'P' };
	char posDirection[4] = { 'N', 'S', 'E', 'W' };
	char posSensor[4] = { '0', '1', '2', '9' };

	//For loop. This loop iterates 12 times.
	for (int index = 0; index < 12; index++)
	{
		//Nested For loop. This loop iterates 8 times.
		for (int count = 0; count < 8; count++)
		{
			//Setting one line of gene data equal to the first robot.
			geneTable[index][count] = fArray[index][count];
		}

		//If rand() returns a variable less than 5 this code will execute.
		//Note: This is where the random gene morphing occurs.
		if (rand() % 100 < 5)
		{
			//Creating a random number with a range of 0 to 7.
			place = rand() % 8;

			//If place is less than 4 this code will execute.
			if (place < 4)
			{
				//Creating a random number with a range of 0 to 3.
				random = rand() % 4;
				//Setting gene to random posSensor array element.
				geneTable[index][place] = posSensor[random];
			}

			//If place is 4 or 6 this code will execute.
			if (place == 4 || place == 6)
			{
				//Creating a random number with range of 0 to 3.
				random = rand() % 4;
				//Setting gene to random posDirection array element.
				geneTable[index][place] = posDirection[random];
			}

			//If place is 5 or 6 this code will execute.
			if (place == 5 || place == 7)
			{
				//Creating a random number with range of 0 to 1.
				random = rand() % 2;
				//Setting gene to random posAction array element.
				geneTable[index][place] = posAction[random];
			}
		}
	}

	//For loop. This loop iterates 12 times.
	for (int index = 12; index < 24; index++)
	{
		//Nested For loop. This loop iterates 8 times.
		for (int count = 0; count < 8; count++)
		{
			//Setting one line of gene data equal to the second robot.
			geneTable[index][count] = sArray[index][count];
		}

		//If rand() returns a variable less than 5 this code will execute.
		//Note: This is where the random gene morphing occurs.
		if (rand() % 100 < 5)
		{
			//Creating a random number with a range of 0 to 7.
			place = rand() % 8;

			//If place is less than 4 this code will execute.
			if (place < 4)
			{
				//Creating a random number with a range of 0 to 3.
				random = rand() % 4;
				//Setting gene to random posSensor array element.
				geneTable[index][place] = posSensor[random];
			}

			//If place is 4 or 6 this code will execute.
			if (place == 4 || place == 6)
			{
				//Creating a random number with range of 0 to 3.
				random = rand() % 4;
				//Setting gene to random posDirection array element.
				geneTable[index][place] = posDirection[random];
			}

			//If place is 5 or 6 this code will execute.
			if (place == 5 || place == 7)
			{
				//Creating a random number with range of 0 to 1.
				random = rand() % 2;
				//Setting gene to random posAction array element.
				geneTable[index][place] = posAction[random];
			}
		}
	}
}
//End of Robot method setGeneTable.

//This Robot class method allows you to compare a robots genes to active sensor data.
void robot::compareGenes(char sensorData[4], char action[4])
{
	//Creating a couple of needed int variables.
	int numMatch = 0;
	int bestMatch = -1;
	int place;

	//For loop. This loop iterates 24 times.
	for (int count = 0; count < 24; count++)
	{
		//Nested For loop. This loop iterates 4 times.
		for (int index = 0; index < 4; index++)
		{
			//If the current geneTable element equals 2 this code will execute.
			if (geneTable[count][index] == '2')
			{
				//Continuing to the next iteration.
				continue;
			}

			//If the sensorData matches the geneTable data this code executes.
			if (sensorData[index] == geneTable[count][index])
			{
				//Incrementing the numMatch variable.
				numMatch++;
			}
		}

		//If numMatch is greater than the bestMatch this code will execute.
		if (numMatch > bestMatch)
		{
			//Setting bestMatch equal to numMatch.
			bestMatch = numMatch;
			//Setting place to the current count.
			place = count;
		}

		//Resetting numMatch to 0 for the next iteration.
		numMatch = 0;
	}

	//For loop. This loop iterates 4 times.
	for (int count = 0; count < 4; count++)
	{
		//Setting the action array to the genes recommended actions.
		action[count] = geneTable[place][count + 4];
	}
}
//End of Robot method compareGenes.

//This Robot class method sets a passed array to the robots current genes.
void robot::getGeneTable(char tArray[24][8])
{
	//For loop. This loop iterates 24 times.
	for (int index = 0; index < 24; index++)
	{
		//Nested For loop. This loop iterates 8 times.
		for (int count = 0; count < 8; count++)
		{
			//Copying one line of gene data from the geneTable.
			tArray[index][count] = geneTable[index][count];
		}
	}
}
//End of Robot method getGeneTable.

//This Robot class method prints the robots current genes.
void robot::printGenes()
{
	//For loop. This loop iterates 24 times.
	for (int index = 0; index < 24; index++)
	{
		//Nested For loop. This loop iterates 8 times.
		for (int count = 0; count < 8; count++)
		{
			//Printing one line of geneTable data.
			cout << geneTable[index][count] << " ";
		}

		//Printing a new line.
		cout << endl;
	}
}
//End of Robot method printGenes.

//Function prototypes. For more info on each function see where they are defined.
void playGame(robot &test, int turns, int moves);
void randomField(char tArray[12][12]);
void printField(char tArray[12][12]);
void breedRobots(robot test[200]);
void examineData(robot test[200]);
void resetRobots(robot test[200]);
void sortRobots(robot test[200]);

robot swapGenes(robot &one, robot &two);

char robotMenu();

//Main function to execute.
int main()
{
	//Printing the programs welcome message.
	cout << "Welcome to the genetic algorithm robot simulation. In this simulation," << endl;
	cout << "the computer will attempt to learn how to navigate a playing field" << endl;
	cout << "in the best way possible using robots!" << endl;

	//Grabbing a seed for the rand() function.
	srand(time(NULL));

	// Constraint 6 - Use a robot population of 200 individuals.
	//Creating an array filled with 200 Robot objects.
	robot test[200];

	//Declaring needed variables.
	string temp;

	//This char variables holds the return value from the menu function.
	char answer;

	//Boolean variables used in loop and first iteration cases.
	bool keepGoing = true;
	bool firstIteration = false;	

	//Program control variables.
	//Note: The variables that have a d in front are default. The others are for custom parameters.
	int cIterations = 100;
	int dIterations = 100;

	int dMoves = 1;
	int cMoves = 1;

	int dSurvival = 25;
	int cSurvival = 25;

	//While loop. This loop iterates until broken out of.
	while (keepGoing == true)
	{
		//Setting answer equal to the return of the robotMenu function.
		answer = robotMenu();

		//Switching answer.
		switch (answer)
		{
		// Bonus - The user can define the desired number of iterations.
		//If the case is 1 this code will execute.
		case '1':
			//Asking the user to enter an integer number.
			cout << "\nPlease enter an integer number." << endl;
			//Reading to a string variable.
			cin >> temp;
	
		//Return point for goto statement.
		tryAgainI:

			// Bonus - Using a couple Try/Catch constructs in my program.
			//Try/Catch construct. Used to catch errors from the stoi function.
			try
			{
				//Attempting to convert string to integer.
				cIterations = stoi(temp);
			}

			//If stoi throws an invalid argument error it will be caught here.
			catch (invalid_argument& e)
			{
				//Asking the user to try again.
				cout << "\nThe number " << cIterations << " is not valid. Try again." << endl;
				cin >> temp;

				//Going to tryAgainI.
				goto tryAgainI;
			}

			//If stoi throws an out of range error it will be caught here.
			catch (out_of_range& e)
			{
				//Asking the user to try again.
				cout << "\nThe number " << cIterations << " is not valid. Try again." << endl;
				cin >> temp;

				//Going to tryAgainI.
				goto tryAgainI;
			}

			//If the value held in cIterations is less than 1 this code will execute.
			if (cIterations < 1)
			{
				//Setting cIterations to 1.
				cIterations = 1;

				//Informing the user of the change.
				cout << "\nIteration value to low. Setting to 1." << endl;
			}

			//If cIterations is greater then 100,000 this code will execute.
			if (cIterations > 100000)
			{
				//Setting cIterations to 100,000.
				cIterations = 100000;

				//Informing the user of the change.
				cout << "\nIteration value to high. Setting to 100,000." << endl;
			}

			//Informing the user that the operation was successful.
			cout << "\nIterations set!" << endl;

			//Breaking out of the case.
			break;

		// Bonus - The user can choose between 2 options for number of moves per gene.
		//If the case is 2 this code will execute.
		case '2':
			//This simple menu gives the user 2 options.
			cout << "\nSelect desired move amount" << endl;
			cout << "========================================" << endl;
			cout << "1. One move per gene." << endl;
			cout << "2. Two moves per gene." << endl;

			//Reading the answer.
			cin >> answer;

			//Input validation loop.
			while (answer < '1' || answer > '2')
			{
				cout << endl << answer << " is not a valid input. Please try again." << endl;
				cin >> answer;
			}

			//If the answer is 1 this code execute.
			if (answer == '1')
			{
				//Setting cMoves to 1.
				cMoves = 1;
			}

			//Else, this code executes.
			else
			{
				//Setting cMoves to 2.
				cMoves = 2;
			}

			//Informing the user that the operation was successful.
			cout << "\nMoves set!" << endl;

			//Breaking out of the case.
			break;

		// Bonus - The user can set the number of turns they want their robots to survive.
		//If the case is 3 this code will execute.
		case '3':
			//Asking the user to enter an integer number.
			cout << "\nPlease enter an integer number." << endl;
			//Reading to a string variable.
			cin >> temp;

		//Return point for goto statement.
		tryAgainS:

			//Try/Catch construct. Used to catch errors from the stoi function.
			try
			{
				//Attempting to convert temp to an integer.
				cSurvival = stoi(temp);
			}

			//If stoi throws the invalid argument error this will catch it.
			catch (invalid_argument& e)
			{
				//Asking the user to try again.
				cout << "\nThe number " << cSurvival << " is not valid. Try again." << endl;
				cin >> temp;

				//Going to tryAgainS.
				goto tryAgainS;
			}

			//If stoi throws the out of range error this will catch it.
			catch (out_of_range& e)
			{
				//Asking the user to try again.
				cout << "\nThe number " << cSurvival << " is not valid. Try again." << endl;
				cin >> temp;
				cSurvival = stoi(temp);

				//Going to tryAgainS.
				goto tryAgainS;
			}

			//If the value stored in cSurvival is less than 1 this code executes.
			if (cSurvival < 1)
			{
				//Setting cSurvival to 1.
				cSurvival = 1;

				//Informing the user of the change.
				cout << "\nSurvival time to low. Setting to 1." << endl;
			}

			//If the value stored in cSurvival is greater than 50 this code executes.
			if (cSurvival > 50)
			{
				//Setting cSurvival to 50.
				cSurvival = 50;

				//Informing the user of the change.
				cout << "\nSurvival time to high. Setting to 50." << endl;
			}

			//Informing the user that the operation was successful.
			cout << "\nSurvival parameters set!" << endl;

			//Breaking out of the case.
			break;

		//If the case is 4 this code executes.
		//Note: This code uses the default parameters.
		case '4':

			//If an iteration has already been run this code executes.
			if (firstIteration == true)
			{
				//Calling the breedRobots function.
				breedRobots(test);
			}

			//Outputting the word "Processing."
			cout << "\nProcessing";

			//For loop. This loop iterates to the size of dIterations.
			for (int index = 0; index < dIterations; index++)
			{
				//Nested For loop. This loop iterates 200 times.
				for (int count = 0; count < 200; count++)
				{
					// Constraint 6 - Run all the robots through the room before breeding.
					//Calling the playGame function for each individual robot.
					playGame(test[count], dSurvival, dMoves);
				}

				//If the current index is one less than the value in dIterations this code executes.
				if (index == dIterations - 1)
				{
					//Calling the sortRobots function.
					sortRobots(test);
					//Breaking out of the loop.
					break;
				}

				//Calling the sortRobots function.
				sortRobots(test);

				//If the current index is divisble by 10 with no remainder this code executes.
				if (index % 10 == 0)
				{
					//Printing a dot.
					cout << "." << flush;
				}

				//Calling the breedRobots function.
				breedRobots(test);
			}

			//Setting firstIteration to true.
			firstIteration = true;

			//Printing a new line.
			cout << endl;

			//Breaking out of the case.
			break;

		//If the case is 5 this code executes.
		//Note: This code uses the custom parameters.
		case '5':

			//If an iteration has already been run this code executes.
			if (firstIteration == true)
			{
				//Calling the breedRobots function.
				breedRobots(test);
			}

			//Printing the word "Processing."
			cout << "\nProcessing";

			//For loop. This loop iterates to the current size of cIterations.
			for (int index = 0; index < cIterations; index++)
			{
				//Nested For loop. This loop iterates 200 times.
				for (int count = 0; count < 200; count++)
				{
					// Constraint 6 - Run all the robots through the room before breeding.
					//Calling the playGame function for each individual robot.
					playGame(test[count], cSurvival, cMoves);
				}

				//If the current index is one less than the value in dIterations this code executes.
				if (index == cIterations - 1)
				{
					//Calling the sortRobots function.
					sortRobots(test);

					//Breaking out of the loop.
					break;
				}

				//Calling the sortRobots function.
				sortRobots(test);

				//If the current index is divisble by 10 with no remainder this code executes.
				if (index % 10 == 0)
				{
					//Printing a dot.
					cout << ".";
				}

				//Calling the breedRobots function.
				breedRobots(test);
			}

			//Setting the firstIteration to true.
			firstIteration = true;

			//Printing a new line.
			cout << endl;

			//Breaking out of the case.
			break;

		//If the case is 6 this code executes.
		case '6':
			//Calling the examineData function.
			examineData(test);

			//Breaking out of the case.
			break;

		// Bonus - The user can reset their robots to infancy.
		//If the case is 7 this code executes.
		case '7':
			//Calling the resetRobots function.
			resetRobots(test);

			//Setting the firstIteration to false.
			firstIteration = false;

			//Informing the user that the operation was successful.
			cout << "\nRobots reset!" << endl;

			//Breaking out of the case.
			break;

		//If the case is 8 this code executes.
		case '8':
			//Setting keepGoing to false.
			keepGoing = false;

			//Breaking out of the case.
			break;
		}
	}

	//Saying Goodbye.
	cout << "\nGoodbye :)" << endl;

	//Exiting with status 0.
	return 0;
}
//End of main function.

//This function accepts one robot object. It then creates a field and allows the robot to play until it is dead or wins.
void playGame(robot &test, int turns, int moves)
{
	//These int variables will hold the robots position.
	int posX;
	int posY;

	//Creating a needed variable.
	int place;

	//These 2 char arrays will hold the sensor data with the corresponding action(s).
	char sensorData[4];
	char action[4];

	//This boolean is set to true when the robot dies.
	bool isDead = false;

	//Creating a char array that will represent the robots 'playground.'
	// Constraint 1 - Create a 12 by 12 square room.
	char playField[12][12];

	//Calling the randomField function.
	randomField(playField);

	//Setting posX to a random number in range of 0 to 10.
	// Constraint 2 - Start your robot on a random square with 5 power.
	posX = rand() % 11;

	//While posX is 0 this code executes.
	while (posX == 0)
	{
		//Setting posX to a new random number.
		posX = rand() % 11;
	}

	//Setting posY to a random number in range of 0 to 10.
	posY = rand() % 11;

	//While posY is 0 this code executes.
	while (posY == 0)
	{
		//Setting posY to a new random number.
		posY = rand() % 11;
	}

	//If the place where the robot is randomly placed is a 1 for battery this code executes.
	if (playField[posY][posX] == '1')
	{
		//Incrementing the batteries collected variable.
		test.incBatteries();
		//Incrementing the robots remaining energy.
		test.incEnergy();
	}

	// Constraint 4 - Each robot will move a total of 12-25 times.
	//This loop iterates to the value of the turns variable.
	for (int count = 0; count < turns; count++)
	{
		//Setting the robots sensor data.
		sensorData[0] = playField[posY + 1][posX];
		sensorData[1] = playField[posY - 1][posX];
		sensorData[2] = playField[posY][posX + 1];
		sensorData[3] = playField[posY][posX - 1];

		//Comparing the sensor data with the robots genes.
		test.compareGenes(sensorData, action);

		//Setting place to 0.
		place = 0;

		//This loop iterates to the value of moves.
		for (int index = 0; index < moves; index++)
		{
			//If the robot current action direction is N this code executes.
			if (action[place] == 'N')
			{
				//If the robots action is M this code executes.
				if (action[place + 1] == 'M')
				{
					//If what is in front of the robot is a 9 this code executes..
					if (playField[posY + 1][posX] == '9')
					{
						// Constraint 5 - Robots that hit walls will fail and lose 1 power.
						//Decrementing the robots energy for hitting a wall.
						test.DecEnergy();

						//If the robots current energy is 0 or less this code executes.
						if (test.getEnergy() <= 0)
						{
							//Setting isDead to true.
							isDead = true;

							//Breaking out of the loop.
							break;
						}

						//Continuing to the next iteration.
						continue;
					}

					//If what is in front of the robot is a 1 this code executes.
					if (playField[posY + 1][posX] == '1')
					{
						//Incrementing batteries collected variable.
						test.incBatteries();

						//Incrementing the robots energy.
						test.incEnergy();

						//Moving the robot up 1.
						posY++;

						//Removing the battery.
						playField[posY][posX] = '0';

						//Continuing to the next iteration.
						continue;
					}

					//If what is in front of the robot is 0 this code executes.
					if (playField[posY + 1][posX] == '0')
					{
						//Moving the robot up 1.
						posY++;

						//Continuing to the next iteration.
						continue;
					}
				}
			}

			//If the robot current action direction is S this code executes.
			if (action[place] == 'S')
			{
				//If the robots action is M this code executes.
				if (action[place + 1] == 'M')
				{
					//If what is behing the robot is a 9 this code executes.
					if (playField[posY - 1][posX] == '9')
					{
						// Constraint 5 - Robots that hit walls will fail and lose 1 power.
						//Decrementing the robots energy.
						test.DecEnergy();

						//If the robots current energy is 0 or less this code executes.
						if (test.getEnergy() <= 0)
						{
							//Setting isDead to true.
							isDead = true;

							//Breaking out of the loop.
							break;
						}

						//Continuing to the next iteration.
						continue;
					}

					//If what is behind the robot is a 1. this code executes.
					if (playField[posY - 1][posX] == '1')
					{
						//Incrementing the batteries collected variable.
						test.incBatteries();
						//Incrementing the robot's energy.
						test.incEnergy();
						//Moving the robot down 1.
						posY--;

						//Removing the battery.
						playField[posY][posX] = '0';

						//Continuing to the next iteration.
						continue;
					}

					//If what is behind the robot is a 0 this code executes.
					if (playField[posY - 1][posX] == '0')
					{
						//Moving the robot down 1.
						posY--;

						//Continuing to the next iteration.
						continue;
					}
				}
			}

			//If the robot current action direction is E this code executes.
			if (action[place] == 'E')
			{
				//If the robots action is M this code executes.
				if (action[place + 1] == 'M')
				{
					//If what is to the ease of the robot is a 9 this code executes.
					if (playField[posY][posX + 1] == '9')
					{
						// Constraint 5 - Robots that hit walls will fail and lose 1 power. 						
						//Decrementing the robots energy.
						test.DecEnergy();

						//If the robots current energy is 0 or less this code executes.
						if (test.getEnergy() <= 0)
						{
							//Setting isDead to true.
							isDead = true;

							//Breaking out of the loop.
							break;
						}

						//Continuing to the next iteration.
						continue;
					}

					//If what is to the east of the robot is a 1 this code executes.
					if (playField[posY][posX + 1] == '1')
					{
						//Incrementing the batteries collected variable.
						test.incBatteries();
						//Incrementing the robots energy.
						test.incEnergy();
						//Moving the robot right 1.
						posX++;

						//Removing the battery.
						playField[posY][posX] = '0';

						//Continuing to the next iteration.
						continue;
					}

					//If what is to the east of the robot is a 0 this code executes.
					if (playField[posY][posX + 1] == '0')
					{
						//Moving the robot right 1.
						posX++;

						//Continuing to the next iteration.
						continue;
					}
				}
			}

			//If the robot current action direction is W this code executes.
			if (action[place] == 'W')
			{
				//If the robots action is M this code executes.
				if (action[place + 1] == 'M')
				{
					//If what is to the west of the robot is a 9 this code executes.
					if (playField[posY][posX - 1] == '9')
					{
						// Constraint 5 - Robots that hit walls will fail and lose 1 power.f 1						
						//Decrementing the robots energy.
						test.DecEnergy();

						//If the robots current energy is 0 or less this code executes.
						if (test.getEnergy() <= 0)
						{
							//Setting isDead to true.
							isDead = true;

							//Breaking out of the loop.
							break;
						}

						//Continuing to the next iteration.
						continue;
					}

					//If what is to the west of the robot is a 1 this code executes.
					if (playField[posY][posX - 1] == '1')
					{
						//Incrementing the batteries variable.
						test.incBatteries();
						//Incrementing the energy variable.
						test.incEnergy();
						//Moving the robot left 1.
						posX--;

						//Removing the battery.
						playField[posY][posX] = '0';

						//Continuing to the next iteration.
						continue;
					}

					//If what is to the west of the robot is a 0 this code executes.
					if (playField[posY][posX - 1] == '0')
					{
						//Moving the robot left 1.
						posX--;

						//Continuing to the next iteration.
						continue;
					}
				}
			}

			//Adding 2 to place.
			place = place + 2;
		}

		//If isDead is true this code executes.
		if (isDead == true)
		{
			//Breaking out of the loop.
			break;
		}

		//Incrementing the robots turns survived.
		test.incTurns();

		//Decrementing the robots remaining energy.
		test.DecEnergy();

		//If the robots energy is 0 this code executes.
		if (test.getEnergy() <= 0)
		{
			//Setting isDead to true.
			isDead = true;

			//Breaking out of the loop.
			break;
		}
	}

	//If isDead is true this code executes.
	if (isDead == true)
	{
		//Returning to the caller.
		return;
	}

	//Else, this code executes.
	else
	{
		// Constraint 4 - The robot's score is the amount of power it has when it exits the game.
		//Setting the robots score to the remaining energy.
		test.setScore(test.getEnergy());

		//Returning to the caller.
		return;
	}
}
//End of playGame function.

//This function accepts a 12x12 array and randomizes for the robot to play on.
void randomField(char tArray[12][12])
{
	//These variables will be used to hold possible battery placement locations.
	int posX;
	int posY;

	//Setting the borders of the field.

	//For loop. This loop iterates 12 times.
	for (int count = 0; count < 12; count++)
	{
		//Setting the array edge to 9.
		tArray[0][count] = '9';
	}

	//For loop. This loop iterates 12 times.
	for (int count = 0; count < 12; count++)
	{
		//Setting the array edge to 9.
		tArray[11][count] = '9';
	}

	//For loop. This loop iterates 12 times.
	for (int count = 0; count < 12; count++)
	{
		//Setting the array edge to 9.
		tArray[count][0] = '9';
	}

	//For loop. This loop iterates 12 times.
	for (int count = 0; count < 12; count++)
	{
		//Setting the array edge to 9.
		tArray[count][11] = '9';
	}

	//Set middle to all zeros.

	//For loop. This loop iterates 10 times.
	for (int index = 1; index < 11; index++)
	{
		//Nested For loop. This loop iterates 10 times.
		for (int count = 1; count < 11; count++)
		{
			//Setting the current element to 0.
			tArray[index][count] = '0';
		}
	}

	//Randomly disperse batteries 40%

	// Constraint 3 - Populate 40% of the squares with batteries.
	//For loop. This loop iterates 40 times.
	for (int count = 0; count < 40; count++)
	{
		//Setting posX to a random number with range of 0 to 10.
		posX = rand() % 11;
		
		//While posX equal 0 this code executes.
		while (posX == 0)
		{
			//Setting posX to a new random number.
			posX = rand() % 11;
		}

		//Setting posY to a random number with range of 0 to 10.
		posY = rand() % 11;

		//While posY equals 0 this code executes.
		while (posY == 0)
		{
			//Setting posY to a new random number.
			posY = rand() % 11;
		}

		//If the current looked at element is already 1 this code executes.
		if (tArray[posY][posX] == '1')
		{
			//Decrementing the count.
			count--;

			//Continuing to the next iteration.
			continue;
		}

		//Else, this code executes.
		else
		{
			//Setting the current array element to 1.
			tArray[posY][posX] = '1';
		}
	}
}
//End of randomField function.

//This function print a 12x12 array of type char.
//Note: This function is only used for debugging purposes.
void printField(char tArray[12][12])
{
	//For loop. This loop iterates 12 times.
	for (int index = 0; index < 12; index++)
	{
		//Nested For loop. This loop iterates 12 times. 
		for (int count = 0; count < 12; count++)
		{
			//Printing the current looked at element.
			cout << tArray[index][count] << " ";
		}

		//Printing a new line.
		cout << endl;
	}
}
//End of printField function.

//This function accepts a batch of robots and breeds them.
void breedRobots(robot test[200])
{
	//Creating a new batch of robots.
	robot temp[200];

	//Several needed int variables.
	int count = 0;
	int place = 0;
	int robotNumber = 0;

	//While loop, this loop iterates until count is 100.
	while (count < 100)
	{
		//Setting the current new robot to the return of swapGenes.
		temp[robotNumber] = swapGenes(test[place], test[place + 1]);

		//Incrementing the robotNumber variable.
		robotNumber++;

		//Setting the current new robot to the return of swapGenes.
		temp[robotNumber] = swapGenes(test[place + 1], test[place]);

		//Incrementing several variables.
		robotNumber++;
		place++;
		count++;
	}

	//Putting the new batch of robots in the old array.

	//For loop. This loop iterates 200 times.
	for (int count = 0; count < 200; count++)
	{
		//Overwriting the old robots with the new ones.
		test[count] = temp[count];
	}
}
//End of breedRobots function.

//This function allows the user to examine the data of the current batch of robots.
void examineData(robot test[200])
{
	//Creating several needed variables.
	char answer;
	int numDisplay;
	int place;
	int high = -1;

	//Printing a menu.
	cout << "\nExamine Data Menu" << endl;
	cout << "========================================" << endl;
	cout << "1. List all basic robot data of current batch." << endl;
	cout << "2. List detailed data for specific robot." << endl;

	//Reading the inputted answer.
	cin >> answer;

	//Input validation loop.
	while (answer < '1' || answer > '2')
	{
		cout << endl << answer << " is not a valid input. Please try again." << endl;
		cin >> answer;
	}

	//If the answer is 1 this code executes.
	if (answer == '1')
	{
		//Printing a menu.
		cout << "\nHow many Robots?" << endl;
		cout << "========================================" << endl;
		cout << "1. 10 top robots" << endl;
		cout << "2. 50 top robots" << endl;
		cout << "3. 100 top robots" << endl;
		cout << "4. 200 top robots" << endl;
		
		//Reading the inputted answer.
		cin >> answer;

		//Input validation loop.
		while (answer < '1' || answer > '4')
		{
			cout << endl << answer << " is not a valid input. Please try again." << endl;
			cin >> answer;
		}

		//Switching the answer.
		switch (answer)
		{
		//If the case is 1 this code executes.
		case '1':
			//Setting numDisplay to 10.
			numDisplay = 10;

			//Breaking out of the case.
			break;

		//If the case is 2 this code executes.
		case '2':
			//Setting numDisplay to 50.
			numDisplay = 50;

			//Breaking out of the case.
			break;

		//If the case is 3 this code executes.
		case '3':
			//Setting numDisplay to 100.
			numDisplay = 100;

			//Breaking out of the case.
			break;

		//If the case is 4 this code executes.
		case '4':
			//Setting numDisplay to 200.
			numDisplay = 200;

			//Breaking out of the case.
			break;
		}

		//For loop. This loop iterates to the size of numDisplay.
		for (int count = 0; count < numDisplay; count++)
		{
			//Printing the robots basic data.
			cout << "\nRobot " << count + 1 << endl;
			cout << "=========================" << endl;
			cout << "Batteries Collected: " << test[count].getBatteries() << endl;
			cout << "Turns Survived: " << test[count].getTurns() << endl;
			cout << "Energy Left: " << test[count].getEnergy() << endl;
			cout << "Score: " << test[count].getScore() << endl;
		}

		//Returning to the caller.
		return;
	}

	//If the answer is 2 this code executes.
	if (answer == '2')
	{
		//Printing a menu.
		cout << "\nWhat Robot?" << endl;
		cout << "========================================" << endl;
		cout << "1. Display detailed data for longest surviving robot." << endl;
		cout << "2. Display detailed data for most batteries collected robot." << endl;

		//Reading the inputted answer.
		cin >> answer;

		//Input validation loop.
		while (answer < '1' || answer > '2')
		{
			cout << endl << answer << " is not a valid input. Please try again." << endl;
			cin >> answer;
		}

		//If the answer is 1 this code executes.
		if (answer == '1')
		{
			//For loop. This loop iterates 200 times.
			for (int count = 0; count < 200; count++)
			{
				//If the current turn count of the robot is greater than high this code executes.
				if (test[count].getTurns() > high)
				{
					//Setting high to the current robots turn total.
					high = test[count].getTurns();

					//Setting place to count.
					place = count;
				}
			}

			//Printing the robots basic details.
			cout << "\nRobot Basic Details" << endl;
			cout << "========================================" << endl;
			cout << "Batteries Collected: " << test[place].getBatteries() << endl;
			cout << "Turns Survived: " << test[place].getTurns() << endl;
			cout << "Energy Left: " << test[place].getEnergy() << endl;
			cout << "Score: " << test[place].getScore() << endl;

			//Printing the robots genes.
			cout << "\nRobot Genes" << endl;
			cout << "========================================" << endl << endl;
			test[place].printGenes();

			//Returning to the caller.
			return;
		}

		//If the answer is 2 this code executes.
		if (answer == '2')
		{
			//For loop. This loop iterates 200 times.
			for (int count = 0; count < 200; count++)
			{
				//If the current robots batteries collected variable is greater than high this code executes.
				if (test[count].getBatteries() > high)
				{
					//Setting high to the current robots batteries collected variable.
					high = test[count].getBatteries();

					//Setting place to count.
					place = count;
				}
			}

			//Printing the robots basic details.
			cout << "\nRobot Basic Details" << endl;
			cout << "========================================" << endl;
			cout << "Batteries Collected: " << test[place].getBatteries() << endl;
			cout << "Turns Survived: " << test[place].getTurns() << endl;
			cout << "Energy Left: " << test[place].getEnergy() << endl;
			cout << "Score: " << test[place].getScore() << endl;

			//Printing the robots genes.
			cout << "\nRobot Genes" << endl;
			cout << "========================================" << endl << endl;
			test[place].printGenes();

			//Returning to the caller.
			return;
		}
	}
}
//End of examineData functin.

//This function clears all current robots and replaces them with new random robots.
void resetRobots(robot test[200])
{
	//Creating a new batch of robots.
	robot temp[200];

	//For loop. This loop iterates 200 times.
	for (int count = 0; count < 200; count++)
	{
		//Overwriting the old robot with the new randomly generated robot.
		test[count] = temp[count];
	}
}
//End of resetRobots function.

//This function sorts an array of robot objects in descending order based on the variable bCollected.
void sortRobots(robot test[200])
{
	//Creating a temp robot object.
	robot temp;

	//Creating a couple needed variables.
	int count = 0;
	int loop = 199;

	//For loop. This loop iterates 200 times.
	for (int index = 0; index < 200; index++)
	{
		//Nested While loop. This loop iterates until count is greater than loop.
		while (count < loop)
		{
			//If the current robots bCollected is greater than the next robots this code executes.
			if (test[count].getBatteries() < test[count + 1].getBatteries())
			{
				//Setting the current robot to temp.
				temp = test[count];
				//Setting the current robot to the next robot.
				test[count] = test[count + 1];
				//Setting the next robot to temp.
				test[count + 1] = temp;
			}
			//Incrementing count.
			count++;
		}

		//Setting count to 0 and decrementing loop.
		count = 0;
		loop--;
	}

	//Returning to the caller.
	return;
}
//End of sortRobots function.

//This function accepts two robots and returns a new robot with their mixed genes.
robot swapGenes(robot &one, robot &two)
{
	//Creating a new robot object.
	robot baby;

	//Creating two char arrays. These arrays will hold the parents genes.
	char rOneGenes[24][8];
	char rTwoGenes[24][8];

	//Copying the robots genes.
	one.getGeneTable(rOneGenes);
	two.getGeneTable(rTwoGenes);

	//Setting the new robots genes to a combination of the parents.
	baby.setGeneTable(rOneGenes, rTwoGenes);

	//Returning the baby.
	return baby;
}
//End of swapGenes function.

//This function displays the programs menu.
char robotMenu()
{
	//Creating a needed variable.
	char answer;

	//Printing the menu.
	cout << "\nGenetic Algorithm Robot Menu" << endl;
	cout << "========================================" << endl;
	cout << "1. Set number of iterations" << endl;
	cout << "2. Set number of moves per gene." << endl;
	cout << "3. Set number of turns for survival." << endl;
	cout << "4. Run (with default parameters)" << endl;
	cout << "5. Run (with custom parameters)" << endl;
	cout << "6. See data on robots." << endl;
	cout << "7. Reset Robots" << endl;
	cout << "8. Quit program" << endl;

	//Reading the inputted answer.
	cin >> answer;

	//Input validation loop.
	while (answer < '1' || answer > '8')
	{
		cout << endl << answer << " is not a valid input. Please try again." << endl;
		cin >> answer;
	}

	//Returning the answer.
	return answer;
}
//End of robotMenu function.
