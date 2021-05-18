//Program name: Inventory Inquistor
//Program Description: This program allows a user to create a record of objects.
//My name: Quinn Roemer W1582947
//CISP 400 T/Th FLC 9-10:20am
//October 10th 2017

#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>

#define NDebug //Comment out to enable asserts.
#include <assert.h>


using namespace std;

// Constraint 5: Using OOP methods.

//This class is used to hold the inventory records.
class inventory {
private:
	//Private class variables.
	string name;
	string description;
	int quantity;
	float wholesale;
	float retailCost;
	string date;
public:
	//This pointer is used to point to the previous list in a linked list.
	inventory* head;
	//Prototype for the class's constructor.
	inventory();
	//Get methods. These are used to get the private variables.
	string getName();
	string getDescription();
	string getDate();
	int getQuantity();
	float getWholesale();
	float getRetailCost();
	//Set methods. These are used to set the private variables.		
	void setName(string);
	void setDescription(string);
	void setQuantity(int);
	void setWholesale(float);
	void setRetailCost(float);
	void setDate(string);
	//This pointer is used to point to the next element of the linked list.
	inventory* next;
};
//Constructor method. Grabs the date from the computer and automatically sets the date string.
inventory::inventory() {
	auto t = time(nullptr);
	auto tm = *localtime(&t);
	ostringstream oss;
	oss << put_time(&tm, "%d-%m-%Y");
	date = oss.str();
}
//Method used to get the name string.
string inventory::getName() {
	return name;
}
//Method used to get the description string.
string inventory::getDescription() {
	return description;
}
//Method used to get the date string.
string inventory::getDate() {
	return date;
}
//Method used to get the quantity int.
int inventory::getQuantity() {
	return quantity;
}
//Method used to get the wholesale float.
float inventory::getWholesale() {
	return wholesale;
}
//Method used to get the retailCost float.
float inventory::getRetailCost() {
	return retailCost;
}
//Method used to set the name string.
void inventory::setName(string rName) {
	name = rName;
}
//Method used to set the description string.
void inventory::setDescription(string rDescription) {
	description = rDescription;
}
//Method used to set the quantity int.
void inventory::setQuantity(int rQuantity) {
	assert(rQuantity >= 0);
	quantity = rQuantity;
}
//Method used to set the wholesale float.
//Note: Calling the method also set the retailCost float to a 100% markup of wholesale.
void inventory::setWholesale(float price) {
	// Bonus : In this program I used a couple asserts to protect some of my methods.
	assert(price >= 5);
	wholesale = price;
	retailCost = wholesale * 2;
}
//Method used to set the retailCost float. 
//Note: Only used when loading a file at program start.
void inventory::setRetailCost(float price) {
	retailCost = price;
}
//Method used to set the date string.
//Note: Only used when loading a file at program start.
void inventory::setDate(string rDate) {
	date = rDate;
}

//Function prototypes.
char displayMenu();
string sUp(string);
inventory* iNode();
inventory* aNode(inventory*);
inventory* sNode(inventory*, int, int);
inventory* dNode(inventory*, int&, int&);
inventory* loadFile(inventory*, int&, int&);
void dNode(inventory*, inventory*, inventory*);
void pNode(inventory*, int, int);
void mNode(inventory*, int, int);
void saveFormatted(inventory*, int, int);
void save(inventory*);
void toContinue();

