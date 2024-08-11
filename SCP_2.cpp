
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

std::string passWord;       // a string to store the real password chosen by the user
std::string guessWord = "a";       // a string to store the programs current guess of the password initialized to "a"
const char charSet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};       // an array of characters which the password can be made up of
const int setNumber = 25;       // a constant integer denoting the size of the array of possible characters (compensated for 0 initialization)
std::vector<int> letterInc = {0};       // a vector to represent the current character in each digit of the guess password

int wordLength = 0;       // integer representing the length of guessWord
bool guessMatch = 0;       // bool indicating whether guessWord and passWord match
int letterNum;       // integer indicating a specific digit of guessWord

int ResetLoop(int g)       // a loop to reset one or more digits of guessword to the initial value and to add a digit to guessword
{
        bool x = 0;
        int counter1 = g;
        do{
        if (guessWord[wordLength] == charSet[setNumber])
        {
            break;
        }
        if(guessWord[counter1] == charSet[setNumber])
        {
            ResetLoop((counter1 + 1));
        }

        else
        {
            letterInc[counter1]++;
            for(int i=wordLength; i>=0; i--) //questionably necessary
            {
                guessWord[i] = charSet[letterInc[i]];
            }
            if (guessWord == passWord)
            {
                guessMatch = 1;
                std::cout<<"Is this your password?"<<std::endl;
                std::cout<<guessWord<<std::endl;
                return 1;

            }
            for(int i=counter1-1; i>=0; i--)
            {
                if(guessWord[(counter1 - 1)] == charSet[setNumber])
                {
                    letterInc[(counter1 - 1)] = 0;
                    if (guessWord == passWord)
                    {
                        guessMatch = 1;
                        std::cout<<"Is this your password?"<<std::endl;
                        std::cout<<guessWord<<std::endl;
                        return 1;

                    }
                    std::cout<<guessWord<<endl;
                }
            }
        letterNum++;
        }
        }while(x == 1);
        return 0;
}

int IncLoop(int x)
{
        if (guessWord == passWord)
        {
            guessMatch = 1;
            std::cout<<"Is this your password?"<<std::endl;
            std::cout<<guessWord<<std::endl;
            return 1;

        }

        letterNum = x;

        if (wordLength == 0)
        {
            for (int i=0; i<=setNumber; i++)
            {
                letterInc[0] = i;
                guessWord[0] = charSet[letterInc[0]];
                if (guessWord == passWord)
                {
                    guessMatch = 1;
                    std::cout<<"Is this your password?"<<std::endl;
                    std::cout<<guessWord<<std::endl;
                    return 1;

                }
                std::cout<<guessWord<<endl;
            }
        }
        else
        {
            if (x == 0)
            {
                for (int i=0; i<=setNumber; i++)
                {
                    letterInc[0] = i;
                    guessWord[0] = charSet[letterInc[0]];
                    if (guessWord == passWord)
                    {
                        guessMatch = 1;
                        std::cout<<"Is this your password?"<<std::endl;
                        std::cout<<guessWord<<std::endl;
                        return 1;

                    }
                    std::cout<<guessWord<<endl;
                }
            }
            if(guessWord[letterNum] == charSet[setNumber])
            {
                ResetLoop(letterNum);
            }
            if(letterNum > 0)
            {
                letterNum--;
                IncLoop(letterNum);
            }
        }
        return 0;
}

void AddLetter()
{
    letterInc.resize((wordLength + 2));
    wordLength++;
    guessWord += "a";
    for(int i=wordLength; i>= 0; i--)
    {
        letterInc[i] = 0;
        guessWord[i] = charSet[letterInc[i]];
        std::cout<<guessWord<<endl;
    }
}

int main()
{
    int n = 4;

    std::cout << "This program will attempt to guess a password of your choice."<<std::endl;
    std::cout << "Please enter a maximum " << n << " digit long password using the following characters only"<< std::endl;
    std::cout << "a b c d e f g h i j k l m n o p q r s t u v w x y z"<< std::endl;

    std::cin>> passWord;


    for (int i=0; i<n; i++)
    {
    if (guessWord == passWord)
    {
        std::cout<<"Is this your password?"<<std::endl;
        std::cout<<guessWord<<std::endl;
        break;
    }
    IncLoop(wordLength);
    if (guessMatch == 1)
    {
        break;
    }
    AddLetter();
    }
    return 0;
}
