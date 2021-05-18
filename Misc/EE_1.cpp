#include <iostream>
#include <cstdlib>
#include <memory>

using namespace std;

//Exception for index out of range.
struct IndexOutOfRangeException
{
	const int index;
	IndexOutOfRangeException(int ix) : index(ix) {}
};

//Simple Vector class.
template <class T>
class SimpleVector
{
	unique_ptr<T[]> aptr;
	int arraySize;
	int position;

public:

	//Simple vector constructors
	SimpleVector(int);
	SimpleVector(const SimpleVector &);

	//Size method.
	int size() const { return size; }

	//Overloaded [] operator.
	T &operator[](int);

	//Outputs the array elements.
	void print() const;

	//Added methods for assignment.
	void push_back(T);
	void pop_back();
};

//Constructor for the SimpleVector class. Sets the size of the array and allocates memory for it.
template <class T>
SimpleVector<T>::SimpleVector(int s)
{
	arraySize = s;
	aptr = make_unique<T[]>(s);
	for (int count = 0; count < arraySize; count++)
	{
		aptr[count] = T();
	}
}

//Copy constructor for SimpleVector class.
template<class T>
SimpleVector<T>::SimpleVector(const SimpleVector &obj)
{
	arraySize = obj.arraySize;
	aptr = make_unique<T[]>(arraySize);
	for (int count = 0; count < arraySize; count++)
	{
		aptr[count] = obj[count];
	}
}

//Overloaded [] operator. The argument is a subscript.
//This function returns a reference to the element
//in the array indexed by the subscript.
template<class T>
T &SimpleVector<T>::operator[](int sub)
{
	if (sub < 0 || sub >= arraySize)
	{
		throw IndexOutOfRangeException(sub);
	}

	position = sub;
	return aptr[sub];
}

//Prints all of the entries in the array.
template <class T>
void SimpleVector<T>::print() const
{
	cout << endl;

	for (int count = 0; count <= position; count++)
	{
		cout << aptr[count] << " ";
	}

	cout << endl;
}

//Pop back moves the array back one.
template <class T>
void SimpleVector<T>::pop_back()
{
	//Creating a new pointer.
	auto NewPtr = make_unique<T[]>(arraySize);

	for (int count = 0; count < arraySize - 1; count++)
	{
		//Setting new pointer to the values of aptr.
		NewPtr[count] = aptr[count];
	}

	//Decrementing position
	position--;
}

//Push back moves the array forward one.
template <class T>
void SimpleVector<T>::push_back(T toAdd)
{
	//If the postion is greater then the range an exception will be thrown.
	if (position + 1 >= arraySize)
	{
		throw IndexOutOfRangeException(position);
	}

	//Otherwise this code will execute.
	else
	{
		aptr[position + 1] = toAdd;
		position++;
	}

}

//Main function to execute.
int main()
{
	//Creating two objects.
	SimpleVector<int> intTable(10);
	SimpleVector<double> doubleTable(10);

	//Setting a couple variables.
	int toAdd = 10;
	double dAdd = 9.55;

	//Populating the intTable object.
	for (int i = 0; i <= 8; i++)
	{
		intTable[i] = i + 1;
	}

	//Populating the doubleTable object.
	for (int i = 0; i < 9; i++)
	{
		doubleTable[i] = i + .55;
	}

	//Printing out intTable.
	cout << "Printing a table of ints." << endl;
	intTable.print();

	//Pushing intTable forward and printing.
	cout << "\nAdding an item to the end." << endl;
	intTable.push_back(toAdd);
	intTable.print();

	//Popping intTable backward and printing.
	cout << "\nRemoving last element." << endl;
	intTable.pop_back();
	intTable.print();

	//Printing doubleTable.
	cout << "\nPrinting a table of doubles." << endl;
	doubleTable.print();

	//Pushing doubleTable forward and printing.
	cout << "\nAdding an item to the end." << endl;
	doubleTable.push_back(dAdd);
	doubleTable.print();

	//Popping doubleTable backward and printing.
	cout << "\nRemoving last element." << endl;
	doubleTable.pop_back();
	doubleTable.print();

	//Creating a new object.
	SimpleVector<int> intTest(10);

	//Populating the new object.
	for (int i = 0; i <= 9; i++)
	{
		intTest[i] = i + 1;
	}

	//Printing intTest.
	cout << "\nPrinting another table of ints." << endl;
	intTest.print();

	//Popping intTest back 3 and printing.
	cout << "\nPopping table of ints back 3 places." << endl;
	intTest.pop_back();
	intTest.pop_back();
	intTest.pop_back();	
	intTest.print();

	//Pushing intTest forward 3 and printing.
	cout << "\nPushing the table of ints forward 3 places." << endl;
	intTest.push_back(13);
	intTest.push_back(13);
	intTest.push_back(13);
	intTest.print();

	//Pushing intTest back 1 and popping it forward 1 and printing.
	cout << "\nPopping the table back one and then pushing it forward 1." << endl;
	intTest.pop_back();
	intTest.push_back(26);
	intTest.print();
}
//End of main.