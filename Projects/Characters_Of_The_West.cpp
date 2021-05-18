//Program name: Characters of the West (COTW)
//Program Description: This program places characters inside of a saloon. It then allows these characters to play poker against each other.
//sometimes resulting in tragic circumstances.

//My name: Quinn Roemer W1582947
//CISP 400 T/Th FLC 9-10:20am
//November 18th 2017

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

//Abstract base class to Pokerplayer
class People
{
protected:
	//A couple strings variables, they hold the name and the type of the character.
	string name;
	string type;

public:
	//Public variables used to hold some special data.
	int kills = 0;
	int gdrawMod = 0;
	int cdrawMod = 0;
	int cheatMod = 25;
	int handsWon = 0;

	//Random name generator, called when an object is instantiated.
	//Constraint 3 - Randomly select a name for each character.
	string randomName()
	{
		//This array hold 25 possible names for the system to choose.
		string nameArray[25] = { "Aaron", "Alonzo", "Butch", "Carson", "Elijah", "Ezrah",
			"Gideon", "George", "Jeb", "Jesse", "Lee", "Grant", "Zachariah", "Roderick", "Owen",
			"Ulysses", "Wyatt", "Travis", "Maxwell", "Viralen", "Archer", "Bill Gates", "Steve Jobs",
			"Alan Turing", "Steve Wozniak" };

		//Generating a random number with a range of 0-24.
		int random = rand() % 25;

		//Returning a random string in the array.
		return nameArray[random];
	}

	//Virtual function used in Pokerplayer
	virtual int play() = 0;
	virtual void drink() = 0;
	virtual int draw() = 0;

	// Constraint 1 - Include methods for setting object values.
	//Several getters and setters for the name and type variables.
	void setName(string sTemp) { name = sTemp; };
	string getName() { return name; };
	string getType() { return type; };
};
//End of class People.

//This class holds the data for a standard PokerPlayer.
class PokerPlayer : public People
{

public:
	//bool drinkShot = false;

	//Method prototypes. Will be defined outside of the class.
	int play();
	void drink();

	//The draw for this method always returns a 1.
	int draw() { return 1; };

	//PokerPlayer constructor.
	PokerPlayer()
	{
		//Setting type and name.
		name = randomName();
		type = "Pokerplayer";
	}

	//Overloaded << operator.
	// Constraint 2 - Overload the insertion operator <<.
	friend ostream &operator<<(ostream &out, People* temp);
};
//End of PokerPlayer class.

//This class is a child of PokerPlayer. It holds the data for the gunslinger type.
class GunSlinger : public PokerPlayer
{
public:

	//Gunslinger constructor.
	GunSlinger()
	{
		//Setting type and name.
		name = randomName();
		type = "Gunslinger";
	}

	//Overloaded methods from PokerPlayer, will be defined outside of class.
	int draw();
	void drink();
};
//End of GunSlinger class.

//This class is a child of PokerPlayer, it holds the data for the CardShark type.
class CardShark : public PokerPlayer
{
public:

	//CardShark Constructor.
	CardShark()
	{
		//Setting type and name.
		name = randomName();
		type = "Cardshark";
	}

	//Overloaded methods from PokerPlayer, will be defined outside of class.
	int draw();
	void drink();
};
//End of CardShark class.

//This class is a child of PokerPlayer, it holds the data for the Bartender type.
class Bartender : public PokerPlayer
{
public:

	//Bartender Constructor.
	Bartender()
	{
		//Setting type and name.
		name = randomName();
		type = "Bartender";
	}

	//Overloaded methods from PokerPlayer, will be defined outsode of class.
	int draw();
	void drink();
};
//End of Bartender class.

