/* minesweeper
 * pc110102
 * uva10189 */

#include <stdio.h>

const int MAX_NUMBER = 100;

int directions[8][2] = {
	{-1, -1}, {-1, 0}, {-1, 1},
	{0, -1}, {0, 1},
	{1, -1}, {1, 0}, {1, 1}
};

int is_valid_dimension(int n, int m) {
	return (n > 0) && (n <= MAX_NUMBER) && (m > 0) && (m <= MAX_NUMBER);
}

int is_valid_cell(int n, int m, int line, int col) {
	return (line >= 0) && (line < n) && (col >= 0) && (col < m);
}

void number_adjacent_mines(char field[MAX_NUMBER][MAX_NUMBER], int n, int m, int line, int col) {
	int number = 0;

	if (field[line][col] == '*') {
		printf("*");
		return;
	}

	for (int counter = 0; counter < 8; counter++) {
		int new_line = line + directions[counter][0];
		int new_col = col + directions[counter][1];

		if (is_valid_cell(n, m, new_line, new_col)) {
			if (field[new_line][new_col] == '*') {
				number++;
			}
		}
	}

	printf("%d", number);
}

void line_adjacent_mines(char field[MAX_NUMBER][MAX_NUMBER], int n, int m, int line) {
	for (int col = 0; col < m; col++) {
		number_adjacent_mines(field, n, m, line, col);
		if (col < m - 1) {
			printf(" ");
		}
	}
	printf("\n");
}

void grid_adjacent_mines(char field[MAX_NUMBER][MAX_NUMBER], int n, int m) {
	for (int line = 0; line < n; line++) {
		line_adjacent_mines(field, n, m, line);
	}
}

int main(void) {
	char field[MAX_NUMBER][MAX_NUMBER];
	int n, m;
	int field_num = 1;
	char c;

	while (1) {
		if (scanf("%d %d", &n, &m) != 2) {
			return -1;
		}

		if (n == 0 && m == 0) {
			break;
		}

		if (!is_valid_dimension(n, m)) {
			return -1;
		}

		while ((c = getchar()) != '\n' && c != EOF);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (scanf(" %c", &field[i][j]) != 1) {
					break;
				}
			}

			while ((c = getchar()) != '\n' && c != EOF);
		}

		if (field_num > 1) {
			printf("\n");
		}
		printf("Field #%d:\n", field_num++);
		grid_adjacent_mines(field, n, m);
	}

	return 0;
}
