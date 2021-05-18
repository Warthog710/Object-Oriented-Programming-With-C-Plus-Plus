//Program name: To Do List
//Program Description: This program allows a user to create and manage a to do list.
//My name: Quinn Roemer W1582947
//CISP 400 T/Th FLC 9-10:20am
//October 23rd 2017

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>

using namespace std;

//This class is used to hold all of the details in the to do list.
// Constraint 1, Use Object Oriented Programming.
class toDo {
private:
	//Private class variables.
	string task;
	string date;
	//Id = placement in dynamic array.
	int id;
	
public:
	//Constructor of the class.
	toDo();
	//These methods are used to get the private variables.
	int getId() { return id; }
	string getTask() { return task; }
	string getDate() { return date; }
	//These methods are used to set the private variables.
	void setTask(string fTemp) { task = fTemp; }
	void setId(int iTemp) { id = iTemp; }
	void setDate(string sTemp) { date = sTemp; }
	// Bonus Overloaded Operators, both the << and >> operators are overloaded in this code.
	friend ostream &operator<<(ostream &out, toDo fToDo);
	friend istream &operator >> (istream &in, toDo &fToDo);
};

//Constructor automatically grabs the date from the computer when an object is created.
toDo::toDo()
{
	auto t = time(nullptr);
	auto tm = *localtime(&t);
	ostringstream oss;
	oss << put_time(&tm, "%d-%m-%y");
	date = oss.str();
}

//Overloaded << operator. This is used to display all of the variables in the class.
ostream &operator<<(ostream& out, toDo fToDo) {
	out << "Task: " << fToDo.getTask() << endl;
	out << "Date added: " << fToDo.getDate() << endl;
	out << "ID: " << fToDo.getId() << endl;
	return out;
}

//Overloaded >> operator. This is used to modify an existing item in the list.
istream &operator >> (istream &in, toDo &fToDo) {
	string fTemp;
	cout << "Enter a new task:" << endl;
	cin.ignore();
	getline(in, fTemp);
	fToDo.setTask(fTemp);

	//Updating the date of the item.
	auto t = time(nullptr);
	auto tm = *localtime(&t);
	ostringstream oss;
	oss << put_time(&tm, "%d-%m-%y");
	fToDo.setDate(oss.str());

	return in;
}

//Function prototypes: See the actual function for descriptions.
toDo* loadFile(int&);
toDo* remove(int, int&, toDo*);
toDo* add(int&, string, toDo*);

string sUp(string);
string stringEval(string);
string extractCommand(string);
string seperateCommand(string);

void toContinue();
void save(int, toDo*);
void displayAll(int, toDo*);
void modify(int, int, toDo*);
void displayOne(int, int, toDo*);
void saveFormatted(int, string, toDo*);