//Play method of PokerPlayer class.
int PokerPlayer::play()
{
	//Creating int variable to hold random number.
	int iTemp;

	//Loop iterates until broken out of.
	while (true)
	{
		//Creating random number within range of 0-52.
		iTemp = rand() % 53;

		//If iTemp = 0 this code will execute.
		if (iTemp == 0)
		{
			//Continuing to the next iteration.
			continue;
		}	

		//Breaking out of the loop.
		break;
	}

	//Returning the random number.
	return iTemp;
}
//End of Play method.

//Draw method of Gunslinger class.
int GunSlinger::draw()
{
	//Creating an int variable to hold the random number.
	int iTemp;

	//This loop iterates until broken out of.
	while (true)
	{
		//Creating a random number with range 0-10.
		iTemp = rand() % 11;

		//If iTemp = 0 this code will execute.
		if (iTemp == 0)
		{
			//Continuing to the next iteration.
			continue;
		}

		//Breaking out of the loop.
		break;

	}

	//Returning iTemp plus the gDrawMod.
	return iTemp + gdrawMod;

}
//End of draw method.

//Draw method of CardShark class.
int CardShark::draw()
{
	//Creating an integer variable to hold the random number.
	int iTemp;

	//This loop iterates until broken out of.
	while (true)
	{
		//Creating a random number within range of 0-15.
		iTemp = rand() % 16;

		//If the random number is less than 5 or greater than 15 this code executes.
		if (iTemp < 5 || iTemp > 15)
		{
			//Continuing to next iteration.
			continue;
		}

		//Breaking out of the loop.
		break;

	}

	//Returning iTemp - the cdrawMod.
	return iTemp - cdrawMod;
}
//End of draw method.

//Draw method of bartender class.
int Bartender::draw()
{
	//Displaying a message to the terminal.
	cout << endl << name << " pours drinks for everyone on the house!" << endl;
	//Returning 0.
	return 0;
}
//End of draw method.

// Bonus - Added seperate behavior depending on what type of character is drinking.
//PokerPlayer drink method.
void PokerPlayer::drink()
{
	//Displaying the name of the character alongside some text.
	cout << name << " takes a sip of his beer." << endl;
}
//End of drink method.

//Gunslinger drink method.
void GunSlinger::drink()
{
	//Displaying the name of the character alongside some text.
	cout << name << " drinks his beer and lets out a long sigh... His aim improves." << endl;
	//Incrementing gdrawMod.
	gdrawMod++;
}
//End of drink method.

//Bartender drink method.
void Bartender::drink()
{
	//Displaying the name of the character alongside some text.
	cout << name << " chugs his beer like a pro!" << endl;
}
//End of drink method.

//CardShark drink method.
void CardShark::drink()
{
	//Displaying the name of the character alongside some text.
	cout << name << " swallows his beer, feeling more confident in the process..." << endl;
	//Incrementing cdrawMod and adding 5 to cheatMod.
	cheatMod = cheatMod + 5;
	cdrawMod++;
}
//End of drink method.

//Overloaded << operator.
ostream &operator<<(ostream &out, People* temp)
{
	//Displaying the name of the character.
	out << "Name: " << temp->getName() << endl;
	//Displaying the number of hands won for that character.
	out << "Hands won: " << temp->handsWon << endl;
	//Returning...
	return out;
}
//End of overloaded << operator.

//Function Prototypes. For further explantion see individual functions.
void playerTurn(vector<People*> &players, int[], int&);

void gunFight(vector<People*> &players, int, int);

void setPlayers(vector<People*> &players);

void toContinue();

char cotwMenu();

