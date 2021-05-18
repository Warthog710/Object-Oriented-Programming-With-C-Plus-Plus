//Program name: Gpa Analyzer
//Program Description: This program accepts a max score and tests grades. It than outputs the average to the user.
//My name: Quinn Roemer W1582947
//CISP 400 T/Th FLC 9-10:20am
//September 18th 2017

#define NDEBUG

#include <limits>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <assert.h>


using namespace std;

class Grade	//A class called grade that will be used to hold all of the grades entered by the user.
{		// Constraint 4 - Using object oriented programming techniques.
public:
	Grade* head;	//A Grade pointer that will be used to point to the previous element of the list.
	string lgrade;	//A string that will hold the letter grade entered by the user.
	float pgrade;	//A float that will hold the percent grade entered by the user.	
	Grade* next;	//A Grade pointer that will be used to point to the next element of the list.
};
//Function Prototypes.
Grade* Inode(int&, int&, int&);					//This function will be used to intilize the linked list.
Grade* Anode(Grade*, int&);					//This function will be used to add a node to the linked list.
int Pnode(Grade*, int, int);					//This function will be used to print all of the nodes of the linked list.
void Dlist(Grade*, Grade*, Grade*, Grade*);			//This function will be used to delete all of the nodes of the linked list.
char userMenu();						//This function will be used to print the menu of the program.
string sUp(string);						//This function will be used to uppercase a passed string.
int pAverage(Grade*, int, int, int);				//This function will be used to print the average of all of the grades entered.
void reset(Grade*, Grade*, Grade*, Grade*, int&, int&, int&);	//This function will be used to reset all of the grade variables.
void quitnoF(Grade*, Grade*, Grade*, Grade*, int, int);		//This function will be used to quit the program with no file output.
void quitwF(Grade*, Grade*, Grade*, Grade*, int, int);		//This function will be used to quit the program with file output.

