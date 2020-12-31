//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: TOE.CPP
//
// This program "learns" to play tic-tac-toe by recording a history of all
// its games and choosing moves that prove historically to win.

#include "prefix.h"
#include <time.h>

MyApp myApp; // instantiate one and only app

const SQM_CHECKED = 1;						 // message sent to parent

enum SQSTATE {
	SQFREE= 1,									 // square is free
	SQOOO = 3,									 // square is O
	SQXXX = 5,									 // square is X
};

////////////////
// Window class for a board square
// 
class Square : public WPWin {
	SQSTATE state;								 // state of square: free, X or O
public:
	BOOL paint();
	BOOL mouse(int msg, WPPoint p, WORD flags);
	Square(WPWin *pwin, int id);
	SQSTATE operator()()			{ return state; }
	void set(SQSTATE newstate);
};

////////////////
// This structure is used to save the result of a game.
// 
struct GAME {
	char moves[9];								 // the game
	int nmoves;									 // number of moves
	int result;									 // whether I won, lost or drew
};
const NHISTORY = 50;							 // save this many games
const NSQUARES = 9;							 // nine squares in board
enum RESULT { LOSE=-1, DRAW=0, WIN=2 };

//////////////////
// This is the main tic-tac-toe window.
// 
class ToeBoard : public WPMainWin {
	Square *squares[NSQUARES];				 // the board = 9 child squares
	GAME history[NHISTORY];					 // history of past games
	int histLen;								 // number of games played
	int curGame;								 // current game number
	int curMove;								 // current nove number
	int win,block;								 // hint: move to win or block

	// these are all special toe functions
	SQSTATE operator[](int x)	{ return (*squares[x%NSQUARES])(); }
	BOOL tictactoe();							 // test if tic-tac-toe
	BOOL tictactoe(int i, int j, int k); // ditto
	BOOL computeValue(int move);			 // compute value of move
	void newGame(int result);				 // start a new game
	int computeMove();						 // figure out next move
	void think();								 // pretend to "think"
	void setSquare(int move, SQSTATE which);

	// Here are the virtual message functions
	BOOL command(int id, WORD msg);		 // handle child message
	BOOL sized(WPRect &pos, WORD how);	 // re-size window
	BOOL kbd(WPEvent& event);

public:
	ToeBoard();
};

//////////////////
// Entry point
// 
void MyApp::main()
{
	mainWin = new ToeBoard;		// create tic-tac-toe board
	run();							// run message loop
}

/////////////////
// Initialize board square.
// 
Square::Square(WPWin *pwin, int id) : WPWin("square", pwin, id)
{
	state = SQFREE;							 // square is free to start
	createArgs.wndcls.hCursor = NULL;	 // we will set cursor in real-time
	createArgs.style |= WS_BORDER;		 // draw a border around it
	createWin();								 // create the window
}

//////////////////
// Paint X or O depending on state of square.
// 
BOOL Square::paint()
{
	WPPaintDC dc(this);
	
	WPRect box = this;
	box -= 2;					// shrink 2 pixels
	switch (state) {
	case SQOOO:
		dc.setPen(COLOR_BLUE);
		dc.ellipse(box);
		break;
	case SQXXX:
		dc.setPen(COLOR_RED);
		dc.line( box.origin(),	box.endpt() );
		dc.line( box.topRight(),box.bottomLeft() );
		break;
	}
	return TRUE;
}

//////////////////
// Change state of square.
// 
void Square::set(SQSTATE newstate)
{ 
	state = newstate; 
	invalidate(TRUE); 
	Cursor = state==SQFREE ? "XCURSOR" : IDC_ARROW;
}

//////////////////
// Handle mouse event.
// 
BOOL Square::mouse(int msg, WPPoint p, WORD flags)
{
	switch (msg) {
	case WM_LBUTTONDOWN:
		if (state!=SQFREE)
			MsgBeep();								 // square is taken: beep
		else
			notifyParent(SQM_CHECKED);			 // tell main window
		break;

	case WM_MOUSEMOVE:
		Cursor = state==SQFREE ? "XCURSOR" : IDC_ARROW;
		break;
	}
	return TRUE;
}

//////////////////
// Create tic-tac-toe board
// 
ToeBoard::ToeBoard()
{
	// compute default size of toe board from screen size
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);
	int side = min(cx,cy)/2;
	createArgs.pos.origin((cx-side)/2, (cy-side)/2);
	createArgs.pos.extent(side, side);
	createWin("TOE");							 // create window
	histLen = curGame = 0;					 // no games played yet

	// create child window for each square
	for (int i=0; i<NSQUARES; i++)
		squares[i] = new Square(this, i);
}

//////////////////
// Resize all the squares to fit the window.
// 
BOOL ToeBoard::sized(WPRect &pos, WORD how)
{
	pos /= 3;									// shrink by 1/3
	WPPoint moveRight(pos.width());		// moves rectangle right one square
	WPPoint moveDown(0, pos.height());	// moves rectangle down one square

	// Now reposition each square (child window)
	int s = 0;
//	WPDeferWinPos defer = NSQUARES;
	for (int i=0; i<3; i++) {
		WPRect box = pos;						 // box = position of 1st square in row
		for (int j=0; j<3; j++) {
//			defer.move(squares[s++], box); // move the window
			squares[s++]->moveWin(box);	 // move the window
			box += moveRight;					 // move box right one
		}
		pos += moveDown;						 // move down one row
	}
	return TRUE;
}

