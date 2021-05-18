//Program name: Hokeeman
//Program Description: This program is a virtual pet simulator. It allows the user to own and manage a virtual pet.
//My name: Quinn Roemer W1582947
//CISP 400 T/Th FLC 9-10:20am
//November 6th 2017

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

//=========================================================================
//		Beginning of Class Declarations/methods			  |
//=========================================================================

//This is an abstract class that is used to derive the child classes.
// Constraint 7 - Implement an abstract base class called creature.
class creature
{
//Declaring shared variables as protected.
protected:
	string name;
	int health;
	int hunger;
	int boredom;
public:
	//Creating a constructor for this class. 
	creature();
	//Several methods which will be shared between all of the objects.
	virtual void passTime() = 0;
	virtual void setHealth(int iTemp) { health = iTemp; }
	virtual void setHunger(int iTemp) { hunger = iTemp; }
	virtual void setBoredom(int iTemp) { boredom = iTemp; }
	virtual int getHealth() { return health; }
	virtual int getHunger() { return hunger; }
	virtual int getBoredom() { return boredom; }
	virtual string getName() { return name; }
};
//End of Creature class.

//Constructor of creature.
// Constraint 4 - Use a constructor to intilize hunger and boredom randomly.
creature::creature()
{
	//Intiliing boredom and hunger to random numbers between 0-9.
	boredom = rand() % 10;
	hunger = rand() % 10;
	//Setting health to 20.
	health = 20;
}

//Derived class, this class hold the data for a water Hokeeman.
// Constraint 8 - Instantiate using child classes. This code contains 4.
class wHokeeman : public creature
{
public:
	//Class constructor.
	wHokeeman()
	{
		//Ignoring all previous input.
		cin.ignore();
		//Asking the user to enter a name and reading the line.
		cout << "\nPlease enter a name for your new Hokeeman" << endl;
		getline(cin, name);
	}
	//Passtime method.
	// Constraint 1 - Implement a passTime() which increases hunger and boredom.
	virtual void passTime()
	{
		//This methods increments boredom and hunger by one.
		boredom++;
		hunger++;

		//This method will increase health by 5 until it reaches 20.
		if (health >= 15)
		{
			health = 20;
		}
		if (health < 15)
		{
			health = health + 5;
		}
	}
};
//End of wHokeeman class.

//Derived class, this class contains the code for an earth Hokeeman.
class eHokeeman : public creature
{
public:
	//Class constructor.
	eHokeeman()
	{
		//Ignoring all previous input.
		cin.ignore();
		//Asking the user to enter a name and reading the line.
		cout << "\nPlease enter a name for your new Hokeeman" << endl;
		getline(cin, name);
	}
	//Passtime method.
	virtual void passTime()
	{
		//This method increases hunger and boredom by 1.
		boredom++;
		hunger++;

		//This method will increase health by 5 until it reaches 20.
		if (health >= 15)
		{
			health = 20;
		}
		if (health < 15)
		{
			health = health + 5;
		}
	}
};
//End of eHokeeman class.

//Derived class, this class contains the code for an air Hokeeman.
class aHokeeman : public creature
{
public:
	//Class constructor.
	aHokeeman()
	{
		// Bonus - Each Hokeemon class contains a constructor that allows you to name the pet.
		//Ignoring all previous input.
		cin.ignore();
		//Asking the user to enter a name and reading the line.
		cout << "\nPlease enter a name for your new Hokeeman" << endl;
		getline(cin, name);
	}
	//Passtime method.
	virtual void passTime()
	{
		//This method increases hunger and boredom by 1.
		boredom++;
		hunger++;

		//This method will increase health by 5 until it reaches 20.
		if (health >= 15)
		{
			health = 20;
		}
		if (health < 15)
		{
			health = health + 5;
		}
	}
};
//End of aHokeeman class.

//Derived class, this class contains the code for a fire Hokeeman.
class fHokeeman : public creature
{
public:
	//Class constructor.
	fHokeeman()
	{
		//Ignoring all previous input.
		cin.ignore();
		//Asking the user to enter a name and reading the line.
		cout << "\nPlease enter a name for your new Hokeeman" << endl;
		getline(cin, name);
	}
	//Passtime method.
	virtual void passTime()
	{
		//This method increases boredom and hunger by 1.
		boredom++;
		hunger++;

		//This method will increase health by 5 until it reaches 20.
		if (health >= 15)
		{
			health = 20;
		}
		if (health < 15)
		{
			health = health + 5;
		}
	}
};
//End of fHokeeman method.

//=========================================================================
//			    Function Prototypes.			  |
//=========================================================================

//For function explanations see below cod.
void buy(vector<creature*> &playerPets, int& gold);

void fight(vector<creature*> &playerPets, int&); 

void feed(vector<creature*> &playerPets, int&); 

void passTime(vector<creature*> &playerPets);

void listen(vector<creature*> &playerPets);

void play(vector<creature*> &playerPets);

void buyFood(int&, int&);

string sUp(string);

void toContinue();

char userMenu();

void help();

//=========================================================================
//				Main Function				  |
//=========================================================================

