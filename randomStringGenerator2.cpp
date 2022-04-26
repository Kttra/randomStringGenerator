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

int generateNum(int digitSize);
std::string generateStrNum(int digitSize);
std::string generateString(int digitSize);
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
    std::cout << "Enter the highest you want your number to be (rand function): ";
    digitSize = getInput(); //std::cin >> digitSize; <- using std::cin means we would assume user puts in valid input
    std::cout << "Random number generated by the rand function: " << randint(rng, 0, digitSize) << '\n' << '\n';
    
    //Max number of digits is 10 because an integer in C++ can only go to int : -2147483648 to 2147483647
    std::cout << "Enter how long you want the number to be (addition of numbers): ";
    digitSize = getInput();
    std::cout << "Random number generated by adding integers together: " << generateNum(digitSize) << '\n' << '\n';
    
    //Adding string values together
    std::cout << "Enter how long you want the next number to be (string made from integers): ";
    digitSize = getInput();
    std::string num = generateStrNum(digitSize);
    std::cout << "Random number generated by string generator: " << num << '\n' << '\n';
    
    //Creating a random string made up of letters
    std::cout << "Enter how long you want your string to be (string made from letters): ";
    digitSize = getInput();
    num = generateString(digitSize);
    std::cout << "Random string generated by string generator: " << num << '\n' << '\n';

    //Waiting for user input to end the program
    std::cout << "Press enter to end the program... ";
    std::string nothing;
    getline(std::cin, nothing);
    
    return 0;
}

//Loops until we receive valid input
int getInput(){
    std::string theInput;
    int inputAsInt;

    getline(std::cin, theInput);

    //If we don't get the correct input, repeat
    while(std::cin.fail() || std::cin.eof() || theInput.find_first_not_of("0123456789") != std::string::npos) {
        std::cout << "Invalid Input. Try again: ";

        //Searches the string for the first character that does not match any of the characters
        //specified in its arguments.
        if(theInput.find_first_not_of("0123456789") == std::string::npos) {
            std::cin.clear();
            std::cin.ignore(256,'\n');
        }
        getline(std::cin, theInput);
    }

    //Convert to integer
    std::string::size_type st;
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
std::string generateStrNum(int digitSize){
    std::string result = "";
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 rng(seed);
	
	for (double digitIndex = 0; digitIndex < digitSize; digitIndex++) {
		int curDigit = randint(rng, 0, 9);
		result += std::to_string(curDigit);
	}
	
	return result;
}

//Generates a string made up of letters
std::string generateString(int digitSize){
    std::string word = "";
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 rng(seed);
    int index = 0;
    std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
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