//////////////////
// Hande keyboard event.  
// 
BOOL ToeBoard::kbd(WPEvent& event)
{
	Square *sq;

	switch (event.msg) {
	case WM_CHAR:
		if (event.wp == ' ' || event.wp == '\r') {
			sq = (Square*)WinFromPoint(Cursor());
			assert(sq);
			sq->mouse(WM_LBUTTONDOWN, Cursor(), 0);
		}
		return TRUE;

	case WM_KEYDOWN:
		if (Keyboard.isArrowKey(event.wp)) {
			// Got arrow key: move cursor

			sq = (Square*)WinFromPoint(Cursor());
			assert(sq);

			int id = sq->getID();
			switch (event.wp) {
			case VK_LEFT:		id--;		break;
			case VK_RIGHT:		id++;		break;
			case VK_UP:			id-=3;	break;
			case VK_DOWN:		id+=3;	break;
			}
			id = (id+NSQUARES) % NSQUARES;		// new square
			WPWindowRect box = squares[id];		// new square's rectangle
			Cursor = box.center();					// put cursor in center of square
			return TRUE;
		}
		break;
	}
	return WPMainWin::kbd(event);
}

//////////////////
// Process message from child square.
// 
BOOL ToeBoard::command(int id, WORD msg)
{
	if (id<0 || id>=NSQUARES) 
		return WPMainWin::command(id, msg);

	switch (msg) {
	case SQM_CHECKED:
		setSquare(id, SQXXX);	// put X where user clicked
		if (tictactoe())			// user got three in a row?
			newGame(LOSE);			// too bad, I lose

		else {
			int mymove = computeMove();	 // figure out my move
			if (mymove >= 0) {				 // got a move:
				think();							 // pretend to think
				setSquare(mymove, SQOOO);	 // put O in my square
				if (tictactoe())				 // three in a row?
					newGame(WIN);				 // hooray, I win!
			} else
				newGame(DRAW);					 // no possible move: draw
		}
		break;
	}
	return TRUE;
}

/////////////////
// Simulate thinking by waiting 2 seconds.
// 
void ToeBoard::think()
{
	WPWaitCursor wait = this;	// change cursor to wait icon
	time_t t;
	t = time(NULL)+2;
	while (time(NULL) < t)
		;
}

//////////////////
// Record a move.  Store it in current game, change square and clear hints.
// 
void ToeBoard::setSquare(int move, SQSTATE which)
{
	history[curGame].moves[curMove++] = move;		// record move in history
	squares[move]->set(which);				 // set square
	win = block = -1;							 // clear hints
	update();									 // force move to be displayed
}

//////////////////
// Clear all squares.  First display message.
// 
void ToeBoard::newGame(int result)
{
	MsgBox(result==WIN ? "I Win!" : result==LOSE ? "You Win!" : "Draw!", "TOE");

	// save game result in history buffer
	history[curGame].result = result;
	history[curGame].nmoves = curMove;
	if (++histLen < NHISTORY)
		curGame++;

	// reset move num to zero and all squares to free
	curMove=0;
	for (int i=0; i<NSQUARES; i++)
		squares[i]->set(SQFREE);
}

//////////////////
// Check for tic-tac-toe.  i,j,k are three squares in a row.  
// Returns TRUE if all the squares are X's or O's, otherwise FALSE.
// If two out of three are X or O, set "block" or "win" to the move that
// either blocks user from tic-tac-toe or wins for me.
// 
int ToeBoard::tictactoe(int i, int j, int k)
{
	ToeBoard &board = *this;				 // board is now reference to this.

	int prod = board[i] * board[j] * board[k];
	if (prod==SQXXX*SQXXX)
		block = board[i]==SQFREE ? i : board[j]==SQFREE ? j : k;
	else if (prod==SQOOO*SQOOO) 
		win = board[i]==SQFREE ? i : board[j]==SQFREE ? j : k;
	return prod==(SQXXX*SQXXX*SQXXX) || prod==(SQOOO*SQOOO*SQOOO);
}

//////////////////
// Determine if there's a tic-tac-toe.  Returns TRUE if there are
// three X's or O's in a row.  Check up-down, left-right and diagonals.
// 
BOOL ToeBoard::tictactoe()
{
	for (int i=0; i<3; i++) {
		if (tictactoe(i, i+3, i+6))		 // up-down
			return TRUE;
		if (tictactoe(3*i, 3*i+1, 3*i+2)) // left-right
			return TRUE;
	}
	if (tictactoe(0, 4, 8))					 // diagonal
		return TRUE;
	return tictactoe(2, 4, 6);				 // other diagonal
}

//////////////////
// Compute "value" of a possible move: start with 1000, then subtract 1
// for each game where the same move caused a loss; add one for each win.
// history.result is +1 (win), -1 (loss), or 0 (draw).
// 
int ToeBoard::computeValue(int move)
{
	history[curGame].moves[curMove] = move;
	int val = 1000;
	for (int h=0; h<min(NHISTORY,histLen); h++) {
		if (history[h].nmoves >= curMove &&
				memcmp(history[curGame].moves, history[h].moves, curMove+1)==0)
			val += history[h].result;
	}
	return val;
}

//////////////////
// Compute next move.  
// First check hints: look first for winner, then block.
// Otherwise, compute value of all possible moves and select the best one.
// Returns the square number of move, or -1 if no squares free (draw).
// 
int ToeBoard::computeMove()
{
	ToeBoard &board = *this;

	if (win>=0)
		return win;								 // I can win
	else if (block>=0)
		return block;							 // I can block

	// compute values of all legal moves
	int moveVal[NSQUARES];
	for (int move=0; move<NSQUARES; move++)
		moveVal[move] = board[move]==SQFREE ? computeValue(move) : -1;

	// moveVal array now has value of each move or -1 if square is taken.
	// Choose the best one.
	// 
	int which = 0;
	for (int i=0; i<NSQUARES; i++) {
		if (moveVal[i] > moveVal[which])
			which = i;
	}
	return moveVal[which] >= 0 ? which : -1;
}
