#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

class Boat
{
private:

    char dir;
    int length;
    vector<int> boatrow;
    vector<int> boatcol;
    int hits;
    string name;

public:

    //Default contstructor
    Boat(char d, int lgth, vector<int> r, vector<int> c, int hit, string nme)
    {
        dir = d;
        length = lgth;
        boatrow = r;
        boatcol = c;
        hits = hit;
        name = nme;
    }

    //set boat hit
    void setHit()
    {
        hits++;
    }

    int checkSunk(int BoatSize)
    {
        if (hits >= BoatSize)
        {
            return 9;
        }
        else
        {
            return 0;
        }
    }

    //get boat playerGuess coordinates
    void boatCoordinates()
    {
        cout << "Coordinates for boat " << name << endl << endl;
        for (int i = 0; i < length; i++)
        {
            cout << "playerGuess [" << boatrow[i] << "][" << boatcol[i] << "]" << endl;
        }
        cout << endl;
    }

    //check coordinate bombed to find particular boat
    string getBoat(int r, int c)
    {
        for (int i = 0; i < length; i++)
        {
            if ((boatrow[i] == r) && (boatcol[i] == c))
            {
                return name;
            }
        }
        return "";
    }
};

enum BoatSize { Submarine = 3, Destroyer = 2, Battleship = 4, Carrier = 5, Cruiser = 3 };
enum BoatType { DESTROYER, SUBMARINE, CRUSIER, BATTLESHIP, CARRIER };
void initplayerGuess(int playerGuess[][10]);
void printBoard(int playerGuess[][10], int computerGuess[][10]);
void printComputerBoard(int computerGuess[][10]);
void printPlayerBoard(int playerGuess[][10]);
int resetColAndRow(int col, int& row, int BoatSize, char d);
char getDirection(int d);
int checkSpaces(int playerGuess[][10], int c, int r, int s, char d);
void editplayerGuess(int playerGuess[][10], int col, int row, int BoatSize, char dir);
bool setBoat(int computerGuess[][10], int BoatSize, int name, vector<Boat>& boatListPlayer);
bool placeBoat(int playerGuess[][10], int BoatSize, int name, vector<Boat>& boatListPlayer);
void editBoatInfo(int playerGuess[][10], int c, int r, int BoatSize, char d, vector<Boat>& boatListPlayer, int name);
void playGame(int playerGuess[][10], int computerGuess[][10], vector<Boat>& boatListPlayer, vector<Boat>& boatListComputer);
int getSpace(int playerGuess[][10], int row, int col);

int main()
{
    int playerGuess[10][10];
    int computerGuess[10][10];
    vector<Boat> boatListPlayer;
    vector<Boat> boatListComputer;
    char play;
    initplayerGuess(playerGuess);
    //    printBoard(playerGuess);  uncomment to see initialised playerGuess
    setBoat(playerGuess, Carrier, 1, boatListPlayer);  //set the boats onto the playerGuess
    setBoat(playerGuess, Battleship, 2, boatListPlayer);
    setBoat(playerGuess, Destroyer, 3, boatListPlayer);
    setBoat(playerGuess, Submarine, 4, boatListPlayer);
    setBoat(playerGuess, Cruiser, 5, boatListPlayer);
    cout << "Welcome to Battleships.  Press c to play the game" << endl << endl;
    placeBoat(computerGuess, Carrier, 1, boatListComputer);  //set the boats onto the playerGuess
    placeBoat(computerGuess, Battleship, 2, boatListComputer);
    placeBoat(computerGuess, Destroyer, 3, boatListComputer);
    placeBoat(computerGuess, Submarine, 4, boatListComputer);
    placeBoat(computerGuess, Cruiser, 5, boatListComputer);

    cout << "The board will show a H for a hit and a M for a miss" << endl << endl;
    cin >> play;
    if (play == 'c')
    {
        playGame(playerGuess, computerGuess, boatListPlayer, boatListComputer);
    }
    else
    {
        cout << "Unknown imput. Accepting this as a no to playing. Restart if there was a issue\n\n";
    }
    return 0;
}