//Begin main.
int main()
{
	//Creating the necessary variables/pointers.
	inventory* head = NULL;
	inventory* bHead = NULL;
	inventory* current = NULL;
	int quit = 0, size = 0, isInit = 0;
	char choice;

	// Constraint 4: Loading the file if it exists at the programs start.

	//Calling the loadFile function. This function looks for a file that contains records. 
	//If it finds such a file it will load them. Otherwise, it will tell the user nothing was found.
	head = loadFile(current, size, isInit);
	bHead = head;

	//This loop iterates until it finds the last record. It then sets the current pointer to that.
	while (head != NULL) {
		current = head;
		head = head->next;
	}

	head = bHead;

	//Welcoming the user to the program.
	cout << "Welcome to the inventory inquistor program. This program allows you to create\nand manage an inventory of objects." << endl;
	 
	while (quit == 0) {

		//Displaying the user's menu and receiving their choice.
		choice = displayMenu();

		switch (choice) {

		case '1': //Case 1: Add a record.

			//If the linked list is not intilized this code will execute.
			if (isInit == 0) {
				//Caling the iNode function. This function intilizes a linked list.
				head = iNode();
				bHead = head;
				current = head;
				isInit = 1;
				size++;
				toContinue();
				break;
			}
			//If the linked list is intilized this code will execute.
			else {
				//Calling the aNode function. This function adds to an existing linked list.
				current = aNode(current);
				size++;
				toContinue();
				break;
			}

		case '2': //Case 2: Print all records.

			//Calling the print function. This function will print out the entire linked list.
			pNode(head, isInit, size);
			head = bHead;
			toContinue();
			break;

		case '3': //Case 3: Display one record.

			//Calling the sNode function. This function searches the linked list for a specific name.
			head = sNode(head, 1, isInit);
			head = bHead;
			toContinue();
			break;

		case '4': //Case 4: Modify a record.

			//Calling the mNode function. This function modifies a record in the linked list.
			mNode(head, isInit, size);
			head = bHead;
			toContinue();
			break;

		case '5': //Case 5: Delete a record.

			//Calling the dNode function. This function deletes anyrecord in the linked list.
			head = dNode(head, size, isInit);
			toContinue();
			break;

		case '6': //Case 6: Save record to a formatted file.

			//Calliing the saveFormatted function. This function saves a formatted file that
			//is easily read by the user.
			saveFormatted(head, isInit, size);
			head = bHead;
			toContinue();
			break;

		case '7': //Case 7: Quit with file save.
			
			// Constraint 4: Saving a file at the end of the program.

			//Calling the save function. This function saves a file for the computer for the
			//next time this program is ran.
			save(head);
			head = bHead;
			//Calling the dNode function. This function deallocates memory to the linked list.
			dNode(head, bHead, current);
			quit++;
			break;

		case '8': //Case 8: Quit, delete file.

			// Bonus : This program has the option of quiting with no file save. To do this
			//the file is removed for the next start up.
			remove("recordList.txt");
			//Calling the dNode function. This function deallocates memory to the linked list.
			dNode(head, bHead, current);
			quit++;
			break;
		}
	}

	//Saying goodbye :(

	cout << "\nGoodbye :)" << endl;
	return 0;

} //End of main.

//This function is used to display the program's menu.
char displayMenu() {
	char choice;
	cout << "\nInventory Menu" << endl;
	cout << "=======================" << endl;
	cout << "1: Add a new record." << endl;
	cout << "2: Display all records." << endl;
	cout << "3: Display a record." << endl;
	cout << "4: Modify a record." << endl;
	cout << "5: Delete a record." << endl;
	cout << "6: Save your records to a formatted file." << endl;
	cout << "7: Exit program. (save records for next start)" << endl;
	cout << "8: Exit program. (delete all records)" << endl;


	cin >> choice;

	//Input validation.
	// Constraint 1: Throughtout this program this is input validation in the necessary places.
	while ((choice < '1') || (choice > '8')) {
		cout << choice << " is not a valid input, please try again." << endl;
		cin >> choice;
	}

	//Returning the user's choice.
	return choice;

} //End of displayMenu.

//This function uppercases a string.
// Bonus : When searching, the program ignores the case of the search parameter.
string sUp(string answer) {

	transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
	return answer;

} //End of sUp.

// Constraint 2: Dynamic memory structure. Can store unlimited items.
// Bonus : Used a linked list as my dynamic memory structure.
//This function intilizes a linked list.
inventory* iNode() {

	string sTemp;
	int iTemp;
	float fTemp;

	//Creating a new inventory objects from the heap.
	inventory* ptr = new inventory;
	ptr->head = ptr;
	ptr->next = NULL;

	//Clearing cin. Preperation for using getline.
	cin.ignore();

	cout << "\nPlease enter the name of the product." << endl;
	getline(cin, sTemp);
	ptr->setName(sTemp);

	cout << "\nPlease enter a short description of your product." << endl;
	getline(cin, sTemp);
	ptr->setDescription(sTemp);

	cout << "\nPlease enter the quantity of your product." << endl;
	cin >> iTemp;

	//Input validation. Quantity cannot be less than 0.
	while ((iTemp < 0) || (cin.fail())) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Input invalid, please try again." << endl;
		cin >> iTemp;
	}

	ptr->setQuantity(iTemp);

	cout << "\nPlease enter the wholesale price of your product." << endl;
	cin >> fTemp;

	//Input validation. Wholesale cannot be less than 5.0.
	while ((fTemp < 5) || (cin.fail())) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Input invalid, please try again." << endl;
		cin >> fTemp;
	}

	ptr->setWholesale(fTemp);

	//Returning a pointer to the newly created object.
	return ptr;

} //End of iNode function.