//Beginning of main.
int main()
{
	//Creating a couple of variables.
	char answer;

	//This variables holds the user's balance in gold.
	// Bonus - Added a currency system. You gain gold by fighting other Hokeeman.
	int gold = 500; 

	//This variable holds the amount of food that the user owns.
	int food = 0;

	//Creating a seed for the rand function.
	srand((unsigned)time(0));

	//Creating a vector of creature pointers entitled playerPets.
	// Constraint 3 - Using a dynamic memory structure from the Standard Template Library.
	vector <creature*> playerPets;

	//Displaying the welcome message.
	cout << "Welcome to the Hokeeman game! In this game you must take care of your\nvery own Hokeeman. Good luck!" << endl;

	//Asking the user if they want to see the help.
	cout << "\nWould you like to see the rules of the game?" << endl;
	cout << "(enter 1 for yes, 0 for no)" << endl;
	cin >> answer;

	//Input validation loop.
	while ((answer != '0') && (answer != '1'))
	{
		cout << answer << " is not a valid input, please try again." << endl;
		cin >> answer;
	}

	//If the user answered '1' this code will execute.
	if (answer == '1')
	{
		//Calling the help() and toContinue() functions.
		help();
		toContinue();
	}

	//This loop will execute until broken out of.
	while (true)
	{
		//Calling the userMenu() function.
		answer = userMenu();

		//Switching the answer that userMenu() returns.
		switch (answer)
		{
		
		//If the answer is 1 this code will execute.
		case '1':
			//Calling buy().
			buy(playerPets, gold);
			//Calling toContinue().
			toContinue();
			//Breaking out of the switch case.
			break;

		//If the answer is 2 this code will execute.
		case '2':
			//Calling buyFood().
			buyFood(gold, food);
			//Calling toContinue().
			toContinue();
			//Breaking out of the switch case.
			break;

		//If the answer is 3 this code will execute.
		case '3':
			//Calling play().
			play(playerPets);
			//Calling toContinue().
			toContinue();
			//Breaking out of the switch case.
			break;
		
		//If the answer is 4 this code will execute.
		case '4':
			//Calling feed().
			feed(playerPets, food);
			//Calling toContinue().
			toContinue();
			//Breaking out of the switch case.
			break;

		//If the answer is 5 this code will execute.
		case '5':
			//Calling listen().
			listen(playerPets);
			//Calling toContinue().
			toContinue();
			//Breaking out of the switch case.
			break;

		//If the answer is 6 this code will execute.
		case '6':
			//Calling fight().
			fight(playerPets, gold);
			//Calling toContinue().
			toContinue();
			//Breaking out of the switch case.
			break;

		//If the answer is 7 this code will execute.
		case '7':
			//Informing the user of their current gold balance.
			cout << "\nYou have " << gold << "g." << endl;
			//Calling toContinue().
			toContinue();
			//Breaking out of the switch case.
			break;

		//If the answer is 8 this code will execute.
		case '8':
			//Asking the user if they really want to quit.
			cout << "\nAre you sure you want to quit?" << endl;
			cout << "(enter 1 for yes, 0 for no)" << endl;
			cin >> answer;
			
			//Input validation loop.
			while ((answer != '0') && (answer != '1'))
			{
				cout << answer << " is not a valid input, please try again." << endl;
				cin >> answer;
			}

			//If answer is 1 this code will execue.
			if (answer == '1')
			{
				//Setting gold to 0 and clearing playerPets.
				gold = 0;
				playerPets.clear();
			}

			//Breaking out of the switch case.
			break;

		}

		//If gold is less than 250 and the player has no pets this code will execute.
		if ((gold < 250) && (playerPets.size() == 0))
		{
			//Breaking out of the while loop.
			break;
		}
	}

	//Informing the user that the game is over.
	cout << "\nGame over!" << endl;
	return 0;
}
//End of main function.

//=========================================================================
//				Function Code.				  |
//=========================================================================

//This function allows the player to buy Hokeeman.
void buy(vector<creature*> &playerPets, int& gold)
{
	//Creating a char variable to hold the answer to questions.
	char answer;

	//If gold is less than 250 this code will execute.
	if (gold < 250)
	{
		//Informing the user they do not have enough gold to buy a Hokeeman.
		cout << "\nYou don't have enough gold to buy a Hokeeman." << endl;
		cout << "\nGo earn some gold in fights!" << endl;
		//Returning to main.
		return;
	}

	//Presenting the user with a menu. This menu asks the user what type of Hokeeman they want to buy.
	cout << "\nThere are 4 different types of Hokeeman to chose from." << endl;
	cout << "\nPlease make a choice." << endl;
	cout << "=========================" << endl;
	cout << "1. Water Hokeeman: 250g" << endl;
	cout << "2. Earth Hokeeman: 250g" << endl;
	cout << "3. Air Hokeeman: 250g" << endl;
	cout << "4. Fire Hokeeman: 250g" << endl;

	//Reading the inputted answer.
	cin >> answer;

	//Input validation loop.
	while ((answer <= '0') || (answer > '4'))
	{
		cout << answer << " is not a valid input, please try again." << endl;
		cin >> answer;
	}

	//Switching the answer.
	switch (answer)
	{
	
	//If answer is 1 this code will execute.
	case '1':

		//Adding a new water Hokeeman to playerPets.
		playerPets.push_back(new wHokeeman);
		//Informing the user they successfully bought a Hokeeman.
		cout << "\nYou have successfully bought a Water Hokeeman." << endl;
		//Breaking out of the switch case.
		break;

	//If the answer is 2 this code will execute.
	case '2':

		//Adding a new earth Hokeeman to playerPets.
		playerPets.push_back(new eHokeeman);
		//Informing the user they successfully bought a Hokeeman.
		cout << "\nYou have successfully bought an Earth Hokeeman." << endl;
		//Breaking out of the switch case.
		break;

	//If the answer is 3 this code will execute.
	case '3':

		//Adding a new air Hokeeman to playerPets.
		playerPets.push_back(new aHokeeman);
		//Informing the user they successfully bought a Hokeeman.
		cout << "\nYou have successfully bought an Air Hokeeman." << endl;
		//Breaking out of the switch case.
		break;

	//If the answer is 4 this code will execute.
	case '4':

		//Adding a new fire Hokeeman to playerPets.
		playerPets.push_back(new fHokeeman);
		//Informing the user they successfully bought a Hokeeman.
		cout << "\nYou have successfully bought a Fire Hokeeman." << endl;
		//Breaking out of the switch case.
		break;
	}
	//End of switch case.

	//Subtracting 250 gold from the user's balance.
	gold = gold - 250;

	//Informing the user of their new gold balance.
	cout << "\nYour new balance is " << gold << "g." << endl;
}