//Main function to execute.
int main()
{
	//Creating a couple needed variables.
	toDo* head = NULL;
	char answer;
	int id, size = 0;
	string wCommand, command, nCommand;

	//Calling loadFile, this function checks to see if there is a save file. If so it loads it.
	head = loadFile(size);

	//Program greeting.
	cout << "Welcome to the To Do list program. This program allows you to create\nand manage your To Do list." << endl;

	//Informing the user that 'help' can be used to display instructions.
	cout << "\nType 'help' when prompted to enter a command to see how to use this program." << endl;

	//A while loop that will iterate until broken out of.
	while (true)
	{
		//Asking the user to enter a command.
		cout << "\nEnter a command:" << endl;
		getline(cin, wCommand);

		//Calling several functions. These functions will validate the string, seperate the command from the string,
		//and seperate the string from the command.
		wCommand = stringEval(wCommand);
		command = extractCommand(wCommand);
		nCommand = seperateCommand(wCommand);

		//If command = + this code will execute.
		// Constraint 2, Allow the user to enters tasks with a "+" symbol.
		if (command == "+")
		{
			//Calling the add function. This function adds an object to the list.
			head = add(size, nCommand, head);
			//Informing the user that their entry was successfully added.
			cout << "\nEntry added!" << endl;
			toContinue();
		}

		//If command = - this code will execute.
		// Constraint 4, Allow the user to remove a task with the "-" symbol.
		if (command == "-")
		{
			//Converting the string into an int.
			id = atoi(nCommand.c_str());
			//Calling the remove function, this function removes an item from the list.
			head = remove(id, size, head);
			toContinue();
		}

		//If command = @ this code will execute.
		if (command == "@")
		{
			//Calling the displayAll function, this function will display all of the items currently in the list.
			displayAll(size, head);
			toContinue();
		}

		//If command = * this code will execute.
		if (command == "*")
		{
			//Converting the string to an int.
			id = atoi(nCommand.c_str());
			//Calling the displayOne function, this function displays one item in the list.
			displayOne(id, size, head);
			toContinue();
		}

		//If command = ~ this code will execute.
		if (command == "~")
		{
			//Converting the string to an int.
			id = atoi(nCommand.c_str());
			//Calling the modify function, this function modifies an item already in the list.
			modify(id, size, head);
			toContinue();
		}

		//If command = & this code will execute.
		if (command == "&")
		{
			//Calling the saveFormatted function, this function creates a user friendly text file
			//that contains the list.
			saveFormatted(size, nCommand, head);
			toContinue();
		}

		//If command = # this code will execute.
		// Constraint 7, Create a command symbol to quit the program.
		if (command == "#")
		{
			//Asking the user if they really want to quit.
			cout << "\nAre you sure you want to quit?" << endl;
			cout << "(enter 1 for yes 0 for no)" << endl;
			cout << "\nNote: This quit will save your list." << endl;
			cin >> answer;
			
			//Input validation loop.
			// Bonus, this program allows the user to quit with no history.
			while ((answer != '0') && (answer != '1'))
			{
				cout << answer << " is not a valid input, please try again." << endl;
				cin >> answer;
			}

			//If answer = 1 this code will execute.
			if (answer == '1')
			{
				//Saving the list for the next start.
				save(size, head);
				//Deleting head.
				delete[] head;
				//Setting head to NULL.
				head = NULL;
				//Saying goodbye... BYE!
				cout << "\nGoodbye :)" << endl;
				//Breaking out of the loop.
				break;
			}
		}

		//If command = ! this code will execute.
		if (command == "!")
		{
			//Asking the user if they really want to quit.
			cout << "\nAre you sure you want to quit?" << endl;
			cout << "(enter 1 for yes 0 for no)" << endl;
			cout << "\nNote: This quit will NOT save your list." << endl;
			cin >> answer;

			//Input validation loop.
			while ((answer != '0') && (answer != '1'))
			{
				cout << answer << " is not a valid input, please try again." << endl;
				cin >> answer;
			}

			//If answer = 1 this code will execute.
			if (answer == '1')
			{
				//Deleting head.
				delete[] head;
				//Setting head to NULL.
				head = NULL;
				//Removing all existence of any records.
				remove("toDoList.txt");
				//Saying goodbye... Adios!
				cout << "\nGoodbye :)" << endl;
				//Breaking out of the loop.
				break;
			}
		}
	}
}
//End of main.

