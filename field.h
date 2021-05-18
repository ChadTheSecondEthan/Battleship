
const int open = 0;
const int ship = 1;
const int attacked = 2;
const int attackedWithShip = 3;

const int playerOne = 0;
const int playerTwo = 1;
const int visiblePlayerOne = 2;
const int visiblePlayerTwo = 3;

int field[4][10][10];
int openSpaces = 0;

void initField()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 10; j++)
            for (int k = 0; k < 10; k++)
                field[i][j][k] = open;
}

void drawField(int fieldType)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
            printf("%d ", field[fieldType][j][i]);
        printf("\n");
    }
}