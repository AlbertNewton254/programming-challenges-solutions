/**
 * Shuffle
 * pc110205
 * uva10026
 */

import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int T = scanner.nextInt();
        boolean isFirst = true;

        while (T-- > 0) {
            if (!isFirst) {
                System.out.println();
            }
            isFirst = false;

            int n = scanner.nextInt();

            int[][] shuffles = new int[n][52];
            for (int k = 0; k < n; k++) {
                for (int i = 0; i < 52; i++) {
                    shuffles[k][i] = scanner.nextInt();
                }
            }

            Shuffle shuffler = new Shuffle(shuffles);
            shuffler.process(scanner);
        }

        scanner.close();
    }
}
