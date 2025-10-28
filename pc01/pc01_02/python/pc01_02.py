"""
minesweeper
pc110102
uva10189
"""

import sys

class MineSweeper:
    DIRECTIONS = [
        (-1, -1), (-1, 0), (-1, 1),
        (0, -1), (0, 1),
        (1, -1), (1, 0), (1, 1)
    ]

    def __init__(self, rows, cols):
        self.rows = rows
        self.cols = cols
        self.field = []

    def read_field(self):
        self.field = [list(input().strip()) for _ in range(self.rows)]

    def is_valid_cell(self, x, y):
        return 0 <= x < self.rows and 0 <= y < self.cols

    def count_adjacent_mines(self, x, y):
        if self.field[x][y] == '*':
            return -1

        count = 0
        for dx, dy in self.DIRECTIONS:
            new_x, new_y = x + dx, y + dy
            if self.is_valid_cell(new_x, new_y) and self.field[new_x][new_y] == '*':
                count += 1
        return count

    def print_solution(self, field_num):
        print(f"Field #{field_num}:")
        for i in range(self.rows):
            for j in range(self.cols):
                count = self.count_adjacent_mines(i, j)
                print('*' if count == -1 else count, end='')
            print()

def main():
    field_num = 1
    first_field = True

    while True:
        try:
            n, m = map(int, input().strip().split())
            if n == m == 0:
                break

            if not first_field:
                print()
            first_field = False

            game = MineSweeper(n, m)
            game.read_field()
            game.print_solution(field_num)
            field_num += 1

        except EOFError:
            break

if __name__ == '__main__':
    main()