//This function evaluates a string and checks the command.
string stringEval(string temp)
{
	//Setting test equal to the first two elements of the passed string.
	string test = temp.substr(0, 2);

	//If the user entered help these instructions will be displayed.
	// Bonus Help!, this code allows the user to ask for help.
	while (sUp(temp) == "HELP") {
		cout << "\nThis program is driven by commands." << endl;
		cout << "\nA command is entered in this fashion..." << endl;
		cout << "\n<command> <string/ID>" << endl;
		cout << "\nHere are all of the commands this program supports and how to use them." << endl;
		cout << "\nNote: Do not include '<' or '>' in the command." << endl;
		cout << "\nNote: Do not forget the space that seperates the command and string/ID." << endl;
		cout << "This is required for commands that don't have a string/ID as well." << endl;
		cout << "\nThis command allows you to add an item to your to do list." << endl;
		cout << "+ <name of task>" << endl;
		cout << "\nThis command allows you to remove an item from your to do list." << endl;
		cout << "- <ID of item wished to be removed>" << endl;
		cout << "\nThis command allows you to print all of your items in your to do list." << endl;
		cout << "@ <no string/ID required>" << endl;
		cout << "\nThis command allows you to print one of your items in your to do list." << endl;
		cout << "* <ID of item desired to be printed>" << endl;
		cout << "\nThis command allows you to modify an already made item in your to do list." << endl;
		cout << "~ <ID of item desired to be modified>" << endl;
		cout << "\nThis command allows you to save a text file with your to do list inside." << endl;
		cout << "& <desired name of file>" << endl;
		cout << "\nThis command allows you to quit the program and save your to do list for the next start." << endl;
		cout << "# <no string/ID required>" << endl;
		cout << "\nThis command allows you to quit the program and remove all saved items on your to do list." << endl;
		cout << "! <no string/ID required>" << endl;

		//Asking the user to enter a command.
		cout << "\nPlease enter a command:" << endl;
		getline(cin, temp);
		//Setting test equal to the first two elements of the passed string.
		test = temp.substr(0, 2);
	}

	//Checking to see if the string contains a valid command.
	while (((((((test != "+ ") && (test != "- ") && (test != "@ ") && (test != "~ ") && (test != "* ") && (test != "& ") && (test != "# ") && (test != "! ")))))))
	{
		//Informing the user that the entered command was not valid.
		cout << "\nYour string must contain a valid command at the beginning with a space after it." << endl;
		getline(cin, temp);
		test = temp.substr(0, 2);
	}
	//Returning the validated string.
	return temp;
}
//End of stringEval

//This function adds to or creates a dynamic array for the toDo list.
// Constraint 6, Load the data into a dynamic array.
toDo* add(int& size, string text, toDo* head)
{
	//If size = 0 this code will execute.
	if (size == 0)
	{
		size++;
		toDo* ptr = new toDo[size];
		//Setting the ID to the size of the list.
		ptr->setId(size);
		//Setting the task to the passed string.
		ptr->setTask(text);
		//Returning a pointer to the newly created dynamic array.
		return ptr;
	}

	//If size != 0 the function defaults to this code.
	size++;
	
	//Creating a new dynamic array.
	toDo* ptr = new toDo[size];

	//Copying the old array into the new one.
	for (int count = 0; count < size - 1; count++)
	{
		ptr[count] = head[count];
	}

	//Deleting the old array.
	delete[](head);

	//Setting ID to the size of the list.
	ptr[size - 1].setId(size);
	//Setting the task to the passed string.
	ptr[size - 1].setTask(text);
	//Returning a pointer to the newly created dynamic array.
	return ptr;
}
//End of add.

//This function displays all of the items currently in the list.
// Constraint 3, Allow the user to display all tasks.
void displayAll(int size, toDo* head)
{
	//Creating a needed variable.
	int location = 1;

	//If size = o this code will execute.
	if (size == 0)
	{
		//Informing the user no items exist and returning to main.
		cout << "\nNo items have been added..." << endl;
		cout << "\nPlease enter some so that I can display them." << endl;
		return;
	}

	cout << endl;

	//Printing the list in its entirety.
	for (int count = 0; count < size; count++)
	{
		//If the item is named deletedItem it will be skipped.
		if (head[count].getTask() == "deletedItem")
		{
			continue;
		}

		//Printing the item out in a easy to ready way.
		cout << "Item #" << location << endl;
		cout << "===========================" << endl;
		cout << head[count] << endl;
		location++;
	}
}
//End of displayAll