int main() //Main function to execute.
{
	Grade* head = NULL;		//Grade pointer that will be used to point to the first element of the list.
	Grade* bhead = NULL;		//Grade pointer backup for head.
	Grade* current = NULL;		//Grade pointer that will be used to point to the current element of the list being manipulated.
	Grade* bcurrent = NULL;		//Grade pointer backup for current.
	string goAgain = "YES";		//A string that will be used to determine if the user wants to enter another grade or not.
	int isInit = 0, size = 0, mScore = 0, hold, quit = 1;	//Several int variables used throughout the program.
	char choice;	//This variable will hold the users choice from the menu.

	cout << "Welcome to the GPA Analyzer program. This program will accept an unlimited\namount of scores and will output the average." << endl;	//Program greeting

	while (quit == 1) {	//A loop that will execute as long as quit = 1.

		choice = userMenu();		//Call to the menu function to print the program's menu.

		switch (choice) {		//Switch case to determine what code to execute depending on the user choice.

		case '1':			//If choice = '1' than the user will be prompted to enter grades.
			if (isInit == 1) {	//If isInit = 1 than the list is already intilized and this code will execute.	
				size++;		//Incrementing the size variable.
				current = Anode(current, size);	//Calling the Anode function to add an element to the list.
				bcurrent = current;		//Changing the backup pointer to be equal to the new address.
			}

			if (isInit == 0) {	//If isInit = 0 than the list is not intilized and this code will execute.
				size++;		//Incrementing the size variable.
				head = Inode(isInit, mScore, size); //Calling the intilize function for the linked list.
				bhead = head; 			    //Setting the backup pointer to be equal to head.
				current = head;			    //Setting the current pointer to be equal to head.
			}

			while (goAgain == "YES") {	//While goAgain = "YES" the user will be asked if they want to go again.
				cout << "\nWould you like to enter another grade? (enter yes or no)" << endl; //Prompting the user.
				cin >> goAgain;		//Reading the inputted answer.
				goAgain = sUp(goAgain);	//Calling the sUp function to uppercase the string.

				while ((goAgain != "YES") && (goAgain != "NO")) {	//Input validation loop.
					cout << "\nInput invalid, please try again." << endl; //Informing the user there input was invalid.	
					cin >> goAgain;			//Reading the inputted answer.
					goAgain = sUp(goAgain);		//Calling the sUp function to uppercase the string.
				}
				if (goAgain == "YES") {			//If goAgain = "YES" this code will be executted.
					size++;				//Incrementing the size variable.
					current = Anode(current, size);	//Calling the Anode function to add an element to the list.
					bcurrent = current;		//Setter the backup pointer to be equal to current.
				}
				if (goAgain == "NO") {			//If goAgain = "NO" this code will be executted.
					goAgain = "YES";		//Resetting the goAgain variable to "YES".
					break;				//Breaking out of the loop.
				}
			}
			break;	//Breaking out of the case.

		case '2':	//If choice = '2' this code will be executted.
			cout << "\nThis program works by presenting you with a menu with certain options." << endl;
			cout << "Depending on your choice this program will do certain things. If you choose" << endl;
			cout << "1 the program will ask you to enter your letter grades and percentage grade" << endl;
			cout << "for a class. This program will keep asking you to enter grades until you" << endl;
			cout << "type no. After this the program will return to the menu where you will be" << endl;
			cout << "expected to enter another choice." << endl; //Printing help for the user.

			cout << "\nTo continue enter 1..." << endl; 		//Asking the user if they want to continue.
			cin >> hold;						//Reading the inputted answer.
			if (hold != 1) {					//If hold != 1 this code will be executted.
				cout << "\nTo continue enter 1..." << endl;	//Asking the user if they want to continue.
				cin >> hold;					//Reading the inputted answer.
			}

			break;	//Breaking out of the case.

		case '3':					//If choice = '3' this code will be executted.
			hold = Pnode(head, 0, size);		//Calling the Pnode function, this will print the contents of the linked list.
			head = bhead;				//Resetting the head pointer.
			break;					//Breaking out of the case.

		case '4':					//If choice = '4' this code will be executted.
			hold = pAverage(head, mScore, size, 0);	//Calling the pAverage function, this will print the average of all scores.
			head = bhead;				//Resetting the head pointer.
			break;					//Breaking out of the case.

		case '5':		// Bonus reset, added the ability to reset all of the scores and start over.
			reset(head, bhead, current, bcurrent, mScore, size, isInit);	//Calling the reset function, to reset the list.
			break;								//Breaking out of the case.

		case '6':							//If choice = '6' this code will be executted.
			quitnoF(head, bhead, current, bcurrent, mScore, size);	//Calling the quitnoF function, this will quit with no file.
			quit = 0;						//Setting quit = 0.
			break;							//Breaking out of the case.

		case '7':							//If choice = '7' this code will be executted.
			quitwF(head, bhead, current, bcurrent, mScore, size);	//Calling the quitwF function, this will quit with a file.
			quit = 0;						//Setting quit = 0.
			break;							//Breaking out of the case.

		case '8':		// Bonus file output, added the ability to output a file without quiting.
			pAverage(head, mScore, size, 3);	//Calling the pAverage function to print a file.
			head = bhead;				//Resetting the head pointer.	
			break;					//Breaking out of the case.
		} //End of case.
	} //End of while.

	cout << "\nGoodbye." << endl; //Telling the user goodbye.
	return 0;		      //Returning 0 to end.
}				      //End of Main

