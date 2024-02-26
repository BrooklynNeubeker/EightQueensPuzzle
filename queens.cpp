/*
Description: Program takes a user input to place a queen on a 8x8 board, then using recursion finds positions for
7 other queens on the board such that they do not threaten one another.
Input: User inputs the row and column coordinates for the first queen. 
Output: Prints the solved board with all 8 queens.
*/
#include <iostream>
using namespace std;

//Board size + row and column for numbers
const int SIZE = 9;
//Create 2D array
char board[SIZE][SIZE];

/*
bool checkDirections: Checks if the passed coordinates have any queens threatening vertically, horizontally, or diagonally.
parameters: Coordinates int x and y to check if the spot is safe.
returns: True if safe, false if unsafe.
*/
bool checkDirections(int x, int y){
    //For current position, check the diagonals, verticals, and horizontal spots
    //check Horizontal
    for(int r = x, c = 1; c < SIZE; c++){
        if(board[r][c] == 'Q')
            return false;
    }
    //Check Vertical
    for(int r =1, c = y; r < SIZE && c < SIZE; r++){
        if(board[r][c] == 'Q')
            return false;
    }
    //Check left upper diagonal
    for(int r = x-1, c = y-1; r > 0 && c > 0; r--, c--){
        if(board[r][c]=='Q')
            return false;
    }

    //Check right upper diagonal
    for(int r = x-1, c = y+1; r > 0 && c < SIZE; r--, c++){
        if(board[r][c]=='Q')
            return false;
    }
    //Check left lower diagonal
    for(int r = x+1, c = y-1; r < SIZE && c > 0; r++, c--){
        if(board[r][c]=='Q')
            return false;
    }
    //Check right lower diagonal
    for(int r = x+1, c = y+1; r < SIZE && c < SIZE; r++, c++){
        if(board[r][c]=='Q')
            return false;
    }
    return true;
    //If all directions come back safe, mark spot
}
/*
void printBoard: Prints the board.
parameters: none
returns: nothing
*/
void printBoard(){
 //print board:
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            cout << board[i][j];
            if(j < SIZE-1)
                cout << "  ";
        }
        cout << endl;
    }
}
/*
bool queenFill: Places remaining seven queens on the board by iterating through the columns of the current row, 
and if a safe spot is found, recursively calling itself for the next row on the board. If a recursive call returns true, this iteration of the call
will also return true. If it returns false, the loop continues searching for the next safe column. If no other safe columns are found, this recursive
call will return false.
parameters: Current row to iterate through, and the initial queen row
returns: True if the previous recursive call was true, false if valid postion through all columns could be found.
*/
bool queenFill(int i, int q){
    //x, y pass in current position, 
    if(i == 9)
        return true;
    //Set up booleans for checking if a spot is safe, and if a function call returned true for spot found
    //Skipping the row with the initially placed queen
    if(i == q){
        if(!queenFill(i+1, q)){
            return false;
        }
        else{
            return true;
        }
    }
        //Column of row
        for(int j = 1; j < SIZE; j++){
        //If current position is not a queen, check other directions
            //If the spot was safe, place the queen and call the next row
            if(board[i][j]!= 'Q' && checkDirections(i , j)){
                board[i][j] = 'Q';
                //If the next row could not place the queen, erase this queen and continue this looping
                if (!queenFill(i+1, q)){
                    board[i][j] = '-';
                    continue;
                }
                //If the next row returns that it could place the queen, return true
                else{
                    return true;
                }
            }
        }
    //If we make it here we checked all columns for the row and we could not place the queen.
    return false;
}

int main(){
    //Initializing bools
    bool inputValid = false;
    //Locations of the user input queen
    int x = 0;
    int y = 0;
    
    //Fill board to start
    for (int i = 0; i <= SIZE; i++){
        for (int j = 0; j <= SIZE; j++){
            if(i == 0 && j == 0){
                //If top left fill with a blank and continue iterating
                board[i][j] = ' ';
                continue;
            }
            //If first row fill with column number
            if(i == 0) {
                board[i][j] = (j + 48);
            }
            //If first column fill with row number
            else if (j == 0){
                board[i][j] = (i + 48);
            }
            //Fill all other squares with '-'
            else{
                board[i][j] = '-';
            }
        }
    }
    //Get a valid input for the position of the first queen.
    while(inputValid == false){
        //Prompt for first queen and get the coordinates, set that location to be a Q
        cout << "Enter initial coordinates of the first queen: ";
        cin >> x >> y;
        if(x < 1 || x > 8 || y < 1 || y > 8){
            cout << "Invalid coordinates!" << endl;
        }
        else {
            inputValid = true;
        }
    }
    cout << x << " " << y << endl << endl;
    // Set the user spot to be the first queen
    board[x][y] = 'Q';
    //If the queens were all placed successfully, print the board, else error message.
    if(queenFill(1,x)){
        printBoard();
    }
    else {
        cout << "Could not solve" << endl;
   }
   return 0;
}