void initplayerGuess(int playerGuess[][10])
{
    for (int col = 0; col < 10; col++) //Outer column loop
    {
        for (int row = 0; row < 10; row++) //Inner row loop
        {
            playerGuess[col][row] = 0;
        }
    }
}

void printBoard(int playerGuess[][10], int computerGuess[][10])  //Print the board with the boats placed on it
{
    cout << "   0|1|2|3|4|5|6|7|8|9" << endl << endl;
    for (int i = 0; i < 10; i++)  //column loop
    {
        for (int j = 0; j < 10; j++)  //row loop
        {
            if (j == 0)
            {
                cout << i << "  "; //print row number and spaces before new row
            }
            cout << playerGuess[i][j];
            if (j != 9)
            {
                cout << "|";
            }
        }
        cout << endl; //new line at end of column
    }
    cout << endl;
}
void printComputerBoard(int computerGuess[][10])
{
    cout << "   0|1|2|3|4|5|6|7|8|9" << endl << endl;
    for (int i = 0; i < 10; i++)  //column loop
    {
        for (int j = 0; j < 10; j++)  //row loop
        {
            if (j == 0)
            {
                cout << i << "  "; //print row number and spaces before new row
            }
            if (computerGuess[i][j] == 1)  //if the space is a hit, print it
            {
                cout << "H";
            }
            else if (computerGuess[i][j] == 9)  //if the space is a miss, print it
            {
                cout << "M";
            }
            else
            {
                cout << "~";  //otherwise, just print a 0
            }

            if (j != 9)
            {
                cout << "|";
            }
        }
        cout << endl; //new line at end of column
    }
    cout << endl;
}

void printPlayerBoard(int playerGuess[][10]) //This is the board that is printed for playing the game.  You cannot see the boats
{
    cout << "   0|1|2|3|4|5|6|7|8|9" << endl << endl;
    for (int i = 0; i < 10; i++)  //column loop
    {
        for (int j = 0; j < 10; j++)  //row loop
        {
            if (j == 0)
            {
                cout << i << "  "; //print row number and spaces before new row
            }
            if (playerGuess[i][j] == 1)  //if the space is a hit, print it
            {
                cout << "H";
            }
            else if (playerGuess[i][j] == 9)  //if the space is a miss, print it
            {
                cout << "M";
            }
            else
            {
                cout << "~";  //otherwise, just print a 0
            }

            if (j != 9)
            {
                cout << "|";
            }
        }
        cout << endl; //new line at end of column
    }
    cout << endl;
}

bool setBoat(int computerGuess[][10], int BoatSize, int name, vector<Boat>& boatListPlayer)
//This function places the individual boats onto the initialised playerGuess
{
    for (BoatType ship = DESTROYER; ship <= CARRIER; ship = BoatType(ship + 1))
    {
        //Generate a 1 or 2 randomly to determine to orient verically or horizontally.
        int ranShipOrientation = rand() % 2 + 1;
        int shipLength;

        switch (ship)
        {
        case DESTROYER:

            shipLength = 2;

            if (ranShipOrientation == 1)
                AddShipVertical(shipLength);
            else
                AddShipHorizontal(shipLength);

            break;

        case SUBMARINE:

            shipLength = 3;

            if (ranShipOrientation == 1)
                AddShipVertical(shipLength);
            else
                AddShipHorizontal(shipLength);

            break;

        case CRUSIER:

            shipLength = 3;

            if (ranShipOrientation == 1)
                AddShipVertical(shipLength);
            else
                AddShipHorizontal(shipLength);

            break;

        case BATTLESHIP:

            shipLength = 4;

            if (ranShipOrientation == 1)
                AddShipVertical(shipLength);
            else
                AddShipHorizontal(shipLength);

            break;

        case CARRIER:

            shipLength = 5;

            if (ranShipOrientation == 1)
                AddShipVertical(shipLength);
            else
                AddShipHorizontal(shipLength);

            break;
        }
    }
}