//Main function to execute.
int main()
{
	//Creating a seed for the rand function.
	srand(unsigned(time(NULL)));	

	//Creating an int to hold the greatest hands played.
	int greatestHands = 0;

	//Creating an int array to hold all of the cards already played.
	int alreadyPlayed[52] = { 0 };

	//Creating an int to hold the current place in the alreadyPlayed array.
	int currentPlace = 0;

	//Creating a vector of classes.
	vector<People*> players;

	//Welcoming the user to the program.
	cout << "Welcome to Characters of the West!" << endl;

	//Calling the menu.
	char answer = cotwMenu();

	//If the menu returns 1 this code will execute.
	if (answer == '1')
	{
		// Constraint 4 - Make sure you have 1 of each class playing to start.
		//Default set-up for the game.
		players.push_back(new PokerPlayer);
		players.push_back(new CardShark);
		players.push_back(new GunSlinger);
		players.push_back(new Bartender);
	}

	//If the menu returns 2 this code will execute.
	if (answer == '2') 
	{
		//Calling setPlayers.
		setPlayers(players);
		//Calling toContinue.
		toContinue();
	}	

	//This loop iterates 13 times. Enough for every card to be played.
	for (int count = 0; count < 13; count++)
	{
		//Displaying turn number.
		cout << "=================================================" << endl;
		cout << "=\t\t     Turn " << count + 1 << "\t\t\t=" << endl;
		cout << "=================================================" << endl;

		//Calling playerTurn.
		// Constraint 5 - Iterate through a dynamic memory structure and call play.
		playerTurn(players, alreadyPlayed, currentPlace);

		//This loop iterates 4 times.
		for (int index = 0; index < 4; index++)
		{
			//If their is a bartender in the group this code will execute.
			if (players[index]->getType() == "Bartender")
			{
				//If rand returns 0 this code will execute.
				if (rand() % 10 == 0)
				{
					//Calling the bartenders draw method.
					players[index]->draw();
				}
			}
		}

		//Calling to continute.
		toContinue();
	}
	//End of first for loop.

	//This loop iterates 4 times.
	for (int count = 0; count < 4; count++)
	{
		//Determining who won the most.
		if (greatestHands < players[count]->handsWon)
		{
			//Setting greatestHands to the players hands won.
			greatestHands = players[count]->handsWon;
			//Saving the currentplace in the vector.
			currentPlace = count;
		}
	}

	//Displaying who run the game.
	cout << endl << players[currentPlace]->getName() << " has won the game!" << endl << endl;

	//Exiting with status 0.
	return 0;
}
//End of main.

