#include <iostream>   // Including Libraries
#include <ctime>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

std::string passWord;                    // a string to store the real password chosen by the user 
char charSet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};       // an array of characters which the password can be made up of
const int setNumber = 25;                // a constant integer denoting the size of the array of possible characters (compensated for 0 initialization)
std::vector<int> letterInc = {0};        // a vector to represent the current character in each digit of the password guess
std::string guessWord = "a";

int wordLength = 0;       // integer representing the length of guessWord (0 initialized)
bool guessMatch = 0;      // bool indicating whether guessWord and passWord match
bool loopStop = 0;            // sfds
int curntDigi = 0;            // interger used by the ResetLoop function to keep track of which digit of guessword it is operating on

void CheckGuess()   // Checks if guessWord matches password and updates guessMatch accordingly
{
    if (guessWord == passWord)
    {
        guessMatch = 1;
    }
}

void ResetLoop()      // The ResetLoop function increments the next digit in guessWord and resets the previous digits to zero
{
    bool x = 0;

    do{
     if (guessWord[wordLength] == charSet[setNumber])     // compares the greatest digit of guessWord to the last digit of charSet
    {
        loopStop = 1;
        break;     // breaks out of the loop ending the function if the current guessWord is at its final iteration for its current length
    }
    if(guessWord[curntDigi] == charSet[setNumber])     // compares the digit of guessWord that coresponds with the current value of curntDigi to the final value of charSet
    {
        curntDigi ++;
        ResetLoop();     // recursively calls the ResetLoop function with the parameter set to curntDigi + 1, this will allow the function to cycle through the digits of guessWord from least to greatest to find the digit wich needs to be incremented
    }

    else
    {
        letterInc[curntDigi]++;     // increments the digit of letterInc which corresponds to the current value of curntDigi
        guessWord[curntDigi] = charSet[letterInc[curntDigi]];
        if (guessWord[wordLength] == charSet[setNumber])
        {
            loopStop = 1;
            break;
        }
        CheckGuess();   // checks if the current guess is correct
        if (guessMatch == 1)   // if the guess is correct exit the function
        {
            return;
        }
        for(int i=curntDigi-1; i>=0; i--)     // for loop which iterates once for each guessword digit with an index lesser than the current value of curntDigi
        {
            letterInc[(i)] = 0;   // reset the leterInc digit representing the guessword digit with the index i to 0
            guessWord[i] = charSet[letterInc[i]];
            CheckGuess();   // Checks if the current guess is correct
             if (guessMatch == 1)   // if the guess is correct exit the function
                {
                    return;
                }
        }
        curntDigi = 0;
    }
    }
    while (x == 1);
}

void IncLoop()   // IncLoop function increments through all possible values for the lowest digit of guessWord, it is also able to call the ResetLoop function to increment higher digits and call itself to continue of iterate through values of the lowest digit after
                     // higher digits have been incremented
{
    CheckGuess();   // Checks if the current guess is correct
    if (guessMatch == 1)   // if the current guess is correct exit the function
        {
            return;
        }

        if (loopStop == 0)     // 
        {
            for (int i=0; i<=setNumber; i++)     // for loop iterates the amount of times as there are digits in charSet
            {
                letterInc[0] = i;     // sets the 0th digit of letterInc to i
                guessWord[0] = charSet[letterInc[0]];    //sets the 0th digit of guessWord to the digit of charSet given by the value of the 0th digit of letterInc
            
                CheckGuess();   // checks if the current guess is correct
                 if (guessMatch == 1)   // if the current guess is correct exit the function
                {
                    return;
                }
            }
            ResetLoop();
            IncLoop();
        }
}

void AddLetter()   // the AddLetter functionin increases the size of the guessWord variable by 1 and accordingly resizes the letterInc vector, increments the wordLength integer and resets the digits of guessWord to 0 and sets the digits of guessWord equal to the 
                   // values of the corresponding digits of the letterInc vector
{
    letterInc.resize((wordLength + 2));   // resizes the letterInc vector to the current value of the wordlength variable + 2
    wordLength++;   // increments the wordLength variable
    guessWord += "a";   // adds a character to the guessWord string
    for(int i=wordLength; i>= 0; i--)   // for loop resets the values of guessWord and sets the digits of guessWord equal to the values of the corresponding digits of letterInc
    {
        letterInc[i] = 0;
        guessWord[i] = charSet[letterInc[i]];
    }
    loopStop = 0;
    curntDigi = 0;
}

int main()
{
    int n = 4;   // declares and initializes integer n to equal 4, this can be adjusted based on how long you want the max password length to be

    std::cout << "This program will attempt to guess a password of your choice."<<std::endl;     // informative text output, prompting the user to enter a password of appropriate length using allowed characters
    std::cout << "Please enter a maximum " << n << " digit long password using the following characters only"<< std::endl;
    std::cout << "a b c d e f g h i j k l m n o p q r s t u v w x y z"<< std::endl;

    std::cin>> passWord;   // collects password from user


    for (int i=0; i<n; i++)   // for loop iterates as many times as the max number of letters the password can have
    {
    if (guessMatch == 1)   // if the guess is correct break out of the loop and output the guess message
    {
        std::cout<<"Is this your password?"<<std::endl;
        std::cout<<guessWord<<std::endl;
        break;
    }
    IncLoop();   // calls the IncLoop function
    if (guessMatch == 1)   // if there is a correct guess break out of the loop and output guess message
    {
        std::cout<<"Is this your password?"<<std::endl;
        std::cout<<guessWord<<std::endl;
        break;
    }
    AddLetter();   // calls the AddLetter function
    }
    return 0;
}