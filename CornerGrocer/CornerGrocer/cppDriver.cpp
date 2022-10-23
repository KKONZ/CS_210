#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

#include <iomanip>
#include <fstream>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	//Py_DECREF(pValue);

	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;
	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
/*
void callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	//Py_DECREF(pValue);
	
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}
*/
/*
function that displays menu for user input
*/
void PrintMenu() {
	cout << "1: Print how many of each item sold" << endl;
	cout << "2: Search count of specific item sold" << endl;
	cout << "3. Display histogram of items sold" << endl;
	cout << "4: Exit:" << endl;
	cout << "Enter your selection as a number 1, 2, 3, or 4" << endl;
}

/*
Validate input is of integer data type, contiune to prompt until 1, 2, or 3 read
Return:
	Validated integer data type input from user
*/
int UserMenuInput() {
	int input;

	// display menu to user
	PrintMenu();

	// read input
	cin >> input;

	// if cin fails or input not 1, 2, 3, or 4 continue loop until appropriate input
	while (cin.fail() || !((input == 1) || (input == 2) || (input == 3) || (input == 4))) {
		cout << "Expected 1, 2, 3, or 4!\n\n";
		cin.clear();
		cin.ignore(256, '\n');

		PrintMenu();
		cin >> input;
	}
	return input;
}


/*
Grocery item to count
Param:
    string of grocery item from user
*/
string UserGroceryInput() {
	// set exception mask for cin stream
	string input = "";

	cout << "Grocery Item to Count:\n";

	cin >> input;

	// if cin fails or input is an empty string continue loop until appropriate input
	while (cin.fail() || input == "") {
		cout << "Unexpected input, enter grocery item as a string value!\n\n";
		cin.clear();
		cin.ignore(256, '\n');

		PrintMenu();
		cin >> input;
	}
	return input;
}


/*
Display histogram of data from file
*/
void PrintHistogram() {
	string item;
	int count;

	// open file stream of counted grocery items
	ifstream file("U:\\CornerGrocer\\Release\\frequency.dat");
	
	// iterate over list and format text histogram to start filling in * values for counts 15 characters after the start of the line
	while (file >> item >> count) {
		cout << left << setw(15) << setfill(' ') << item << " " << string(count, '*') << endl;
	}

	// close the file
	file.close();

	// delete the file after the histogram has completed
	remove("U:\\CornerGrocer\\Release\\frequency.dat");
}


/*
Takes input and calls associated function in python via callIntFunc
Param:
	int input from user input for which menu item to run
Return:
    int count of searched item
*/
void ProcessInput(int input) {
	string groceryItem = "";
	int itemCount = 0;

	// if param for user value was 1 then call python function countAll
	if (input == 1) {
		cout << endl;
		CallProcedure("countAll");
		cout << endl;
	}

	// if param for user value was 2 then call python function countItem
	if (input == 2) {
		cout << endl;
		groceryItem = UserGroceryInput();
		itemCount = callIntFunc("countItem", groceryItem);
		cout << itemCount <<endl;
		cout << endl;
	}

	// if param for user value was 3 then call python function write summary and 
	// call c++ function printHistogram
	if (input == 3){
		cout << endl;
		CallProcedure("writeSummary");
		cout << endl;
		PrintHistogram();
		cout << endl;
	}

	// if param for user value was 4 then exit program
	if (input == 4) {
		exit(0);
	}
}

/*
Loop through user inputs while input does not equal 3
*/
void LoopInput() {
	int userInput = 0;
	while (userInput != 4) {
		userInput = UserMenuInput();
		ProcessInput(userInput);
	}
}


int main()
{
	LoopInput();
	return 0;
}