//This functin allows the user to fight another Hokeeman.
// Bonus - This function allows the enslaved Hokeeman to fight to the death.
void fight(vector<creature*> &playerPets, int& gold)
{
	//Creating several needed variables.
	string name, temp;
	int place, random, cHealth, tRandom;
	bool isFound = false;
	char answer;

	//If the user has no pets this code will execute.
	if (playerPets.size() == 0)
	{
		//Informing the user they have no pets.
		cout << "\nYou don't own any Hokeeman." << endl;
		cout << "\nGo buy some Hokeeman!" << endl;
		//Returning to main.
		return;
	}

	//Ignoring all previous input.
	cin.ignore();
	//Asking the user to enter the name of their Hokeeman they want to fight with.
	cout << "\nPlease enter the name of the Hokeeman you want to fight with." << endl;
	getline(cin, name);
	temp = name;

	//This loop executes until isFound is true.
	do
	{
		//This loop will execute to the size of playerPets.
		for (unsigned int count = 0; count < playerPets.size(); count++)
		{
			//If the name = the user entered name this code will execute.
			if (sUp(playerPets[count]->getName()) == sUp(temp))
			{
				//Saving the index of the found Hokeeman.
				place = count;
				//Setting name = name of found Hokeeman.
				name = playerPets[place]->getName();
				//Setting isFound to true.
				isFound = true;
				//Informing the user that their Hokeeman was found.
				cout << "\nYour Hokeeman was found!" << endl;
			}
		}

		//If isFound = false this code will execute.
		if (isFound == false)
		{
			//Informing the user that no Hokeeman was found.
			cout << "\nThat Hokeeman was not found." << endl;
			cout << "\nPlease enter a new name to search for. Or 0 to quit." << endl;
			getline(cin, name);

			//If the user enters zero this code will execute.
			if (name == "0")
			{
				//Returning to main.
				return;
			}
		}

	//End of Do While loop.
	} while (isFound == false);

	//Asing the user if they are sure they want to fight.
	cout << "\nAre you sure you want to fight with this Hokeeman?" << endl;
	cout << "(enter 1 for yes, 0 for no)" << endl;
	cin >> answer;

	//Input validation loop.
	while ((answer != '0') && (answer != '1'))
	{
		cout << answer << " is not a valid input, please try again." << endl;
		cin >> answer;
	}

	//If the answer is 0 this code will execute.
	if (answer == '0')
	{
		cout << "\nThe fight is off!" << endl;
		//Returning to main.
		return;
	}

	//Setting the computers health to 10.
	cHealth = 10;
	//Creating a random number. This number determines who goes first.
	tRandom = rand() % 2;
	cout << "\nFIGHT!!!" << endl;

	//This loop will execute until broken out of.
	while (true)
	{
		//If tRandom = 0 this code will execute.
		if (tRandom == 0)
		{
			//Informing the user that it is their turn.
			cout << "\nIt is your turn!" << endl;
			cout << "\nDo you want to attack or hold?" << endl;
			cout << "(enter 1 for attack, 0 for hold" << endl;
			cin >> answer;

			//Input validation loop.
			while ((answer != '0') && (answer != '1'))
			{
				cout << answer << " is not a valid input, please try again." << endl;
				cin >> answer;
			}

			//If answer = 0 this code will execute.
			if (answer == '0')
			{
				//Having the user's pet mentally attack the user.
				cout << endl << name << " quickly glances your way. You see a look of confusion on his/her face." << endl;
			}

			//If answer = 1 this code will execute.
			if (answer == '1')
			{
				//Creating a random number between 0-4.
				random = rand() % 5;

				//If random = 0 this code will execute.
				if (random == 0)
				{
					cout << endl << name << " missed!" << endl;
				}

				//If random is greater than 0 this code will execute.
				if (random > 0)
				{
					//Informing the user that they hit. Also, telling how much damage they dealt.
					cout << endl << name << " hit!" << endl;
					cout << endl << name << " dealt " << random << " damage to the enemy." << endl;
					//Subtracting the hit amount from the computers health.
					cHealth = cHealth - random;

					//If the computer has no health left this code will execute.
					if (cHealth <= 0)
					{
						//Breaking out of the while loop.
						break;
					}

					//Informing the user of the computers remaining health.
					cout << "The enemy now has " << cHealth << " health left." << endl;
				}
			}
			
			//Informing the user that it is now the enemies turn.
			cout << "\nIt is now the enemies turn!" << endl;

			//Creating a random number between 0-4.
			random = rand() % 5;

			//If random = 0 this code will execute.
			if (random == 0)
			{
				//Informing the user that the enemy missed.
				cout << "\nThe enemy missed!" << endl;
			}

			//If random is greater then 0 this code will execute.
			if (random > 0)
			{
				//Informing the user that the enemy hit.
				cout << "\nThe enemy hit and dealt " << random << " damage." << endl;
				//Subtracting the hit amount from the player pets health.
				playerPets[place]->setHealth(playerPets[place]->getHealth() - random);

				//If the player pets health is zero this code will execute.
				if (playerPets[place]->getHealth() <= 0)
				{
					//Breaking out of the while loop.
					break;
				}

				//Informing the user of the current health of their pet.
				cout << endl << name << " now has " << playerPets[place]->getHealth() << " health left." << endl;
			}
		}
		
		//If tRandom = 1 this code will execute.
		if (tRandom == 1)
		{
			//Informing the user that the computer gets to go first.
			cout << "\nIt is the computers turn." << endl;

			//Creating a random number between 0-4.
			random = rand() % 5;

			//If random = 0 this code will execute.
			if (random == 0)
			{
				//Informing the user that the enemy missed.
				cout << "\nThe enemy missed!" << endl;
			}

			//If random is greater than 0 this code will execute.
			if (random > 0)
			{
				//Informing the user that the enemy hit.
				cout << "\nThe enemy hit and dealt " << random << " damage." << endl;
				//Subtractng the hit amount from the players pet.
				playerPets[place]->setHealth(playerPets[place]->getHealth() - random);

				//If te player pets health is zero this code will execute.
				if (playerPets[place]->getHealth() <= 0)
				{
					//Breaking out of the while loop.
					break;
				}

				//Informing the user of the remaining health of their pet.
				cout << endl << name << " now has " << playerPets[place]->getHealth() << " health left." << endl;
			}

			//Informing the user that it is their turn.
			cout << "\nIt is your turn!" << endl;
			cout << "\nDo you want to attack or hold?" << endl;
			cout << "(enter 1 for attack, 0 for hold)" << endl;
			cin >> answer;

			//Input validation loop.
			while ((answer != '0') && (answer != '1'))
			{
				cout << answer << " is not a valid input, please try again." << endl;
				cin >> answer;
			}

			//If the answer is 0 this code will execute.
			if (answer == '0')
			{
				//Have the user's pet mentally attack the user.
				cout << endl << name << " quickly glances your way. You see a look of confusion on his/her face." << endl;
			}

			//Creating a random number between 0-4.
			random = rand() % 5;

			//If random = 0 this code will execute.
			if (random == 0)
			{
				//Informing the user that they missed.
				cout << endl << name << " missed!" << endl;
			}

			//If random is greater than 0 this code will execute.
			if (random > 0)
			{
				//Informing the user that they hit.
				cout << endl << name << " hit!" << endl;
				//Informing the user of the damage they dealt.
				cout << endl << name << " dealt " << random << " damage to the enemy." << endl;
				//Sutracting the hit amount from the computers health.
				cHealth = cHealth - random;

				//If the computers health is zero this code will execute.
				if (cHealth <= 0)
				{
					//Breaking out of the while loop.
					break;
				}

				//Informing the user of the enemies remaining health.
				cout << "\nThe enemy now has " << cHealth << " heath left." << endl;
			}
		}
	}
	//End of while loop.

	//If the player pets health is zero this code will execute.
	if (playerPets[place]->getHealth() <= 0)
	{
		//Informing the user that they lost.
		cout << endl << name << " has perished." << endl;
		cout << "\nYou have lost the fight." << endl;
		cout << "\nYou recieve no loot." << endl;

		//Removing the pet in question from their care.
		auto iter = playerPets.begin() + place;
		//Rotating the pet to the end of the vector.
		rotate(iter, iter + 1, playerPets.end());
		//Moving the vector back one.
		playerPets.pop_back();

		//Informing the user that their pet has been removed.
		cout << endl << name << " has been removed from your care." << endl;
	}

	//If the computers health is zero this code will execute.
	if (cHealth <= 0)
	{
		//Informing the user that they won the fight.
		cout << endl << name << " has won the fight!" << endl;
		//Creating a random number between 0-999.
		random = rand() % 1000;
		//Informing the user of the gold they recieved.
		cout << "\nYou receive " << random << "g!" << endl;
		//Adding the recieved gold to the user's balance.
		gold = gold + random;

		//Informing the user of their pets current health.
		cout << endl << name << "'s current health is " << playerPets[place]->getHealth() << "." << endl;
	}

	//Calling toContinue().
	toContinue();
	//Calling passTime().
	passTime(playerPets);
}
//End of fight().