//playerTurn function. This functions contains the code for a single turn.
void playerTurn(vector<People*> &players, int alreadyPlayed[52], int& currentPlace)
{
	//Declaring needed variables.
	int card, place, random, cheaterPlace, gunPlace;

	//This int array hold the cards played during the turn.
	int allCard[4];

	//Several bool flags to be used.
	bool isGun = false;

	bool isCheat = false;

	bool isSame;

	//This loop iterates 4 times.
	for (int count = 0; count < 4; count++)
	{		
		//Displaying the player number.
		cout << "\n\t\t    Player " << count + 1 << endl;

		//If rand return 0 this code will execute.
		if (rand() % 10 == 0)
		{
			//Having the current player drink.
			cout << endl;
			players[count]->drink();	
		}

		//Displaying message to terminal.
		// Bonus - This program displays the players type along with the name.
		cout << endl << players[count]->getName() << " the " << players[count]->getType() << " looks down at his hand." << endl;

		//This loop iterates until broken out of.
		while (true)
		{
			//bool flag.
			isSame = false;

			//Setting card equal to the return of the current players play method.
			card = players[count]->play();

			//This loop iterates 52 times.
			for (int index = 0; index < 52; index++)
			{
				//Checking to see if the card has already been played.
				if (card == alreadyPlayed[index])
				{
					//If the card has been played isSame is set to true.
					isSame = true;
				}
			}

			//If isSame = true this code will execute.
			if (isSame == true)
			{
				//Continuing to next iteration.
				continue;
			}

			//Otherwise, this code will execute.

			//Saving the card in alreadyPlayed.
			alreadyPlayed[currentPlace] = card;
			//Incrementing currentPlace.
			currentPlace++;
			//Breaking out of the loop.
			break;
		}

		//If the players type is CardShark this code will execute.
		if (players[count]->getType() == "Cardshark")
		{
			//If rand returns a value less than cheatmod this code will execute.
			if (players[count]->cheatMod >= rand() % 100)
			{
				//Saving the cheaters place.
				cheaterPlace = count;
				//Setting isCheat to true.
				isCheat = true;

				//Determining the new card that the cheater will play.
				random = rand() % currentPlace;

				//Setting card to an alreadyPlayed card.
				card = alreadyPlayed[random];
			}
		}

		//If the players type is Gunslinger this code will execute.
		if (players[count]->getType() == "Gunslinger")
		{
			//Setting isGun to true.
			isGun = true;
			//Saving the gunslingers spot.
			gunPlace = count;
		}

		//Displaying what card the character has played.
		cout << "He plays a " << card << "!" << endl;

		//Saving the card to allCard.
		allCard[count] = card;
	}

	//Setting card to 0.
	card = 0;

	//This loop iterates 4 times.
	for (int count = 0; count < 4; count++)
	{
		//Determining who played the highest card.
		if (card < allCard[count])
		{
			//Saving the highest cards number and place.
			card = allCard[count];
			place = count;
		}
	}

	//Displaying who won the turn.
	cout << "\nPlayer " << place + 1 << " won the turn!" << endl;

	//Incrementing the winner hands won variable.
	players[place]->handsWon++;

	//If isCheat = true this code will execute.
	if (isCheat == true)
	{
		//Informing the user that some player has cheated.
		cout << endl << players[cheaterPlace]->getName() << " has cheated!" << endl;

		//If isGun = true this code will execute.
		if (isGun == true)
		{
			//If rand returns 0 this code will execute.
			if (rand() % 2 == 0)
			{
				//Displaying that the GunSlinger caught the cheater.
				cout << endl << players[gunPlace]->getName() << " caught the cheater!" << endl;
				cout << "\nA draw is called..." << endl;
				toContinue();
				//Calling gunFight.
				gunFight(players, cheaterPlace, gunPlace);
				toContinue();
			}

			//Otherwise, this code will execute.
			else
			{
				//Displaying that the GunSlinger did not catch the cheater.
				cout << endl << players[gunPlace]->getName() << " does not catch the cheater." << endl;
			}
		}

		//If isGun = false this code will execute.
		if (isGun == false)
		{
			//Displaying that there is no gunslinger to catch the cheater.
			cout << "\nHowever, there is no gunslinger to catch him." << endl;
		}
	}

	//Displaying the turns details.
	cout << "\n=================================================" << endl;
	cout << "=\t\t  Turn Details  \t\t=" << endl;
	cout << "=================================================" << endl;
	cout << endl;

	//This loop iterates 4 times.
	for (int count = 0; count < 4; count++)
	{
		//Printing the characters names and hands won through the overloaded operator.
		cout << players[count] << endl;
	}
}
//End of playerTurn.

