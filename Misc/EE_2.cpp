#include <iostream>
#include <string>
#include <vector>
#include <fstream>


using namespace std;

//Function prototypes.
bool loadFile(vector<string> &names, vector<string> &places);
void searchAndPrint(vector<string> &names, vector<string> &places);

//Main function to execute.
int main()
{
	//Creating two vectors. One to hold the peoples names and another to hold the places they want to go.
	vector<string> names;
	vector<string> places;	

	//Holds the user's response.
	char answer;

	//Setting isLoad to the return of loadFile.
	bool isLoad = loadFile(names, places);

	//If isLoad = false this code will execute.
	if (isLoad == false)
	{
		//Setting isLoad to the return of loadFile.
		isLoad = loadFile(names, places);
	}

	//While isLoad = true this code will execute.
	while (isLoad == true)
	{

		//Calling searchAndPrint.
		searchAndPrint(names, places);

		//Prompting the user for an answer.
		cout << "\nDo you want to search for another name?" << endl;
		cout << "(enter 1 for yes and 0 for no.)" << endl;

		//Reading the answer.
		cin >> answer;
		cin.ignore();

		//Input validation loop.
		while (answer != '1' && answer != '0')
		{
			cout << "\nInvalid input. Please try again." << endl;
			cin >> answer;
			cin.ignore();
		}

		//If answer = 0 this code will set isLoad to false.
		if (answer == '0')
		{
			isLoad = false;
		}
	}
	//Saying goodbye.
	cout << "\nGoodbye :)" << endl;
}

//This function loads the file or creates a new one.
bool loadFile(vector<string> &names, vector<string> &places)
{
	//Creating a file object.
	ifstream myfile;

	//Holds the user's response.
	char answer;

	//Opening data.txt
	myfile.open("data.txt");

	//If the file is not opened correctly this code will execute.
	if (!myfile.is_open()) 
	{
		//Informing the user no file has been found.
		cout << "No file found!" << endl;

		//Informing the user that a file will be created.
		cout << "\nSince no file has been found I will quickly create\nthe file from the textbook" << endl;

		//Creating another file object and opening a new file.
		ofstream newFile;

		newFile.open("data.txt");

		//Printing to the file.
		newFile << "3" << endl;
		newFile << "0 Paul" << endl;
		newFile << "1 Peter" << endl;
		newFile << "2 David" << endl;
		newFile << endl;
		newFile << "0 3 Chicago Boston Memphis" << endl;
		newFile << "1 1 Boston" << endl;
		newFile << "2 0";

		//Asking the user if they want to continue.
		cout << "\nEnter 1 to continue." << endl;
		cin >> answer;

		//Input validation loop.
		while (answer != '1')
		{
			cout << "Invalid input. Please try again." << endl;
			cin >> answer;
		}

		//Closing both opened files.
		myfile.close();
		newFile.close();

		//Ignoring cin.
		cin.ignore();

		//Returning false.
		return false;
	}

	//Needed string variables.
	string peopleNumber = "0";
	string temp;
	string rTemp;
	int count = 0;

	//Getting the first line of the file.
	getline(myfile, peopleNumber);

	//Converting string to an int.
	count = stoi(peopleNumber);

	//A loop that executes to the value of count.
	for (int index = 0; index < count; index++)
	{
		//Getting the next line in the file.
		getline(myfile, temp);

		//Creating a new string.
		rTemp = temp.substr(2);

		//Pushing back the vector to add the name.
		names.push_back(rTemp);
	}

	//Reading the next line of the file.
	getline(myfile, temp);

	//A loop that executes to the value of count.
	for (int index = 0; index < count; index++)
	{
		//Reading the next line of the file.
		getline(myfile, temp);

		//Creating a new string.
		rTemp = temp.substr(2);

		//Pushing back the vector to add the place(s).
		places.push_back(rTemp);
	}

	//Closing the file and returning with true.
	myfile.close();
	return true;
}

//This function searches the vectors for a name and displays it if found.
void searchAndPrint(vector<string> &names, vector<string> &places)
{
	//Needed variables.
	string temp;
	int place;
	bool isFound = false;

	//Asking the user to input a name to search for.
	cout << "\nPlease enter a name to search for." << endl;
	getline(cin, temp);

	//This loop executes to the end of the vector.
	for (unsigned int count = 0; count < names.size(); count++)
	{
		//If the name in the vector equals the searched term this code will execute.
		if (names[count] == temp)
		{
			//Saving the place and breaking out of the loop.
			place = count;
			isFound = true;
			break;
		}
	}

	//If isFound == false this code will execute.
	if (isFound == false)
	{
		//Informing the user the name was not found and returning to main.
		cout << "\nName not found." << endl;
		return;
	}

	//Informing the user that the person was found.
	cout << "\nPerson found!" << endl << endl;

	//Printing the name of the person found.
	cout << names[place] << " wants to go to..." << endl << endl;

	//Printing the number of places the person wants to go.
	cout << places[place].substr(0, 1) << " place(s)." << endl << endl;

	//If the next digit is zero this code will execute.
	if (places[place].substr(0, 1) == "0")
	{
		return;
	}

	//Listing the places the person wants to go.
	cout << "These place(s) are..." << endl << endl;

	cout << places[place].substr(2) << "." << endl;
}