//This function is used to add to a previously created linked list.
inventory* aNode(inventory* cPtr) { 
	
	//Creating a new inventory objects from the heap.
	inventory* ptr = new inventory;

	string sTemp;
	int iTemp;
	float fTemp;

	ptr->head = cPtr;
	cPtr->next = ptr;
	ptr->next = NULL;

	//Clearing cin. Preperation for using getline.
	cin.ignore();

	cout << "\nPlease enter the name of the product." << endl;
	getline(cin, sTemp);
	ptr->setName(sTemp);

	cout << "\nPlease enter a short description of your product." << endl;
	getline(cin, sTemp);
	ptr->setDescription(sTemp);

	cout << "\nPlease enter the quantity of your product." << endl;
	cin >> iTemp;

	//Input validation. Quantity cannot be less than 0.
	while ((iTemp < 0) || (cin.fail())) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Input invalid, please try again." << endl;
		cin >> iTemp;
	}

	ptr->setQuantity(iTemp);

	cout << "\nPlease enter the wholesale price of your product." << endl;
	cin >> fTemp;

	//Input validation. Wholesale cannot be less than 5.0.
	while ((fTemp < 5) || (cin.fail())) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Input invalid, please try again." << endl;
		cin >> fTemp;
	}

	ptr->setWholesale(fTemp);

	//Returning a pointer to the newly created object.
	//Note: This pointer is to the current object. Not the first one.
	return ptr;

} //End of aNode function.

//This function is used to search the linked list. It returns a pointer to the found element.
//Note: If no element is found NULL is returned.
inventory* sNode(inventory* ptr, int print, int isInit) { 
	
	string search, sRecord;
	bool isFound = false;
	char choice;

	//Clearing cin. Preperation for using getline.
	cin.ignore();

	//If no records have been created the user will be informed.
	if (isInit == 0) {
		cout << "\nPlease enter some records so that I can display them." << endl;
		return ptr;
	}

	cout << "\nPlease enter the name of the record that you want to display, modify, or delete." << endl;
	getline(cin, search);

	//Uppercasing the string to be searched for.
	search = sUp(search);

	//This loop sequentially searches the list.
	//Note: The name of the list is uppercased as well. This allows case to not matter in seaches.
	while (ptr != NULL) {
		sRecord = ptr->getName();
		sRecord = sUp(sRecord);
		if (search == sRecord) {
			isFound = true;
			break;
		}
		ptr = ptr->next;	
	}

	//If the record is found. The user will be asked if they want to print it.

	if (isFound == true) { 
		cout << "\nYour record has been found!" << endl;

		//Note: If print is 1. (Determined when this function is called) The user will not be asked if they
		//want to print the record.
		if (print == 1) {
			cout << "\nWould you like to print the record?\n(Enter 1 for yes and 0 for no)" << endl;
			cin >> choice;
			if (choice == '1') {
				cout << "\nName: " << ptr->getName() << endl;
				cout << "Description: " << ptr->getDescription() << endl;
				cout << "Quantity: " << ptr->getQuantity() << endl;
				cout << "Wholesale price: $" << ptr->getWholesale() << endl;
				cout << "Retail Price: $" << ptr->getRetailCost() << endl;
				cout << "Date created: " << ptr->getDate() << endl << endl;
			}
		}
	}

	//If no record is found the user will be informed and sent back to the program's menu.
	//Note: NULL will be returned.
	if (isFound == false) {
		cout << "\nYour record was not found." << endl;
		return NULL;
	}

	//Returning the address of the found record.
	return ptr;

} //End of sNode function.