//This function contains the code for a gunFight between two players.
void gunFight(vector<People*> &players, int cheaterPlace, int gunPlace)
{
	//Setting toRemove to 0 and creating a variable to hold a random number.
	int toRemove = 0, random;

	//Informing the user that both players have drawn their guns.
	cout << "\nBoth " << players[cheaterPlace]->getName() << " & " << players[gunPlace]->getName() << " draw their guns..." << endl;

	//Setting two int variables to the return of both draw functions.
	int cShot = players[cheaterPlace]->draw();
	int gShot = players[gunPlace]->draw();

	//If cShot = gShot this code will execute.
	// Bonus - If the dualers roll the same number they kill each other.
	if (cShot == gShot)
	{
		//Informing the user that both players have died.
		cout << "\nBoth players are dead!!!" << endl;
		cout << "\nBoth players have been removed from the game." << endl;

		//Removing a player from the vector.
		auto iter = players.begin() + gShot;
		rotate(iter, iter + 1, players.end());
		players.pop_back();

		//Removing a player from the vector.
		iter = players.begin() + cShot;
		rotate(iter, iter + 1, players.end());
		players.pop_back();

		//This loop iterates two times.
		for (int count = 0; count < 2; count++)
		{
			//Creating a random number with a range of 0-3.
			random = rand() % 4;

			//Switching the random number.
			switch (random)
			{
			//If the case is 0 this code will execute.
			case 0:
				//Adding a new PokerPlayer to the vector.
				players.push_back(new PokerPlayer);
				//Informing the user of the addition.
				cout << "\nA new Pokerplayer named " << players[3]->getName() << " has entered the game." << endl;
				break;

			//If the case is 1 this code will execute.
			case 1:
				//Adding a new CardShark to the vector.
				players.push_back(new CardShark);
				//Informing the user of the addition.
				cout << "\nA new Cardshark named " << players[3]->getName() << " has entered the game." << endl;
				break;

			//If the case is 2 this code will execute.
			case 2:
				//Adding a new Gunslinger to the vector.
				players.push_back(new GunSlinger);
				//Informing the user of the addition.
				cout << "\nA new Gunslinger named " << players[3]->getName() << " has entered the game." << endl;
				break;

			//If the case is 3 this code will execute.
			case 3:
				//Adding a new bartender to the vector.
				players.push_back(new Bartender);
				//Informing the user of the addition.
				cout << "\nA new Bartender named " << players[3]->getName() << " has entered the game." << endl;
				break;
			}
		}
		//Returning to the calling function.
		return;
	}

	//If cShot is greater than gShot this code will execute.
	if (cShot > gShot)
	{
		//Informing the user of the death.
		cout << endl << players[cheaterPlace]->getName() << " won the draw." << endl;
		cout << endl << players[gunPlace]->getName() << " is dead :(" << endl;

		//Informing the user that he has been removed.
		cout << "\nHe has been removed from the game." << endl;
		//Setting toRemove to gunPlace.
		toRemove = gunPlace;
	}

	//If cShot is less than gShot this code will execute.
	if (cShot < gShot)
	{
		//Informing the user of the death.
		cout << endl << players[gunPlace]->getName() << " won the draw." << endl;
		cout << endl << players[cheaterPlace]->getName() << " is dead :(" << endl;

		//Incrementing teh gunSlingers kills.
		players[gunPlace]->kills++;

		//Informing the user that he has been removed.
		cout << "\nHe has been removed from the game." << endl;

		//Informing the user of the gunslingers kill count.
		cout << endl << players[gunPlace]->getName() << " has killed " << players[gunPlace]->kills << " people." << endl;

		//Setting to remove to Cheater place.
		toRemove = cheaterPlace;
	}

	//Removing a player from the vector.
	auto iter = players.begin() + toRemove;
	rotate(iter, iter + 1, players.end());
	players.pop_back();

	//Creating a random number with a range of 0-3.
	random = rand() % 4;

	//Switching the random number.
	switch (random)
	{
		//If the case is 0 this code will execute.
	case 0:
		//Adding a new PokerPlayer to the vector.
		players.push_back(new PokerPlayer);
		//Informing the user of the addition.
		cout << "\nA new Pokerplayer named " << players[3]->getName() << " has entered the game." << endl;
		break;

		//If the case is 1 this code will execute.
	case 1:
		//Adding a new CardShark to the vector.
		players.push_back(new CardShark);
		//Informing the user of the addition.
		cout << "\nA new Cardshark named " << players[3]->getName() << " has entered the game." << endl;
		break;

		//If the case is 2 this code will execute.
	case 2:
		//Adding a new Gunslinger to the vector.
		players.push_back(new GunSlinger);
		//Informing the user of the addition.
		cout << "\nA new Gunslinger named " << players[3]->getName() << " has entered the game." << endl;
		break;

		//If the case is 3 this code will execute.
	case 3:
		//Adding a new bartender to the vector.
		players.push_back(new Bartender);
		//Informing the user of the addition.
		cout << "\nA new Bartender named " << players[3]->getName() << " has entered the game." << endl;
		break;
	}
}
//End of gunFight function.

