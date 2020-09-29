
/*
ALGORITHM
1.declare variables, write function prototypes
2.initialize character array to '?' and initialize bool array to false
3. use the rand function to randomly place mines in the bool array,
     implements those locations into  variables into the bool array as true
4. create a loop that prints out the current game board
    then prompt user for location to dig into an x and y variable
5. put those x and y in the array as a location to 'dig'
6. check those locations to see if the are mines there or if that location
    in the bool array was true
        -if it was true, the game would end because user had 'dug' up a mine
        -if it was false, the game would continue as usual
7. user/player would win if they've dug up every place that did not have a mine, 
    if there were 10 mines, then there should be 10 '?' left in the game. 
    That would indicate the player has won

*/

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

struct tile
{
    char letter;
    bool hasmine;
};

struct minesweeper
{
    tile board[9][12]; //board
    int width;
    int height;
    int minecount;
    int flagcount;
    int unrevealedcount;
    int moves;
};
void displayboard(minesweeper game);
void displaymines(minesweeper game);
bool hasplayerwon(minesweeper game);

//const int height = 12;
//const int width = 9;

int main(int argc, char *argv[])
{
    minesweeper game;
    game.width = 12;
    game.height = 9;
    game.moves = 1;
    game.flagcount = 0;
    game.minecount = 0;
    game.unrevealedcount = 0;
    //arrays
    //char chararray[9][12];
    //bool boolarray[9][12];

    bool validxy = true;
    bool toDig = false;
    //bool flagexists = false;
    char action;
    int flagx = 0;
    int flagy = 0;
    //bool mineexists = false;
    //int mineexistscount = 0;
    //width/height
    //int width = 12, height = 9;

    //x and y?
    int x = 0, y = 0, truecount = 0;

    //initialize random number generator?
    srand(time(NULL));

    //dig x and y?
    int digx = 0, digy = 0;

    //mines
    bool checkagain = true;
    int minecount = 0;

    int x1 = 0, y1 = 0;

    //for debug mode srand will be seeded 0
    if (argc > 1)
        srand(0);

    //initialize all arrays to false and '?'
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            game.board[i][j].letter = '?';
            //cout << chararray[i][j] << " ";
        }
        //cout << endl;
    }

    //initialize bool array to false
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            game.board[i][j].hasmine = false;
            //cout << boolarray[i][j] << " ";
        }
        //cout << endl;
    }
    //random mine generator
    while (truecount < 10)
    {
        x = rand() % 12;
        y = rand() % 9;
        //cout << x << " " << y << endl;
        if (game.board[y][x].hasmine == false)
        {
            game.board[y][x].hasmine = true;
            //cout << x << " " << y << endl;
            truecount++;
        }
    }

    //displaymines(game);
    //cout << "amount of true's: " << truecount << endl;
    //start large loop here, loop only ends when player wins or digs up a mine and loses
    while (!hasplayerwon(game))
    {
        displayboard(game);

        //display menu that prompts user for option
        cout << endl
             << "Move " << game.moves << endl;
        cout << "[D]ig up Tile" << endl;
        cout << "[F]lag/Unflag Tile. " << game.flagcount << " flag(s) placed." << endl;
        cout << "[Q]uit" << endl;
        cout << "Choose an action: ";
        cin >> action;

        switch (action)
        {
        case 'd':
        case 'D':
            toDig = true;
            game.moves++;
            break;

        case 'f':
        case 'F':
            cout << "Place flag at:" << endl;
            do
            {
                cout << "X: ";
                cin >> flagx;
            } while (!(flagx <= 12 && flagx >= 1));

            do
            {
                cout << "Y: ";
                cin >> flagy;
            } while (!(flagy <= 9 && flagy >= 1));

            if(game.board[flagy - 1][flagx -1].letter == '?')
            {
                game.board[flagy - 1][flagx - 1].letter = 'P'; //creating segfault
                //flagexists = true;
                game.flagcount++;
            }
            else
            {
                game.board[flagy - 1][flagx - 1].letter = '?';
                game.flagcount--;
            }
            
            //displayboard(game);
            
            break;

        case 'q':
        case 'Q':
            cout << "Quitting.." << endl;
            exit(0);
            break;

        default:
            cout << "Invalid input.." << endl;
            cout << "Quitting..\n"
                 << endl;
            exit(0);
        }

        //resets validxy so that it will always run once
        validxy = true;

        while (validxy && toDig)
        {

            cout << "Dig at X: ";
            cin >> digx;

            //check to proper range of input for digx
            //can't be less than 0 or greater than 12
            while (1 > digx || digx > 12)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid range - try again" << endl;
                cout << "Dig at X: ";
                cin >> digx;
            }

            cout << "Dig at Y: ";
            cin >> digy;

            //check to proper range of input for digy
            while (1 > digy || digy > 9)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid range - try again" << endl;
                cout << "Dig at Y: ";
                cin >> digy;
            }
            //if x y location is a question mark then allow to pass through
            if (game.board[digy - 1][digx - 1].letter == '?')
            {
                validxy = false;
                toDig = false;
            }
            else //else loop will run through again until valid points are entered
            {
                cout << "Cannot dig there - try again" << endl;
                validxy = true;
                toDig = true;
            }

            cout << endl;
            
        }
        //take user input and implement into array to set to 'C'
        game.board[digy - 1][digx - 1].letter = 'c';
        //displayboard(chararray, width, height);

        //check for mine in the array location
        if (game.board[digy - 1][digx - 1].hasmine == true)
        {
            //print out the mine board
            displaymines(game);
            //end game if mine was dug up
            cout << "You hit a mine!  Game over." << endl;
            //end the game
            return 0;
        }
        //so that loop will run again after the first time
        checkagain = true;

        //check for mines nested loops (3)
        while (checkagain == true)
        {
            checkagain = false;

            for (int i = 0; i < game.height; i++)
            {
                for (int j = 0; j < game.width; j++)
                {

                    //when the element is the character array is equal to c
                    if (game.board[i][j].letter == 'c')
                    {
                        minecount = 0;
                        //cout << " current: " << j + 1 << "," << i + 1 << endl;
                        //checkagain = false;
                        //8 checks for mines around 'c' location in char array
                        //checking for bounds in array
                        y1 = i - 1;
                        x1 = j;
                        if (y1 >= 0 && y1 < 9 && x1 >= 0 && x1 < 12)
                        {
                            //cout << "a checked: " << x1 + 1 << "," << y1 + 1 << endl;
                            if (game.board[i - 1][j].hasmine == true) //1 above location
                            {
                                //cout << "mine: " << x1 + 1 << "," << y1 + 1 << endl;
                                minecount++;
                                //checkagain = false;
                            }
                        }
                        y1 = 0;
                        x1 = 0;
                        y1 = i + 1;
                        x1 = j;
                        if (y1 >= 0 && y1 < 9 && x1 >= 0 && x1 < 12)
                        {
                            //cout << "b checked: " << x1 + 1 << "," << y1 + 1 << endl;
                            if (game.board[i + 1][j].hasmine == true) //1 below location
                            {
                                //cout << "mine: " << x1 + 1 << "," << y1 + 1 << endl;
                                minecount++;
                                //checkagain = false;
                            }
                        }
                        y1 = 0;
                        x1 = 0;
                        y1 = i;
                        x1 = j - 1;
                        if (y1 >= 0 && y1 < 9 && x1 >= 0 && x1 < 12)
                        {
                            //cout << "c checked: " << x1 + 1 << "," << y1 + 1 << endl;
                            if (game.board[i][j - 1].hasmine == true) //1 left of location
                            {
                                //cout << "mine: " << x1 + 1 << "," << y1 + 1 << endl;
                                minecount++;
                            }
                        }
                        y1 = 0;
                        x1 = 0;
                        y1 = i;
                        x1 = j + 1;
                        if (y1 >= 0 && y1 < 9 && x1 >= 0 && x1 < 12)
                        {
                            //cout << "d checked: " << x1 + 1 << "," << y1 + 1 << endl;
                            if (game.board[i][j + 1].hasmine == true) //1 right of location
                            {
                                //cout << "mine: " << x1 + 1 << "," << y1 + 1 << endl;
                                minecount++;
                            }
                        }
                        y1 = 0;
                        x1 = 0;
                        y1 = i - 1;
                        x1 = j - 1;
                        if (y1 >= 0 && y1 < 9 && x1 >= 0 && x1 < 12)
                        {
                            //cout << "e checked: " << x1 + 1 << "," << y1 + 1 << endl;
                            if (game.board[i - 1][j - 1].hasmine == true) //Upper left diagonal
                            {
                                //cout << "mine: " << x1 + 1 << "," << y1 + 1 << endl;
                                minecount++;
                            }
                        }
                        y1 = 0;
                        x1 = 0;
                        y1 = i + 1;
                        x1 = j + 1;
                        if (y1 >= 0 && y1 < 9 && x1 >= 0 && x1 < 12)
                        {
                            //cout << "f checked: " << x1 + 1 << "," << y1 + 1 << endl;
                            if (game.board[i + 1][j + 1].hasmine == true) //Lower right diagonal
                            {
                                //cout << "mine: " << x1 + 1 << "," << y1 + 1 << endl;
                                minecount++;
                            }
                        }
                        y1 = 0;
                        x1 = 0;
                        y1 = i + 1;
                        x1 = j - 1;
                        if (y1 >= 0 && y1 < 9 && x1 >= 0 && x1 < 12)
                        {
                            //cout << "g checked: " << x1 + 1 << "," << y1 + 1 << endl;
                            if (game.board[i + 1][j - 1].hasmine == true) //Lower left diagonal
                            {
                                //cout << "mine: " << x1 + 1 << "," << y1 + 1 << endl;
                                minecount++;
                            }
                        }
                        y1 = 0;
                        x1 = 0;
                        y1 = i - 1;
                        x1 = j + 1;
                        if (y1 >= 0 && y1 < 9 && x1 >= 0 && x1 < 12)
                        {
                            //cout << "h checked: " << x1 + 1 << "," << y1 + 1 << endl;
                            if (game.board[i - 1][j + 1].hasmine == true) //Upper right diagonal
                            {
                                //cout << "mine: " << x1 + 1 << "," << y1 + 1 << endl;
                                minecount++;
                            }
                        }

                        if (minecount > 0) //if mines exist around c
                        {
                            game.board[i][j].letter = ('0' + minecount);
                        }

                        if (minecount == 0)
                        {
                            game.board[i][j].letter = ' ';

                            y1 = 0;
                            x1 = 0;
                            y1 = i - 1;
                            x1 = j;
                            if (y1 >= 0 && y1 < 9 && x1 >= 0 && x1 < 12)
                            {
                                if (game.board[i - 1][j].letter == '?') //1 above location
                                {
                                    game.board[i - 1][j].letter = 'c';
                                    checkagain = true;
                                }
                            }
                            y1 = 0;
                            x1 = 0;
                            y1 = i + 1;
                            x1 = j;
                            if (y1 >= 0 && y1 < 9 && x1 >= 0 && x1 < 12)
                            {
                                if (game.board[i + 1][j].letter == '?') //1 below location
                                {
                                    game.board[i + 1][j].letter = 'c';
                                    checkagain = true;
                                }
                            }
                            y1 = 0;
                            x1 = 0;
                            y1 = i;
                            x1 = j - 1;
                            if (y1 >= 0 && y1 < 9 && x1 >= 0 && x1 < 12)
                            {
                                if (game.board[i][j - 1].letter == '?') //1 left of location
                                {
                                    game.board[i][j - 1].letter = 'c';
                                    checkagain = true;
                                }
                            }
                            y1 = 0;
                            x1 = 0;
                            y1 = i;
                            x1 = j + 1;
                            if (y1 >= 0 && y1 < 9 && x1 >= 0 && x1 < 12)
                            {
                                if (game.board[i][j + 1].letter == '?') //1 right of location
                                {
                                    game.board[i][j + 1].letter = 'c';
                                    checkagain = true;
                                }
                            }
                            y1 = 0;
                            x1 = 0;
                            y1 = i - 1;
                            x1 = j - 1;
                            if (y1 >= 0 && y1 < 9 && x1 >= 0 && x1 < 12)
                            {
                                if (game.board[i - 1][j - 1].letter == '?') //Upper left diagonal
                                {
                                    game.board[i - 1][j - 1].letter = 'c';
                                    checkagain = true;
                                }
                            }
                            y1 = 0;
                            x1 = 0;
                            y1 = i + 1;
                            x1 = j + 1;
                            if (y1 >= 0 && y1 < 9 && x1 >= 0 && x1 < 12)
                            {
                                if (game.board[i + 1][j + 1].letter == '?') //Lower right diagonal
                                {
                                    game.board[i + 1][j + 1].letter = 'c';
                                    checkagain = true;
                                }
                            }
                            y1 = 0;
                            x1 = 0;
                            y1 = i + 1;
                            x1 = j - 1;
                            if (y1 >= 0 && y1 < 9 && x1 >= 0 && x1 < 12)
                            {
                                if (game.board[i + 1][j - 1].letter == '?') //Lower left diagonal
                                {
                                    game.board[i + 1][j - 1].letter = 'c';
                                    checkagain = true;
                                }
                            }
                            y1 = 0;
                            x1 = 0;
                            y1 = i - 1;
                            x1 = j + 1;
                            if (y1 >= 0 && y1 < 9 && x1 >= 0 && x1 < 12)
                            {
                                if (game.board[i - 1][j + 1].letter == '?') //Upper right diagonal
                                {
                                    game.board[i - 1][j + 1].letter = 'c';
                                    checkagain = true;
                                }
                            }
                        }
                    }
                }
            }
        }

        //displaymines(game);
    }

    //displayboard(chararray, width, height);
}

