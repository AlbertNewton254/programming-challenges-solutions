/**
 * Minesweeper
 * pc110102
 * uva10189
 */

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int fieldNum = 1;
        boolean firstField = true;

        while (true) {
            int n = scanner.nextInt();
            int m = scanner.nextInt();

            if (n == 0 && m == 0) break;

            if (!firstField) System.out.println();
            firstField = false;

            MineSweeper game = new MineSweeper(n, m);
            game.readField(scanner);
            game.printSolution(fieldNum++);
        }

        scanner.close();
    }
}