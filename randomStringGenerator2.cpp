/*
    Program created to generate random numbers and random strings.

    We use the <random> library in this program instead of the rand() function.
    Using the rand() function is generally considered to be bad.

    This program generates higher-quality random numbers and will allow you to
    have multiple random number generators with different seeds at once.
    
    In this program we look at the limitations of integers and how strings
    could be used as a work around if we are looking to print out the value
    to the user.
*/

#include <iostream>
#include <math.h>  /* pow */
#include <stdlib.h>
#include <time.h> //time()
#include <random> //Better rand
#include <chrono> //Need to generate seed

using namespace std;

int generateNum(int digitSize);
string generateStrNum(int digitSize);
string generateString(int digitSize);
int randint(std::mt19937_64& rng, int lbound, int ubound);
int getInput();

int main(){
    int digitSize = 0;  
    
    //Seed the RNG so it doesn't generate the same numbers every time 
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 rng(seed);

    //Generates a random number between 5 and 20, inclusive
    //randint(rng, 5, 20)

    //Using random function where the values range from 1 to digitSize
    cout << "Enter the highest you want your number to be (rand function): ";
    digitSize = getInput(); //cin >> digitSize; <- using cin means we would assume user puts in valid input
    cout << "Random number generated by the rand function: " << randint(rng, 0, digitSize) << endl << endl;
    
    //Max number of digits is 10 because an integer in C++ can only go to int : -2147483648 to 2147483647
    cout << "Enter how long you want the number to be (addition of numbers): ";
    digitSize = getInput();
    cout << "Random number generated by adding integers together: " << generateNum(digitSize) << endl << endl;
    
    //Adding string values together
    cout << "Enter how long you want the next number to be (string made from integers): ";
    digitSize = getInput();
    string num = generateStrNum(digitSize);
    cout << "Random number generated by string generator: " << num << endl << endl;
    
    //Creating a random string made up of letters
    cout << "Enter how long you want your string to be (string made from letters): ";
    digitSize = getInput();
    num = generateString(digitSize);
    cout << "Random string generated by string generator: " << num << endl << endl;

    //Waiting for user input to end the program
    cout << "Press enter to end the program... ";
    string nothing;
    getline(cin, nothing);
    
    return 0;
}

//Loops until we receive valid input
int getInput(){
    string theInput;
    int inputAsInt;

    getline(cin, theInput);

    //If we don't get the correct input, repeat
    while(cin.fail() || cin.eof() || theInput.find_first_not_of("0123456789") != string::npos) {
        cout << "Invalid Input. Try again: ";

        //Searches the string for the first character that does not match any of the characters
        //specified in its arguments.
        if(theInput.find_first_not_of("0123456789") == string::npos) {
            cin.clear();
            cin.ignore(256,'\n');
        }
        getline(cin, theInput);
    }

    //Convert to integer
    string::size_type st;
    inputAsInt = stoi(theInput,&st);

    return inputAsInt;
}

//Generates a random number that has digitSize digits
int generateNum(int digitSize){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 rng(seed);

    int result = 0;
	
	for (double digitIndex = 0; digitIndex < digitSize; digitIndex++) {
		int curDigit = randint(rng, 0, 9);
		curDigit *= pow(10, digitIndex);
		result += curDigit;
	}
	
	return result;
}

//Generates a string made up of random numbers
string generateStrNum(int digitSize){
    string result = "";
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 rng(seed);
	
	for (double digitIndex = 0; digitIndex < digitSize; digitIndex++) {
		int curDigit = randint(rng, 0, 9);
		result += to_string(curDigit);
	}
	
	return result;
}

//Generates a string made up of letters
string generateString(int digitSize){
    string word = "";
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 rng(seed);
    int index = 0;
    string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    //0123456789 can add numbers to the letters string if we want
	
	for(int i = 0; i < digitSize; i++){
		index = randint(rng, 0, 52);
        word += letters[index];
	}
	
	return word;
}

//Generate an integer between lbound and ubound, inclusive 
int randint(std::mt19937_64& rng, int lbound, int ubound){ 
    return rng() % (ubound - lbound + 1) + lbound; 
}