/*
ALGORITHM
1. print out x axis
2. print out the horizontal lines 
3. print out array
    a.nested loop to print out whatevers in the array

*/
void displayboard(minesweeper game)
{
    cout << " ";
    //numbers on x axis
    for (int i = 1; i <= game.width; i++)
    {
        cout << setw(4) << i;

        if (i == game.width)
            cout << endl;
    }
    //grid shape
    for (int i = 1; i <= game.width; i++)
    {
        if (i == 1)
            cout << "  ";

        cout << "+---";

        if (i == game.width)
            cout << "+" << endl;
    }

    //board outline
    for (int i = 0; i < 9; i++)
    {
        cout << i + 1; //prints out y axis index
        //prints out the 'lines'
        for (int j = 0; j < 12; j++)
        {
            cout << " | " << game.board[i][j].letter;
            if (j == 11)
                cout << " ";
        }
        cout << "|" << endl;

        //prints out the x lines +---+
        for (int i = 1; i <= game.width; i++)
        {
            if (i == 1)
                cout << "  ";

            cout << "+---";

            if (i == game.width)
                cout << "+" << endl;
        }
    }
    return;
}

/*
ALGORITHM
1. print out x axis
2. print out the horizontal lines 
3. print out array
    a. if the array position equals false, then print out a space
    b. if array position equals true, then print out a asterisk
    c. print out horizontal lines at the end of each row


*/
void displaymines(minesweeper game)
{

    //printing out bool array to see what's true and which is false
    cout << " ";
    //numbers on x axis
    for (int i = 1; i <= game.width; i++)
    {
        cout << setw(4) << i;

        if (i == game.width)
            cout << endl;
    }
    //grid shape
    for (int i = 1; i <= game.width; i++)
    {
        if (i == 1)
            cout << "  ";

        cout << "+---";

        if (i == game.width)
            cout << "+" << endl;
    }

    //board outline
    for (int i = 0; i < 9; i++)
    {
        cout << i + 1; //prints out y axis index
        //prints out the 'lines'
        for (int j = 0; j < 12; j++)
        {
            cout << " | ";
            if (game.board[i][j].hasmine == false)
                cout << " ";
            if (game.board[i][j].hasmine == true)
                cout << "*";

            if (j == 11)
                cout << " ";
        }
        cout << "|" << endl;

        //prints out the x lines +---+
        for (int i = 1; i <= game.width; i++)
        {
            if (i == 1)
                cout << "  ";

            cout << "+---";

            if (i == game.width)
                cout << "+" << endl;
        }
    }

    return;
}

/*
ALGORITHM
1. nested loop to run through the entire char array to find either a '?' or a 'P'
2. if found, compare that location to that in the bool array and check to see if 
    a mine exists there
3. if mine does exist count will be incremented by 1
4. at the end of the array, the count does not equal the amount of mines will be returned false
5. if it does equal amount of mines, array will return true

*/
bool hasplayerwon(minesweeper game) //cause of seg fault?
{
    int count = 0;
    //checks entire 2-d array for ?, iterates count if so
    for (int i = 0; i < game.height; i++)
    {
        for (int j = 0; j < game.width; j++)
        {
            if (game.board[i][j].letter == '?' || game.board[i][j].letter == 'P')
            {
                //if(game.board[i][j].hasmine == true)
                    count++;
            }
            //if(game.board[i][j].letter == 'P')
        }
    }

    if (count != 10)
        return false;

    //if count is equal to amount of mines(10), then player has won
    if (count == 10)
        cout << "You won!" << endl;

    return true;
}
