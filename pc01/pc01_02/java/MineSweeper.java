/**
 * Minesweeper
 * pc110102
 * uva10189
 */

import java.util.Scanner;

public class MineSweeper {
    private char[][] field;
    private final int rows;
    private final int cols;

    private static final int[][] DIRECTIONS = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1}, {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    public MineSweeper(int n, int m) {
        this.rows = n;
        this.cols = m;
        this.field = new char[n][m];
    }

    public void readField(Scanner scanner) {
        for (int i = 0; i < rows; i++) {
            String line = scanner.next();
            for (int j = 0; j < cols; j++) {
                field[i][j] = line.charAt(j);
            }
        }
    }

    private boolean isValidCell(int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols;
    }

    private int countAdjacentMines(int x, int y) {
        if (field[x][y] == '*') return -1;

        int count = 0;
        for (int[] dir : DIRECTIONS) {
            int newX = x + dir[0];
            int newY = y + dir[1];

            if (isValidCell(newX, newY) && field[newX][newY] == '*') {
                count++;
            }
        }
        return count;
    }

    public void printSolution(int fieldNum) {
        System.out.println("Field #" + fieldNum + ":");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int count = countAdjacentMines(i, j);
                System.out.print(count == -1 ? '*' : count);
            }
            System.out.println();
        }
    }
}