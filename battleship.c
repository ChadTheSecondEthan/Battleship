#include <string.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define isY(c) c == 121 || c == 89

bool playerOneTurn;
bool playing;
bool randomShipsPlayerOne;

#include "field.h"
#include "ship.h"

#define isLegalAnswer(fieldType, ans) (ans >= 0 && ans <= 99 && (!(field[fieldType][ans % 10][ans / 10] == attacked || field[fieldType][ans % 10][ans / 10] == attackedWithShip)))

char* nameOne;
char* nameTwo;
const char* instructions[] = { 
    "\nThis is a game of Battleship. You begin the game by placing\n",
    "your ships down on your board. During each turn, pick a\n",
    "number on the board corresponding to the spot you would like\n",
    "to attack. If your attack all of your opponents ships, you win.\n",
    "Your board is a ten by ten grid, with 0's, corresponding to empty\n",
    "space, 1's, corresponding to ships on the board, 2's, corresponding\n",
    "to spaces not containing ships that have been hit, and 3's, \n",
    "corresponding to areas hit that previous contained ships.\n"
};

void init();
void randomizeShips();
void update();
bool checkWin(bool playerOnes);
void gameOver(bool playerOnes);

int main(void)
{
    playerOneTurn = true;
    playing = true;

    srand(time(NULL));

    nameOne = get_string("Input name: ");

    init();

    printf("Here is your field.\n");
    drawField(playerOne);
    printf("\nHere is the enemy's field.\n\n");
    drawField(visiblePlayerTwo);

    while(playing)
    {
        update(playerOneTurn);
        drawField(!playerOneTurn ? playerTwo : playerOne);
    }

    return 0;
}

void init()
{
    // initialize the field to open
    initField();

    // check if user wants to see the instructions
    char a = get_char("%s, would you like to see the instructions? Answer y or n: ", nameOne);
    if (isY(a))
    {
        for (int i = 0; i < sizeof(instructions) / sizeof(char*); i++)
            printf(instructions[i]);
        printf("\n");
    }

    // check if user wants to randomize ships
    char ans = get_char("%s, would you like to randomize your ships' positions? Answer y or n: ", nameOne);
    randomShipsPlayerOne = isY(ans);

    // add the ships to the field
    addShipsToField(playerOne, randomShipsPlayerOne);

    // add the computer ships to the field
    addShipsToField(playerTwo, true);
}

void update()
{
    // variables for the input along with the x and y values of the field
    // that it corresponds to
    int answer;
    int answerX;
    int answerY;

    // get the current field
    int fieldType = playerOneTurn ? playerTwo : playerOne;

    if (playerOneTurn)
    {
        do
        {
            answer = get_int("Input desired target (Between 00 and 99): ");
            if (isLegalAnswer(fieldType, answer))
                break;

            printf("Invalid. Try again.\n");
        } while (true);
    }
    else
    {
        do
        {
            answer = rand() % 100 + 1;
            if (isLegalAnswer(fieldType, answer))
                break;
        } while (true);
    }

    answerX = answer % 10;
    answerY = answer / 10;

    // check if the ship has been hit
    if (field[fieldType][answerX][answerY] == ship)
    {
        if (playerOneTurn)
            printf("Congradulations, %s. You have hit an opponents ship!\n", (playerOneTurn) ? nameOne : nameTwo);
        else
            printf("Your ship has been hit!\n");

        field[fieldType][answerX][answerY] = attackedWithShip;
        field[fieldType + 2][answerX][answerY] = attackedWithShip;
    }
    else
    { 
        if (playerOneTurn)
            printf("You have not hit a ship this turn.\n");
        else
            printf("The opponent did not hit any of your ships this turn.\n");

        field[fieldType][answerX][answerY] = attacked;
        field[fieldType + 2][answerX][answerY] = attacked;
    }

    if (checkWin(playerOneTurn))
        gameOver(playerOneTurn);

    playerOneTurn = !playerOneTurn;
}

bool checkWin(bool playerOnes)
{
    int board = (playerOnes) ? playerOne : playerTwo;

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (field[board][j][i] == ship)
                return false;
    return true;
}

void gameOver(bool playerOnes)
{
    playing = false;

    if (playerOnes)
        printf("Congradulations, %s! You have won BattleShip!\n", nameOne);
    else
        printf("%s, you have lost. Better luck next time!\n", nameOne);

    printf("Here is the enemy's board.\n");
    drawField(playerTwo);
}