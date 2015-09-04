/* CSCI 261 -- HW 09 -- CONNECT FOUR

    Author: Nick Collins

    Use a 2D array to represent a connect four game, randomly fill it according to the rules of the game(pieces fall to the bottom)
    Evaluate the random board for wins (4 in a row or 4 in a column)
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>

using namespace std;

//Constants
const int ROWS = 6;
const int COLS = 7;

//PlayGame functions
void playGame();
int randomMove(bool availableColumns[COLS]);
void doMove(char board[ROWS][COLS], int move, char RorG, bool availableColumns[COLS]);
bool outputBoard(char board[ROWS][COLS]);

//Evaluate Functions
void evaluateGame();
bool initializeArray(char evalBoard[ROWS][COLS]);
bool evaluateRow(char row[COLS], char evalChar);
void evaluateRows(char evalBoard[ROWS][COLS], int& gRows, int& rRows);
void transposeArray(const char myArray[ROWS][COLS], char transArray[COLS][ROWS]);
void outputResults(int, int, int, int);

int main()
{
    srand(time(NULL));
    playGame();
    evaluateGame();
    cout << "Done!" << endl;
    return 0;
}

void playGame(){
    char board[ROWS][COLS];
    const int turns = 21;
    bool availableColumns[COLS];
    int move;

    //Initialize available columns
    for(int i = 0; i < COLS; i++){
        availableColumns[i] = true;
    }

    //initialize array
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            board[i][j] = 'b';
        }
    }

    //Loop through doing random moves
    for(int t = 0; t < turns; t++){
        move = randomMove(availableColumns);
        doMove(board,move,'r',availableColumns);
        move = randomMove(availableColumns);
        doMove(board,move,'g',availableColumns);
    }

    outputBoard(board);
    return;
}

int randomMove(bool availableColumns[COLS]){
    int theMove; //between 0 and 6
    vector<int> possibleMoves;
    for(int i = 0; i < COLS; i++){
        if(availableColumns[i]){
            possibleMoves.push_back(i);
        }
    }

    //Randomly selects move from available moves
    theMove = possibleMoves.at(rand() % possibleMoves.size());
    //cout << "Move selected: " << theMove << endl;
    return theMove;
}

void doMove(char board[ROWS][COLS], int move, char RorG, bool availableColumns[COLS]){
    //loop upward through board, placing piece at first available position
    for(int i = (ROWS - 1); i >= 0; i--){
        if(board[i][move] == 'b'){
            board[i][move] = RorG;

            if(i == 0){ //if piece was placed at top, the column is not longer available to move in
                availableColumns[move] = false;
                //cout << "Column: " << move + 1 << " is now full." << endl;
            }
            break;
        }
    }
    return;
}

bool outputBoard(char board[ROWS][COLS]){
    ofstream output;
    output.open("connect4board.txt");
    if(output.fail()){
        return false;
    }

    //Print to file
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            output << board[i][j] << ' ';
        }
        output << endl;
    }

    output.close();

    //Print to console
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < COLS; j++){
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;

    return true;
}


void evaluateGame(){
    //initialize variables
    char evalBoard[ROWS][COLS];
    char transposedBoard[COLS][ROWS];
    int gRows = 0;
    int rRows = 0;
    int gCols = 0;
    int rCols = 0;
    initializeArray(evalBoard);

    //check rows for wins
    evaluateRows(evalBoard, gRows, rRows);

    //transpose array
    transposeArray(evalBoard, transposedBoard);

    //check columns for win (same function, transposed array)
    evaluateRows(transposedBoard, gCols, rCols);

    //output results
    outputResults(gRows, rRows, gCols, rCols);
    return;
}

bool initializeArray(char evalBoard[ROWS][COLS]){
    ifstream input;
    input.open("connect4board.txt");
    if(input.fail()){
        cerr << "File failed to open." << endl;
        return false;
    }

    //get data from file created earlier
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < COLS; j++){
            input >> evalBoard[i][j];
        }
    }

    input.close();
    return true;
}

bool evaluateRow(char row[COLS], char evalChar){
    bool win = false;

    //loop through row, seeing if 4 in a row are the same
    for(int i = 0; i < (COLS - 3); i++){ //stops at COLS-3 because the loop checks up to i+3 (max is 6, 7 is out of bounds)
        if((row[i] == evalChar) && (row[i+1] == evalChar) && (row[i+2] == evalChar) && (row[i+3] == evalChar)){
            win = true;
        }
    }
    return win;
}

void evaluateRows(char evalBoard[ROWS][COLS], int& gRows, int& rRows){
    char row[COLS];
    //loop through rows
    for(int i = 0; i < ROWS; i++){
        //copy row being evaluated into 1D array
        for(int j = 0; j < COLS; j++){
            row[j] = evalBoard[i][j];
        }

        //run row through function twice, checking for Red and Green wins
        if(evaluateRow(row,'g')){
            gRows++;
        }
        if(evaluateRow(row,'r')){
            rRows++;
        }
    }
    return;
}

//Transpose array from Lab08A (changed to char instead of int)
void transposeArray(const char myArray[ROWS][COLS], char transArray[COLS][ROWS]){
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            transArray[j][i] = myArray[i][j];
        }
    }
    return;
}

void outputResults(int gRows, int rRows, int gCols, int rCols){
    //is # is one, do not include s
    if(gRows == 1){
        cout << "Green won " << gRows << " row." << endl;
    }
    else{
        cout << "Green won " << gRows << " rows." << endl;
    }

    if(rRows == 1){
        cout << "Red won " << rRows << " row." << endl;
    }
    else{
        cout << "Red won " << rRows << " rows." << endl;
    }

    if(gCols == 1){
        cout << "Green won " << gCols << " column." << endl;
    }
    else{
        cout << "Green won " << gCols << " columns." << endl;
    }

    if(rCols == 1){
        cout << "Red won " << rCols << " column." << endl;
    }
    else{
        cout << "Red won " << rCols << " columns." << endl;
    }

    return;
}
