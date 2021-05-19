#define open 0
#define ship 1
#define attacked 2
#define attackedWithShip 3

const int playerOne = 0;
const int playerTwo = 1;

int field[2][10][10];
int openSpaces = 0;

void initField()
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 10; j++)
            for (int k = 0; k < 10; k++)
                field[i][j][k] = open;
}

void drawField(int fieldType, bool visible)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++) {
            if (field[fieldType][j][i] == open || (!visible && field[fieldType][j][i] == ship))
                printf("  ");
            else 
                switch(field[fieldType][j][i]) {
                case ship:
                    printf("* ");
                    break;
                case attacked:
                    printf("0 ");
                    break;
                case attackedWithShip:
                    printf("X ");
                    break;
                }
        }
        printf("\n");
    }
}