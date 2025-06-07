
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

char characterSet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};       // an array of characters which the password can be made up of
std::string passWord;                          // Stores the real password chosen by the user
extern const int setNumber = 25;                      // Size of the array of possible password characters (compensated for 0 initialization)
std::vector<int> guessLetterTracker = {0};     // Tracks the characters of each digit of the guess password
std::string guessWord = "a";                   // The guess password

int wordLength = 0;          // Length of guessWord (0 initialized)
bool loopStop = false;       // Controls the recursion of IncLoop
int currentDigit = 0;        // Used by ResetLoop function to track which digit of guessword it is operating on

bool CheckGuess()   // Check if guess password matches real password and updates guessMatch
{
        return guessWord == passWord;
}

void ResetLoop()     // Increment the next non maxxed digit in guessWord and resets lower digits
{
    bool x = false;

    do{
     if (guessWord[wordLength] == characterSet[setNumber])     // If guessWord is maxxed stop IncLoop
    {
        loopStop = true;
        break;     
    }
    if(guessWord[currentDigit] == characterSet[setNumber])     // If the current digit is maxxed move to the next digit
    {
    currentDigit ++;
        ResetLoop();
    }

    else     // Increment non maxxed digit and reset lesser digits
    {
        guessLetterTracker[currentDigit]++;
        guessWord[currentDigit] = characterSet[guessLetterTracker[currentDigit]];
        if (guessWord[wordLength] == characterSet[setNumber])
        {
            loopStop = true;
            break;
        }
        if (CheckGuess())
        {
            return;
        }
        for(int i=currentDigit-1; i>=0; i--)
        {
            guessLetterTracker[(i)] = 0;
            guessWord[i] = characterSet[guessLetterTracker[i]];
             if (CheckGuess())
                {
                    return;
                }
        }
        currentDigit = 0;
    }
    }
    while (x == true);
}

void IncLoop()     // Cycles through all possible values of the first digit of guessWord and calls ResetLoop when necessary
{
    if (CheckGuess())
        {
            return;
        }

        if (loopStop == false)     // Assign each character in characterSet to the first digit of guessWord
        {
            for (int i=0; i<=setNumber; i++)
            {
                guessLetterTracker[0] = i;
                guessWord[0] = characterSet[guessLetterTracker[0]];
                 if (CheckGuess())
                {
                    return;
                }
            }
            ResetLoop();
            IncLoop();
        }
}

void AddLetter()     // Add a letter to guessWord and update variables accordingly
{
    guessLetterTracker.resize((wordLength + 2));
    wordLength++;
    guessWord += "a";
    for(int i=wordLength; i>= 0; i--)
    {
        guessLetterTracker[i] = 0;
        guessWord[i] = characterSet[guessLetterTracker[i]];
    }
    loopStop = false;
    currentDigit = 0;
}

int main()
{
    int n = 5;     // Max password length (testing purposes)

    std::cout << "This program will attempt to guess a password of your choice."<<std::endl;
    std::cout << "Please enter a maximum " << n << " digit long password using the following characters only"<< std::endl;
    std::cout << "a b c d e f g h i j k l m n o p q r s t u v w x y z"<< std::endl;

    std::cin>> passWord;     // collect password from user


    for (int i=0; i<n; i++)     // test all possible character combinations for passwords 1 to n characters long
    {
    if (CheckGuess())
    {
        std::cout<<"Is this your password?"<<std::endl;
        std::cout<<guessWord<<std::endl;
        break;
    }
    IncLoop();
    if (CheckGuess())
    {
        std::cout<<"Is this your password?"<<std::endl;
        std::cout<<guessWord<<std::endl;
        break;
    }
    AddLetter();
    }
    return 0;
}