//This function deletes any record in the linked list.
inventory* dNode(inventory* head, int& size, int& isInit) {

	//If no records have been created the user will be informed.
	if ((isInit == 0) || (size == 0)) {
		cout << "\nPlease enter some records so that I can delete them." << endl;
		return head;
	}

	char choice;
	inventory* bHead = head;

	//Calling the sNode function to search for a record to delete.
	inventory* ptr = sNode(head, 0, isInit);

	head = bHead;
 	
	//This loop iterates if sNode returns NULL. It asks the user if they want to search for something
	//else. If so it calls the sNode function again. Otherwise, the user is sent back to the program's menu.
	while (ptr == NULL) {
		cout << "\nWould you like to try again?\n(Enter 1 for yes and 0 for no)" << endl;
		cin >> choice;

		//Input validation.
		while ((choice != '1') && (choice != '0')) {
			cout << choice << " is not a valid input, please try again." << endl;
			cin >> choice;
		}

		if (choice == '1') {
			ptr = sNode(head, 0, isInit);
			head = bHead;
		}

		if (choice == '0') {
			return head;
		}
	}

	head = bHead;

	//Asking the user if they really want to delete the record.
	cout << "\nAre you sure you want to delete this record?\n(Enter 1 for yes and 0 for no)" << endl;
	cin >> choice;

	//Input validaton.
	while ((choice != '1') && (choice != '0')) {
		cout << choice << " is not a valid input, please try again." << endl;
		cin >> choice;
	}
	//If choice equals 0 the original head pointer will be returned.
	if (choice == '0') {
		return head;
	}
	//If choice equals 1 the record will be renamed.
	if (choice == '1') {
		ptr->setName("deletedRecord");
	}

	//Decrementing size and returning the original head pointer.
	size--;
	return head;

} //End of dNode function.

// Constraint 3: This program loads a file if it exists.
//This function runs at the programs start. It attempts to locate a file and if successful loads those records.
inventory* loadFile(inventory* current, int& size, int& isInit) {

	inventory* ptr = NULL;
	inventory* head = NULL;
	inventory* previous = NULL;
	string sTemp[6];
	int iTemp;
	float fTemp;

	//Opening the file recordList.txt.
	//Note: The file must be in the same directory as the program executable.
	ifstream myfile;
	myfile.open("recordList.txt");

	//If the file fails to open or is empty NULL is returned.
	if ((!myfile.is_open()) || (myfile.peek() == ifstream::traits_type::eof())) {
		cout << "No file found." << endl;
		cout << "\nStarting program with no previous records." << endl << endl;
		return NULL;
	}

	//This loop iterates until the end of file marker is found.
	while (!myfile.eof()) {

		//If size is 0 this will run and intilize the linked list.
		if (size == 0) {
			getline(myfile, sTemp[0]);

			for (int count = 1; count < 6; count++) {
				getline(myfile, sTemp[count]);
			}

			//Creating a new inventory object on the heap.
			ptr = new inventory;
			head = ptr;
			previous = ptr;

			ptr->setName(sTemp[0]);
			ptr->setDescription(sTemp[1]);

			//Converting the string to an int.
			iTemp = atoi(sTemp[2].c_str());
			ptr->setQuantity(iTemp);

			//Converting the string to a float.
			fTemp = stof(sTemp[3].c_str());
			ptr->setWholesale(fTemp);
			ptr->setDate(sTemp[5]);

			ptr->head = head;
			ptr->next = NULL;
			isInit++;
			size++;
		}

		//If size is not equal to 0 this will run and add to an existing linked list.
		else {

			for (int count = 0; count < 6; count++) {
				getline(myfile, sTemp[count]);
			}

			//Creating a new inventory object on the heap.
			ptr = new inventory;
			current = ptr;
			ptr->head = previous;
			ptr->next = NULL;
			previous->next = ptr;
			previous = ptr;

			ptr->setName(sTemp[0]);
			ptr->setDescription(sTemp[1]);

			//Converting the string to an int.
			iTemp = atoi(sTemp[2].c_str());
			ptr->setQuantity(iTemp);

			//Converting the string to a float.
			fTemp = stof(sTemp[3].c_str());
			ptr->setWholesale(fTemp);
			ptr->setDate(sTemp[5]);

			size++;
		}
	}

	//Informing the user the file successfully loaded and returning a pointer to the first element.
	cout << "File successfully loaded!" << endl << endl;
	return head;

} //End of loadFile.