void AddShipVertical(int shipLength, int computerGuess[][10], )
{
    //This bool determines if the function body should be repeated with a new random number because the first random number caused overlap
    bool isShipOverlap;
    do
    {
        //Generate a random column index
        int ranColumn = rand() % 10;

        isShipOverlap = IsComputerShipOverlap(ranColumn, shipLength, UP);

        if (isShipOverlap == false) //If no ship is found in the validation read
        {
            for (shipLength; shipLength > 0; --shipLength)
            {
                computerGuess[shipLength][ranColumn] = '#';
            }
        }

    } while (isShipOverlap);
}

void AddShipHorizontal(int shipLength)
{
    //This bool determines if the function body should be repeated with a new random number because the first random number caused overlap
    bool isShipOverlap;
    do
    {
        //Generate a random row index
        int ranRow = rand() % 10;

        //IsComputerShipOverlap() will return a bool value that determines if there is ship overlap or not
        isShipOverlap = IsComputerShipOverlap(ranRow, shipLength, LEFT);

        //If there wasn't ship overlap
        if (isShipOverlap == false)
        {
            //creates ship horizontally
            for (shipLength; shipLength > 0; --shipLength)
            {
                computer.shipArray[ranRow][shipLength] = '#';
            }
        }
    } while (isShipOverlap);

}

bool IsComputerShipOverlap(int ranRowsorColumns, int shipLength, orientation shipDirection)
{
    if (shipDirection == UP) //Verifying if a column for a ship
    {
        //Does initial read of area where a ship will be added to check if a ship is already there.
        for (shipLength; shipLength > 0; --shipLength)
        {
            //Creates a ship vertically 
            if (computer.shipArray[shipLength][ranRowsorColumns] == '#')
            {
                return true;
            }
        }

        return false;
    }
    else if (shipDirection == LEFT) //verifying if a row for a ship
    {
        for (shipLength; shipLength > 0; --shipLength)
        {
            if (computer.shipArray[ranRowsorColumns][shipLength] == '#')
            {
                return true;
            }
        }

        return false;
    }
}

void ValidateUserInput(int& shipLength)
{
    //This bool is a loop control that is set to true if the user has overlapping ships or out-of-bounds ships
    bool isValidInput;

    //Identifiers for user input
    int row;
    int column;
    string shipOrientation;

    do
    {
        isValidInput = false;

        cout << "\nEnter the starting x-coordinate for your ship: ";
        cin >> column;

        //Loops while user provides invalid input
        while (!cin || column < 0 || column > 10)
        {
            cin.clear();
            cin.ignore(1000, '\n');

            InvalidInputMessage();
            cin >> column;
        }

        cout << "\nEnter the starting y-coordinate for your ship: ";
        cin >> row;

        //Loops while user provides invalid input
        while (!cin || row < 0 || row > 10)
        {
            cin.clear();
            cin.ignore(1000, '\n');

            InvalidInputMessage();
            cin >> row;
        }

        cout << "\nEnter the orientation you want your ship to have (\"up\", \"down\", \"left\", or \"right\"): ";
        cin >> shipOrientation;

        //While the first letter of shipOrientation string is NOT equal to U, D, R, or L
        while (toupper(shipOrientation[0]) != 'U' && toupper(shipOrientation[0]) != 'D' && toupper(shipOrientation[0]) != 'L' && toupper(shipOrientation[0]) != 'R')
        {
            cout << "\n\nInvalid input - input should be one of the following (\"up\", \"down\", \"left\", or \"right\")\a\n";
            cout << "Try again: ";
            cin >> shipOrientation;
        }

        //These are decremented by one from the values the user entered (1 - 10). This way they function as indexes for the gameboard array which has valid indexes of 0 - 9 for the coming function calls.
        row--;
        column--;

        //Checks for out of array bounds or ship overlap
        isValidInput = IsValidOrientation(row, column, shipOrientation, shipLength);

        //If input array indexes are not invalid
        if (isValidInput == true)
            PlaceUserShip(row, column, shipLength, shipOrientation);

    } while (!isValidInput); //If overlap or out-of-array bounds then this function loops until the user enters valid data
}