//This function allows the user to feed their pets. Thus decreasing hunger.
void feed(vector<creature*> &playerPets, int& food)
{
	//Creating the needed variables.
	string name, temp;
	int place, cHunger;
	char answer;
	bool isFound = false;

	//If the user has no pets this code will execute.
	if (playerPets.size() == 0)
	{
		//Informing the user they don't have any Hokeeman.
		cout << "\nYou don't own any Hokeeman." << endl;
		cout << "\nGo buy some Hokeeman!" << endl;
		//Returning to main.
		return;
	}

	//If the user has no food this code will execute.
	if (food <= 0)
	{
		//Informing the user that they have no food.
		cout << "\nYou do not have enough food to feed your pets." << endl;
		cout << "\nGo buy some food!" << endl;
		//Returning to main.
		return;
	}

	//Ignoring all previous inputs.
	cin.ignore();

	//Asking the user to enter the name of the Hokeeman they wish to feed.
	cout << "\nPlease enter the name of the Hokeeman you want to feed." << endl;
	getline(cin, name);
	temp = name;

	//This loop will execute while isFound = false.
	do
	{
		//This loop executes to the current size of playerPets.
		for (unsigned int count = 0; count < playerPets.size(); count++)
		{
			//If the pet's name = the searched for name this code will execute.
			if (sUp(playerPets[count]->getName()) == sUp(temp))
			{
				//Saving the index of the found pet.
				place = count;
				//Setting isFound to true.
				isFound = true;
				//Setting name = to the found pet's name.
				name = playerPets[place]->getName();
				//Informing the user that their Hokeeman was found.
				cout << "\nYour Hokeeman was found!" << endl;
			}
		}

		//If isfound = false this code will execute.
		if (isFound == false)
		{
			//Informing the user that no Hokeeman was found.
			cout << "\nThat Hokeeman was not found." << endl;
			//Asking them to enter a new name.
			cout << "\nPlease enter a new name to search for. Or 0 to quit." << endl;
			getline(cin, name);

			//If the user enters 0 this code will execute.
			if (name == "0")
			{
				//Returning to main.
				return;
			}
		}

	//End of Do While loop.
	} while (isFound == false);

	//Asking the user if they really want to feed their pet.
	cout << "\nAre you sure you want to feed " << name << "?" << endl;
	cout << "(enter 1 for yes, 0 for no)" << endl;
	cin >> answer;

	//Input validation loop.
	while ((answer != '0') && (answer != '1'))
	{
		cout << answer << " is not a valid input, please try again." << endl;
		cin >> answer;
	}

	//If the answer = 0 this code will execute.
	if (answer == '0')
	{
		//Returning to main.
		return;
	}

	//Setting cHunger to the player pets current hunger.
	cHunger = playerPets[place]->getHunger();

	//If cHunger is equal or less than 4 this code will execute.
	if (cHunger <= 4)
	{
		//Setting the pets hunger to 0.
		playerPets[place]->setHunger(0);
	}

	//If the player hunger is greater than 4 this code will execute.
	if (cHunger > 4)
	{
		//Subtracting 4 from the pets current hunger.
		playerPets[place]->setHunger(cHunger - 4);
	}

	//Decrementing food by one.
	food--;

	//Informing the user that their pet has been fed.
	cout << endl << name << " has been fed!" << endl;
	//Informing the user of their pets current hunger.
	cout << "\nHis/her current hunger level is: " << playerPets[place]->getHunger() << endl;
	//Informing the user of the food they have remaining.
	cout << "Food left: " << food << endl;

	//Calling toContinue().
	toContinue();
	//Calling passTime().
	passTime(playerPets);
}
//End of feed().