//This function displays a single item in the list.
// Bonus Display one item, this code is capable of displaying only one item from the list.
void displayOne(int id, int size, toDo* head)
{
	string temp;

	//If ID = 0 the user will be informed that no records were found.
	if (id == 0)
	{
		cout << "\nNo record was found with " << id << " as its ID." << endl;
		cout << "Unable to print..." << endl;
		return;
	}

	//If size = 0 the user will be informed that no items exist.
	if (size == 0)
	{
		cout << "\nNo items have been added..." << endl;
		cout << "\nPlease enter some so that I can display them." << endl;
		return;
	}

	//This loop searches for the item with the correct ID.
	for (int count = 0; count < size; count++)
	{
		//If the current element of head is equal to the id this code will execute.
		if (head[count].getId() == id)
		{
			//Printing the record.
			cout << "\nRecord found!" << endl;
			cout << "===========================" << endl;
			cout << head[count];
			//Returning to main.
			return;
		}
	}
	//If no record is found the user will be informed.
	cout << "\nNo record was found with " << id << " as its ID." << endl;
	cout << "Unable to print..." << endl;
	//Returning to main.
	return;
}
//End of displayOne.

//This functions extracts the command from a passed string.
string extractCommand(string temp)
{
	//Creating a string that consists of the first element of the passed string.
	string command = temp.substr(0, 1);
	//Returning the string that contains the command.
	return command;
}
//End of extractCommand.

//This function seperates the command from the rest of the string.
string seperateCommand(string temp)
{
	//Erasing the first two elements of the passed string.
	string nCommand = temp.erase(0, 2);
	//Returning the string that contains no command.
	return nCommand;
}
//End of seperateCommand.

//This function removes an item from the list.
toDo* remove(int id, int& size, toDo* head)
{
	//Creating several needed variables.
	int count = 0, location = 1;
	char answer;

	//This loop will execute until broken out of.
	while (true)
	{
		//Searching the list for a specific item.
		for (count = 0; count < size; count++)
		{
			//If the current elements ID = the passed ID this code will execute.
			if (head[count].getId() == id)
			{
				//Informing the user the record was found. Also, asking if they really want to delete it.
				cout << "\nRecord found!" << endl;
				cout << "\nAre you sure you want to delete this item?" << endl;
				cout << "(enter 1 to continue or 0 to go back." << endl;
				cin >> answer;

				//Input validation loop.
				while ((answer != '0') && (answer != '1'))
				{
					cout << answer << " is not a valid input, please try again." << endl;
					cin >> answer;
				}

				//If answer = 1 this code will execute.
				if (answer == '1')
				{
					//Iterating through the array to find the element again...
					for (count = 0; count < size; count++)
					{
						//If the current elements ID = the passed ID or is named 'deletedItem' this code will execute.
						if ((head[count].getId() == id) || (head[count].getTask() == "deletedItem"))
						{
							//Setting the task to 'deletedItem.
							head[count].setTask("deletedItem");
							//Setting the ID to 0.
							head[count].setId(0);
							//Continuing to the next iteration.
							continue;

						}
						//If the ID is not found the elements ID will be set to the current location.
						head[count].setId(location);
						location++;
					}
					//Informing the user that the item was successfuly deleted.
					cout << "\nItem successfully deleted!" << endl;
					//Returning head.
					return head;
				}

				//If answer = 0 this code will execute.
				if (answer == '0')
				{
					//Returning head.
					return head;
				}
			}
		}

		//If the ID was not found the user will be asked if they want to enter another one to try.
		cout << "\nThat ID was not found. Would you like to try another ID?" << endl;
		cout << "(enter 1 for yes 0 for no)" << endl;
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
			//Returning head.
			return head;
		}
		//Asking the user to enter a new ID.
		cout << "\nPlease enter a new ID" << endl;
		cin >> id;
	}
}
//End of remove.