bool placeBoat(int playerGuess[][10], int BoatSize, int name, vector<Boat>& boatListPlayer)
{
    int col = 0;
    int row = 0;
    char d = 'v';
    bool placementFailure = true;
    char check = 'v';
    int cS = 0;
    cout << "Choose where to place " << name << "First input h for horizontal or v for vertical\n";
    cin >> d;
    cout << "Now choose the coordinate to center it ussing two numbers between 0 and 9(Ex: 1,2 or 1 2)";
    cin >> col >> row;
    while (placementFailure)
    {
        if (d == 'h')
        {
            cS = checkSpaces(playerGuess, col, row, BoatSize, d);//check to make sure the boat can be placed without overlapping another boat
            if (cS == 1)//if the boat overlaps, generate another random column, row and direction and start the loop again
            {
                cout << "Choose a new placement this one is overlaping(Ex: h, 1, 2 or v, 5, 8)";
                cin >> d >> col >> row;
                continue;
            }
            editplayerGuess(playerGuess, col, row, BoatSize, d);//place the boat on the playerGuess
            editBoatInfo(playerGuess, col, row, BoatSize, d, boatListPlayer, name);//create the boat object
            return 0;
        }//end of 'if horizontal'
        else if (d == 'v')
        {
            cS = checkSpaces(playerGuess, col, row, BoatSize, d);
            if (cS == 1)
            {
                cout << "Choose a new placement this one is overlaping(Ex: h, 1, 2 or v, 5, 8)";
                cin >> d >> col >> row;
                continue;
            }
            editplayerGuess(playerGuess, col, row, BoatSize, d);
            editBoatInfo(playerGuess, col, row, BoatSize, d, boatListPlayer, name);
            return 0;
        }
    }
}

char getDirection(int d)
{
    if (d > 4)
    {
        return 'h';  //randomly pick which direction to place boat
    }
    else
    {
        return 'v';
    }
}

void editplayerGuess(int playerGuess[][10], int col, int row, int BoatSize, char dir)
//This function puts the numbers that correspond to the boat type on the playerGuess
{
    if (dir == 'h')
    {
        for (int i = 0; i < BoatSize; i++)
        {
            playerGuess[row][col] = BoatSize;
            col++;
            cout << endl;
        }
    }
    else if (dir == 'v')
    {
        for (int i = 0; i < BoatSize; i++)
        {
            playerGuess[row][col] = BoatSize;
            row++;
            cout << endl;
        }
    }
    else
    {
        cout << "Error!  No direction passed" << endl;
    }
    //printBoard(playerGuess);  //uncomment to see finished playerGuess
}

int checkSpaces(int playerGuess[][10], int c, int r, int s, char d)
//check the playerGuess to make sure that none of the boats will overlap
{
    int check = 0;
    if (d == 'h')
    {
        for (int i = c; i < c + s; i++)
        {
            check = playerGuess[r][i];
            if (check != 0)
            {
                return 1;
            }
        }

        return 0;
    }
    else
    {
        for (int i = r; i < r + s; i++)
        {
            check = playerGuess[i][c];
            if (check != 0)
            {
                return 1;

            }
        }

        return 0;
    }
}

int resetColAndRow(int col, int& row, int BoatSize, char d)
{
    switch (BoatSize) //Generate random column and row based on boat size so we don't go over the edge of the playerGuess
    {
    case Submarine || Cruiser:
        if (d == 'h')
        {
            col = rand() % 8;
            row = rand() % 10;
        }
        else
        {
            col = rand() % 10;
            row = rand() % 8;
        }
        break;
    case Destroyer:
        if (d == 'h')
        {
            col = rand() % 7;
            row = rand() % 10;
        }
        else
        {
            col = rand() % 10;
            row = rand() % 7;
        }
        break;
    case Battleship:
        if (d == 'h')
        {
            col = rand() % 6;
            row = rand() % 10;
        }
        else
        {
            col = rand() % 10;
            row = rand() % 6;
        }
        break;
    case Carrier:
        if (d == 'h')
        {
            col = rand() % 5;
            row = rand() % 10;
        }
        else
        {
            col = rand() % 10;
            row = rand() % 5;
        }
    }
    return col;
}

