/**
 * Minesweeper
 * pc110102
 * uva10189
 */

#include <stdio.h>

const int MAX_NUMBER = 100;

int directions[8][2] = {
	{-1, -1}, {-1, 0}, {-1, 1},
	{0, -1}, {0, 1},
	{1, -1}, {1, 0}, {1, 1}
};

int is_valid_cell(int row_count, int column_count, int line, int col) {
	return (line >= 0) && (line < row_count) && (col >= 0) && (col < column_count);
}

void number_adjacent_mines(char field[MAX_NUMBER][MAX_NUMBER], int row_count, int column_count, int line, int col) {
	int number = 0;

	if (field[line][col] == '*') {
		printf("*");
		return;
	}

	for (int counter = 0; counter < 8; counter++) {
		int new_line = line + directions[counter][0];
		int new_col = col + directions[counter][1];

		if (is_valid_cell(row_count, column_count, new_line, new_col)) {
			if (field[new_line][new_col] == '*') {
				number++;
			}
		}
	}

	printf("%d", number);
}

void line_adjacent_mines(char field[MAX_NUMBER][MAX_NUMBER], int row_count, int column_count, int line) {
	for (int col = 0; col < column_count; col++) {
		number_adjacent_mines(field, row_count, column_count, line, col);
	}
	printf("\n");
}

void grid_adjacent_mines(char field[MAX_NUMBER][MAX_NUMBER], int row_count, int column_count) {
	for (int line = 0; line < row_count; line++) {
		line_adjacent_mines(field, row_count, column_count, line);
	}
}

int main(void) {
	char field[MAX_NUMBER][MAX_NUMBER];
	int row_count, column_count;
	int field_num = 1;
	char c;

	while (1) {
		if (scanf("%d %d", &row_count, &column_count) != 2) {
			return -1;
		}

		if (row_count == 0 && column_count == 0) {
			break;
		}

		while ((c = getchar()) != '\n' && c != EOF);

		for (int row = 0; row < row_count; row++) {
			for (int column = 0; column < column_count; column++) {
				if (scanf(" %c", &field[row][column]) != 1) {
					break;
				}
			}

			while ((c = getchar()) != '\n' && c != EOF);
		}

		printf("\n");
		printf("Field #%d:\n", field_num++);
		grid_adjacent_mines(field, row_count, column_count);
	}

	return 0;
}