//This function deallocates a linked list.
void dNode(inventory* head, inventory* bHead, inventory* current) {

	inventory* dhead = head;

	//This loop iterates until NULL is reached deleting the records along the way.
	while (dhead != NULL) {
		head = dhead->next;
		delete (dhead);
		dhead = head;
	}

	//Nulling all of the pointers.
	head = NULL;
	dhead = NULL;
	current = NULL;
	bHead = NULL;

}//End of dNode.

//This function prints all of the elements of a linked list.
// Bonus : This program can print all of the records to the screen at one time.
void pNode(inventory* ptr, int isInit, int size) {
	
	int number = 1;

	//If no records have been created the user will be sent back the program's menu.
	if ((isInit == 0) || (size == 0)) {
		cout << "\nPlease enter some records so that I can display them." << endl;
		return;
	}

	cout << "\nHere are all of the records that you have entered.\n" << endl;
	
	//This loop iterates until NULL is found.
	while (ptr != NULL) {

		//If the name of the object is deletedRecord the object is skipped.
		if (ptr->getName() == "deletedRecord") {
			ptr = ptr->next;
			if (ptr == NULL) {
				return;
			}
			continue;
		}
		cout << "Record #" << number << endl;
		cout << "========================" << endl;
		cout << "Name: " << ptr->getName() << endl;
		cout << "Description: " << ptr->getDescription() << endl;
		cout << "Quantity: " << ptr->getQuantity() << endl;
		cout << "Wholesale price: $" << ptr->getWholesale() << endl;
		cout << "Retail Price: $" << ptr->getRetailCost() << endl;
		cout << "Date created: " << ptr->getDate() << endl << endl;
		number++;
		ptr = ptr->next;		
	}

	//Returning nothing.
	return;

} //End of pNode.

//This function modifies an objects value.
void mNode(inventory* head, int isInit, int size) {

	//If no records have been created the user will be sent back the program's menu.
	if ((isInit == 0) || (size == 0)) {
		cout << "\nPlease enter some records so that I can modify them." << endl;
		return;
	}

	//Calling the sNode function. To find the record to modify.
	inventory* ptr = sNode(head, 0, isInit);

	char choice;
	string sTemp;
	int iTemp;
	float fTemp;

	//This loop iterates if sNode returns NULL. It asks the user if they want to search for something
	//else. If so it calls the sNode function again. Otherwise, the user is sent back to the program's menu.
	while (ptr == NULL) {
		cout << "\nWould you like to search for another record.\n(Enter 1 for yes or 0 for no)" << endl;
		cin >> choice;

		//Input validation.
		while ((choice != '1') && (choice != '0')) {
			cout << choice << " is not a valid input. Please try again." << endl;
			cin >> choice;
		}

		if (choice == '1') {
			ptr = sNode(head, 0, isInit);
		}
		if (choice == '0') {
			return;
		}
	}

	cout << "\nAre you sure you want to modify this record?\n(Enter 1 for yes or 0 for no)" << endl;
	cin >> choice;

	//Input validation.
	while ((choice != '1') && (choice != '0')) {
		cout << choice << " is not a valid input. Please try again." << endl;
		cin >> choice;
	}

	//If choice is 1 the user will be asked to enter new value for the record.
	if (choice == '1') {

		//Ignoring cin. In preperation of getline.
		cin.ignore();

		cout << "\nPlease enter the new name of the product." << endl;
		getline(cin, sTemp);
		ptr->setName(sTemp);

		cout << "\nPlease enter a new short description of your product." << endl;
		getline(cin, sTemp);
		ptr->setDescription(sTemp);

		cout << "\nPlease enter the new quantity of your product." << endl;
		cin >> iTemp;

		//Input validation. Quantity cannot be less than 0.
		while ((iTemp < 0) || (cin.fail())) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Input invalid, please try again." << endl;
			cin >> iTemp;
		}
		ptr->setQuantity(iTemp);

		cout << "\nPlease enter the new wholesale price of your product." << endl;
		cin >> fTemp;

		//Input validation. Wholesale cannot be less than 5.0.
		while ((fTemp < 5) || (cin.fail())) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Input invalid, please try again." << endl;
			cin >> fTemp;
		}
		ptr->setWholesale(fTemp);
	}

	//If choice is 0 this code will execute and return nothing.
	if (choice == '0')
		return;

} //End of mNode.

