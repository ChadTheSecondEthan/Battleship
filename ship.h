const int shipSizes[5] = { 2, 3, 3, 4, 5 };

void makeVerticalShip(int, int, bool);
void makeHorizontalShip(int, int, bool);

void addShipsToField(int fieldType, bool randomize)
{
    for (int i = 0; i < 5; i++)
    {
        if (!randomize)
        {
            char ans = get_char("Should this ship of length %d be vertical? Answer y or n: ", shipSizes[i]);
            if (isY(ans))
                makeVerticalShip(shipSizes[i], fieldType, false);
            else
                makeHorizontalShip(shipSizes[i], fieldType, false);
        }
        else
        {
            if (rand() % 2 == 0)
                makeVerticalShip(shipSizes[i], fieldType, true);
            else
                makeHorizontalShip(shipSizes[i], fieldType, true);
        }
    }
}

void makeVerticalShip(int size, int fieldType, bool random)
{
    int positionX;
    int positionY;
    int openSpaces = 0;

    bool legalAnswer;

    if (fieldType == playerOne && !random)
    {
        do
        {
            legalAnswer = false;
            positionX = get_int("Enter x - value for ship of length %d: ", size) - 1;
            if (positionX < 0 || positionX > 10)
                // checks if the answer is out of bounds or not
                legalAnswer = false;
            else
            {
                for (int j = 0; j < 10; j++)
                {
                    if (field[fieldType][positionX][j] == open)
                    {
                        openSpaces++;
                        if (openSpaces == size)
                        {
                            openSpaces = 0;
                            legalAnswer = true;
                            break;
                        }
                    }
                    else
                        openSpaces = 0;
                }
            }
            if (!legalAnswer)
                printf("Invalid. Try again.\n");
        } while (!legalAnswer);

        do
        {
            legalAnswer = false;
            positionY = get_int("Enter y - value for ship of length %d: ", size) - 1;
            if (positionY < 0 || positionY > 10 - size)
                // checks if the answer is out of bounds or not
                legalAnswer = false;
            else
                for (int j = 0; j < size; j++)
                {
                    if (field[fieldType][positionX][positionY + j] != open)
                    {
                        legalAnswer = false;
                        break;
                    }
                    else
                        legalAnswer = true;
                }
            if (!legalAnswer)
                printf("Invalid. Try again.\n");
        } while (!legalAnswer);

        for (int j = 0; j < size; j++)
            field[fieldType][positionX][positionY + j] = 1;
    }
    else
    {
        do
        {
            legalAnswer = false;
            positionX = rand() % 10;
            for (int j = 0; j < size; j++)
            {
                // checks if positionX is valid by checking if every spot, up to "size" below it, is valid
                if (field[fieldType][positionX][j] == open)
                {
                    openSpaces++;
                    if (openSpaces == size)
                    {
                        openSpaces = 0;
                        legalAnswer = true;
                        break;
                    }
                }
                else
                    openSpaces = 0;
            }
        } while (!legalAnswer);

        do
        {
            legalAnswer = false;
            positionY = rand() % (10 - size);
            for (int j = 0; j < size; j++)
            {
                // this checks if there will be enough open spaces at the row of positionY
                if (field[fieldType][positionX][positionY + j] != open)
                {
                    legalAnswer = false;
                    break;
                }
                else
                    legalAnswer = true;
            }
        } while (!legalAnswer);

        for (int j = 0; j < size; j++)
            field[fieldType][positionX][positionY + j] = 1;
    }
}

void makeHorizontalShip(int size, int fieldType, bool random)
{
    int positionX;
    int positionY;
    int openSpaces = 0;

    bool legalAnswer;

    if (fieldType == playerOne && !random)
    {
        do
        {
            legalAnswer = false;
            positionY = get_int("Enter y - value for ship of length %d: ", size) - 1;
            if (positionY < 0 || positionY > 10)
                // checks if the answer is out of bounds or not
                legalAnswer = false;
            else
                for (int j = 0; j < 10; j++)
                {
                    // this checks if there will be enough open spaces at the row of positionY
                    if (field[fieldType][j][positionY] == open)
                    {
                        openSpaces++;
                        if (openSpaces == size)
                        {
                            openSpaces = 0;
                            legalAnswer = true;
                            break;
                        }
                    }
                    else
                        openSpaces = 0;
                }
            if (!legalAnswer)
                printf("Invalid. Try again.\n");
        } while (!legalAnswer);

        do
        {
            legalAnswer = false;
            positionX = get_int("Enter x - value for ship of length %d: ", size) - 1;
            if (positionX < 0 || positionX > 10 - size)
                // checks if the answer is out of bounds or not
                legalAnswer = false;
            else
                for (int j = 0; j < size; j++)
                {
                    // checks if positionX is valid by checking if every spot, up to "size" below it, is valid
                    if (field[fieldType][positionX + j][positionY] != open)
                    {
                        legalAnswer = false;
                        break;
                    }
                    else
                        legalAnswer = true;
                }
            if (!legalAnswer)
                printf("Invalid. Try again.\n");
        } while (!legalAnswer);

        for (int j = 0; j < size; j++)
            field[fieldType][positionX + j][positionY] = 1;

    }
    else
    {
        do
        {
            legalAnswer = false;
            positionY = rand() % 10;
            for (int j = 0; j < size; j++)
            {
                // checks if positionX is valid by checking if every spot, up to "size" below it, is valid
                if (field[fieldType][j][positionY] == open)
                {
                    openSpaces++;
                    if (openSpaces == size)
                    {
                        openSpaces = 0;
                        legalAnswer = true;
                        break;
                    }
                }
                else
                    openSpaces = 0;
            }
        } while (!legalAnswer);

        do
        {
            legalAnswer = false;
            positionX = rand() % (10 - size);
            for (int j = 0; j < size; j++)
            {
                // this checks if there will be enough open spaces at the row of positionY
                if (field[fieldType][positionX + j][positionY] != open)
                {
                    legalAnswer = false;
                    break;
                }
                else
                    legalAnswer = true;
            }
        } while (!legalAnswer);

        for (int j = 0; j < size; j++)
            field[fieldType][positionX + j][positionY] = 1;
    }
}