//This function increments all of the user's pets health, hunger, and boredom.
void passTime(vector<creature*> &playerPets)
{
	//Creating a string.
	string name;

	//Creating a iterator for playerPets.
	auto iter = playerPets.begin();

	//Informing the user that a turn has elapsed.
	cout << "\nA turn has elapsed..." << endl;

	//This loop executes to the current size of player pets.
	for (unsigned int count = 0; count < playerPets.size(); count++)
	{
		//Calling the current pets passTime method.
		playerPets[count]->passTime();

		//If the currents pets boredom is greater than 20 this code will execute.
		// Constraint 6 - If boredom exceeds 20 your Hokeemon will slip into a catonic state.
		if (playerPets[count]->getBoredom() > 20)
		{
			//Setting name to the current pet's name.
			name = playerPets[count]->getName();
			//Informing the user of there loss.
			cout << endl << name << " has entered a catonic state." << endl;
			//Threatening the user...
			cout << "\nMaybe someday he/she will wake up to enact its revenge on you..." << endl;
			//Setting iter to the beginning of playerPets.
			iter = playerPets.begin() + count;
			//Rotating the pet in question to the end of the vector.
			rotate(iter, iter + 1, playerPets.end());
			//Moving the vector back one.
			playerPets.pop_back();
			//Informing the user that their pet has been removed.
			cout << endl << name << " has been removed from your care." << endl;
			continue;
		}

		//If the currents pets hunger is greater than 10 this code will execute.
		// Constraint 5 - If hunger exceeds 10 your Hokeeman will die of starvation.
		if (playerPets[count]->getHunger() > 10)
		{
			//Setting name to the current pet's name.
			name = playerPets[count]->getName();
			//Informing the user of their loss.
			cout << endl << name << " has starved to death." << endl;
			//Making the user cry...
			cout << "\nBefore he/she goes you hear it scream, YOU'RE A MONSTER!!!" << endl;
			//Setting the iter to the beginning of playerPets.
			iter = playerPets.begin() + count;
			//Rotating the pet in question to the end of the vector.
			rotate(iter, iter + 1, playerPets.end());
			//Moving the vector back one.
			playerPets.pop_back();
			//Informing the user that their pet has been removed.
			cout << endl << name << " has been removed from your care." << endl;
			continue;
		}
	}

	//If the user has at least one pet this code will execute.
	if (playerPets.size() != 0)
	{
		//Informing the user of the changes.
		cout << "\nAll of your pets hunger and boredom have increased by 1" << endl;
		cout << "\nAlso, your injured pets health have increased by 5." << endl;
	}
}
//End of passTime().