Grade* Inode(int& isInit, int& max, int& size) {// Bonus linked list, used a linked list instead of an array.
	Grade* head = new Grade;		//Creating a new dynamically allocated object.
	cout << "\nBefore you enter your grades please enter the max score for the class\nin question." << endl; //Prompting the user.
	cin >> max; 				//Reading the inputted answer.
	assert(max > 0);			//Assert that will trigger if max is ever less than 1.
	while ((max < 0) || (cin.fail())) {	//Input validation, making sure max is always greater than 0.
		cin.clear(); 			//Clearing a cin fail state.
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	//Ignoring the user input.
		cout << "\nInput invalid, please try again." << endl;		//Prompting the user.
		cin >> max;			//Reading the inputted answer.
	}
	cout << "\nPlease enter your letter grade for test " << size << "." << endl;	//Prompting the user.
	cin >> head->lgrade;			//Reading the inputted answer.
	head->lgrade = sUp(head->lgrade);	//Sending string to sUp function to be uppercased.
	while (((((((head->lgrade != "A") && (head->lgrade != "B") && (head->lgrade != "C") && (head->lgrade != "D") && ((head->lgrade != "F") || (cin.fail())))))))) { //Input validation, making sure that lgrade is only ever equal to A, B, C, D, F.
		cin.clear();			//Clearing a cin fail state.
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	//Ignoring the user input.
		cout << "\nInput invalid, please try again." << endl;		//Prompting the user.
		cin >> head->lgrade;						//Reading the inputted answer.
		head->lgrade = sUp(head->lgrade);				//Sending string to sUp function to be uppercased.
	}
	cout << "\nPlease enter your score grade for test " << size << "." << endl;	//Prompting the user.
	cin >> head->pgrade;			//Reading the inputted answer.
	assert(head->pgrade > 0);		//Assert that will trigger if pgrade is ever less than 0.
	while ((head->pgrade < 0) || (cin.fail())) {	//Input validation, making sure pgrade is always greater than 0.
		cin.clear();			//Clearing a cin fail state.
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	//Ignoring the user input.
		cout << "\nInput invalid, please try again." << endl;		//Prompting the user.	
		cin >> head->pgrade;		//Reading the inputted answer.
	}
	head->head = head;			//Setting the head of the new object equal to itself.
	head->next = NULL;			//Setting the head of the next object to NULL.
	isInit = 1;				//Setting isInit to 1. This informs the program that the list is already intilized.
	return head;				//Returning the head pointer.
}

Grade* Anode(Grade* head, int& size) {		//This function is used to add a node to the linked list.
	Grade* current = new Grade;		// Constraint 2 - Use new() to properly handle your array/linked list.
	current->head = head;			//Setting the head pointer of the new object equal to the head pointer of the previous object.
	current->next = NULL;			//Setting the new objects next pointer to NULL.
	head->next = current;			//Setting the previous objects next pointer to the head of this new object.
	cout << "\nPlease enter your letter grade for test " << size << "." << endl;	//Prompting the user.
	cin >> current->lgrade;			//Reading the inputted answer.
	current->lgrade = sUp(current->lgrade);	//Sending the string to the sUp function to be uppercased.
	while (((((((current->lgrade != "A") && (current->lgrade != "B") && (current->lgrade != "C") && (current->lgrade != "D") && ((current->lgrade != "F") || (cin.fail())))))))) {	//Input validation, make sure lgrade is only ever equal to A, B, C, D, F.
		cin.clear();			//Clearing a cin fail state.
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	//Ignorring the user input.
		cout << "\nInput invalid, please try again." << endl;		//Prompting the user.
		cin >> current->lgrade;		//Reading the inputted answer.
		current->lgrade = sUp(current->lgrade);	//Sending the string to the sUp function to be uppercased.
	}
	cout << "\nPlease enter your score grade for test " << size << "." << endl; //Prompting the user.
	cin >> current->pgrade;			//Reading the inputted answer.
	assert(head->pgrade > 0);		//Assert that will trigger whenever pgrade is less than 0.
	while ((current->pgrade < 0) || (cin.fail())) {	// Constraint 1 - Do not accept negative test scores.
		cin.clear();			//Clearing a cin fail state.
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	//Ignoring the user input.
		cout << "\nInput invalid, please try again." << endl;		//Prompting the user.
		cin >> current->pgrade;		//Reading the inputted answer.
	}
	return current;				//Returning the current pointer.
}

