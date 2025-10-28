/**
 * The 3 * n + 1 problem
 * pc110101
 * uva100
 */

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        long startTime = System.nanoTime();

        CycleFinder cycleFinder = new CycleFinder();
        Scanner scanner = new Scanner(System.in);

        while (scanner.hasNextInt()) {
            int number1 = scanner.nextInt();
            int number2 = scanner.nextInt();

            try {
                System.out.printf("%d %d %d%n",
                    number1, number2, cycleFinder.maxCycleLength(number1, number2));
            } catch (IllegalArgumentException e) {
                continue;
            }
        }

        scanner.close();

        long endTime = System.nanoTime();
        double seconds = (endTime - startTime) / 1e9;
        System.err.printf("Time of execution: %.6f seconds%n", seconds);
    }
}