//This function modifies an existing item in the list.
// Bonus Modification, this program allows the user to modify an already created item.
void modify(int id, int size, toDo* head)
{
	//Creating a needed variable.
	char answer;

	//If ID = 0 this code will execute.
	if (id == 0)
	{
		//Informing the user no items were found with the ID of 0.
		cout << "\nNo record was found with " << id << " as its ID." << endl;
		cout << "Unable to modify..." << endl;
		//Returning to main.
		return;
	}

	//This loop execute to the current size of the dynamic array.
	for (int count = 0; count < size; count++)
	{
		//If the elements ID = the passed ID this code will execute.
		if (head[count].getId() == id)
		{
			//Informing the user the record was found, and asking if they want to continue.
			cout << "\nRecord found!" << endl;
			cout << "\nAre you sure you want to modify this record?" << endl;
			cout << "(enter 1 for yes 0 for no)" << endl;
			cin >> answer;

			//Input validation loop.
			while ((answer != '0') && (answer != '1'))
			{
				cout << answer << " is not a valid input, please try again." << endl;
				cin >> answer;
			}

			//Modifying the current element.
			cin >> head[count];
			//Informing the user the operation was performed successfully.
			cout << "\nRecord successfully modified!" << endl;
			//Returning to main.
			return;
		}
	}
	//Informing the user the ID was not found.
	cout << "\nNo record was found with " << id << " as its ID." << endl;
	cout << "Unable to modify..." << endl;
	//Returning to main.
	return;
}
//End of modify.

//This function saves a file for the computers use.
// Constraint 5, Save the item so it persists when the program is restarted.
void save(int size, toDo* head)
{
	int location = 0;

	//If size = 0 this code will execute.
	if (size == 0)
	{
		//Informing the user no items exist.
		cout << "\nNo items were created..." << endl;
		cout << "\nUnable to save." << endl;
		//Returning to main.
		return;
	}

	//Creaeting a file pointer.
	ofstream myfile;

	//Opening a new file.
	myfile.open("toDoList.txt");

	//If the file is open this code will execute.
	if (myfile.is_open())
	{
		//This loop executes to the size of the dynamic array.
		for (int count = 0; count < size; count++)
		{
			//If the element is named 'deletedItem it is skipped.
			if (head[count].getTask() == "deletedItem")
			{
				continue;
			}

			//If location = 0 this code is executed.
			if (location == 0)
			{
				myfile << head[count].getTask() << endl;
				myfile << head[count].getDate() << endl;
				myfile << head[count].getId();
				location++;
				continue;
			}

			//If location is greater than 0 this code is executed.
			if (location > 0)
			{
				myfile << endl << head[count].getTask() << endl;
				location++;
			}

			myfile << head[count].getDate() << endl;
			myfile << head[count].getId();
		}
		//Closing the file.
		myfile.close();
		//Returning to main.
		return;
	}
	//If the file does not open the user will be informed.
	cout << "Unable to save a file..." << endl;
	//Returning to main.
	return;
}
//End of save.