int Pnode(Grade* head, int quit, int size) {	//This function is used to print the linked list.
	int hold;				//Creating an int variable. This will be used to determine when the user is ready to continue.
	if (size == 0) {			//If no grades have been inputted this code will execute.
		cout << "\nPlease enter some grades." << endl;			//Informing the user they have entered no grades.
		return 0;			//Returning to main.
	}
	cout << "\nHere are the grades you entered." << endl;			//Telling the user they grades are being printed.
	cout << "\nLetter Grade		Score" << endl;				//Printing headers.
	cout << "------------	        -----" << endl;				//Printing underline.
	while (head != NULL) {			//While the head pointer is not NULL this loop will execute.
		cout << head->lgrade;		//Printing lgrade of the object.
		cout << "			" << head->pgrade << endl;	//Printng pgrade of the object.
		head = head->next;		//Setting the head pointer to the next object.
	}
	if (quit == 0) {			//If quit = 0 this code will execute.
		cout << "\nTo continue enter 1..." << endl;			//Prompting the user if they are ready to continue.
		cin >> hold;			//Reading the inputted answer.
		if (hold != 1) {		//If hold != 1 this code will execute.
			cout << "\nTo continue enter 1..." << endl;		//Prompting the user if they are ready to continue.
			cin >> hold;		//Reading the inputted answer.
		}
	}
	return 0; //Returning to main.
}

void Dlist(Grade* head, Grade* current, Grade* bhead, Grade* bcurrent) {	//This function is used to delete the linked list.
	Grade* dhead = head;			//Creating a new grade pointer and setting it equal to head.
	while (dhead != NULL) {			//While head != NULL this code will execute.
		head = dhead->next;		//Setting head to the next object.
		delete (dhead);			// Constraint 2 - Using delete() to properly handle my linked list.
		dhead = head;			//Setting dhead to head.
	}

	head = NULL;				//Setting head = NULL.
	dhead = NULL;				//Setting dhead = NULL.
	current = NULL;				//Setting current = NULL.
	bhead = NULL;				//Setting bhead = NULL.
	bcurrent = NULL;			//Setting bcurrent = NULL.
}

char userMenu() {				//This function is used to print the menu and read the users choice.
	char user_menu;
	cout << "\nGPA Anaylzer Menu" << endl; //Prompting the user.
	cout << "=======================" << endl;
	cout << "1: Enter grade." << endl;
	cout << "2: Help." << endl;
	cout << "3: Print grades." << endl;
	cout << "4: Print average." << endl;
	cout << "5: Reset scores." << endl;
	cout << "6: Quit (without file output)" << endl;
	cout << "7: Quit (with file output)" << endl;
	cout << "8. Output file." << endl;
	cin >> user_menu;			//Reading the inputted answer.
	while (((((((user_menu != '1') && (user_menu != '2') && (user_menu != '3') && (user_menu != '4') && (user_menu != '5') && (user_menu != '6') && (user_menu != '7') && (user_menu != '8'))))))) { //While head is not equal to 1,2,3,4,5,6,7,8, this code will execute.
		cout << "\n" << user_menu << " is not a valid input, please try again." << endl; //Telling the user there input was invalid.
		cin >> user_menu;		//Reading the inputted answer.
	}
	return user_menu;			//Returning the choice.
}

string sUp(string answer) {			//This function is used to uppercase a string.
	transform(answer.begin(), answer.end(), answer.begin(), ::toupper);	//Transforming to uppercase.
	return answer; 				//Returning the uppercased string.
}

