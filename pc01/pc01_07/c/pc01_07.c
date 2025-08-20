/* check the check
 * pc110107
 * uva10196 */

#include <stdio.h>

const int SIZE = 8;

typedef struct {
	int row;
	int col;
	char name;
} Piece;

int is_valid_position(int row, int col) {
	return (row >= 0 && row < SIZE && col >= 0 && col < SIZE);
}

Piece get_king_position(char board[SIZE][SIZE], int is_white) {
	Piece king;
	king.name = is_white ? 'K' : 'k';
	king.row = -1;
	king.col = -1;

	for (int i = 0; i < SIZE; i++) {
		int found = 0;
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j] == king.name) {
				king.row = i;
				king.col = j;
				found = 1;
				break;
			}
		}
		if (found) {
			break;
		}
	}

	return king;
}

int is_attacked_by_pawn(char board[SIZE][SIZE], Piece king, int is_white) {
	int row_dir = is_white ? -1 : 1;
	int row = king.row + row_dir;

	if (is_valid_position(row, king.col - 1) && board[row][king.col - 1] == (is_white ? 'p' : 'P')) {
		return 1;
	}

	if (is_valid_position(row, king.col + 1) && board[row][king.col + 1] == (is_white ? 'p' : 'P')) {
		return 1;
	}

	return 0;
}

int is_attacked_by_knight(char board[SIZE][SIZE], Piece king, int is_white) {
	int knight_directions[8][2] = {
		{-2, -1}, {-2, 1},
		{-1, -2}, {-1, 2},
		{2, -1}, {2, 1},
		{1, -2}, {1, 2}};

	for (int i = 0; i < 8; i++) {
		int direction[2];
		int row_dir = knight_directions[i][0];
		int col_dir = knight_directions[i][1];

		int row = king.row + row_dir;
		int col = king.col + col_dir;

		if (is_valid_position(row, col) && board[row][col] == (is_white ? 'n' : 'N')) {
			return 1;
		}
	}
	return 0;
}

int check_diagonal_attack(char board[SIZE][SIZE], Piece king, int is_white, int row_dir, int col_dir) {
	int row = king.row + row_dir;
	int col = king.col + col_dir;

	while (is_valid_position(row, col)) {
		if (board[row][col] != '.') {
			if (board[row][col] == (is_white ? 'b' : 'B') || board[row][col] == (is_white ? 'q' : 'Q')) {
			       return 1;
			}
			break;
		}
		row += row_dir;
		col += col_dir;
	}
	return 0;
}

int check_straight_attack(char board[SIZE][SIZE], Piece king, int is_white, int row_dir, int col_dir) {
	int row = king.row + row_dir;
	int col = king.col + col_dir;

	while (is_valid_position(row, col)) {
		if (board[row][col] != '.') {
			if (board[row][col] == (is_white ? 'r' : 'R') || board[row][col] == (is_white ? 'q' : 'Q')) {
			       return 1;
			}
			break;
		}
		row += row_dir;
		col += col_dir;
	}
	return 0;
}

int is_attacked_by_bishop_or_queen(char board[SIZE][SIZE], Piece king, int is_white) {
	if (check_diagonal_attack(board, king, is_white, -1, -1) || 
			check_diagonal_attack(board, king, is_white, 1, 1) || 
			check_diagonal_attack(board, king, is_white, -1, 1) || 
			check_diagonal_attack(board, king, is_white, 1, -1)) {
		return 1;
	}
	return 0;
}

int is_attacked_by_rook_or_queen(char board[SIZE][SIZE], Piece king, int is_white) {
	if (check_straight_attack(board, king, is_white, -1, 0) || 
			check_straight_attack(board, king, is_white, 1, 0) || 
			check_straight_attack(board, king, is_white, 0, -1) || 
			check_straight_attack(board, king, is_white, 0, 1)) {
		return 1;
	}
	return 0;
}

int is_in_check(char board[SIZE][SIZE], int is_white) {
	Piece king = get_king_position(board, is_white);

	if (king.row == -1) {
		return 0;
	}

	if (is_attacked_by_pawn(board, king, is_white) ||
			is_attacked_by_knight(board, king, is_white) ||
			is_attacked_by_bishop_or_queen(board, king, is_white) ||
			is_attacked_by_rook_or_queen(board, king, is_white)) {
		return 1;
	}
	return 0;
}

int main(void) {
	char board[SIZE][SIZE];
	int game_count = 0;

	while (1) {
		int empty = 1;

		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				scanf(" %c", &board[i][j]);
				if (board[i][j] != '.') {
					empty = 0;
				}
			}
		}

		if (empty) break;
		game_count++;

		int white_in_check = is_in_check(board, 1);
		int black_in_check = is_in_check(board, 0);

		printf("Game #%d: ", game_count);
		if (white_in_check) {
			printf("white king is in check.\n");
		} else if (black_in_check) {
			printf("black king is in check.\n");
		} else {
			printf("No king is in check.\n");
		}
	}

	return 0;
}