//This function allows the player to set the players names and type before the game begins.
// Bonus - This program gives the player the ability to change the starting compisition.
void setPlayers(vector<People*> &players)
{
	//Creating neede char variables.
	char answer, answer2;

	//Creating a temp string.
	string sTemp;

	//Informing the user of a rule.
	cout << "\nYou can start the game with 4 players." << endl;

	//This loop iterates 4 times.
	for (int count = 0; count < 4; count++)
	{
		//Asking the user what type of player they want to add.
		cout << "\nPlease choose type." << endl;
		cout << "=====================================" << endl;
		cout << "1. Pokerplayer" << endl;
		cout << "2. Cardshark" << endl;
		cout << "3. Gunslinger" << endl;
		cout << "4. Bartender" << endl;

		//Reading the answer.
		cin >> answer;

		//Input validation loop.
		while (answer < 1 && answer > 4)
		{
			cout << "Input invalid, please try again." << endl;
			cin >> answer;
		}

		//Switching the answer.
		switch (answer)
		{
		//If the case is 1 this code will execute.
		case '1':
			//Adding a new PokerPlayer.
			players.push_back(new PokerPlayer);
			cout << "\nA Pokerplayer has been added..." << endl;
			break;

		//If the case is 2 this code will execute.
		case '2':
			//Adding a new CardShark.
			players.push_back(new CardShark);
			cout << "\nA Cardshark has been added..." << endl;
			break;

		//If the case is 3 this code will execute.
		case '3':
			//Adding a new GunSlinger.
			players.push_back(new GunSlinger);
			cout << "\nA Gunslinger has been added..." << endl;
			break;

		//If the case is 4 this code will execute.
		case '4':
			//Adding a new Bartender.
			players.push_back(new Bartender);
			cout << "\nA Bartender has been added..." << endl;
			break;
		}
		//End of switch case.

		//Asking the player if they want to rename their new character.
		// Bonus - This program allows the user to change a characters name if they choose the starting comp.
		cout << "\nYour player has been automatically named " << players[count]->getName() << endl;
		cout << "\nWould you like to rename them?" << endl;
		cout << "(enter 1 for yes 0 for no)" << endl;
		//Reading the answer.
		cin >> answer2;

		//Input validation loop.
		while (answer2 != '0' && answer2 != '1')
		{
			cout << "\nInput invalid, please try again." << endl;
			cin >> answer2;
		}

		//If answer2 = 1 this code will execute.
		if (answer2 == '1')
		{
			//Prompting the user to enter a new name.
			cout << "\nPlease enter a new name." << endl;

			cin.ignore();

			//Reading the entire line entered.
			getline(cin, sTemp);

			//Renaming the player.
			players[count]->setName(sTemp);

			//Informing the user of the success.
			cout << "\nName set." << endl;
		}
	}
}
//End of setPlayers.

//This function asks the user of they want to continue.
void toContinue()
{
	//Creating a needed variable.
	string answer;

	//Asking the user to enter something.
	cout << "\nEnter something to continue" << endl;
	cin >> answer;
}
//End of toContinue.

//This function displays the menu for the program.
char cotwMenu()
{
	//Creating a needed variable.
	char answer;

	//Outputting the menu.
	cout << "\nCharacters of the West Menu" << endl;
	cout << "=====================================" << endl;
	cout << "1. Start a default game." << endl;
	cout << "2. Set beginning players." << endl;

	//Reading the inputted answer.
	cin >> answer;

	//Input validation loop.
	while (answer != '1' && answer != '2')
	{
		cout << "\nInput invalid, please try again." << endl;
		cin >> answer;
	}

	//Returning the answer.
	return answer;
}
//End of cotwMenu.