int pAverage(Grade* head, int max, int size, int quit) { //This function is used to display the average and print a .txt file.

	int hold; //Creating a int variable. This will be used to determine when the user is ready to continue.

	if (size == 0) {			//If size = 0 the user will be informed they have entered no grades.
		cout << "\nPlease enter some grades." << endl;			//Prompting the user.
		return 0;			//Returning to main.
	}

	float sum = 0;				//This variable will hold the sum of all test scores.
	float average = 0;			//This variable will hold the average of all test scores.
	float grade = 0;			//This variable will hold the graded test scores.
	string lgrade;				//This variable will hold the average/recieved letter grade.

	while (head != NULL) {			//This loop is used to add up the sum of all of the test scores.
		sum += head->pgrade;		//Adding the sum of the current objects pgrade to sum.
		head = head->next;		//Pointing head to the next object.	
	}

	average = sum / size;			//Performing a calculation to find the average score.

	grade = sum / max;			//Performing a calculation to find the recieved letter grade.

	if (grade >= .9)			//A series of if statements to determine what grade the user got.
		lgrade = "A";
	if ((grade >= .8) && (grade < .9))
		lgrade = "B";
	if ((grade >= .7) && (grade < .8))
		lgrade = "C";
	if ((grade >= .6) && (grade < .7))
		lgrade = "D";
	if (grade < .6)
		lgrade = "F";


	if (quit == 3) {			//If this function is called with a 3 it will print a file.
		string name;			//Creating a string to hold the file name.
		cout << "\nWhat would you like to name your file?" << endl; // Bonus file name, added the ability to name the outputted file.
		cin >> name;			//Reading the inputted name.
		ofstream myfile;		//Preparing to open the file.
		myfile.open(name);		//Creating a new file in the same directory where this code is being executted.
		myfile << "Grade Summary" << endl;				//Printing to the file.
		myfile << "=======================================================" << endl;		//Printing to the file.
		myfile << "You received " << sum << " points out of a possible " << max << "." << endl;	//Pringing to the file.
		myfile << "Your average score was " << average << " on each test." << endl;		//Printing to the file.
		myfile << "You should receive a " << lgrade << " in the class." << endl;		//Printing to the file.
		cout << "\nA file has been saved with your grade summaries." << endl; //Informing the user their file has been created.
		myfile.close();			//Closing the file.
		return 0;			//Returning to main.			
	}

	cout << "\nYou received " << sum << " points out of a possible " << max << "." << endl;	//Printing the sum of scores to screen.
	cout << "\nYour average score was " << average << " on each test." << endl;		//Printing the average score.
	cout << "\nYou should receive a " << lgrade << " in the class." << endl;		//Printing the letter grade.


	if (quit == 0) {			//If quit = 0 this code will execute.
		cout << "\nTo continue enter 1..." << endl;			//Prompting the user if they want to continue.
		cin >> hold;			//Reading the inputted answer.
		if (hold != 1) {		//If hold != 1 this code will execute.
			cout << "\nTo continue enter 1..." << endl;		//Prompting the user if they want to continue.
			cin >> hold;		//Reading the inputted answer.
		}
	}
	return 0;				//Returning to main.
}

void reset(Grade* head, Grade* bhead, Grade* current, Grade* bcurrent, int& max, int& size, int& isInit) { //Function used to reset scores.
	int hold; //Creating a new int, this will be used to determine when the user want to go again.
	max = 0;				//Setting max to 0.
	size = 0;				//Setting size to 0.
	isInit = 0;				//Setting isInit to 0.

	Dlist(head, bhead, current, bcurrent);	//Deleting the entirety of the linked list.

	cout << "\nYour grades have been reset. Enter 1 to continue..." << endl;//Prompting the user if they want to continue.
	cin >> hold;				//Reading the inputted answer.
	if (hold != 1) {			//If hold != 1 this code will execute.
		cout << "\nTo continue enter 1..." << endl;			//Prompting the user if they want to continue.
		cin >> hold;			//Reading the inputted answer.
	}
}						//End of function.

void quitnoF(Grade* head, Grade* bhead, Grade* current, Grade* bcurrent, int max, int size) { //Function used to quit with no file output.
	Pnode(head, 1, size);			//Printing all of the entered scores.
	head = bhead;				//Setting head = bhead.
	pAverage(head, max, size, 1);		//Printing the average of all of the entered scores.
	head = bhead;				//Setting head = bhead.
	Dlist(head, bhead, current, bcurrent);	//Deleting the entirety of the linked list.
}						//End of function.

void quitwF(Grade* head, Grade* bhead, Grade* current, Grade* bcurrent, int max, int size) { //Function used to quit with file output.
	Pnode(head, 1, size);			//Printing all of the entered scores.
	head = bhead;				//Setting head = bhead.
	pAverage(head, max, size, 1);		//Printing the average of all of the entered scores.
	head = bhead;				//Setting head = bhead.
	pAverage(head, max, size, 3);		//Calling pAverage to print a file with the grade summaries.
	Dlist(head, bhead, current, bcurrent);	//Deleting the entirety of the linked list.
}						//End of function.
