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

