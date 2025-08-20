/* check the check
 * pc110107
 * uva10196 */

#include <stdio.h>

const int SIZE = 8;

int black_pawn_dirs[8][2] = {
	{-1, -1},
	{-1, 1},
	{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};

int white_pawn_dirs[8][2] = {
	{1, -1},
	{1, 1},
	{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};

int knight_dirs[8][2] = {
	{-2, -1}, {-2, 1},
	{2, -1}, {2, 1}, 
	{-1, -2}, {-1, 2},
	{1, -2}, {1, 2}};

int rook_dirs[8][2] = {
	{-1, 0},
	{1, 0},
	{0, -1},
	{0, 1},
	{0, 0}, {0, 0}, {0, 0}, {0, 0}};

int bishop_dirs[8][2]= {
	{-1, -1},
	{-1, 1},
	{1, -1},
	{1, 1},
	{0, 0}, {0, 0}, {0, 0}, {0, 0}};

int queen_dirs[8][2] = {
	{-1, -1}, {-1, 0}, {-1, 1},
	{0, -1}, {0, 1},
	{1, -1}, {1, 0}, {1, 1}};

typedef struct {
	int row;
	int col;
	char name;
	int directions[8][2];
	int repeat;
} Piece;

typedef struct {
	char board[SIZE][SIZE];
	Piece white_king;
	Piece black_king;
} Chess;

int is_valid_position(int row, int col) {
	return (row >= 0 && row < SIZE && col >= 0 && col < SIZE);
}

void init_piece(Piece *piece, char name, int repeat, int directions[8][2]) {
	piece->name = name;
	piece->repeat = repeat;
	for (int i = 0; i < 8; i++) {
		piece->directions[i][0] = directions[i][0];
		piece->directions[i][1] = directions[i][1];
	}
}

int is_attacked_by_piece(Chess chess, int is_white, Piece piece) {
	Piece king = is_white ? chess.white_king : chess.black_king;
	
	for (int i = 0; i < 8; i++) {
		int row_dir = piece.directions[i][0];
		int col_dir = piece.directions[i][1];

		if (row_dir == 0 && col_dir == 0) {
			continue;
		}

		int row = king.row;
		int col = king.col;

		if (piece.repeat) {
			row += row_dir;
			col += col_dir;
			while (is_valid_position(row, col)) {
				if (chess.board[row][col] != '.') {
					if (chess.board[row][col] == piece.name) {
						return 1;
					}
					break;
				}
				row += row_dir;
				col += col_dir;
			}
		} else {
			row += row_dir;
			col += col_dir;

			if (is_valid_position(row, col) && chess.board[row][col] == piece.name) {
				return 1;
			}
		}
	}
	return 0;
}

int is_in_check(Chess chess, int is_white) {
	Piece attacker;

	// Check pawn attacks
	init_piece(&attacker, (is_white ? 'p' : 'P'), 0, (is_white ? black_pawn_dirs : white_pawn_dirs));
	if (is_attacked_by_piece(chess, is_white, attacker)) {
		return 1;
	}

	// Check knight attacks
	init_piece(&attacker, (is_white ? 'n' : 'N'), 0, knight_dirs);
	if (is_attacked_by_piece(chess, is_white, attacker)) {
		return 1;
	}

	// Check rook attacks
	init_piece(&attacker, (is_white ? 'r' : 'R'), 1, rook_dirs);
	if (is_attacked_by_piece(chess, is_white, attacker)) {
		return 1;
	}

	// Check bishop attacks
	init_piece(&attacker, (is_white ? 'b' : 'B'), 1, bishop_dirs);
	if (is_attacked_by_piece(chess, is_white, attacker)) {
		return 1;
	}

	// Check queen attacks
	init_piece(&attacker, (is_white ? 'q' : 'Q'), 1, queen_dirs);
	if (is_attacked_by_piece(chess, is_white, attacker)) {
		return 1;
	}

	return 0;
}

int main(void) {
	char input_board[SIZE][SIZE];
	int game_count = 0;

	while (1) {
		int empty = 1;
		Chess chess;

		// Read board and initialize chess structure
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				scanf(" %c", &input_board[i][j]);
				chess.board[i][j] = input_board[i][j];
				
				if (input_board[i][j] != '.') {
					empty = 0;
				}
				
				// Find king positions
				if (input_board[i][j] == 'K') {
					chess.white_king.row = i;
					chess.white_king.col = j;
					chess.white_king.name = 'K';
				} else if (input_board[i][j] == 'k') {
					chess.black_king.row = i;
					chess.black_king.col = j;
					chess.black_king.name = 'k';
				}
			}
		}

		if (empty) break;
		game_count++;

		int white_in_check = is_in_check(chess, 1);
		int black_in_check = is_in_check(chess, 0);

		printf("Game #%d: ", game_count);
		if (white_in_check) {
			printf("white king is in check.\n");
		} else if (black_in_check) {
			printf("black king is in check.\n");
		} else {
			printf("no king is in check.\n");
		}
	}

	return 0;
}
