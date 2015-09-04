


class Board{
public:
	Board();
	Board(/*fnctn pointers?*/);
	int playGame(); //returns winner
	bool doTurn(); //Gets move from appropriate source (i.e. human through console/gui or ai)
	int evaluateGame();
	
	bool checkLegal(int moveCol); //Compares move to top row position
	char getBoardArr();
	void makeMove(int moveCol);
	void undoMove(int moveCol);
	
private:
	char board[ROWS][COLS];
	bool turn;
	static const int turns = 21;
	static const int ROWS = 6;
	static const int COLS = 7;
	
	/* Ai pointer/ function pointer
		Human player info (console/gui/2/1/0)
	*/
}

/*
Console start menu -> takes inputs, then starts game on gui or computes games if double AI
creates board/AI/GUI objects
plays game
ends back to console with stats/replay option
*/
