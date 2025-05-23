#include <iostream>   // Including Libraries
#include <ctime>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

char charSet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};       // an array of characters which the password can be made up of
std::string passWord;                    // a string to store the real password chosen by the user 
const int setNumber = 25;                // a constant integer denoting the size of the array of possible characters (compensated for 0 initialization)
std::vector<int> letterInc = {0};        // a vector to represent the current character in each digit of the password guess
std::string guessWord = "a";             // a string representing the programs guess of the password

int wordLength = 0;       // integer representing the length of guessWord (0 initialized)
bool guessMatch = false;      // bool indicating whether guessWord and passWord match
bool loopStop = false;        // bool which controls the recursion of IncLoop
int curntDigi = 0;        // interger used by the ResetLoop function to keep track of which digit of guessword it is operating on

void CheckGuess()   // Checks if guessWord matches password and updates guessMatch accordingly
{
    if (guessWord == passWord)
    {
        guessMatch = true;
    }
}

void ResetLoop()      // The ResetLoop function increments the next digit in guessWord and resets the previous digits to zero
{
    bool x = 0;       // bool to control the do while loop

    do{
     if (guessWord[wordLength] == charSet[setNumber])     // if the last diggit of guessWord is equal to the last character in charSet, stop incLoops recursion, and break out of the main loop
    {
        loopStop = true;
        break;     
    }
    if(guessWord[curntDigi] == charSet[setNumber])       // if the current digit of guessWord = the last character of charSet, increment curntDigi and recursively call ResetLoop
    {
        curntDigi ++;
        ResetLoop();
    }

    else     // if guessWord isnt maxed out and curntDigi represents a non maxed digit, increment that digit, check for a maxed guessWord or a password match, reset previous digits of guessWord, and reset curntDigi to 0
    {
        letterInc[curntDigi]++;
        guessWord[curntDigi] = charSet[letterInc[curntDigi]];
        if (guessWord[wordLength] == charSet[setNumber])
        {
            loopStop = true;
            break;
        }
        CheckGuess();
        if (guessMatch == 1)
        {
            return;
        }
        for(int i=curntDigi-1; i>=0; i--)
        {
            letterInc[(i)] = 0;
            guessWord[i] = charSet[letterInc[i]];
            CheckGuess();
             if (guessMatch == true)
                {
                    return;
                }
        }
        curntDigi = 0;
    }
    }
    while (x == 1);
}

void IncLoop()         // The IncLoop functioniterates through all possible values of the first digit of guessWord before calling ResetLoop and then itself
{
    CheckGuess();      // Checks for a guess match and terminates the function if found
    if (guessMatch == true)
        {
            return;
        }

        if (loopStop == false)     // if the IncLoop control variable = = 0 iterate through all characters of charSet assigning them to the first digit of guessWord through letterInc
        {
            for (int i=0; i<=setNumber; i++)
            {
                letterInc[0] = i;
                guessWord[0] = charSet[letterInc[0]];
            
                CheckGuess();
                 if (guessMatch == true)
                {
                    return;
                }
            }
            ResetLoop();     // call ResetLoop
            IncLoop();       // recursivly call IncLoop
        }
}

void AddLetter()   // the AddLetter function increases the size of letterInc, wordLength, and guessWord by 1, maps guessWord to charSet and letterInc, and resets the digits of guessWord
{
    letterInc.resize((wordLength + 2));     // increase the size of letterInc by 1
    wordLength++;                           // increases the size of wordLength by 1
    guessWord += "a";                       // adds a character to the guessWord string
    for(int i=wordLength; i>= 0; i--)       // sets every digit of guessWord = charSet[letterInc] = 0
    {
        letterInc[i] = 0;
        guessWord[i] = charSet[letterInc[i]];
    }
    loopStop = false;
    curntDigi = 0;
}

int main()
{
    int n = 4;   // integer determinig the max password length (testing purposes)

    std::cout << "This program will attempt to guess a password of your choice."<<std::endl;     // text output prompting the user to enter a password of appropriate length using allowed characters
    std::cout << "Please enter a maximum " << n << " digit long password using the following characters only"<< std::endl;
    std::cout << "a b c d e f g h i j k l m n o p q r s t u v w x y z"<< std::endl;

    std::cin>> passWord;   // collects password from user


    for (int i=0; i<n; i++)   // check all possible combinations of characters for a password starting at 1 digit long and increaseing the size each time up to n times
    {
    if (guessMatch == true)
    {
        std::cout<<"Is this your password?"<<std::endl;
        std::cout<<guessWord<<std::endl;
        break;
    }
    IncLoop();   // calls the IncLoop function
    if (guessMatch == true)
    {
        std::cout<<"Is this your password?"<<std::endl;
        std::cout<<guessWord<<std::endl;
        break;
    }
    AddLetter();   // calls the AddLetter function
    }
    return 0;
}