void editBoatInfo(int playerGuess[][10], int c, int r, int BoatSize, char d, vector<Boat>& boatListPlayer, int name)
{
    switch (name)
    {
    case 1:
        if (d == 'h')
        {
            vector<int> r1(5);
            //  put coordinate data into the vectors using at()
            for (int i = 0; i < (int)r1.size(); ++i)
            {
                r1.at(i) = r;
            }
            vector<int> c1(5);
            for (int i = 0; i < (int)c1.size(); ++i)
            {
                c1.at(i) = c;
                c++;
            }
            //Aircraft Carrier
            Boat carrierBoat('h', 5, r1, c1, 0, "Aircraft Carrier");
            boatListPlayer.push_back(carrierBoat);
        }
        else if (d == 'v')
        {
            vector<int> r1(5);
            for (int i = 0; i < (int)r1.size(); ++i)
            {
                r1.at(i) = r;
                r++;
            }
            vector<int> c1(5);
            for (int i = 0; i < (int)c1.size(); ++i)
            {
                c1.at(i) = c;
            }
            //Aircraft Carrier
            Boat carrierBoat('v', 5, r1, c1, 0, "Aircraft Carrier");
            boatListPlayer.push_back(carrierBoat);
        }
        break;
    case 2:
        if (d == 'h')
        {
            vector<int> r1(4);
            for (int i = 0; i < (int)r1.size(); ++i)
            {
                r1.at(i) = r;
            }
            vector<int> c1(4);
            for (int i = 0; i < (int)c1.size(); ++i)
            {
                c1.at(i) = c;
                c++;
            }
            //Battleship 1
            Boat battleship1Boat('h', 4, r1, c1, 0, "Battleship 1");
            boatListPlayer.push_back(battleship1Boat);
        }
        else if (d == 'v')
        {
            vector<int> r1(4);
            for (int i = 0; i < (int)r1.size(); ++i)
            {
                r1.at(i) = r;
                r++;
            }
            vector<int> c1(4);
            for (int i = 0; i < (int)c1.size(); ++i)
            {
                c1.at(i) = c;
            }
            //Battleship 1
            Boat battleship1Boat('v', 4, r1, c1, 0, "Battleship 1");
            boatListPlayer.push_back(battleship1Boat);
        }
        break;
    case 3:
        if (d == 'h')
        {
            vector<int> r1(3);
            for (int i = 0; i < (int)r1.size(); ++i)
            {
                r1.at(i) = r;
            }
            vector<int> c1(3);
            for (int i = 0; i < (int)c1.size(); ++i)
            {
                c1.at(i) = c;
                c++;
            }
            //Destroyer 1
            Boat destroyer1Boat('h', 3, r1, c1, 0, "Destroyer 1");
            boatListPlayer.push_back(destroyer1Boat);
        }
        else if (d == 'v')
        {
            vector<int> r1(3);
            for (int i = 0; i < (int)r1.size(); ++i)
            {
                r1.at(i) = r;
                r++;
            }
            vector<int> c1(3);
            for (int i = 0; i < (int)c1.size(); ++i)
            {
                c1.at(i) = c;
            }
            //Destroyer 1
            Boat destroyer1Boat('v', 3, r1, c1, 0, "Destroyer 1");
            boatListPlayer.push_back(destroyer1Boat);
        }
        break;
    case 4:
        if (d == 'h')
        {
            vector<int> r1(2);
            for (int i = 0; i < (int)r1.size(); ++i)
            {
                r1.at(i) = r;
            }
            vector<int> c1(2);
            for (int i = 0; i < (int)c1.size(); ++i)
            {
                c1.at(i) = c;
                c++;
            }
            //Submarine1
            Boat submarine1Boat('h', 2, r1, c1, 0, "Submarine 1");
            boatListPlayer.push_back(submarine1Boat);
        }
        else if (d == 'v')
        {
            vector<int> r1(2);
            for (int i = 0; i < (int)r1.size(); ++i)
            {
                r1.at(i) = r;
                r++;
            }
            vector<int> c1(2);
            for (int i = 0; i < (int)c1.size(); ++i)
            {
                c1.at(i) = c;
            }
            //Submarine 1
            Boat submarine1Boat('v', 2, r1, c1, 0, "Submarine 1");
            boatListPlayer.push_back(submarine1Boat);
        }
        break;
    case 5:
        if (d == 'h')
        {
            vector<int> r1(2);
            for (int i = 0; i < (int)r1.size(); ++i)
            {
                r1.at(i) = r;
            }
            vector<int> c1(2);
            for (int i = 0; i < (int)c1.size(); ++i)
            {
                c1.at(i) = c;
                c++;
            }
            //Cruiser 1
            Boat cruiser1Boat('h', 2, r1, c1, 0, "Cruiser 1");
            boatListPlayer.push_back(cruiser1Boat);
        }
        else if (d == 'v')
        {
            vector<int> r1(2);
            for (int i = 0; i < (int)r1.size(); ++i)
            {
                r1.at(i) = r;
                r++;
            }
            vector<int> c1(2);
            for (int i = 0; i < (int)c1.size(); ++i)
            {
                c1.at(i) = c;
            }
            //Cruiser 1
            Boat cruiser1Boat('v', 2, r1, c1, 0, "Cruiser 1");
            boatListPlayer.push_back(cruiser1Boat);
        }
        break;
    case 6:
        if (d == 'h')
        {
            vector<int> r1(5);
            //  put coordinate data into the vectors using at()
            for (int i = 0; i < (int)r1.size(); ++i)
            {
                r1.at(i) = r;
            }
            vector<int> c1(5);
            for (int i = 0; i < (int)c1.size(); ++i)
            {
                c1.at(i) = c;
                c++;
            }
            //Aircraft Carrier
            Boat carrierBoat('h', 5, r1, c1, 0, "Aircraft Carrier");
            boatListPlayer.push_back(carrierBoat);
        }
        else if (d == 'v')
        {
            vector<int> r1(5);
            for (int i = 0; i < (int)r1.size(); ++i)
            {
                r1.at(i) = r;
                r++;
            }
            vector<int> c1(5);
            for (int i = 0; i < (int)c1.size(); ++i)
            {
                c1.at(i) = c;
            }
            //Aircraft Carrier
            Boat carrierBoat('v', 5, r1, c1, 0, "Aircraft Carrier");
            boatListPlayer.push_back(carrierBoat);
        }
        break;
    case 7:
        if (d == 'h')
        {
            vector<int> r1(4);
            for (int i = 0; i < (int)r1.size(); ++i)
            {
                r1.at(i) = r;
            }
            vector<int> c1(4);
            for (int i = 0; i < (int)c1.size(); ++i)
            {
                c1.at(i) = c;
                c++;
            }
            //Battleship 1
            Boat battleship1Boat('h', 4, r1, c1, 0, "Battleship 1");
            boatListPlayer.push_back(battleship1Boat);
        }
        else if (d == 'v')
        {
            vector<int> r1(4);
            for (int i = 0; i < (int)r1.size(); ++i)
            {
                r1.at(i) = r;
                r++;
            }
            vector<int> c1(4);
            for (int i = 0; i < (int)c1.size(); ++i)
            {
                c1.at(i) = c;
            }
            //Battleship 1
            Boat battleship1Boat('v', 4, r1, c1, 0, "Battleship 1");
            boatListPlayer.push_back(battleship1Boat);
        }
        break;
    case 8:
        if (d == 'h')
        {
            vector<int> r1(3);
            for (int i = 0; i < (int)r1.size(); ++i)
            {
                r1.at(i) = r;
            }
            vector<int> c1(3);
            for (int i = 0; i < (int)c1.size(); ++i)
            {
                c1.at(i) = c;
                c++;
            }
            //Destroyer 1
            Boat destroyer1Boat('h', 3, r1, c1, 0, "Destroyer 1");
            boatListPlayer.push_back(destroyer1Boat);
        }
        else if (d == 'v')
        {
            vector<int> r1(3);
            for (int i = 0; i < (int)r1.size(); ++i)
            {
                r1.at(i) = r;
                r++;
            }
            vector<int> c1(3);
            for (int i = 0; i < (int)c1.size(); ++i)
            {
                c1.at(i) = c;
            }
            //Destroyer 1
            Boat destroyer1Boat('v', 3, r1, c1, 0, "Destroyer 1");
            boatListPlayer.push_back(destroyer1Boat);
        }
        break;
    case 9:
        if (d == 'h')
        {
            vector<int> r1(2);
            for (int i = 0; i < (int)r1.size(); ++i)
            {
                r1.at(i) = r;
            }
            vector<int> c1(2);
            for (int i = 0; i < (int)c1.size(); ++i)
            {
                c1.at(i) = c;
                c++;
            }
            //Submarine1
            Boat submarine1Boat('h', 2, r1, c1, 0, "Submarine 1");
            boatListPlayer.push_back(submarine1Boat);
        }
        else if (d == 'v')
        {
            vector<int> r1(2);
            for (int i = 0; i < (int)r1.size(); ++i)
            {
                r1.at(i) = r;
                r++;
            }
            vector<int> c1(2);
            for (int i = 0; i < (int)c1.size(); ++i)
            {
                c1.at(i) = c;
            }
            //Submarine 1
            Boat submarine1Boat('v', 2, r1, c1, 0, "Submarine 1");
            boatListPlayer.push_back(submarine1Boat);
        }
        break;
    case 10:
        if (d == 'h')
        {
            vector<int> r1(2);
            for (int i = 0; i < (int)r1.size(); ++i)
            {
                r1.at(i) = r;
            }
            vector<int> c1(2);
            for (int i = 0; i < (int)c1.size(); ++i)
            {
                c1.at(i) = c;
                c++;
            }
            //Cruiser 1
            Boat cruiser1Boat('h', 2, r1, c1, 0, "Cruiser 1");
            boatListPlayer.push_back(cruiser1Boat);
        }
        else if (d == 'v')
        {
            vector<int> r1(2);
            for (int i = 0; i < (int)r1.size(); ++i)
            {
                r1.at(i) = r;
                r++;
            }
            vector<int> c1(2);
            for (int i = 0; i < (int)c1.size(); ++i)
            {
                c1.at(i) = c;
            }
            //Cruiser 1
            Boat cruiser1Boat('v', 2, r1, c1, 0, "Cruiser 1");
            boatListPlayer.push_back(cruiser1Boat);
        }
        break;
    }
}