//This function loads a file at the start of the program.
toDo* loadFile(int& size)
{
	//Creating a couple necessary pointers and other variables.
	toDo* head = NULL;
	toDo* ptr = NULL;

	string sTemp[3];
	int iTemp;

	//Creating a file pointer.
	ifstream myfile;

	//Opening the text file.
	myfile.open("toDoList.txt");

	//If the file does not open or is empty this code will execute.
	if ((!myfile.is_open()) || (myfile.peek() == ifstream::traits_type::eof())) {
		//Informing the user no file was found.
		cout << "No file found." << endl;
		cout << "\nStarting program with no previous items." << endl << endl;
		//Returning NULL.
		return NULL;
	}

	//While the file pointer is not pointing to the end of the file this code will execute.
	while (!myfile.eof())
	{
		//If size = 0 this code will execute.
		if (size == 0)
		{
			size++;

			//Reading several lines from the file.
			getline(myfile, sTemp[0]);

			for (int count = 1; count < 3; count++)
			{
				getline(myfile, sTemp[count]);
			}

			//Creating a new dynamic array.
			head = new toDo[size];

			//Setting the first element of the dynamic array equal to the read items.
			head[size - 1].setTask(sTemp[0]);
			head[size - 1].setDate(sTemp[1]);
			iTemp = atoi(sTemp[2].c_str());
			head[size - 1].setId(iTemp);

			//Continuing to the next iteration.
			continue;
		}

		//If size is greater than 0 this code will execute.
		if (size > 0)
		{
			size++;

			//Creating a new dynamic array.
			ptr = new toDo[size];

			//Copying the old array into the new array.
			for (int count = 0; count < size - 1; count++)
			{
				ptr[count] = head[count];
			}

			//Deleting the old array.
			delete[] head;
			//Setting head = to the new array.
			head = ptr;
			//Nulling ptr.
			ptr = NULL;

			//Reading 3 lines from the file.
			for (int count = 0; count < 3; count++)
			{
				getline(myfile, sTemp[count]);
			}

			//Setting the current element of the dynamic array equal to the read items.
			head[size - 1].setTask(sTemp[0]);
			head[size - 1].setDate(sTemp[1]);
			iTemp = atoi(sTemp[2].c_str());
			head[size - 1].setId(iTemp);

			//Continuing to the next iteration.
			continue;
		}
	}

	//Informing the user that the file was successfully loaded.
	cout << "File successfully loaded!" << endl << endl;
	//Returning the head pointer.
	return head;
}
//End of loadFile.

//This function saves a formatted file for the user.
// Bonus, this function allows the user to save a special formatted file for their use.
void saveFormatted(int size, string name, toDo* head)
{
	//Creating a string.
	string temp;

	//If size = 0 this code will execute.
	if (size == 0)
	{
		//Informing the user no items exist in the list.
		cout << "\nNo items found to save..." << endl;
		cout << "\nPlease enter some items so that I can save them." << endl;
		//Returning to main.
		return;
	}

	//This loop execute until broken out of.
	while (true)
	{
		//Reading the size of the passed string.
		int sSize = name.size();

		//If the size is less than 4 this code will execute.
		if (name.size() < 4)
		{
			//Appending .txt to the end of the string.
			name.append(".txt");
			//Breaking out of the loop.
			break;
		}

		//Setting temp equal to the last 4 characters of the passed string.
		temp = name.substr(sSize - 4, 4);

		//If temp doesn't equal .txt this code will execute.
		if (temp != ".txt")
		{
			//Appending .txt to the end of the string.
			name.append(".txt");
			//Breaking out of the loop.
			break;
		}

		else
		{
			//Breaking out of the loop.
			break;
		}
	}

	//Creating a file pointer.
	ofstream myfile;

	//Opening the file with the passed string as the name.
	myfile.open(name);

	//This loop iterates to the current size of the dynamic array.
	for (int count = 0; count < size; count++)
	{
		//If the item is named deletedItem is is skipped.
		if (head[count].getTask() == "deletedItem")
		{
			continue;
		}

		//Writing the item to the file in a neat fashion.
		myfile << "Item #" << count + 1 << endl;
		myfile << "===========================" << endl;
		myfile << head[count] << endl;
	}

	//Closing the file.
	myfile.close();
	//Informing the user that the file was created successfully.
	cout << "\nFile successfully saved!" << endl;
	//Returning to main.
	return;
}
//End of saveFormatted.

//This function uppercases a passed string.
string sUp(string answer)
{
	//Uppercasing the string.
	transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
	//Returning the uppercased string.
	return answer;
}
//End of sUp.

//This function asks the user if they want to continue.
void toContinue()
{
	char choice;

	//Asking the user to enter 1 to contine.
	cout << "\nTo continue enter 1" << endl;
	cin >> choice;

	//Input validation loop.
	while (choice != '1')
	{
		cout << choice << " is not a valid input, please try again." << endl;
		cin >> choice;
	}
	//Clearing cin.
	//Note: This solved a bug when returning to main.
	cin.ignore();
}
//End of toContinue.