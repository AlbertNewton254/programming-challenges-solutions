/**
 * Minesweeper
 * pc110102
 * uva10189
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MAX_SIZE = 100;

const int dirs[8][2] = {
	{-1, -1}, {-1, 0}, {-1, 1},
	{0, -1}, {0, 1},
	{1, -1}, {1, 0}, {1, 1}
};

class MineSweeper {
private:
	vector<vector<char>> field;
	int rows, cols;

	bool isValidCell(int x, int y) const {
		return x >= 0 && x < rows && y >= 0 && y < cols;
	}

	int countAdjacentMines(int x, int y) const {
		if (field[x][y] == '*') return -1;

		int count = 0;
		for (auto [dx, dy] : dirs) {
			int newX = x + dx;
			int newY = y + dy;
			if (isValidCell(newX, newY) && field[newX][newY] == '*') {
				count++;
			}
		}
		return count;
	}

public:
	MineSweeper(int n, int m) : rows(n), cols(m) {
		field.resize(n, vector<char>(m));
	}

	void readField() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				cin >> field[i][j];
			}
		}
	}

	void printSolution(int fieldNum) {
		cout << "Field #" << fieldNum << ":\n";
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				int count = countAdjacentMines(i, j);
				cout << (count == -1 ? '*' : char('0' + count));
			}
			cout << '\n';
		}
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	int fieldNum = 1;
	bool firstField = true;

	while (cin >> n >> m && n && m) {
		if (!firstField) cout << '\n';
		firstField = false;

		MineSweeper game(n, m);
		game.readField();
		game.printSolution(fieldNum++);
	}

	return 0;
}