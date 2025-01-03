
#include <iostream>
#include "Deck.h"
using namespace std;

int GetMenuSelection(string prompt, int minimumS, int maximumS);
bool playFibo(Deck deck);
bool isFibo(int fiboNumber);

int main()
{
    Deck deck = Deck();

    bool gameIsRunning = true;
    while (gameIsRunning)
    {
        string menuPrompt = "Welcome to Fibonacci Solitaire!\n"
                            "Select an option...\n"
                            "1. Create New Deck\n"
                            "2. Display Deck\n"
                            "3. Shuffle Deck\n"
                            "4. Play Fibo Solitaire\n"
                            "5. Win Fibo Solitaire\n"
                            "6. Exit\n"
                            "Selection: ";
        int menuSelection = GetMenuSelection(menuPrompt, 1, 6);

        cout << endl;

        if (menuSelection == 1) // Create New Deck
            deck.newDeck();

        if (menuSelection == 2) // Shuffle Deck
            deck.show();

        if (menuSelection == 3) // Display Deck
            deck.shuffle();

        if (menuSelection == 4) // Play Fibo Solitaire
            playFibo(deck);

        if (menuSelection == 5) // Win Fibo Solitaire (Keep playing Fibo until a win)
        {
            int gameCount = 1;

            while (!playFibo(deck)) // PlayFibo returns a boolean that shows whether or not the game was won, therefore, while (not Won)
            {
                gameCount += 1;
                deck.shuffle();

                cout << "\nShuffling for next game...\n"
                     << endl;
            }
            cout << endl;
            cout << "Games Played : " << gameCount << endl;
            cout << endl;
        }

        if (menuSelection == 6) // Exit
            gameIsRunning = false;

        cout << endl;
    }
}

int GetMenuSelection(string prompt, int minimumS, int maximumS) // Receives menu selection
{
    bool inputVal = false;

    while (!inputVal)
    {
        cout << prompt; 
        string latestInputString;
        cin >> latestInputString; 

        bool inputOnlyContainsInts = true;
        for (int charIndex = 0; charIndex < latestInputString.length(); charIndex++){
            char loopChar = latestInputString[charIndex];
            if (!isdigit(loopChar)){
                inputOnlyContainsInts = false;
            }
        }

        bool inputIsWithinRange = false;
        if (inputOnlyContainsInts){
            int inputAsInt = stoi(latestInputString);
            if ((minimumS <= inputAsInt) && (inputAsInt <= maximumS)){
                return inputAsInt;
            }
        }
        cout << "\nNot a valid selection.\n" << endl; 
    }
    return 0;
}

bool playFibo(Deck deck) //will play the game.
{
    bool isWinner = false;
    int pileSum = 0;
    int numberOfPiles = 0;

    while (!deck.isEmpty())
    {
        Card drawnCard = deck.deal();
        pileSum += drawnCard.getValue();
        drawnCard.show();
        cout << ", ";

        if (isFibo(pileSum)){
            cout << "Fibo : " << pileSum << endl;
            pileSum = 0;
            numberOfPiles += 1;
        }
    }

    if (pileSum == 0){
        isWinner = true;
    }

    if (!isWinner){
        cout << "Last Pile NOT Fibo : " << pileSum << endl;
        cout << endl;
        numberOfPiles += 1;
    }

    if (isWinner)
        cout << "Winner";
    else
        cout << "Loser";
    cout << " in " << numberOfPiles << " piles!" << endl;

    return isWinner;
}

bool isFibo(int fiboNumber) // Checks to find if the value is the Fibo number.
{
    vector <int> fiboList = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377};
    for (int fiboNumberIndex = 0; fiboNumberIndex < 13; fiboNumberIndex++){
        if (fiboNumber == fiboList[fiboNumberIndex])
            return true;
    }
    return false;
}