//This function allows the user to see the pets current health, hunger, and boredom.
void listen(vector<creature*> &playerPets)
{
	//If the player has no pets this code will execute.
	if (playerPets.size() == 0)
	{
		//Informing the user that they have no pets.
		cout << "\nYou don't own any Hokeeman to listen to." << endl;
		cout << "\nGo buy some Hokeeman!" << endl;
		//Returning to main.
		return;
	}

	//This loop executes to the current size of player pets.
	for (unsigned int count = 0; count < playerPets.size(); count++)
	{
		//Making the pet talk.
		cout << endl << playerPets[count]->getName() << " tells you that he/she is..." << endl;

		// Bonus - Added moods for both hunger and boredom when listen is called.
		//If the pets health is less than or equal to 4 this code will execute.
		if (playerPets[count]->getHunger() <= 4)
		{
			//Informing the user of their pets healthy status.
			cout << "\nFull of food." << endl;
			cout << "Hunger level: " << playerPets[count]->getHunger() << endl;
		}

		//If the pets health is greater than 4 but less than 8 this code will execute.
		if ((playerPets[count]->getHunger() > 4) && (playerPets[count]->getHunger() < 8))
		{
			//Informing the user of their pets hungry status.
			cout << "\nHungry for food." << endl;
			cout << "Hunger level: " << playerPets[count]->getHunger() << endl;

		}
		
		//If the pets health is greater than or equal to 8 this code will execute.
		if (playerPets[count]->getHunger() >= 8)
		{
			//Informing the user of their pets dire status.
			cout << "\nStarving for food." << endl;
			cout << "Hunger level: " << playerPets[count]->getHunger() << endl;

		}

		//AND!
		cout << "\n\t&" << endl;

		//If the pets boredom is less than or equal to 4 this code will execute.
		if (playerPets[count]->getBoredom() <= 4)
		{
			//Informing the user that their pet is happy.
			cout << "\nHappy with you!" << endl;
			cout << "Boredom level: " << playerPets[count]->getBoredom() << endl;
		}

		//If the pets boredom is greater than 4 and less than or equal to 9 this code executes.
		if ((playerPets[count]->getBoredom() > 4) && (playerPets[count]->getBoredom() <= 9))
		{
			//Informing the user that their pets is doing good.
			cout << "\nContent with you." << endl;
			cout << "Boredom level: " << playerPets[count]->getBoredom() << endl;
		}

		//If the pets boredom is greater than 9 and less than or equal to 14 this code execute.
		if ((playerPets[count]->getBoredom() > 9) && (playerPets[count]->getBoredom() <= 14))
		{
			//If the user of their pets boredom.
			cout << "\nFrustrated at you." << endl;
			cout << "Boredom level: " << playerPets[count]->getBoredom() << endl;
		}

		//If the pets boredom is greater than 14 this code executes.
		if (playerPets[count]->getBoredom() > 14)
		{
			//Informing the user of their pets angry status.
			cout << "\nMad at you!" << endl;
			cout << "Boredom level: " << playerPets[count]->getBoredom() << endl;

		}

		//AND!
		cout << "\n\t&" << endl;
		//Informing the user of their pets current health.
		cout << endl << playerPets[count]->getName() << "'s health = " << playerPets[count]->getHealth() << "." << endl;
	}

	//Calling toContinue().
	toContinue();
	//Calling passTime().
	passTime(playerPets);
}
//End of listen().