//This function saves a formatted file for reading by the user.
// Bonus : This program can save a formatted file for the user.
void saveFormatted(inventory* ptr, int isInit, int size) {

	string name;
	int number = 1;

	//If no records have been created the user will be sent back the program's menu.
	if ((isInit == 0) || (size == 0)) {
		cout << "\nPlease enter some records so that I can save them." << endl;
		return;
	}
	
	//Asking the user to enter a name for their file.
	cout << "\nPlease enter a name for your file.\n(Please add .txt to the end of the name)" << endl;
	cin >> name;

	//Opening the file.	
	ofstream myfile;
	myfile.open(name);

	//If the file opened correctly this code will execute.
	if (myfile.is_open()) {	
	
		//Printing some things to the file for readability.
		myfile << "Record List" << endl;
		myfile << "=========================================" << endl << endl;
	
		//While ptr is not NULL this loop will execute and print all of the records
		//to the file in a readable fashion.
		while (ptr != NULL) {

			//If the record name is deletedRecord the record will be skipped.
			if (ptr->getName() == "deletedRecord") {
				ptr = ptr->next;
				if (ptr == NULL) {
					myfile.close();
					cout << "\nFile successfully saved!" << endl;
					return;
				}
				continue;
			}
			myfile << "Record #" << number << endl;
			myfile << "============================" << endl;
			myfile << "Name: " << ptr->getName() << endl;
			myfile << "Description: " << ptr->getDescription() << endl;
			myfile << "Quantity: " << ptr->getQuantity() << endl;
			myfile << "Wholesale: $" << ptr->getWholesale() << endl;
			myfile << "Retail Cost: $" << ptr->getRetailCost() << endl;
			myfile << "Date: " << ptr->getDate() << endl << endl;
			ptr = ptr->next;
			number++;
		}

		//Closing the file. And returning to main.
		myfile.close();
		cout << "\nFile successfully saved!" << endl;
		return;
	}

	//If the file was not opened correctly this code will execute.
	cout << "Unable to save a file." << endl;
	return;

} //End of saveFormatted.

// Constraint 3: This program saves a file that contains the records for the next startup.
//This function saves a file for the computers use. This file is used to load records at the programs start.
void save(inventory* ptr) {
	
	int count = 0;

	//Opening a file called recordList.txt.
	ofstream myfile;
	myfile.open("recordList.txt");

	//If the file opened correctly this code will execute.
	if (myfile.is_open()) {

		//While ptr is not NULL this loop will execute.
		while (ptr != NULL) {

			//If the name of the record is deletedRecord it will be skipped.
			if (ptr->getName() == "deletedRecord") {
				ptr = ptr->next;
				if (ptr == NULL) {
					return;
				}
				continue;
			}

			//These if statements prevent a newline from being added to the end of the file
			//while preserving the necessary format.	
			if (count == 0)
				myfile << ptr->getName() << endl;
			if (count >= 1)
				myfile << endl << ptr->getName() << endl;
			myfile << ptr->getDescription() << endl;
			myfile << ptr->getQuantity() << endl;
			myfile << ptr->getWholesale() << endl;
			myfile << ptr->getRetailCost() << endl;
			myfile << ptr->getDate();
			count++;
			ptr = ptr->next;
		}
		//Closing the file and returning to main.
		myfile.close();
		return;
	}
	//If the file was not able to be opened this code will execute.
	cout << "Unable to save a file." << endl;
	return;

} //End of save.

//This function asks the user if they want to continue.
void toContinue() {

	char choice;

	//Asking the user if they want to continue.
	cout << "\nTo continue enter 1." << endl;
	cin >> choice;

	//Input validation.
	while (choice != '1') {
		cout << choice << " is not a valid input, please try again." << endl;
		cin >> choice;
	}
} //End of toContinue.
