// PIG (a Rolling Game)
// Nima_Mahanloo_HW1_PIG.CPP
// Nima Mahanloo, CISP 400
// 01/25/2018
#include <iostream>
#include <random>
#include <ctime>
using namespace std;
// PIG game class
class rollDie
{
    /* Public members */
    public:
        // Function Prototype
        // Default constructor
        rollDie();
        // Destructor
        ~rollDie();
        // void function to reset private members values for new game
        void resetGame();
        // void mutator function to calculate and set player's new roll
        void setDice(int);
        // Integer function to access private member for player's new roll value
        int getDice();
        // Program Greeting
        // void function as game greeting and main menu
        void firstMenu();
        // Boolean function to check player score vs required winner score value
        bool scoreCheck(int);
    /* Private members */
    private:
        // Fix integer value for winner score
        int const WINNERSCORE = 100;
        // A character variable for game player numbers (1 or 2)
        char playerNum;
        // Integer variable contains new roll value
        int dice;
        //char aiChar;
        // Integer variable contains AI difficulty (3)
        int AI;
        // Character variable for user option to game over or replay
        char userChoice;
        // Boolean variable for game over status as a flag
        bool gameOver;
};
// Simple structure for each player's score data
struct player
{
    // Integer contains player total score
    int totalScore;
};
/* The game class default constructor */
rollDie::rollDie()
{
    /* Private members initialization */
    playerNum = '0';
    dice = 0;
    //aiChar = '0';
    AI = -1;
    userChoice = '?';
    gameOver = false;
}
/* The game class Destructor */
rollDie::~rollDie()
{
    /* No pinter available on this class to destruct */
    ;
}
/* The game class void function to reset all private members value for new game */
void rollDie::resetGame()
{
    playerNum = '0';
    dice = 0;
    //aiChar = '0';
    AI = -1;
    userChoice = '?';
    gameOver = false;
}
// Program Greeting
/* The game class greeting function as new game first screen */
void rollDie::firstMenu()
{
    /* Display title of the game */
    cout << "Pig - Rolling A Die Game" << endl << endl;
    /* A while loop to verify and get user input */
    while ((playerNum != '1') && (playerNum != '2'))
    {
        /* Prompt a request message to user to input number of human players */
        cout << "Select Players - 1 or 2 >" << endl;
        /* Get player numbers in */
        cin >> playerNum;
    }
    /* A condition to check player numbers is 1 or not */
    if (playerNum == '1')
    {
       /*while ((aiChar != '1') && (aiChar != '2') && (aiChar != '3') && (aiChar != '4') && (aiChar != '5') && (aiChar != '6'))
        {
            cout << "Enter AI difficulty between 1 to 6 >" << endl;
            cin >> aiChar;
        }
        AI = static_cast <int> (aiChar) - 48;*/
        /* Set AI difficulty to 3 */
        AI = 3;
        /* Display a message to user */
        cout << "Player 2 is Computer" << endl;
    }
}
/* The game class mutator function to calculate user's new roll and set private member */
void rollDie::setDice(int pNum)
{
    /* Initial character variable value for new request message */
    userChoice = 'r';
    /* A while loop to check and execute user input as re-roll */
    while (userChoice == 'r')
    {
        /* Calculate a new random number between 1 to 6 for user new roll */
        dice = rand() %6 + 1;
        /* Show calculated roll value to player */
        cout << "Player " << pNum << "'s this turn score is : " << dice << endl;
        /* A condition to check current player is human or not */
        if (((playerNum == '1') && (pNum == 1)) || (playerNum == '2'))
        {
            /* Initial character variable for user input */
            userChoice = '?';
            /* A while condition to verify and get user input about hold current roll or re-roll */
            while ((userChoice != 'r') && (userChoice != 'h'))
            {
                cout << "Do you hold (h) or roll again (r) ?" << endl;
                cin >> userChoice;
            }
        }
        /* If current player is computer and current roll is bigger than AI difficulty then re-roll */
        else if (dice > AI)
        {
            userChoice = 'r';
        }
        /* else hold current roll */
        else
        {
            userChoice = 'h';
        }
        /* If re-rolling show this message */
        if (userChoice == 'r')
        {
           cout << "Re-rolling ..."  << endl;
        }
    }
}
/* The game class access function to private member value for new roll value */
int rollDie::getDice()
{
    return dice;
}
/* The game class boolean function to check current player score vs required score to win */
bool rollDie::scoreCheck(int playerScore)
{
    /* Initial game over status flag */
    gameOver = false;
    /* If current player total score is equal or greater than 100 then */
    if (playerScore >= WINNERSCORE)
    {
        /* Set game over flag to true */
        gameOver = true;
    }
    /* Return game over flag value to main module */
    return gameOver;
}
int main()
{
    // A boolean variable contains new game greeting screen status as flag
    bool firstRound = true;
    // A boolean variable contains game over status as flag
    bool gameOver = false;
    // A boolean variable contains current player winning status as flag
    bool gameStatus = false;
    // Character variable contains player decision to re-play or end the game
    char replay;
    // Create new object from the game class
    rollDie newGame;
    // create new objects from player score data structure for each player
    player player1, player2;
    /* Use s-random function include time function as seed to generate unique random numbers */
    srand(time(0));
    /* A conditional loop to check game over status flag */
    while (gameOver == false)
    {
        /* If this is a new game then reset values and show greeting menu */
        if (firstRound == true)
        {
            newGame.resetGame();
            player1.totalScore = 0;
            player2.totalScore = 0;
            newGame.firstMenu();
            firstRound = false;
        }
        /* Else continue the game */
        else
        {
            /* Display this is player 1 turn */
            cout << endl << "Player 1 >" << endl;
            /* Call the game class function to generate new roll value for player 1 */
            newGame.setDice(1);
            /* Add player 1 current roll value to his total score */
            player1.totalScore = player1.totalScore + newGame.getDice();
            /* Display player 1 current total score */
            cout << "Player 1 total score is : " << player1.totalScore << endl;
            /* Call the game class function to check player 1 current total score winning status */
            gameStatus = newGame.scoreCheck(player1.totalScore);
            /* if player 1 won then */
            if (gameStatus == true)
            {
                /* Initial character variable for user input about re-play or end the game */
                replay = '?';
                /* Display the game winner and game over message to user */
                cout << endl << "player 1 Wins!" << endl << "Game Over!" << endl;
                /* A while loop to verify and get user input about re-play or end the game */
                while ((replay != 'y') && (replay != 'n'))
                {
                    cout << endl << "Do you want to play again?" << endl << "(y or n)" << endl << "> ";
                    cin >> replay;
                }
                /* Reset new game status flag */
                firstRound = true;
                /* End the game */
                if (replay == 'n')
                {
                    gameOver = true;
                }
            }
            /* Continue the game */
            else
            {
                /* Display this is player 2 turn */
                cout << endl << "Player 2 >" << endl;
                /* Call the game class function to generate new roll value for player 2 */
                newGame.setDice(2);
                /* Add player 2 current roll value to his total score */
                player2.totalScore = player2.totalScore + newGame.getDice();
                /* Display player 2 current total score */
                cout << "Player 2 total score is : " << player2.totalScore << endl;
                /* Call the game class function to check player 2 current total score winning status */
                gameStatus = newGame.scoreCheck(player2.totalScore);
                /* if player 2 won then */
                if (gameStatus == true)
                {
                    /* Initial character variable for user input about re-play or end the game */
                    replay = '?';
                    /* Display the game winner and game over message to user */
                    cout << endl << "player 2 Wins!" << endl << "Game Over!" << endl;
                    /* A while loop to verify and get user input about re-play or end the game */
                    while ((replay != 'y') && (replay != 'n'))
                    {
                        cout << endl << "Do you want to play again?" << endl << "(y or n)" << endl << "> ";
                        cin >> replay;
                    }
                    /* Reset new game status flag */
                    firstRound = true;
                    /* End the game */
                    if (replay == 'n')
                    {
                        gameOver = true;
                    }
                }
            }
        }
    }
    return 0;
}
