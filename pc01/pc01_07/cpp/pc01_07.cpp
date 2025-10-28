/**
 * Check the check
 * pc110107
 * uva10196
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int SIZE = 8;

const int BLACK_PAWN_DIRS[8][2] = {
	{-1, -1}, {-1, 1},
	{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}
};

const int WHITE_PAWN_DIRS[8][2] = {
	{1, -1}, {1, 1},
	{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}
};

const int KNIGHT_DIRS[8][2] = {
	{-2, -1}, {-2, 1},
	{2, -1}, {2, 1},
	{-1, -2}, {-1, 2},
	{1, -2}, {1, 2}
};

const int ROOK_DIRS[8][2] = {
	{-1, 0}, {1, 0}, {0, -1}, {0, 1},
	{0, 0}, {0, 0}, {0, 0}, {0, 0}
};

const int BISHOP_DIRS[8][2] = {
	{-1, -1}, {-1, 1}, {1, -1}, {1, 1},
	{0, 0}, {0, 0}, {0, 0}, {0, 0}
};

const int QUEEN_DIRS[8][2] = {
	{-1, -1}, {-1, 0}, {-1, 1},
	{0, -1}, {0, 1},
	{1, -1}, {1, 0}, {1, 1}
};

struct Position {
	int row;
	int col;
	Position() : row(-1), col(-1) {}
	Position(int r, int c) : row(r), col(c) {}
};

class ChessBoard {
private:
	vector<vector<char>> board;
	Position whiteKing;
	Position blackKing;
	
	bool isValidPosition(int row, int col) const {
		return row >= 0 && row < SIZE && col >= 0 && col < SIZE;
	}
	
	bool isAttackedByPiece(Position kingPos, char pieceChar, const vector<vector<int>>& dirs, bool repeating) const {
		for (int i = 0; i < 8; i++) {
			int rowDir = dirs[i][0];
			int colDir = dirs[i][1];
			
			if (rowDir == 0 && colDir == 0) continue;
			
			int row = kingPos.row;
			int col = kingPos.col;
			
			if (repeating) {
				row += rowDir;
				col += colDir;
				while (isValidPosition(row, col)) {
					if (board[row][col] != '.') {
						if (board[row][col] == pieceChar) {
							return true;
						}
						break;
					}
					row += rowDir;
					col += colDir;
				}
			} else {
				row += rowDir;
				col += colDir;
				if (isValidPosition(row, col) && board[row][col] == pieceChar) {
					return true;
				}
			}
		}
		return false;
	}

public:
	ChessBoard() : board(SIZE, vector<char>(SIZE)) {}
	
	void readBoard() {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				cin >> board[i][j];
				if (board[i][j] == 'K') {
					whiteKing = Position(i, j);
				} else if (board[i][j] == 'k') {
					blackKing = Position(i, j);
				}
			}
		}
	}
	
	bool isInCheck(bool isWhite) const {
		Position kingPos = isWhite ? whiteKing : blackKing;
		char pieces[6] = {
			isWhite ? 'p' : 'P',
			isWhite ? 'n' : 'N',
			isWhite ? 'r' : 'R',
			isWhite ? 'b' : 'B',
			isWhite ? 'q' : 'Q',
			isWhite ? 'k' : 'K'
		};
		
		vector<vector<int>> pawnDirs(8, vector<int>(2));
		for (int i = 0; i < 8; i++) {
			pawnDirs[i][0] = isWhite ? BLACK_PAWN_DIRS[i][0] : WHITE_PAWN_DIRS[i][0];
			pawnDirs[i][1] = isWhite ? BLACK_PAWN_DIRS[i][1] : WHITE_PAWN_DIRS[i][1];
		}
		if (isAttackedByPiece(kingPos, pieces[0], pawnDirs, false)) return true;
		
		vector<vector<int>> knightDirs(8, vector<int>(2));
		for (int i = 0; i < 8; i++) {
			knightDirs[i][0] = KNIGHT_DIRS[i][0];
			knightDirs[i][1] = KNIGHT_DIRS[i][1];
		}
		if (isAttackedByPiece(kingPos, pieces[1], knightDirs, false)) return true;
		
		vector<vector<int>> rookDirs(8, vector<int>(2));
		for (int i = 0; i < 8; i++) {
			rookDirs[i][0] = ROOK_DIRS[i][0];
			rookDirs[i][1] = ROOK_DIRS[i][1];
		}
		if (isAttackedByPiece(kingPos, pieces[2], rookDirs, true)) return true;
		
		vector<vector<int>> bishopDirs(8, vector<int>(2));
		for (int i = 0; i < 8; i++) {
			bishopDirs[i][0] = BISHOP_DIRS[i][0];
			bishopDirs[i][1] = BISHOP_DIRS[i][1];
		}
		if (isAttackedByPiece(kingPos, pieces[3], bishopDirs, true)) return true;
		
		vector<vector<int>> queenDirs(8, vector<int>(2));
		for (int i = 0; i < 8; i++) {
			queenDirs[i][0] = QUEEN_DIRS[i][0];
			queenDirs[i][1] = QUEEN_DIRS[i][1];
		}
		if (isAttackedByPiece(kingPos, pieces[4], queenDirs, true)) return true;
		
		return false;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int gameCount = 0;
	ChessBoard chess;
	bool isEmpty;
	
	while (true) {
		isEmpty = true;
		chess = ChessBoard();
		chess.readBoard();
		
		for (int i = 0; i < SIZE && isEmpty; i++) {
			for (int j = 0; j < SIZE; j++) {
				char c;
				cin.get(c);
				if (c != '.' && c != '\n') {
					isEmpty = false;
					break;
				}
			}
		}
		
		if (isEmpty) break;
		gameCount++;
		
		bool whiteInCheck = chess.isInCheck(true);
		bool blackInCheck = chess.isInCheck(false);
		
		cout << "Game #" << gameCount << ": ";
		if (whiteInCheck) {
			cout << "white king is in check.\n";
		} else if (blackInCheck) {
			cout << "black king is in check.\n";
		} else {
			cout << "no king is in check.\n";
		}
	}
	
	return 0;
}