//This function allows the user to play with their pet. Thus decreasing boredom.
void play(vector<creature*> &playerPets)
{
	//Creating the needed variables.
	string name, temp;
	int place, cBoredom, random;
	char answer;
	bool isFound = false;

	//If the player has no pets this code will execute.
	if (playerPets.size() == 0)
	{
		//Informing the user that they have no pets.
		cout << "\nYou don't own any Hokeeman to play with." << endl;
		cout << "\nGo buy some Hokeeman!" << endl;
		//Returning to main.
		return;
	}

	//Ignoring all previous inputs.
	cin.ignore();

	//Asking the user to enter the name of the pet they wish to play with.
	cout << "\nPlease enter the name of the Hokeeman you want to play with." << endl;
	getline(cin, name);
	temp = name;

	//This loop executes while isFound = false.
	do
	{
		//This loop executes to the current size of playerPets.
		for (unsigned int count = 0; count < playerPets.size(); count++)
		{
			//If the name = the current pets name this code will execute.
			if (sUp(playerPets[count]->getName()) == sUp(temp))
			{
				//Saving the founds pets current index.
				place = count;
				//Setting name to the found pets name.
				name = playerPets[place]->getName();
				//Setting isFound = true.
				isFound = true;
				//Informing the user that their pet was found.]
				cout << "\nYour Hokeeman was found!" << endl;
			}
		}

		//If isFound = false this code will execute.
		if (isFound == false)
		{
			//Informing the user that their Hokeeman was not found.
			cout << "\nThat Hokeeman was not found." << endl;
			cout << "\nPlease enter a new name to search for. Or 0 to quit." << endl;
			getline(cin, name);

			//If the user enters 0 this code will execute.
			if (name == "0")
			{
				//Returning to main.
				return;
			}
		}

	//End of the Do WHile loop.
	} while (isFound == false);

	//Presenting the user with a menu that asks them how they want to play with their pet.
	// Bonus - Added multiple ways to play with your pets.
	cout << "\nHow do you want to play with your pet?" << endl;
	cout << "==============================================" << endl;
	cout << "1. Pet your Hokeeman: -5 boredom." << endl;
	cout << "2. Play fetch with your Hokeeman: -10 boredom" << endl;
	cout << "3. Walk your Hokeeman: -15 boredom." << endl;

	//Reading the inputted answer.
	cin >> answer;

	//Input validation loop.
	while ((answer <= '0') || (answer > '3'))
	{
		cout << answer << " is not a valid input, please try again." << endl;
		cin >> answer;
	}

	//If the answer = 1 this code will execute.
	if (answer == '1')
	{
		//Making the user have emotions for their pet...
		cout << "\nYou pet " << name << "." << endl;
		cout << endl << name << " purrs in gratitude." << endl;

		//Setting cBoredom to the pets current boredom.
		cBoredom = playerPets[place]->getBoredom();

		//If cBordedom is less than or equal to 5 this code will execute.
		if (cBoredom <= 5)
		{
			//Setting the player pets boredom to 0.
			playerPets[place]->setBoredom(0);
		}

		//If cBoredom is greater than 5 this code will execute.
		if (cBoredom > 5)
		{
			//Subtracting 5 from cBoredom and setting the pets boredom to the new number.
			cBoredom = cBoredom - 5;
			playerPets[place]->setBoredom(cBoredom);
		}
	}

	//If answer = 2 this code will execute.
	if (answer == '2')
	{
		//This loop will execute 5 times.
		for (int count = 0; count < 5; count++)
		{
			//Asking the user if they want to throw the stick.
			cout << "\nEnter 1 to throw the stick or 0 to be a meanie!" << endl;
			cin >> answer;

			//Input validation loop.
			while ((answer != '0') && (answer != '1'))
			{
				cout << answer << " is not a valid input, please try again." << endl;
				cin >> answer;
			}

			//If answer = 0 this code will execute.
			if (answer == '0')
			{
				//Destroying the user's remaining emotions.
				cout << endl << name << " glares at you with digust in it's eyes." << endl;
				//Continueing to the next iteration of the loop.
				continue;
			}

			//If answer = 1 this code will execute.
			if (answer == '1')
			{
				//Creating a random number between 0-1.
				random = rand() % 2;

				//Informing the user they successfully threw the stick.
				cout << "\nYou throw the stick!" << endl;
				cout << endl << name << " happily chases after the stick!" << endl;

				//If random = 1 this code will execute.
				if (random == 1)
				{
					//Informing the user that their pet failed to catch the stick.
					cout << endl << name << " fails to catch the stick..." << endl;
					cout << "\nHowever, " << name << " is willing to try again!" << endl;
					//Continueing to the next iteration of the loop.
					continue;
				}

				//If random = 0 this code will execute.
				if (random == 0)
				{
					//Informing the user that there pet caught the stick.
					cout << endl << name << " easily catches the stick!" << endl;
					cout << endl << name << " brings the stick back for you to throw again!" << endl;
					//Continueing to the next iteration of the loop.
					continue;
				}
			}
		}

		//Informing the user that their game of fetch is over. BUMMER!!!
		cout << "\nFeeling tired you decide to stop playing fetch..." << endl;

		//Getting the current boredom of the pet.
		cBoredom = playerPets[place]->getBoredom();

		//If cBoredom is less than or equal to 10 this code will execute.
		if (cBoredom <= 10)
		{
			//Setting the pets boredom to 0.
			playerPets[place]->setBoredom(0);

		}

		//If cBoredom is greater than 10 this code will execute.
		if (cBoredom > 10)
		{
			//Subtracting 10 from cBoredom.
			cBoredom = cBoredom - 10;
			//Setting the pets boredom to the new number.
			playerPets[place]->setBoredom(cBoredom);
		}
	}

	//If answer = 3 this code will execute.
	if (answer == '3')
	{
		//Creating a random number between 0-1.
		random = rand() % 2;

		//If random = 0 this code will execute.
		if (random == 0)
		{
			//Playing with the user's emotions.
			cout << "\nYou attach " << name << " to a leash." << endl;
			cout << endl << name << " looks at you with pure happiness." << endl;
			cout << "\nSeeing this, tears begin to sprout from your eyes!" << endl;
			cout << "\nYou and " << name << " have the best walk ever!" << endl;
		}

		//If random = 1 this code will execute.
		if (random == 1)
		{
			//Informing the user how the walk went...
			cout << "\nYou attach " << name << " to a leash." << endl;
			cout << endl << name << " runs around frantically in circles." << endl;
			cout << "\nSeeing this, you come to the conclusion that " << name << " has way too much energy!" << endl;
			cout << "\nBecause of " << name << "'s abounding energy you feel like you were being walked." << endl;
		}

		//Grabbing the current boredom of the pet.
		cBoredom = playerPets[place]->getBoredom();

		//If the pets boredom is less than or equal to 15 this code will execute.
		if (cBoredom <= 15)
		{
			//Setting the pets boredom to 0.
			playerPets[place]->setBoredom(0);
		}

		//If the pets boredom is greater than 15 this code will execute.
		if (cBoredom > 15)
		{
			//Setting the pets boredom to minus 15 the original number.
			cBoredom = cBoredom - 15;
			playerPets[place]->setBoredom(cBoredom);
		}

	}

	//Informing the user of their pets current boredom level.
	cout << endl << name << "'s current boredom level is: " << playerPets[place]->getBoredom() << endl;

	//Calling toContinue().
	toContinue();
	//Calling passTime().
	passTime(playerPets);
}
//End of play().