void playGame(int playerGuess[][10], int computerGuess[][10], vector<Boat>& boatListPlayer, vector<Boat>& boatListComputer)
{
    bool gameInProgress = true;
    int row = 0;
    int col = 0;
    int guess = 0;
    int hit = 0;
    int miss = 0;
    int space = 0;
    char d = 'g';
    string btname = "";
    int sunk = 0;

    while (gameInProgress)
    {
        printPlayerBoard(playerGuess);
        //printBoard(playerGuess);  //uncomment to see the game board with the boats on it

        srand((unsigned)time(0));
        row = 1 + (rand() % 10);
        col = 1 + (rand() % 10);

        space = getSpace(computerGuess, row, col);

        switch (space)
        {
        case 0:
            computerGuess[row][col] = 9;
            miss++;
            break;
        case 1:
            break;
        case 2:
            computerGuess[row][col] = 1;
            hit++;

            btname = boatListPlayer[3].getBoat(row, col);  //Check to see if boat is Submarine 1
            if (btname == "Submarine 1")
            {
                boatListPlayer[3].setHit();
                sunk = boatListPlayer[3].checkSunk(Submarine);
                if (sunk == 9)
                {
                    cout << "Computer has sunk Submarine 1." << endl;
                }
            }
            else if (btname.empty())
            {
                btname = boatListPlayer[4].getBoat(row, col);  //Check to see if boat is Submarine 4
                boatListPlayer[4].setHit();
                sunk = boatListPlayer[4].checkSunk(Cruiser);
                if (sunk == 9)
                {
                    cout << "Computer has sunk Cruiser 1." << endl;
                }
            }
            btname.clear();
            break;
        case 3:
            computerGuess[row][col] = 1;
            hit++;

            btname = boatListPlayer[2].getBoat(row, col);  //Check to see if boat is Destroyer 1
            if (btname == "Destroyer 1")
            {
                boatListPlayer[2].setHit();
                sunk = boatListPlayer[2].checkSunk(Destroyer);
                if (sunk == 9)
                {
                    cout << "Computer has sunk Destroyer 1." << endl;
                }
            }
            btname.clear();
            break;
        case 4:
            computerGuess[row][col] = 1;
            hit++;

            btname = boatListPlayer[1].getBoat(row, col);  //Check to see if boat is Battleship 1
            if (btname == "Battleship 1")
            {
                boatListPlayer[1].setHit();
                sunk = boatListPlayer[1].checkSunk(Battleship);
                if (sunk == 9)
                {
                    cout << "Computer has sunk Battleship 1." << endl;
                }
            }
            btname.clear();
            break;
        case 5:
            computerGuess[row][col] = 1;
            hit++;
            boatListPlayer[0].setHit();
            sunk = boatListPlayer[0].checkSunk(Carrier);
            if (sunk == 9)
            {
                cout << "Computer has sunk the aircraft carrier." << endl;
            }
            break;
        }//end of switch


        cout << "Enter a row coordinate to hit: ";
        cin >> row;
        cout << "Enter a column coordinate to hit: ";
        cin >> col;
        cout << endl;
        guess++;
        space = getSpace(playerGuess, row, col);
        switch (space)
        {
        case 0:
            cout << "You have missed" << endl;
            playerGuess[row][col] = 9;
            miss++;
            break;
        case 1:
            cout << "This space has already been bombed.  Your guess was wasted!" << endl;
            break;
        case 2:
            playerGuess[row][col] = 1;
            hit++;

            btname = boatListComputer[3].getBoat(row, col);  //Check to see if boat is Submarine 1
            if (btname == "Submarine 1")
            {
                cout << "You have bombed " << btname << "!" << endl;
                boatListComputer[3].setHit();
                sunk = boatListComputer[3].checkSunk(Submarine);
                if (sunk == 9)
                {
                    cout << "You have sunk Submarine 1." << endl;
                }
            }
            else if (btname.empty())
            {
                btname = boatListComputer[4].getBoat(row, col);  //Check to see if boat is Submarine 4
                cout << "You have bombed " << btname << "!" << endl;
                boatListComputer[4].setHit();
                sunk = boatListComputer[4].checkSunk(Cruiser);
                if (sunk == 9)
                {
                    cout << "You have sunk Cruiser 1." << endl;
                }
            }

            btname.clear();
            break;
        case 3:
            playerGuess[row][col] = 1;
            hit++;

            btname = boatListComputer[2].getBoat(row, col);  //Check to see if boat is Destroyer 1
            if (btname == "Destroyer 1")
            {
                cout << "You have bombed " << btname << "!" << endl;
                boatListComputer[2].setHit();
                sunk = boatListComputer[2].checkSunk(Destroyer);
                if (sunk == 9)
                {
                    cout << "You have sunk Destroyer 1." << endl;
                }
            }
            btname.clear();
            break;
        case 4:
            playerGuess[row][col] = 1;
            hit++;

            btname = boatListComputer[1].getBoat(row, col);  //Check to see if boat is Battleship 1
            if (btname == "Battleship 1")
            {
                cout << "You have bombed " << btname << "!" << endl;
                boatListComputer[1].setHit();
                sunk = boatListComputer[1].checkSunk(Battleship);
                if (sunk == 9)
                {
                    cout << "You have sunk Battleship 1." << endl;
                }
            }
            btname.clear();
            break;
        case 5:
            cout << "You have bombed the aircraft carrier! " << endl;
            playerGuess[row][col] = 1;
            hit++;
            boatListComputer[0].setHit();
            sunk = boatListComputer[0].checkSunk(Carrier);
            if (sunk == 9)
            {
                cout << "You have sunk the aircraft carrier." << endl;
            }
            break;
        }//end of switch
        if (hit == 30)
        {
            gameInProgress = false;
        }
    }//end of while game is playing loop

    cout << "Thank you for playing!  You have sunk all my battleships in " << guess << " moves!" << endl;

}//end of playGame function

int getSpace(int playerGuess[][10], int row, int col)
{
    int space = 0;
    space = playerGuess[row][col];
    return space;
}