//This function allows the user to buy food.
// Bonus - Added the need to buy food to feed your pets.
void buyFood(int& gold, int& food)
{
	//Creating a char variable to hold the user's answers.
	char answer;

	//If the user does not have 10 gold this code will execute.
	if (gold < 10)
	{
		//Informing the user of their poverty.
		cout << "\nYou do not have enough gold to buy food. Go earn some in fights!" << endl;
		//Returning to main.
		return;
	}

	//Informing the user of their current gold balance.
	cout << "\nYour current balance is " << gold << "g." << endl;

	//Asking the user how much food they want to buy.
	cout << "\nHow much food would you like to buy?" << endl;
	cout << "========================================" << endl;
	cout << "1. 1 food: 10g" << endl;
	cout << "2. 5 food: 50g" << endl;
	cout << "3. 10 food: 100g" << endl;

	//Reading the inputted answer.
	cin >> answer;

	//Input validation loop.
	while ((answer <= '0') || (answer > '3'))
	{
		cout << answer << " is not a valid input, please try again." << endl;
		cin >> answer;
	}

	//If the answer is 1 this code will execute.
	if (answer == '1')
	{
		//Setting gold to gold - 10.
		gold = gold - 10;
		//Incrementing food.
		food++;

		//Informing the user that the purchase was successful.
		cout << "\nYou have bought 1 food." << endl;
		cout << "\nYour new balance is " << gold << "g." << endl;
		//Returning to main.
		return;
	}

	//If answer = 2 this code will excute.
	if (answer == '2')
	{
		//If gold is less than 50 this code will execute.
		if (gold < 50)
		{
			//Informing the user oftheir lack of gold.
			cout << "\nYou do not have enought gold!" << endl;
			cout << "\nTry buying a smaller quantity of food." << endl;
			//Returning to main.
			return;
		}

		//Setting gold to gold minus 50.
		gold = gold - 50;
		//Adding 5 to food.
		food = food + 5;

		//Informing the user of their successful purchase.
		cout << "\nYou have bought 5 food." << endl;
		cout << "\nYour new balance is " << gold << "g." << endl;
		//Returning to main.
		return;
	}

	//If the answer is 3 this code will execute.
	if (answer == '3')
	{
		//If the user does not have 100 gold this code will execute.
		if (gold < 100)
		{
			//Informing the user of their lack of gold.
			cout << "\nYou do not have enought gold!" << endl;
			cout << "\nTry buying a smaller quantity of food." << endl;
			//Returning to main.
			return;
		}

		//Setting gold to gold minus 100.
		gold = gold - 100;
		//Setting food to food + 10.
		food = food + 10;

		//Informing the user of their successful purchase.
		cout << "\nYou have bought 10 food." << endl;
		cout << "\nYour new balance is " << gold << "g." << endl;
		//Returning to main.
		return;
	}
}
//End of buyFood().

//This function uppercases a passed string.
string sUp(string answer)
{
	//Uppercasing the string.
	transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
	//Returning the uppercased string.
	return answer;
}
//End of sUp().

//This function asks the user if they want to continue.
void toContinue()
{
	//Creating a variable that holds the users answer.
	char answer;

	//Asking the user if they want to continue.
	cout << "\nEnter 1 to continue." << endl;
	cin >> answer;

	//Input validation loop.
	while (answer != '1')
	{
		cout << answer << " is not a valid input, please try again." << endl;
		cin >> answer;
	}
}
//End of toContinue.

//This function presents the user with the programs menu.
// Constraint 2 - Create a numeric menu.
char userMenu()
{
	//Creating a variable to hold the users answer.
	char answer;

	//Displaying the menu.
	cout << "\nHokeeman Menu" << endl;
	cout << "=========================" << endl;
	cout << "1. Buy a Hokeeman" << endl;
	cout << "2. Buy food" << endl;
	cout << "3. Play with a Hokeeman" << endl;
	cout << "4. Feed a Hokeeman" << endl;
	cout << "5. Listen to your Hokeeman" << endl;
	cout << "6. Fight another Hokeeman" << endl;
	cout << "7. See your gold balance" << endl;
	cout << "8. Quit the game" << endl;

	//Reading the inputted answer.
	cin >> answer;

	//Input validation loop.
	while ((answer <= '0') || (answer > '8'))
	{
		cout << answer << " is not a valid input, please try again." << endl;
		cin >> answer;
	}

	//Returning the answer.
	return answer;
}
//End of userMenu().

//This help displays instructions to the user.
// Bonus - Added the ability to see instructions at the beginning of the program.
void help()
{
	//Displaying the help.
	cout << "\nEverything in this game costs money. To help you out you start with 500 gold" << endl;
	cout << "\nThe object of this game is to take care of one or many Hokeeman's" << endl;
	cout << "\nYou start with no Hokeeman's and must buy one or more for 250g a pop." << endl;
	cout << "\nYou must not let your new Hokeeman's boredom go above 20 or it's hunger above 10." << endl;
	cout << "\nTo see your Hokeeman's current stats you must listen to them." << endl;
	cout << "\nTo make boredom decrease you must play with your pet." << endl;
	cout << "\nTo make hunger decrease you must feed your pet." << endl;
	cout << "\nFeeding your pet requires food. You must buy this food with your gold." << endl;
	cout << "\nThe only way to earn more gold is to win fights." << endl;
	cout << "\nGood luck!" << endl;
}
//End of help().
